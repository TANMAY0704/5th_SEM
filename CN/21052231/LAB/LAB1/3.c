#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student
{
    int rollNumber;
    char gender;
    char mobileNumber[11];
    int phyMark;
    int chemMark;
    int mathMark;
    char dob[11];
};

void displayStudentList(struct Student students[], int n)
{
    printf("SL.no\tRoll number\tName\tGender\tDOB\tMobile number\tPhy mark\tChem mark\tMath mark\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%c\t%s\t%s\t%d\t%d\t%d\n", i + 1, students[i].rollNumber, students[i].gender,
               students[i].dob, students[i].mobileNumber, students[i].phyMark, students[i].chemMark, students[i].mathMark);
    }
}

void displayMaleAndFemale(struct Student students[], int n)
{
    printf("Male students:\n");
    printf("SL.no\tRoll number\tName\tGender\tDOB\tMobile number\tPhy mark\tChem mark\tMath mark\n");
    for (int i = 0; i < n; i++)
    {
        if (students[i].gender == 'M')
        {
            printf("%d\t%d\t%c\t%s\t%s\t%d\t%d\t%d\n", i + 1, students[i].rollNumber, students[i].gender,
                   students[i].dob, students[i].mobileNumber, students[i].phyMark, students[i].chemMark, students[i].mathMark);
        }
    }

    printf("Female students:\n");
    printf("SL.no\tRoll number\tName\tGender\tDOB\tMobile number\tPhy mark\tChem mark\tMath mark\n");
    for (int i = 0; i < n; i++)
    {
        if (students[i].gender == 'F')
        {
            printf("%d\t%d\t%c\t%s\t%s\t%d\t%d\t%d\n", i + 1, students[i].rollNumber, students[i].gender,
                   students[i].dob, students[i].mobileNumber, students[i].phyMark, students[i].chemMark, students[i].mathMark);
        }
    }
}

void sortByPercentage(struct Student students[], int n)
{
    // Sort students based on percentage (average of three subjects)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            int totalMarks1 = students[j].phyMark + students[j].chemMark + students[j].mathMark;
            int totalMarks2 = students[j + 1].phyMark + students[j + 1].chemMark + students[j + 1].mathMark;
            float percentage1 = (float)totalMarks1 / 3.0;
            float percentage2 = (float)totalMarks2 / 3.0;

            if (percentage1 < percentage2)
            {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("Students sorted by percentage:\n");
    displayStudentList(students, n);
}

void displayMobileNumberEndingWith042(struct Student students[], int n)
{
    printf("Students with mobile numbers ending with 042:\n");
    printf("SL.no\tRoll number\tName\tGender\tDOB\tMobile number\tPhy mark\tChem mark\tMath mark\n");
    for (int i = 0; i < n; i++)
    {
        if (strcmp(students[i].mobileNumber + 7, "042") == 0)
        {
            printf("%d\t%d\t%c\t%s\t%s\t%d\t%d\t%d\n", i + 1, students[i].rollNumber, students[i].gender,
                   students[i].dob, students[i].mobileNumber, students[i].phyMark, students[i].chemMark, students[i].mathMark);
        }
    }
}

void displayHighestAndLowestMark(struct Student students[], int n)
{
    int choice;
    printf("Select subject to find highest and lowest marks:\n");
    printf("1. Physics\n2. Chemistry\n3. Mathematics\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 3)
    {
        printf("Invalid choice!\n");
        return;
    }

    int highestMark = -1;
    int lowestMark = 101;

    char subject[15];

    switch (choice)
    {
    case 1:
        strcpy(subject, "Physics");
        for (int i = 0; i < n; i++)
        {
            if (students[i].phyMark > highestMark)
            {
                highestMark = students[i].phyMark;
            }
            if (students[i].phyMark < lowestMark)
            {
                lowestMark = students[i].phyMark;
            }
        }
        break;
    case 2:
        strcpy(subject, "Chemistry");
        for (int i = 0; i < n; i++)
        {
            if (students[i].chemMark > highestMark)
            {
                highestMark = students[i].chemMark;
            }
            if (students[i].chemMark < lowestMark)
            {
                lowestMark = students[i].chemMark;
            }
        }
        break;
    case 3:
        strcpy(subject, "Mathematics");
        for (int i = 0; i < n; i++)
        {
            if (students[i].mathMark > highestMark)
            {
                highestMark = students[i].mathMark;
            }
            if (students[i].mathMark < lowestMark)
            {
                lowestMark = students[i].mathMark;
            }
        }
        break;
    }

    printf("Highest mark in %s: %d\n", subject, highestMark);
    printf("Lowest mark in %s: %d\n", subject, lowestMark);
}

int main()
{
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct Student students[MAX_STUDENTS];

    int choice;
    do
    {
        printf("\nStudent Menu:\n");
        printf("0. Quit\n");
        printf("1. Store student data\n");
        printf("2. Display student data\n");
        printf("3. Display male and female categories separately\n");
        printf("4. Display student data along with % mark sorted in % mark\n");
        printf("5. Display the student data having a mobile number ending with 042\n");
        printf("6. Display the highest and lowest mark in any subject as per the user's wish\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            printf("Goodbye!\n");
            break;
        case 1:
            printf("Enter student details:\n");
            for (int i = 0; i < n; i++)
            {
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
            break;
        case 2:
            displayStudentList(students, n);
            break;
        case 3:
            displayMaleAndFemale(students, n);
            break;
        case 4:
            sortByPercentage(students, n);
            break;
        case 5:
            displayMobileNumberEndingWith042(students, n);
            break;
        case 6:
            displayHighestAndLowestMark(students, n);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 0);

    return 0;
}
