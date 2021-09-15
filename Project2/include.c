#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "types.h"


#define YES 1
#define NO  0
//

	void free_list( prime* head)
	{
	   struct prime* temp;

	   while (head != NULL)
	    {
	       temp = head;
	       head = head->next;
	       free(temp);
	    }

	}

	void insert_prime(prime *head,my_num my_rec){
			prime * temp=constructor_prime();
			prime * help=constructor_prime();
			prime * temp_help=constructor_prime();
			temp=head;
			int flag1=0,flag2=0;
				while(temp->next !=NULL){
							 temp=temp->next;
				}

					temp->primer=my_rec.prime;
					temp->prime_timer=my_rec.time;
					temp->next=constructor_prime();
			}



//sig2
				double max_time(double* my_time , int lim){
					double want=my_time[0];
					for(int k=0 ; k<lim ; k++){
						if(my_time[k]>want){
							want=my_time[k];
						}
					}
					return want;
				}
				int max_time_pos(double* my_time , int lim){
					double want=my_time[0];
					int position=0;
					for(int k=0 ; k<lim ; k++){
						if(my_time[k]>want){
							want=my_time[k];
							position =k;
						}
					}
					return position ;
				}
				double min_time(double* my_time , int lim){
					double want=my_time[0];
					int position=0;
					for(int k=0 ; k<lim ; k++){
						if(my_time[k]<want){
							want=my_time[k];
						}
					}
							return want;
				}

				int min_time_pos(double* my_time , int lim){
					double want=my_time[0];
					int position=0;
					for(int k=0 ; k<lim ; k++){
						if(my_time[k]<want){
							want=my_time[k];
							position=k;
						}
					}
						return position;
				}

				double find_time(prime* temp){

					double want=temp->prime_timer;
					while(temp->next !=NULL){
							if(temp->prime_timer > want){
								 want=temp->prime_timer;
							}
								temp=temp->next;
				 }
				 return want;

				}

			void insert_primee(prime *head,my_num my_rec){
			    prime * temp=constructor_prime();
			    prime * help=constructor_prime();
			    prime * temp_help=constructor_prime();
			 		temp=head;
					int count;
			      while(temp->next !=NULL){
									count=temp->counter;
								   temp=temp->next;
			      }
							count++;
						temp->counter=count;
						//printf("counter is %d\n",temp->counter );
			        temp->primer=my_rec.prime;
			        temp->prime_timer=my_rec.time;

			        temp->next=constructor_prime();
					}


			  void print_prime(prime *head){
					prime * my_el=constructor_prime();
			      while(head->next !=NULL){
			        printf("prime is %d\n", head->primer);
			        printf("time is %lf\n", head->prime_timer);
							my_el=head;
			        head=head->next;
			      }
					}


			  int find_count(prime *head){
					prime * my_el=constructor_prime();
			      while(head->next !=NULL){
							my_el=head;
			        head=head->next;
			      }
						return my_el->counter;
					}
						//printf("counter is %d\n", my_el->prime_timer);


						void bubbleSort( prime *head)
						{
						    int swapped, i;
						     prime *temp;
						     prime *help = NULL;

						    /* Checking for empty list */
						    if (head == NULL)
						        return;

						    do
						    {
						        swapped = 0;
						        temp = head;
										//printf("temp_prime %d next is %d \n",temp->primer , temp->next->primer );

						        while (temp->next != NULL)
						        {

						            if (temp->primer > temp->next->primer && temp->next->primer)
						            {
						                swap(temp, temp->next);
						                swapped = 1;
						            }
						            temp = temp->next;
						        }

						        help = temp;

						    }
						    while (swapped);
						}



			  prime * constructor_prime(){
			          prime *temp_prime=(prime*)malloc(sizeof(prime));
								temp_prime->counter=0;
			          temp_prime->next=NULL;
			          return temp_prime;
			  }

				void swap( prime *temp,  prime *my_rec)
					{
					    int primer = temp->primer;
					    int timer = temp->prime_timer;
							temp->primer = my_rec->primer;
							temp->prime_timer = my_rec->prime_timer;
					    my_rec->primer = primer;
					    my_rec->prime_timer = timer;
					}

  int prime_2(int n){
          int i=0, limitup=0;
          limitup = (int)(sqrt((float)n));

          if (n==1) return(NO);
          for (i=2 ; i <= limitup ; i++)
                  if ( n % i == 0) return(NO);
          return(YES);
  }



  int fuction_prime(int n){
          int i;
          if (n==1) return(NO);
          for (i=2 ; i<n ; i++)
                  if ( n % i == 0) return(NO);
          return(YES);
  }



  unsigned  long  ipolipo(unsigned long d,int a,unsigned long int i)
  {
         unsigned long int b;
         unsigned  long result;

  	b=a;
  	result=1;

  	while(d>=1)
  	{
  		if (d%2==0)		//είναι άρτιος κανε
  		{
  		    b=(b*b)%i;		// βαση*βαση mod i
  	            d=d/2;
  		}
  		else				// ειναι περιττος
  		{
  		result=(result*b)%i;  // πολλαπλασιασε την βαση απο τους αρτιους με το ειδη result και βγαλε mod i
  		b=(b*b)%i;		 //βαση *βαση mod i
  		d=d/2;
  		}
  	}
  	return result;
  }
