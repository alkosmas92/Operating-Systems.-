#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"

int count_linee(char const *argv[] ){

  FILE *fp;
    int count_line = 0;  // Line count_lineer (result)
    char filename[100];
    char c;  // To store a character read from file
    fp = fopen(argv[2],"r");

  // Check if file exists
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }

  // Extract characters from file and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp)){
        if (c == '\n') // Increment count_line if this character is newline
            count_line = count_line + 1;
    }


  // Close the file
    fclose(fp);

    return count_line;
}

int read_file(char const *argv[],hash_table_student hash_student ,record **head1 ,time_in **Listhead,city **zip_city){

     record *my_rec=malloc(sizeof( record));
       constructor_record(my_rec);
         int zip=0;
     //
     // record *head2=NULL;
     // record *head1=NULL;

            FILE *ptr;
            ptr = fopen(argv[2],"r");

            if(ptr==NULL)
              {
                printf("ptr fail\n");
                return -1;
              }

            char *line = NULL;
                   size_t  lenght;
                   ssize_t  test;

             while((test = getline(&line, &lenght , ptr)) != -1){
              char check[]=" ";
              char *broke = strtok(line,check);
              strcpy(my_rec->Student_ID,broke);
                  broke=strtok(NULL,check);
              strcpy(my_rec->Last_Name,broke);
                  broke=strtok(NULL,check);
              strcpy(my_rec->First_Name,broke);
                  broke=strtok(NULL,check);
                  zip=atoi(broke);
              strcpy(my_rec->Zip,broke);
                  broke=strtok(NULL,check);
              strcpy(my_rec->Year,broke);
                  broke=strtok(NULL,check);
              strcpy( my_rec->GPA,broke);

              insert_hash_student(my_rec , &hash_student ,argv );

              insert_time(head1,Listhead,my_rec);

              insert_zip(zip_city , zip );

           }


  }

void insert(record* my_rec , hash_table_student * hash_student  , char const *argv[]){

   int position=hash_function(my_rec->Student_ID,sizeof(my_rec->Student_ID),count_linee(argv));
   record *head=malloc(sizeof(record));
   head = hash_student->b_student[position].information;
   record * previous=malloc(sizeof(record));
   constructor_record(previous);
   record * temp=malloc(sizeof(record));
   constructor_record(temp);
   record * plus=malloc(sizeof(record));
   constructor_record(plus);

   temp=head;



   if (head->next==NULL){

     nodecpy(head,my_rec);
     printf("- Student | %s | inserted\n",my_rec->Student_ID);

     head->next=previous;
   }

   else{
   while(temp->next !=NULL){
     if(strcmp(temp->Student_ID ,my_rec->Student_ID)==0){
       printf("- Student | %s | exists \n",my_rec->Student_ID );
       break;
     }
     temp=temp->next;
     previous=temp;


   }

   if(previous->next==NULL){
     nodecpy(previous,my_rec);
     printf("- Student | %s | inserted\n",my_rec->Student_ID);

       previous->next=plus;
       //print_hash_table(hash_student,argv);
     }
   }

 }

void insert_hash_student(record* my_rec , hash_table_student * hash_student  , char const *argv[]){

  int position=hash_function(my_rec->Student_ID,sizeof(my_rec->Student_ID),count_linee(argv));
  record *head=malloc(sizeof(record));
  head = hash_student->b_student[position].information;
  insert_record(head,my_rec );

}

void insert_record(record* head,record* my_rec){


  record * previous=malloc(sizeof(record));
  constructor_record(previous);
  record * temp=malloc(sizeof(record));
  constructor_record(temp);
  record * plus=malloc(sizeof(record));
  constructor_record(plus);

  temp=head;

  if (head->next==NULL){

    nodecpy(head,my_rec);
    head->next=previous;
  }


  while(temp->next !=NULL){

    temp=temp->next;
    previous=temp;


  }

  if(previous->next==NULL){
    nodecpy(previous,my_rec);
      previous->next=plus;
    }
}

