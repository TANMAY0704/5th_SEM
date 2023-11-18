#include <stdio.h>
#include <stdlib.h>

void sort_arr(int act[], int start[], int finish[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int duration_i = finish[i] - start[i];
            int duration_j = finish[j] - start[j];

            if (duration_i > duration_j)
            {
                int temp = start[j];
                start[j] = start[i];
                start[i] = temp;

                temp = act[j];
                act[j] = act[i];
                act[i] = temp;

                temp = finish[j];
                finish[j] = finish[i];
                finish[i] = temp;
            }
        }
    }
}

int act_selection(int act[], int start[], int finish[], int n, int final[])
{
    int time = 0, k = 0;

    for (int i = 0; i < n; i++)
    {
        if (start[i] >= time)
        {
            final[k] = act[i];
            k++;
            time = finish[i];
        }
    }
    return k;
}

void print_arr(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("%d", arr[n - 1]);
}

int main()
{
    int n;
    printf("Enter the number of activities : ");
    scanf("%d", &n);
    int act[n], start[n], finish[n];

    for (int i = 0; i < n; i++)
    {
        printf("Activity %d : ", i);
        scanf("%d %d", &start[i], &finish[i]);
        act[i] = i;
    }
    int final[10];
    sort_arr(act, start, finish, n);
    int f = act_selection(act, start, finish, n, final);
    printf("Maximum number of non-overlapping activities: ");
    print_arr(final, f);

    return 0;
}
