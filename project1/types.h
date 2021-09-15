typedef struct my_record{
  char Student_ID[20];
  char Last_Name[20];
  char First_Name[20];
  char Zip[20];
  char city[20];
  char Year[20];
  char GPA[20];
  struct my_record* next;

}record;

typedef struct my_city{
  int count;
  int Zip;
  struct my_city *next;
}city;

typedef struct time_inside{
  //char year[20];
  struct time_inside* next;
  city* start;
  record * info;
}time_in;

// typedef struct infostudent{
//   char Student_ID[20];
//   record *information;
//   struct infostudent * next;
// }info_student;

typedef struct bucketstudent{
  //char Student_ID[20];
  record *information;
}bucket_student;

typedef struct{
  int size_of_bucket_student;
   bucket_student *b_student;
}hash_table_student;
