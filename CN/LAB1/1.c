#include <stdio.h>
#include <stdlib.h>

struct swap{
    int a;
    int b;
};

void swap(struct swap *s)
{
    int temp = s->a;
    s->a = s->b;
    s->b = temp;
}

int main()
{
    struct swap s;
    scanf("%d %d", &s.a, &s.b);
    swap(&s);
    printf("%d %d", s.a, s.b);
    
    return 0;
}