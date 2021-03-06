#include <stdio.h>

int BIT[1000]= {0}, a[1000], n;
void update(int x, int val)
{
    for(; x <= n; x += x&-x)
        BIT[x] += val;
}
int query(int x)
{
    int sum = 0;
    for(; x > 0; x -= x&-x)
        sum += BIT[x];
    return sum;
}

int main()
{
    scanf("%d", &n);
    int i;
    for(i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        update(i, a[i]);
    }
    printf("sum of first 10 elements is %d\n", query(10));
    printf("sum of all elements in range [2, 7] is %d\n", query(7) - query(2-1));
    return 0;
}