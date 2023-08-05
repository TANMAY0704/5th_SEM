#include<stdio.h>
#include<stdlib.h>
struct swap{
    int a;
    int b;
};

void swapdata(struct swap *data) {
    int temp=0;
    temp=data->a;
    data->a = data->b;
    data->b = temp;
}
int main(){
    struct swap obj = {10, 20};
    printf("Before Swapping Value of a = %d, b = %d\n", obj.a, obj.b);
    
    swapdata(&obj);
    
    printf("After swapping:");
    printf("A = %d, B = %d\n", obj.a, obj.b);
    return 0;
}

