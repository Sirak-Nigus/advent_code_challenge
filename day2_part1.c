#include <stdio.h>
#include <stdlib.h>

#define MAX_LEVELS 1000

int is_safe(int *levels, int n)
{
    int increasing = 0, decreasing = 0;
    for (int i = 1; i < n; i++)
    {
        int diff = levels[i] - levels[i - 1];
        if (diff == 0 || diff < -3 || diff > 3)
            return 0;
        if (diff > 0)
            increasing++;
        if (diff < 0)
            decreasing++;
    }
    return (increasing == n - 1 || decreasing == n - 1);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <input_filename>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f)
    {
        perror("Cannot open file");
        return 1;
    }

    int safe_count = 0;
    char line[4096];

    while (fgets(line, sizeof(line), f))
    {
        int levels[MAX_LEVELS];
        int n = 0;
        char *ptr = line;
        int val;
        while (sscanf(ptr, "%d", &val) == 1)
        {
            levels[n++] = val;
            while (*ptr && *ptr != ' ' && *ptr != '\n')
                ptr++;
            while (*ptr == ' ')
                ptr++;
        }
        if (n > 0 && is_safe(levels, n))
            safe_count++;
    }

    fclose(f);

    printf("Number of safe reports: %d\n", safe_count);
    return 0;
}