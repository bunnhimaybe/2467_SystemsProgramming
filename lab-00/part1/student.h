/* student.h */
/* define a struct for storing student information */

struct student_info {
   int id;
   char name[80]; /* 80 characters should be more than enough to store a name, right? */
   char preferredName[80];

   /* need more stuff here */
   int csci_classes[20]; /* has anyone taken more than 20 CS classes? */
   char classGoals[400]; /* what I want out of this class */
   char reason[400]; /* This means my reason for studying CS must be
                        less than 400 characters, or I will have to 
                        increase the array size. */
  char interest[400]; /* a non-cs interest */
};

/* this is a function prototype, the function itself is in student.c */
struct student_info make_student(void);

