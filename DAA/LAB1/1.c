//find second largest and second smallest number in array
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n,i,j,temp;
    printf("Enter the size of array: ");
    scanf("%d",&n);
    int a[n];
    printf("Enter the elements of array: ");
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(a[j]>a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }	
    }
    printf("Second largest number is %d\n",a[n-2]);
    printf("Second smallest number is %d\n",a[1]);
    return 0;
} 