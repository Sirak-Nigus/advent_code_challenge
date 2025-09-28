#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <inputfile>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("Error opening file");
        return 1;
    }

    char s[100000]; // buffer for file content
    size_t idx = 0;
    int c;

    // Read the entire file into the buffer
    while ((c = fgetc(fp)) != EOF && idx < sizeof(s) - 1)
    {
        s[idx++] = (char)c;
    }
    s[idx] = '\0';
    fclose(fp);

    long long sum = 0;
    int enabled = 1; // mul instructions enabled by default
    size_t len = strlen(s);

    for (size_t i = 0; i < len; i++)
    {
        // Check for do() or don't()
        if (strncmp(&s[i], "do()", 4) == 0)
        {
            enabled = 1;
            i += 3;
        }
        else if (strncmp(&s[i], "don't()", 7) == 0)
        {
            enabled = 0;
            i += 6;
        }
        // Check for mul(X,Y)
        else if (strncmp(&s[i], "mul(", 4) == 0)
        {
            size_t j = i + 4;
            char a[20] = {0}, b[20] = {0};
            int ai = 0, bi = 0;

            // Parse first number
            while (j < len && isdigit(s[j]))
                a[ai++] = s[j++];
            if (j >= len || s[j] != ',')
            {
                i++;
                continue;
            }
            j++;
            // Parse second number
            while (j < len && isdigit(s[j]))
                b[bi++] = s[j++];
            if (j >= len || s[j] != ')')
            {
                i++;
                continue;
            }
            j++;

            if (enabled)
                sum += atoll(a) * atoll(b);
            i = j - 1; // move to end of mul
        }
    }

    printf("%lld\n", sum);
    return 0;
}