#include <stdio.h>
#include <string.h>

struct dob {
    int day;
    int month;
    int year;
};

struct student_info {
    int roll_no;
    char name[50];
    float CGPA;
    struct dob age;
};

void printStudentByValue(struct student_info student) {
    printf("Roll No: %d\n", student.roll_no);
    printf("Name: %s\n", student.name);
    printf("CGPA: %.2f\n", student.CGPA);
    printf("Date of Birth (DD.MM.YYYY): %d.%d.%d\n", student.age.day, student.age.month, student.age.year);
}

void printStudentByAddress(struct student_info *student) {
    printf("Roll No: %d\n", student->roll_no);
    printf("Name: %s\n", student->name);
    printf("CGPA: %.2f\n", student->CGPA);
    printf("Date of Birth (DD.MM.YYYY): %d.%d.%d\n", student->age.day, student->age.month, student->age.year);
}

int main() {
    struct student_info student1 = {
        .roll_no = 101,
        .name = "John Doe",
        .CGPA = 8.75,
        .age = {1, 1, 2000}
    };

    struct student_info student2;
    student2.roll_no = 102;
    strcpy(student2.name, "Jane Smith");
    student2.CGPA = 9.0;
    student2.age.day = 15;
    student2.age.month = 5;
    student2.age.year = 1999;

    printf("Printing student1 using call-by-value:\n");
    printStudentByValue(student1);

    printf("\nPrinting student2 using call-by-address:\n");
    printStudentByAddress(&student2);

    return 0;
}