void insert_time(record **head , time_in **Listhead ,record* save  ){

  record *temp_node,*current_node,*plus;
  temp_node=malloc(sizeof( record));
  nodecpy(temp_node,save);
  temp_node->next=NULL;

  time_in *temp_list,*current_list;
  temp_list=malloc(sizeof( time_in));

  int check=0;

  if((*Listhead)==NULL){

     if((*head)==NULL){
        (*head)=temp_node;
        temp_list->info=(*head);
        temp_list->next=NULL;
        (*Listhead)=temp_list;
      }
  }


  else{
  current_list=(*Listhead);
    while(current_list->next!=NULL){
          current_node=current_list->info;
          if(current_node->Student_ID==save->Student_ID){

            exit(0);
          }
         if(strcmp(current_node->Year, save->Year)==0){
            check=1;
            break;
         }
      current_list=current_list->next;
     }
    current_node=current_list->info;
    if(strcmp(current_node->Year, save->Year)==0){
       check=1;
    }
    if(check==1){
      while(current_node->next!=NULL){
        current_node=current_node->next;
      }
      current_node->next=temp_node;
    }

     if(current_list->next==NULL && check==0){
       temp_list->info=temp_node;
       temp_list->next=NULL;
       current_list->next=temp_list;
     }
   }
}

void printMenu(void) {
	printf("\nYour options:\n");
	printf("\ni studentid lastname firstname zip year gpa<space>\n");
	printf("\nl(ook-up) studentid<space>\n");
	printf("\nd(elete) studentid<space> \n");
	printf("\nn(umber) year<space>\n");
	printf("\na(verage) year<space>\n");
  printf("\nm(inimum) year<space>\n");
  printf("\nc(ount) year<space>\n");
  printf("\np(ostal code) rank<space>\n");
  printf("\nexit<space>\n\n\n");

}

void lookup(char* save, hash_table_student* hash_student,char const *argv[]){

  int position=hash_function(save,sizeof(record),count_linee(argv));
  record *head=malloc(sizeof(record));
  head = hash_student->b_student[position].information;
  record * temp=malloc(sizeof(record));
  constructor_record(temp);
  temp=head;
  int id=atoi(temp->Student_ID);

  while (temp != NULL && strcmp(temp->Student_ID ,save)!=0)
  {
      temp = temp->next;

  }

  if(temp != NULL && strcmp(temp->Student_ID ,save)==0){
    print_record(temp);
  }

  else if(temp == NULL ){
    printf("- Student | %s | does not exist\n", save);
  }


}

void delet(char* save, hash_table_student* hash_student,char const *argv[]){
  int position=hash_function(save,sizeof(save),count_linee(argv));
  record *head=malloc(sizeof(record));
  head = hash_student->b_student[position].information;

  record * temp=malloc(sizeof(record));
  constructor_record(temp);
  record * follow=malloc(sizeof(record));
  constructor_record(follow);
  record * prev=malloc(sizeof(record));
  constructor_record(prev);

  temp=head;

      if (temp != NULL && strcmp(temp->Student_ID ,save)==0)
      {
          head = temp->next;   // Changed head
          free(temp);               // free old head
          return;
      }
      //
      // // Search for the key to be deleted, keep track of the
      // // previous node as we need to change 'prev->next'
      while (temp != NULL && strcmp(temp->Student_ID ,save)!=0)
      {
          prev = temp;
          temp = temp->next;
      }

      // If key was not present in linked list
      if (temp == NULL){
        printf("- Student | %s | does not exist\n",temp->Student_ID );
        return;
        }
      // Unlink the node from linked list
      prev->next = temp->next;
      printf("- Student | %s | deleted\n",save );


      free(temp);  // Free memory


}

void count( time_in* Listhead){
  int count=0;
   time_in *current;
   record *currentlist;
  current=Listhead;
  if(current==NULL){
      printf("- No students enrolled  \n" );
  }
  while(current!=NULL){
          currentlist=current->info;
          count=0;
          printf("- list({ | %s |, ",currentlist->Year );
      while(currentlist!=NULL){
              count=count+1;
              currentlist=currentlist->next;
        }
      printf("| %d | }) \n" ,count );
      current=current->next;
  }

}

