#include "types.h"
//find the position from id so find or insert the record
int count_linee(char const *argv[] );
//read the line of file and insert in struct hash_table_student, listehead and zip(use for count of cities)
int read_file(char const *argv[],hash_table_student hash_student ,record **head1 ,time_in **Listhead,city **zip_city);
//find the position from id so find or insert the record
int hash_function(char* id , int lenght , int size);
//create space memory for hash_student
void my_constructor_hash_table_student(char const *argv[] , hash_table_student *hash_student);
//free memory space for hash_student
void distractor_hash_table(char const *argv[] , hash_table_student *hash_student);
//special insert for struct hash_student
void insert_hash_student(record* my_rec ,hash_table_student * hash_student  , char const *argv[]);
//special insert inside insert_hash_student in order to create unique list for every hash_student node
void insert_record(record* head,record* my_rec );
//insert for new record in hash_student
void insert(record* my_rec , hash_table_student * hash_student  , char const *argv[]);
//print in terminal  map for help
void printMenu(void);
//print record inside hash_student
void print_hash_table(hash_table_student * hash_student , char const *argv[]);
//print a record
void print_record(record* temp);
//cope record from save to temp_node
void nodecpy(record* temp_node,record *save);
//initialize a strruct   record
void constructor_record(record *node);
//initialize the struct time_in
void constructor_time_in(time_in* node);
//ind and print the record with id my_rec
void lookup(char* save, hash_table_student* hash_student,char const *argv[]);
//find and delete the record with id my_rec
void delet(char* my_rec ,hash_table_student* hash_student  , char const *argv[]);
//find the count of student every year
void count(time_in* Listhead);
//find the number  of students who are activate every moment until this year
void number(char* save, time_in* Listhead);
//find the average of student who inside the the university same year
void avarage(char* save, time_in* Listhead);
//find the id which have lower gpa in the same year
void min_gpa(char* save, time_in* Listhead);
//insert record* save  inside to time_in ** Listhead and create one list of lists base on the different year which inside to university
void insert_time(record **head , time_in **Listhead ,record* save );
//insert zip in list of zip and count of zip in order to find the more popular cities of file
void insert_zip( city **head ,int zip );
//find the top-k cities form list city
void postal_code(city *zip,int k);
//print a list of node
void print_node(record* node);
//free struct and exit
void my_exit(hash_table_student *hash_student,time_in *Listhead,record* head1,city *zip_city,char const *argv[]);
