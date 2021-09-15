#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"

int main(int argc, char const *argv[])
{

  int count_line;
  count_line = count_linee(argv);
  printf("The file has %d lines\n",count_line);
  hash_table_student hash_student;
  my_constructor_hash_table_student(argv , &hash_student);

  time_in *Listhead=malloc(sizeof(time_in));
  record *head1=malloc(sizeof(record));
  head1=NULL;
  Listhead=NULL;
  city* zip_city=malloc(sizeof(city));
  zip_city=NULL;

   read_file(argv, hash_student ,&head1,&Listhead,&zip_city );

  printMenu();
    char *UserCommand = NULL;
    size_t combytes = 200;
    UserCommand = (char *) malloc(combytes);
    char * line = (char *) malloc(combytes);
    char *broke;

    while(getline(&UserCommand, &combytes, stdin) != EOF) {
        strcpy(line, UserCommand);
        broke = strtok(UserCommand, " \n");    // Tokenize input
        char check[]=" ";

      if (broke != NULL) {
          if (strcmp(broke, "i") == 0) {
            record* my_rec=malloc(sizeof(record));
            constructor_record(my_rec);
            broke = strtok(NULL,check);
            strcpy(my_rec->Student_ID,broke);
                broke=strtok(NULL,check);
            strcpy(my_rec->Last_Name,broke);
                broke=strtok(NULL,check);
            strcpy(my_rec->First_Name,broke);
                broke=strtok(NULL,check);
                int zip=atoi(broke);
            strcpy(my_rec->Zip,broke);
                broke=strtok(NULL,check);
            strcpy(my_rec->Year,broke);
                broke=strtok(NULL,check);
            strcpy( my_rec->GPA,broke);

            insert(my_rec,&hash_student,argv);
            insert_time(&head1 , &Listhead ,my_rec  );
            insert_zip(&zip_city , zip );

        }
        else if(strcmp(broke, "l") == 0){
          broke = strtok(NULL,check);
          record* my_rec=malloc(sizeof(record));
          constructor_record(my_rec);
          strcpy(my_rec->Student_ID,broke);
          lookup(my_rec->Student_ID, &hash_student , argv);

        }
        else if(strcmp(broke, "d") == 0){
          broke = strtok(NULL,check);
          char* Student_ID[20];
          strcpy(Student_ID,broke);
          delet( Student_ID , &hash_student , argv);
        }
      else if(strcmp(broke, "n") == 0){
        broke = strtok(NULL,check);
        char* Year[20];
        strcpy(Year,broke);
        number( Year , Listhead );
      }
      else if(strcmp(broke, "a") == 0){
        broke = strtok(NULL,check);
        char* Year[20];
        strcpy(Year,broke);
        avarage( Year , Listhead );

      }
      else if(strcmp(broke, "m") == 0){
        broke = strtok(NULL,check);
        char* Year[20];
        strcpy(Year,broke);
        min_gpa( Year , Listhead );

      }
      else if(strcmp(broke, "c") == 0){
          count(  Listhead );

      }
      else if(strcmp(broke, "p") == 0){
        broke = strtok(NULL,check);
        int k=atoi(broke);
        postal_code(  zip_city , k);

      }
      else if(strcmp(broke, "exit") == 0){

        my_exit( &hash_student,Listhead,head1,zip_city,argv);
        break;
      }
    }
  }
}