void number(char* save, time_in* Listhead){

  int count=0;
   time_in *current;
   record *currentlist;
  current=Listhead;
  while(current!=NULL){
          currentlist=current->info;

          if(strcmp(save,currentlist->Year)>=0){

          while(currentlist!=NULL){
              count=count+1;
              currentlist=currentlist->next;
        }
      }
      current=current->next;

  }
  if(count>0){
    printf("- |%d| student(s) in | %s |\n",count ,save );
  }
  else{
    printf("- No students enrolled in |%s| \n",save );
  }

}

void avarage(char* save, time_in* Listhead){

  float count=0.0;
  float sum_avg=0.0;
  float avg=0.0;
   time_in *current;
   record *currentlist;
  current=Listhead;
  int check=0;
  while(current!=NULL){
          currentlist=current->info;
      if(strcmp(currentlist->Year ,save)==0){
        check=1;
        while(currentlist!=NULL){
              count=count+1.0;

              float avarage=atof(currentlist->GPA);

              sum_avg=sum_avg+avarage;

              currentlist=currentlist->next;
        }
      }
      current=current->next;
  }

    avg=sum_avg/count;
    if(check==1){
        printf("avg is %.5f\n",avg );
    }
    else if(check==0){
        printf("- No students enrolled in |%s| \n",save );
    }
}

void min_gpa(char* save, time_in* Listhead){
   time_in *current;
   record *currentlist;
   record *min_record=malloc(sizeof(record));
   constructor_record(min_record);
  current=Listhead;
  while(current!=NULL){
          currentlist=current->info;

      if(strcmp(save,currentlist->Year)==0){
              min_record=currentlist;
          while(currentlist!=NULL){
              if(strcmp(currentlist->GPA, min_record->GPA)<0){
                printf("eimai edw \n" );
                min_record=currentlist;
              }
            currentlist=currentlist->next;
        }
      }
      current=current->next;

  }
  if(strcmp(min_record->Year,"0")!=0){
      printf("- list(| %s |)\n",min_record->Student_ID );
  }
  else{
      printf("- No students enrolled in |%s| \n",save );
  }

}

void insert_zip( city **zip_city ,int zip ){
  // printf("->Zip %d\n",zip );
  //
  // printf("NEOOOO\n" );

     city *temp,*current;
    temp=malloc(sizeof( city));
    temp->Zip=zip;
    temp->count=1;
    temp->next=NULL;
    int check=0;

    if((*zip_city)==NULL){
        (*zip_city)=temp;
    }
    else{
        current=(*zip_city);
        while(current->next!=NULL){
         // printf("current->Zip %d\n",current->Zip );
            if(current->Zip==zip){
              check=1;
              break;
            }
            current=current->next;
        }
        if(current->Zip==zip){
          check=1;

        }
        if(check==1){
          current->count=current->count +1;
        }
        if(check==0){
        current->next=temp;
        }
    }
}

void postal_code(city *zip_city, int k){

    city* win_zip=malloc(sizeof(city));
    win_zip=zip_city;
    city* again_city=malloc(sizeof(city));
    again_city=zip_city;
    //printf("again_city %d\n",again_city );
    int huge=100000000;
    int i=0;

    for( i; i<k ;i++){
    //  printf("huge is %d\n",huge );
        while(zip_city->next!=NULL){

          if(win_zip->count<zip_city->count && zip_city->count<huge){
            win_zip=zip_city;
          }
          zip_city=zip_city->next;
        }
        huge=win_zip->count;
        zip_city=again_city;
        printf("list(|%d|) is/are |%d| most popular\n",win_zip->Zip,k );
        //printf("count %d\n",win_zip->count );

        win_zip->count=0;

      }
}

