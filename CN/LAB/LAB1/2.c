#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    int rollNumber;
    char gender;
    char mobileNumber[11];
    int phyMark;
    int chemMark;
    int mathMark;
    char dob[11];
};

void displayStudentList(struct Student students[], int n) {
    printf("SL.no\tRoll number\tName\tGender\tDOB\tMobile number\tPhy mark\tChem mark\tMath mark\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%c\t%s\t%s\t%d\t%d\t%d\n", i + 1, students[i].rollNumber, students[i].gender,
            students[i].dob, students[i].mobileNumber, students[i].phyMark, students[i].chemMark, students[i].mathMark);
    }
}

int main() {
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct Student students[MAX_STUDENTS];

    printf("Enter student details:\n");
    for (int i = 0; i < n; i++) {
        printf("Student %d:\n", i + 1);
        printf("Roll number: ");
        scanf("%d", &students[i].rollNumber);

        printf("Gender (M/F): ");
        scanf(" %c", &students[i].gender);

        printf("Date of Birth (DD.MM.YYYY): ");
        scanf("%s", students[i].dob);

        printf("Mobile number: ");
        scanf("%s", students[i].mobileNumber);

        printf("Physics mark: ");
        scanf("%d", &students[i].phyMark);

        printf("Chemistry mark: ");
        scanf("%d", &students[i].chemMark);

        printf("Mathematics mark: ");
        scanf("%d", &students[i].mathMark);
    }

    displayStudentList(students, n);

    return 0;
}
