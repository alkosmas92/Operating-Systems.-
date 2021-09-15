typedef struct my_prime{
  double prime_timer;
  int primer;
  int counter;
  struct my_prime *next
}prime;


typedef struct my_num{
	double time;
  int  position;
	int prime;
}my_num;


typedef struct num_time{
	double time_min;
	double time_max;
  int  position_min;
  int  position_max
}num_time;



//myprime
void free_list( prime* head);
void insert_prime(prime *head,my_num my_rec);
//sig2
double max_time(double* my_time , int lim);
double min_time(double* my_time , int lim);
int max_time_pos(double* my_time , int lim);
int min_time_pos(double* my_time , int lim);
double find_time(prime* temp);
void insert_primee(prime *head,my_num my_rec);
void print_prime(prime *head);
int find_count(prime *head);
void bubbleSort( prime *head);
prime * constructor_prime();
void swap( prime *temp,  prime *my_rec);

//prime1_1
int fuction_prime(int );
int prime_2(int);
unsigned  long  ipolipo(unsigned long d,int a,unsigned long int i);
