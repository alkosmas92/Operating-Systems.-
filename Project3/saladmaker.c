/* semtest3a.c POSIX Semaphore test example using shared memory */

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

extern int errno;

int main(int argc,char **argv)
{


		int lb,shmid,ub;

		int k =0;
		while(k<argc){					// vres tis simaies kai pare ta data pou xriazesai
			if(!strcmp("-t1",argv[k]))
					 lb = atoi(argv[k+1]);
		 else if(!strcmp("-t2",argv[k]))
					  ub = atoi(argv[k+1]) ;
		 else if(!strcmp("-s",argv[k]))
					  shmid = atoi(argv[k+1]) ;
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

	int retval;
	int id, err;
	int whatisthevalue=0;

	time_t rawtime = time(NULL);

	double t1, t2, cpu_time;
	struct tms tb1, tb2;
	double ticspersec;
	int    i, sum = 0;

	ticspersec = (double) sysconf(_SC_CLK_TCK);
	t1 = (double) times(&tb1);

	struct tm *ptm = localtime(&rawtime);

	struct timespec sleeptime;
		sleeptime.tv_sec = 0;
		sleeptime.tv_nsec = TEN_MILLION;
		float time_spent;


	FILE *f1;
	f1  = fopen ("chef.log", "w");


	FILE *fp1;
	FILE *fp2;
	FILE *fp3;
	fp1 = fopen("saladmaker1.log", "w");
	fp2 = fopen("saladmaker2.log", "w");
	fp3 = fopen("saladmaker3.log", "w");

	if (argc <= 1) { printf("Need shmem id. \n"); exit(1); }

	/* Get id from command line. */
	sscanf(argv[6], "%d", &id);
	printf("Allocated %d\n", id);

	/* Attach the segment. */
	void * shared_memory = (void *) shmat(id,(void*) 0, 0);


	Staff_struct* pointer_staff = shared_memory;


	while(pointer_staff->num_of_salad > 0){
		int k=rand()%2;
		if(k==0){
				sleeptime.tv_nsec = lb;
			}
		else{
				sleeptime.tv_nsec = ub;
			}

		if(pointer_staff->products==0 && pointer_staff->waiting1==0){
			pointer_staff->num_of_salad--;

					t2 = (double) times(&tb2);
							fprintf(fp1, "[%02d:%02d:%05.02f][2][saladmaker1][Waiting for ingredients]  \n" ,ptm->tm_hour-ptm->tm_hour,
							ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
		sem_wait(&pointer_staff->chef1);
		sem_wait(&pointer_staff->mutex1);
							t2 = (double) times(&tb2);
							fprintf(fp1, "[%02d:%02d:%05.02f][2][saladmaker1][Get ingredients]  \n" ,ptm->tm_hour-ptm->tm_hour,
							ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
		sem_post(&pointer_staff->saladmaker1);
		sem_post(&pointer_staff->mutex1);
							t2 = (double) times(&tb2);
							fprintf(fp1, "[%02d:%02d:%05.02f][2][saladmaker1][Start making salad]  \n" ,ptm->tm_hour-ptm->tm_hour,
							ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
		nanosleep(&sleeptime, NULL);
							t2 = (double) times(&tb2);
							fprintf(fp1, "[%02d:%02d:%05.02f][2][saladmaker1][End making salad]  \n" ,ptm->tm_hour-ptm->tm_hour,
							ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );

			pointer_staff->waiting1=1;
		}

	else if(pointer_staff->products==1 && pointer_staff->waiting2==0){
		 		pointer_staff->num_of_salad--;

							t2 = (double) times(&tb2);
							fprintf(fp2, "[%02d:%02d:%05.02f][3][saladmaker2][Waiting for ingredients]  \n" ,ptm->tm_hour-ptm->tm_hour,
							ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
		sem_wait(&pointer_staff->chef2);
		sem_wait(&pointer_staff->mutex1);
							t2 = (double) times(&tb2);
							fprintf(fp2, "[%02d:%02d:%05.02f][3][saladmaker2][Get ingredients]  \n" ,ptm->tm_hour-ptm->tm_hour,
							ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
		sem_post(&pointer_staff->saladmaker2);
		sem_post(&pointer_staff->mutex1);
							t2 = (double) times(&tb2);
							fprintf(fp2, "[%02d:%02d:%05.02f][3][saladmaker2][Start making salad]  \n" ,ptm->tm_hour-ptm->tm_hour,
							ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
		nanosleep(&sleeptime, NULL);
							t2 = (double) times(&tb2);
							fprintf(fp2, "[%02d:%02d:%05.02f][3][saladmaker2][End making salad]  \n" ,ptm->tm_hour-ptm->tm_hour,
							ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
			pointer_staff->waiting2=1;
	}

	 if(pointer_staff->products==2 && pointer_staff->waiting3==0){
		 	pointer_staff->num_of_salad--;
							t2 = (double) times(&tb2);
							fprintf(fp3, "[%02d:%02d:%05.02f][4][saladmaker3][Waiting for ingredients]  \n" ,ptm->tm_hour-ptm->tm_hour,
							ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
		sem_wait(&pointer_staff->chef3);
		sem_wait(&pointer_staff->mutex1);
							t2 = (double) times(&tb2);
							fprintf(fp3, "[%02d:%02d:%05.02f][4][saladmaker3][Get ingredients]  \n" ,ptm->tm_hour-ptm->tm_hour,
							ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
		sem_post(&pointer_staff->saladmaker3);
		sem_post(&pointer_staff->mutex1);
							t2 = (double) times(&tb2);
							fprintf(fp3, "[%02d:%02d:%05.02f][4][saladmaker3][Start making salad]  \n" ,ptm->tm_hour-ptm->tm_hour,
							ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
		nanosleep(&sleeptime, NULL);
							t2 = (double) times(&tb2);
							fprintf(fp3, "[%02d:%02d:%05.02f][4][saladmaker3][End making salad]  \n" ,ptm->tm_hour-ptm->tm_hour,
							ptm->tm_min-ptm->tm_min, (t2 - pointer_staff->start) / ticspersec );
			 pointer_staff->waiting3=1;
		}


	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	/* Remove segment. */
	err = shmctl(id, IPC_RMID, 0);
	if (err == -1) perror("Removal.");
	else printf("Removed. %d\n",err);


	return 0;
}
