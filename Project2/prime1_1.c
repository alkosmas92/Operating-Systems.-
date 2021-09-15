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
#include <math.h>
#include <sys/times.h>  /* times() */
#include <unistd.h>     /* sysconf() */
#include <time.h>



#define YES 1
#define NO  0

volatile sig_atomic_t fl_s = 0;
void handle_sigusr1(int sigmy_num) {
	fl_s++;
	printf("/\\/\\ Child1 Process %d: Received USR1\n", getpid());
}

volatile sig_atomic_t break_s = 0;
void handle_break1(int sigmy_num) {
	break_s++;
	printf("/\\/\\ Child1 Process %d: Received USR2\n", getpid());
}


/* Executable: mysig */
int main(int argc , char * argv[]){
	int test,start=0, end=0 , counter=0,fd1;
	test=atoi(argv[3])%3;
	my_num temp_prime;
	start=atoi(argv[1]);
	end=atoi(argv[2]);

	char final_file[15];
	strcpy(final_file,argv[4]);

double t1, t2,t5, cpu_time;
struct tms tb1, tb2;
double ticspersec;
int i_time, sum = 0;

if ((fd1 = open(final_file, O_WRONLY)) < 0)
perror("child - open");

signal(SIGUSR1, handle_sigusr1);
signal(SIGUSR2, handle_break1);

	  if(test==0){
							 int i=0;
							 int k;
							 int sir=end-start;
							 ticspersec = (double) sysconf(_SC_CLK_TCK);
							 t1 = (double) times(&tb1);
								    for (i=start ; i <= end ; i++ , start++){
								          if ( fuction_prime(i)==YES ){

														t2 = (double) times(&tb2);
														cpu_time = (double) ((tb2.tms_utime + tb2.tms_stime) -
																								 (tb1.tms_utime + tb1.tms_stime));

														temp_prime.prime=i;
														temp_prime.time=(t2 - t1) / ticspersec;
															write(fd1, &temp_prime,sizeof(my_num));
						             }
						        }
								}

		else if(test==1){
					int i=0;
					int k;
					int sir=end-start;
					ticspersec = (double) sysconf(_SC_CLK_TCK);
					t1 = (double) times(&tb1);
							 for (i=start ; i <= end ; i++ , start++){
										 if ( prime_2(i)==YES ){
											 t2 = (double) times(&tb2);
											 temp_prime.prime=i;
											 temp_prime.time=(t2 - t1) / ticspersec;
											 write(fd1, &temp_prime,sizeof(my_num));
										 }
							 }
					}

		else if(test==2){
				        int i=0;
								int  r,k,z,plithos=0,a=0, a1=2,a2=7,a3=61,flag=0;
								long unsigned  num, d=0, x=0, lu=0 ;

						ticspersec = (double) sysconf(_SC_CLK_TCK);
						t1 = (double) times(&tb1);
						t5 = (double) times(&tb1);
						if(start%2!=0){
							start=start-1;
						}
						ticspersec = (double) sysconf(_SC_CLK_TCK);
						t1 = (double) times(&tb1);
						for( num = (start +1) ; num <= end ; num+=2 ) //επαναληψη για το κρισιμο διαστημα στους περιττους
												{			//υπολογισμος num-1=(2^r)*d
													r=0;
													d = num-1;
													while (d % 2 == 0) 	// επαναληψη μεχρι ο d να γινει περριτος
													{
														r++; 	// κρατα το πληθος που χρειαζεται για να ισουται ο d με num-1
														d = d/2;
													}
													k=r;
													a=a1;
													x=ipolipo(d,a,num);
													if (x==1 || x==num-1 )				// ελενχω την πρώτη συνθήκη ισότητας για α=2
													{
														a2;

														x=ipolipo(d,a,num);

														if (x==1 || x==num-1)				// ελενχω την πρώτη συνθήκη ισότητας για α=7
														{
															a=a3;
															x=ipolipo(d,a,num);

																if (x==1 || x==num-1)				// αν η 1η συνθήκη ισότητας για α=61 ισχύει
																{
											            flag=1;
																	plithos++;					// ειναι πρωτος, αυξησε το πληθος των πρώτων
																}
																else if(x != 1 && x != num -1)		// αν δεν ισχυει η 1η συνθηκη  για α=61 κανε
																{			k=r;
																			for(k ; k-1 >= 0 ; k--) 	//επανάληψη
																			{
																					lu= ((long)x)*((long)x);
																					lu=lu % num;
																					x= lu;			//χ*χ mod num
																					if(x==num-1)		// αν ισχύει η 2η συνθήκη για α=61 τοτε
																					{
											                      flag=1;
																						plithos++;	// ειναι πρωτος, αυξησε το πληθος των πρώτων
																						break;
																					}
																					else if(k-1==0)
																					{
																						break;
																					}
																			}
																}

														}
														else if(x!=1 && x != num -1 )		// αν δεν ισχυει η 1η συνθηκη  για α=7 κανε
														{			k=r;
														for(k ; k-1 >= 0 ; k--) 			//επανάληψη
														{
																lu= (( long)x)*((long)x);
																lu=lu % num;
																x= lu;				//χ*χ mod num
																if(x==num-1)  			// ελένχω με 2η συνθήκη για α=7
																{
																		a=a3;
																		x=ipolipo(d,a,num);

																			if (x==num-1 || x==1)		// αν η 1η συνθήκη ισότητας για α=61 ισχύει τότε
																			{
											                  flag=1;
											                  plithos++;	// ειναι πρωτος, αυξησε το πληθος των πρώτων
																				break;
																			}
																			else if(x != 1 && x != num -1)		// αν δεν ισχυει η 1η συνθηκη  για α=61 κανε
																				{
																				for(r ; r-1 >= 0 ; r--) 			//επαναληψη
																				{
																						lu= ((long)x)*((long)x);
																						lu=lu % num;
																						x= lu;			//χ*χ mod num
																						if(x==num-1)		// αν ισχύει η 2η συνθήκη για α=61 τοτε
																						{
											                        flag=1;
											                        plithos++;	// ειναι πρωτος, αυξησε το πληθος των πρώτων
																							break;
																						}
																				}
																				}
																}
																else if(k-1==0)
																{
																	break;
																}
															}
														}
													}
													else if(x != 1 && x != num -1 )	// αν δεν ισχυει η 1η συνθηκη  για α=2 κανε
													{
														k=r;
													for(k ; k-1 >= 0 ; k--) 			//επανάληψη
													{
															lu= ((long)x)*((long)x);
															lu=lu % num;
															x= lu;						//χ*χ mod num
															if(x==num-1 )					//ελενχω την 2η συνθήκη για α=2
															{
																a=a2;
																x=ipolipo(d,a,num);
																if (x==1 || x==num-1)				// ελενχω την 1η συνθήκη ισότητας για α=7
																{
																		a=a3;
																		x=ipolipo(d,a,num);

																			if (x==1 || x==num-1)		//ελένχω με 1η συνθηκη για α=61
																			{
											                  flag=1;
											                  plithos++;			// ειναι πρωτος, αυξησε το πληθος των πρώτων
																				break;
																			}
																			else if(x != 1 && x != num -1)			// αν δεν ισχυει η 1η συνθηκη  για α=61 κανε
																						{
																						for(r ; r-1 >= 0 ; r--) 		//επανάληψη
																						{		k=r;
																								lu= (( long)x)*((long)x);
																								lu=lu % num;
																								x= lu;			//χ*χ mod num
																								if(x==num-1)		// αν ισχύει η 2η συνθήκη για α=61 τοτε
																								{
											                            flag=1;
											                            plithos++;	// ειναι πρωτος, αυξησε το πληθος των πρώτων
																									break;
																								}

																						}
																						}

																}
																else if(x!=1 && x != num -1 )		// αν δεν ισχυει η 1η συνθηκη  για α=7 κανε
																{			z=r;
																for(z ; z-1 >= 0 ; z--) 			//επανάληψη
																{
																	lu= ((long)x)*((long)x);
																	lu=lu % num;
																	x= lu;					//χ*χ mod num

																		if(x==num-1 ) 			 // αν ισχυει η 2η συνθηκη  για α=7 κανε
																		{
																			a=a3;
																			x=ipolipo(d,a,num);
																				if (x==1 || x==num-1)		// αν ισχυει η 1η συνθηκη  για α=61 τοτε
																				{
											                    flag=1;
											                    plithos++;			// ειναι πρωτος, αυξησε το πληθος των πρώτων
																					break;
																				}
																				else if(x != 1 && x != num -1)	// αν δεν ισχυει η 1η συνθηκη  για α=61 κανε
																				{
																				for(r ; r-1 >= 0 ; r--)
																				{
																						lu= ((long)x)*((long)x);
																						lu=lu % num;
																						x= lu;				//χ*χ mod num
																						if(x==num-1)			// αν ισχύει η 2η συνθήκη για α=61 τοτε
																						{
											                        flag=1;
											                        plithos++;		// ειναι πρωτος, αυξησε το πληθος των πρώτων
																							break;
																						}
																						else if(k-1==0)
																						{
																							break;
																						}

																				}
																			     }
																		}
																		else if(k-1==0)
																		{
																			break;
																		}

																}
																}
															}
														else if(k-1==0)
															{
																break;
															}

													}
													}
					    if(flag==1){

								t2 = (double) times(&tb2);
								cpu_time = (double) ((tb2.tms_utime + tb2.tms_stime) -
																		 (tb1.tms_utime + tb1.tms_stime));

								temp_prime.prime=num;
								temp_prime.time=(t2 - t1) / ticspersec;
								//printf("prime is %d\n",temp_prime.prime );

									//printf("prime is %d\n",temp_prime.prime );
								write(fd1, &temp_prime,sizeof(my_num));

								 flag=0;
					    }
						}
					}
					close(fd1);
			}
