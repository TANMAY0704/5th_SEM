#include <stdio.h>
#include <stdlib.h>
 struct stud
 {
    char name[50];
    int roll;
    char sec[10];
    


 };
 


int main()
{
    struct stud s;

    
    
    printf("Enter the name of the student: ");
    scanf("%s", &s.name);
    printf("Enter the roll number of the student: ");
    scanf("%d", &s.roll);
    printf("Enter the section of the student: ");
    scanf("%s", s.sec);

    printf("Name: %s\n", s.name);
    printf("Roll number: %d\n", s.roll);
    printf("Section: %s\n", s.sec);




    return 0;
}