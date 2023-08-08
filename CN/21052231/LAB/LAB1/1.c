#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student
{
    int roll;
    char name[20];
    char gender[10];
    char mobile[10];
    int phy;
    int chem;
    int math;
};

int main()
{
    int i,n;
    struct student s[100];
    printf("Enter the number of student: ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter the roll number\n");
        scanf("%d",&s[i].roll);
        printf("Enter the name\n");
        scanf("%s",s[i].name);
        printf("Enter the gender\n");
        scanf("%s",s[i].gender);
        printf("Enter the mobile number\n");
        scanf("%s",s[i].mobile);
        printf("Enter the phy mark\n");
        scanf("%d",&s[i].phy);
        printf("Enter the chem mark\n");
        scanf("%d",&s[i].chem);
        printf("Enter the math mark\n");
        scanf("%d",&s[i].math);
    }
    printf("SL.no\tRoll number\tName\tGender\tMobile number\tPhy mark\tChem mark\tMath mark\n");
    for(i=0;i<n;i++)
    {
        printf("%d\t%d\t%s\t%s\t%s\t%d\t%d\t%d\n",i+1,s[i].roll,s[i].name,s[i].gender,s[i].mobile,s[i].phy,s[i].chem,s[i].math);
    
    }
    return 0;
}