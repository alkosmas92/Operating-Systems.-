#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <poll.h>

#include <sys/times.h>  /* times() */
#include <unistd.h>     /* sysconf() */

#define FIFO_NAME "myfifo_"
#define FIFO_TIME "fifotime_"


volatile sig_atomic_t fl_s = 0;

void handle_sigusr1(int sigmy_num) {
	fl_s ++;
}
volatile sig_atomic_t break_s = 0;

void handle_break1(int sigmy_num) {
	break_s ++;
}


int main(int argc , char * argv[]) {
	int status,fd1,fd2,fd3,rc;
	int lim , end_sig , start_sig;

	int k=0;
	 while(k<argc){					// vres tis simaies kai pare ta data pou xriazesai
		 if(!strcmp("-l",argv[k]))
				 start_sig=atoi(argv[k+1]);
		else if(!strcmp("-u",argv[k]))
			 end_sig = atoi(argv[k+1]) ;
		else if(!strcmp("-w",argv[k]))
			 lim = atoi(argv[k+1]) ;
		 k++;
	 }
	 printf("lim %d end %d start %d\n",lim ,end_sig ,start_sig );

	pid_t pid;
	prime *list_prime=constructor_prime();
	my_num temp_prime;
	struct pollfd fdarray [1];
	int num_e;
	char final_file[lim][15]; 										//pinakas me ta name pipe wtse na suniparxoun me to child number
	char start_1[lim][10];
	char end_1[lim][10];
	int distance = (end_sig - start_sig) / lim;
	char num_child[2];
	char choice[2];
	char time_node[lim][15];


	signal(SIGUSR1, handle_sigusr1);
	signal(SIGUSR2, handle_break1);

	for (num_e=0;num_e<lim; num_e++){
				strcpy(final_file[num_e],FIFO_NAME);					//grapse to standar name
				sprintf(choice, "%d", num_e % lim);							//perna to number ws char
				strncat(final_file[num_e], choice, 2);			//prosthese to num of child gia na einai monadiko
			if (mkfifo(final_file[num_e], 0666) < 0)  		//dimiourgise ta filefifo
					perror("mkfifo2_2");

			if(num_e==0){																			//se periprwsi pou einai to arxiko diastima
					sprintf(start_1[num_e], "%d", start_sig + ((num_e*distance)) );
					sprintf(end_1[num_e], "%d", start_sig + ((num_e+1)*distance) );
			}

			else{
			sprintf(start_1[num_e], "%d", start_sig + ((num_e*distance)+1) );    		// prosarmozw me vasi to number of child to epomeno start
					if(num_e!=lim-1){																											//stin periptwsi pou den einai to teliko chlid
							sprintf(end_1[num_e], "%d", start_sig + ((num_e+1)*distance) );
					}
					else{																																//otan einai to teliko child wste na exw olo to euros ton arithmwn
							sprintf(end_1[num_e], "%d",end_sig );
					}
			}
		}

 	for (num_e=0;num_e<lim; num_e++)					//dimourgise tosa paidia osa to lim me ena patera
		if ( (pid = fork()) <= 0 )
			 break;

/*-----------------------------------Child--------------------------------------------------------*/

		 if(pid==0){
			  sprintf(num_child, "%d", lim);							//perna to num of children  ws char
				sprintf(choice, "%d", num_e);							//perna to num_e ws char
				if((execl("./sig2","sig2",start_1[num_e] , end_1[num_e] , num_child , choice , final_file[num_e] ,time_node[num_e],  NULL)) == -1){
													perror("exec");
							}
		 }

/*-----------------------------------Parent--------------------------------------------------------*/
		else{
			num_time my_time[lim];
			for (num_e=0;num_e<lim; num_e++){
				fd1 = open(final_file[num_e], O_RDONLY);
							for (;;){
								/* initialize poll parameters*/
											fdarray [0].fd = fd1 ;
											fdarray [0].events = POLLIN ;
											/* wait for incomign data or poll timeout*/
											rc = poll ( fdarray , 1 , 0);
											 if ( ( rc == 1) && ( fdarray [0].revents & POLLIN ) ){
														if ( fdarray [0]. fd == fd1 ){
																 read (fd1 , &temp_prime , sizeof(my_num) );
																 if(temp_prime.prime>0){						//otan einai thetiko to prime pernw ta prime kai ton xrono tous
																 				insert_prime(list_prime,temp_prime);
														 			}
																 if(temp_prime.prime==-1){					//otan einai -1 to prime pernw min kai tin fuction pou xrisimopoei
																	 my_time[num_e].time_min=temp_prime.time;
																	 my_time[num_e].position_min =temp_prime.position;
																}
																 if(temp_prime.prime==-2){				//otan einai -2 to prime pernw to max time kai tin tin fuction pou xrisimopoiei
																	 my_time[num_e].time_max=temp_prime.time;
																	my_time[num_e].position_max =temp_prime.position;
																}
														fflush ( stdout );
													}
											}
											else if ( ( rc == 1) && ( fdarray [0].revents & POLLHUP ) ){	 // an den exeis kati allo na diavaseis vges apo tin loupa
												break;
											}
								}
							close(fd1);
					unlink(final_file[num_e]);
				}
				bubbleSort( list_prime);			//taksinomisi me vasi tous prime
				print_prime(list_prime); 			//ektipwse tous prime kai tous xronous tou


			for (num_e=0;num_e<lim; num_e++){
				printf("for node %d the min time for prime is %lf from %dst fuction and max  time for prime is %lf from %dst fuction\n",
				num_e ,my_time[num_e].time_min,my_time[num_e].position_min+1,my_time[num_e].time_max,my_time[num_e].position_max+1);
			}
	 		printf("sum of signal is %d\n",fl_s + break_s );
		}
			free_list(list_prime);
	}
