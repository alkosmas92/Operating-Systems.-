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
#include "types.h"
#include <time.h>
#include <sys/times.h>  /* times() */
#include <unistd.h>     /* sysconf() */

#define FIFO_NAME0 "myfifo_"


volatile sig_atomic_t fl_s =0;

void handle_sigusr1(int sigmy_num) {
	fl_s++;
}
volatile sig_atomic_t break_s = 0;

void handle_break1(int sigmy_num) {
	break_s ++;
}

int main(int argc , char * argv[]) {

	int status,fd1,fd2,fd3,rc;
	char str[20];
	int lim=atoi(argv[3]);
	pid_t pid;
	prime *list_prime=constructor_prime();
	my_num temp_prime;
	struct pollfd fdarray [1];
	int num_e;
	char final_file[lim][15];
	char start_1[lim][10];
	char end_1[lim][10];
	int end_sig = atoi(argv[2]) ;
	int start_sig = atoi(argv[1]) ;
	int distance = (end_sig - start_sig) / lim;
	char choice[2];
	int test=atoi(argv[4]);
	double my_time[lim];


	signal(SIGUSR1, handle_sigusr1);
	signal(SIGUSR2, handle_break1);

	for (num_e=0;num_e<lim; num_e++){

				strcpy(final_file[num_e],FIFO_NAME0);					//grapse to standar name
				sprintf(choice, "%d", test);
				strncat(final_file[num_e], choice, 2);			//prosthese to num of child gia na einai monadiko
				sprintf(choice, "%d", num_e % lim);							//perna to number ws char
				strncat(final_file[num_e], choice, 2);			//prosthese to num of child gia na einai monadiko

			if (mkfifo(final_file[num_e], 0666) < 0)
					perror("mkfifo2_2");

			if(num_e==0){
						sprintf(start_1[num_e], "%d", start_sig + ((num_e*distance)) );
						sprintf(end_1[num_e], "%d", start_sig + ((num_e+1)*distance) );
				}

			else{
					sprintf(start_1[num_e], "%d", start_sig + ((num_e*distance)+1) );    		// prosarmozw me vasi to number of child to epomeno start
							if(num_e!=lim-1){																											//stin periptwsi pou den einai to teliko chlid
									sprintf(end_1[num_e], "%d", start_sig + ((num_e+1)*distance) );
							}
							else{																																//otan einai to teliko child wste na min exw olo to euros ton arithmwn
									sprintf(end_1[num_e], "%d",end_sig );
							}
				}
			}

	 	for (num_e=0;num_e<lim; num_e++)								//dimourgise tosa paidia osa to lim me ena patera
			if ( (pid = fork()) <= 0 )
				 break;

/*-----------------------------------Child--------------------------------------------------------*/


			 if(pid==0){
				 sprintf(choice, "%d", num_e % lim);							//perna to number ws char
					if((execl("./prime1_1","prime1_1",start_1[num_e] , end_1[num_e] , choice , final_file[num_e],NULL)) == -1){
														perror("exec");
								}
			 }


/*-----------------------------------Parent--------------------------------------------------------*/
			else{
					for (num_e=0;num_e<lim; num_e++){
						fd1 = open(final_file[num_e], O_RDONLY);
									for (;;){
													fdarray [0].fd = fd1 ;
													fdarray [0].events = POLLIN ;
													rc = poll ( fdarray , 1 , 0);

												 if ( ( rc == 1) && ( fdarray [0].revents & POLLIN ) ){
																if ( fdarray [0]. fd == fd1 ){
																		 read (fd1 , &temp_prime , sizeof(my_num) );
																		 insert_primee(list_prime,temp_prime);
																			fflush ( stdout );
															}
													}
													else if ( ( rc == 1) && ( fdarray [0].revents & POLLHUP ) ){
														break;
													}
										}
							close(fd1);
							unlink(final_file[num_e]);
						 my_time[num_e]=find_time(list_prime);

						kill(getppid(), SIGUSR2);
					}

				kill(getppid(), SIGUSR1);
						int fdd1;
						int l=0;
						char file[15];
						strcpy(file,argv[5]);
						bubbleSort( list_prime);
						int size = find_count(list_prime) ;
							my_num array[size+lim];
										fdd1 = open(file, O_WRONLY);
										while(list_prime->next!=NULL){
											array[l].prime = list_prime->primer;
											array[l].time = list_prime->prime_timer;
											write(fdd1, &array[l],sizeof(my_num));
											l++;
											list_prime=list_prime->next;
										}
											array[l].prime = -1; 				//to xrisimopoiw gia elanxo meta stin poll
											array[l].time =  min_time(&my_time,lim);		//pernaw to min time
											array[l].position =  min_time_pos(&my_time,lim);
											write(fdd1, &array[l],sizeof(my_num));
											l++;
											array[l].prime = -2;			//to xrisimopoiw gia elanxo meta stin riza
											array[l].time =  max_time(&my_time,lim);			//pernaw to max time
											array[l].position = max_time_pos(&my_time,lim);
											write(fdd1, &array[l],sizeof(my_num));
						 close(fdd1);
				 	}

			}
