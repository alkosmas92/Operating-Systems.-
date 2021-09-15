#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>  /* times() */
#include <string.h>


#define SEGMENTSIZE sizeof(sem_t)
#define SEGMENTPERM 0666
#define TEN_MILLION 10000000L

int main(int argc, char **argv)
{


	int numOfSlds,mantime;

	int k=0;
	 while(k<argc){					// vres tis simaies kai pare ta data pou xriazesai
		 if(!strcmp("-n",argv[k]))
					numOfSlds = atoi(argv[k+1]);
		else if(!strcmp("-m",argv[k]))
					 mantime = atoi(argv[k+1]) ;
		 k++;
	 }

	typedef struct {
			int products;
			int waiting1;
			int waiting2;
			int waiting3;

	    int num_of_salad;
			double start;
	    sem_t saladmaker2;
	    sem_t saladmaker3;
	    sem_t saladmaker1;
	    sem_t chef1;
	    sem_t chef2;
	    sem_t chef3;
	    sem_t mutex1;
	    sem_t mutex2;
	    sem_t mutex3;

	}Staff_struct;


	int retval,retval2;
	int id, err;
	int whatisthevalue=0;

	time_t rawtime = time(NULL);

	double  t2, cpu_time;
	struct tms tb1, tb2;
	double ticspersec;
	int    i, sum = 0;

	ticspersec = (double) sysconf(_SC_CLK_TCK);


	struct tm *ptm = localtime(&rawtime);

	struct timespec sleeptime;
	sleeptime.tv_sec = 0;
	sleeptime.tv_nsec = mantime;

	FILE *f1;
	f1 = fopen("chef.log", "w"); // a+ (create + append) option will allow appending which is useful in a log file


	/* Make shared memory segment. */
 id = shmget(IPC_PRIVATE, sizeof(Staff_struct) ,0666);
	if (id == -1) perror("Creation");
	else printf("Allocated %d\n", id);

	/* Attach the segment. */
  void * shared_memory = (void *) shmat(id,(void*) 0, 0);

	Staff_struct* pointer_staff = shared_memory;

	pointer_staff->start = (double) times(&tb1);

	pointer_staff->num_of_salad=numOfSlds;
	pointer_staff->waiting1=0;
	pointer_staff->waiting2=0;
	pointer_staff->waiting3=0;
	pointer_staff->products=5;


	retval = sem_init(&pointer_staff->chef3 , 1, 0 );
	if (retval != 0) {
			perror("Couldn't initialize.");
			exit(3);
	}

	retval = sem_init(&pointer_staff->mutex1 , 1, 1 );
	if (retval != 0) {
			perror("Couldn't initialize.");
			exit(3);
	}
	retval = sem_init(&pointer_staff->mutex2 , 1, 1 );
	if (retval != 0) {
			perror("Couldn't initialize.");
			exit(3);
	}
	retval = sem_init(&pointer_staff->mutex3 , 1, 1 );
	if (retval != 0) {
			perror("Couldn't initialize.");
			exit(3);
	}
	retval = sem_init(&pointer_staff->saladmaker2 , 1, 0 );
	if (retval != 0) {
			perror("Couldn't initialize.");
			exit(3);
	}
	retval = sem_init(&pointer_staff->saladmaker3 , 1, 0 );
	if (retval != 0) {
			perror("Couldn't initialize.");
			exit(3);
	}
	retval = sem_init(&pointer_staff->saladmaker1 , 1, 0 );
	if (retval != 0) {
			perror("Couldn't initialize.");
			exit(3);
	}
	retval = sem_init(&pointer_staff->chef1 , 1, 0 );
	if (retval != 0) {
			perror("Couldn't initialize.");
			exit(3);
	}
	retval = sem_init(&pointer_staff->chef2 , 1, 0 );
	if (retval != 0) {
			perror("Couldn't initialize.");
			exit(3);
	}

	getchar();

int test_product=pointer_staff->products;

int count1=0; //gia metrisi salatwnn
int count2=0;
int count3=0;


while(pointer_staff->num_of_salad>0  ){ // epanalave oso num_of_salad den einai miden

	test_product=pointer_staff->products;
	pointer_staff->products=rand()%3;  //dwse ena tuxaio sundiasmo prointwn
		while(test_product==pointer_staff->products){ // mexri na min einai idia me tin proigoumeni
			pointer_staff->products=rand()%3;
		}


		if(pointer_staff->products==0 ){ //otan o sundiasmos prointwn tou sef einia ntomata piperia mpes
			count1++;
			pointer_staff->waiting1=0;
										t2 = (double) times(&tb2);
										fprintf(f1, "[%02d:%02d:%05.02f][1][Chef][Selecting ingredients ntomata piperia]  \n" ,ptm->tm_hour-ptm->tm_hour,
					   				ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
				sem_wait(&pointer_staff->mutex1);
				sem_post(&pointer_staff->chef1);
				sem_post(&pointer_staff->mutex1);
										t2 = (double) times(&tb2);
										fprintf(f1, "[%02d:%02d:%05.02f][1][Chef][Notify saladmaker 1]  \n" ,ptm->tm_hour-ptm->tm_hour,
										ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
				sem_wait(&pointer_staff->saladmaker1);
										t2 = (double) times(&tb2);
										fprintf(f1, "[%02d:%02d:%05.02f][1][Chef][Man time for resting]  \n" ,ptm->tm_hour-ptm->tm_hour,
										ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
				nanosleep(&sleeptime, NULL);
		}
	  else if(pointer_staff->products==1  ){ //otan o sundiasmos prointwn tou sef einia ntomata kremidi mpes
			count2++;
				pointer_staff->waiting2=0;
							t2 = (double) times(&tb2);
							fprintf(f1, "[%02d:%02d:%05.02f][1][Chef][Selecting ingredients ntomata kremidi]  \n" ,ptm->tm_hour-ptm->tm_hour,
							ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
				sem_wait(&pointer_staff->mutex1);
				sem_post(&pointer_staff->chef2);
				sem_post(&pointer_staff->mutex1);
							t2 = (double) times(&tb2);
							fprintf(f1, "[%02d:%02d:%05.02f][1][Chef][Notify saladmaker 2]  \n" ,ptm->tm_hour-ptm->tm_hour,
							ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
				sem_wait(&pointer_staff->saladmaker2);
							t2 = (double) times(&tb2);
							fprintf(f1, "[%02d:%02d:%05.02f][1][Chef][Man time for resting]  \n" ,ptm->tm_hour-ptm->tm_hour,
			        ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
				nanosleep(&sleeptime, NULL);
			}
	  else if(pointer_staff->products==2  ){  //otan o sundiasmos prointwn tou sef einia kremidi piperia mpes
			count3++;
				pointer_staff->waiting3=0;
								t2 = (double) times(&tb2);
								fprintf(f1, "[%02d:%02d:%05.02f][1][Chef][Selecting ingredients kremidi piperia]  \n" ,ptm->tm_hour-ptm->tm_hour,
								ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
				sem_wait(&pointer_staff->mutex1);
				sem_post(&pointer_staff->chef3);
				sem_post(&pointer_staff->mutex1);
								t2 = (double) times(&tb2);
								fprintf(f1, "[%02d:%02d:%05.02f][1][Chef][Notify saladmaker 3]  \n" ,ptm->tm_hour-ptm->tm_hour,
								ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
				sem_wait(&pointer_staff->saladmaker3);
								t2 = (double) times(&tb2);
								fprintf(f1, "[%02d:%02d:%05.02f][1][Chef][Man time for resting]  \n" ,ptm->tm_hour-ptm->tm_hour,
								ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
				nanosleep(&sleeptime, NULL);
			}

	//	printf("num-end salad from chef is %d\n",pointer_staff->num_of_salad );


}


printf("count of make salad is %d \n",count1+count2+count3 );
printf("count from 1h saladmaker is %d \n",count1 );
printf("count from 2h saladmaker is %d \n",count2 );
printf("count from 3h saladmaker is %d \n",count3 );

	fclose(f1);

	/* Remove segment. */
	err = shmctl(id, IPC_RMID, 0);
	if (err == -1) perror("Removal.");
	else printf("Removed. %d\n",err);

	return 0;
}
