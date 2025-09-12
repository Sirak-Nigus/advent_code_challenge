// day 1 part 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100000 // upper bound of lines

int cmp(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int main(void)
{
    int left[MAXN], right[MAXN];
    int n = 0;

    // Read pairs of integers until EOF
    while (scanf("%d %d", &left[n], &right[n]) == 2)
    {
        n++;
        if (n >= MAXN)
        {
            fprintf(stderr, "Increase MAXN to handle more lines.\n");
            return 1;
        }
    }

    // Sort both arrays
    qsort(left, n, sizeof(int), cmp);
    qsort(right, n, sizeof(int), cmp);

    long long total = 0;
    for (int i = 0; i < n; i++)
    {
        total += llabs((long long)left[i] - (long long)right[i]);
    }

    printf("%lld\n", total);
    return 0;
}