void print_city(city* zip_city){
  if(zip_city->next==NULL){
    printf("zipppp is %s\n",zip_city->Zip );
    printf("countttt is %d\n",zip_city->count );
  }
  while(zip_city->next!=NULL){
    printf("zip is %s\n",zip_city->Zip );
    printf("count is %d\n",zip_city->count );
    zip_city=zip_city->next;
  }

}

int hash_function(char* id , int lenght , int size){

  int num=atoi(id);
   int pos = 0;
   int MIN=1;
   int MAX=size/10;
   for(int i=0 ; i<lenght ; i++)
      pos = num % MAX;
    return pos %= size;
 }

 //int insert_hash_student(infostudent *student ,char const *argv[] )

void distractor_info_student( record *node ){
    // free(node-> Student_ID );
    // free(node-> Last_Name );
    // free(node-> First_Name );
    // free(node-> Zip );
    // free(node-> city );
    // free(node-> Year );
    // free(node-> GPA );
    // free(node->next);
}

void constructor_record(record *node){
  strcpy(node->Year,"0");
  node->next=NULL;
}

void constructor_time_in(time_in* node){
  //
  // node->info=malloc(sizeof(record));
  // constructor_record(node->info);
  // node->next=NULL;
}

void my_constructor_hash_table_student(char const *argv[] , hash_table_student *hash_student){
  hash_student->b_student = malloc((count_linee(argv)/10)*sizeof(bucket_student));
  hash_student->size_of_bucket_student=count_linee(argv)/10;
  for(int i = 0 ;i <= count_linee(argv)/10 ;i++ ){
      hash_student->b_student[i].information=malloc((hash_student->size_of_bucket_student)*sizeof(record));
      hash_student->b_student[i].information->next=NULL;
  }
}

void distractor_hash_table(char const *argv[] , hash_table_student *hash_student){
  for(int i = 0 ;i <= count_linee(argv)/10 ;i++ ){
      free(hash_student->b_student[i].information);
    }
    free(hash_student->b_student );
  }

void nodecpy(record* temp_node,record *save){
  strcpy(temp_node->Student_ID,save->Student_ID);
  strcpy(temp_node->Last_Name,save->Last_Name);
  strcpy(temp_node->First_Name,save->First_Name);
  strcpy(temp_node->Zip,save->Zip);
  strcpy(temp_node->city,save->city);
  strcpy(temp_node->Year,save->Year);
  strcpy(temp_node->GPA,save->GPA);

}

void print_node(record* node){
  if(node->next==NULL){
    print_record(node);
  }
  while(node->next!=NULL){

    print_record(node);
    node=node->next;
  }

}

void print_hash_table(hash_table_student * hash_student ,  char const *argv[]){
  int i=0;

    for(i ; i <= (count_linee(argv)/10) ; i++){
      record* temp=malloc(sizeof(record));
      temp=hash_student->b_student[i].information;


      while(temp->next!=NULL){
        print_record(temp);
        temp=temp->next;
      }
    }
}

void print_record(record *temp){
  printf("- |%s| |%s| |%s| |%s| |%s| |%s| \n", temp->Student_ID ,
  temp->Last_Name , temp->First_Name , temp->Zip , temp->Year , temp->GPA);

}

void show(time_in* Listhead){
    int i=1;
     time_in *current;
     record *currentlist;
    current=Listhead;
    while(current!=NULL){
            currentlist=current->info;
        printf("List %d: \n",i);
        while(currentlist!=NULL){
            printf(" Student_ID is %s Last_Name %s First_Name %s Zip %s Year %s GPA %s",currentlist->Student_ID, currentlist-> Last_Name,
              currentlist-> First_Name,currentlist->Zip,currentlist-> Year,currentlist-> GPA );
              currentlist=currentlist->next;
        }
        i++;
        printf("\n");
        current=current->next;
    }
}

void my_exit(hash_table_student *hash_student,time_in *Listhead,record* head1,city *zip_city,char const *argv[]){
  distractor_hash_table(argv,hash_student);
  free(Listhead);
  free(head1);
  free(zip_city);
  printf("exit_program\n" );
}
