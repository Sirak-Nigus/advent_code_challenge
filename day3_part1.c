#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    // Read entire input into a bufferfer
    char *buffer = NULL;
    size_t len = 0;
    char chunk[4096];

    while (fgets(chunk, sizeof(chunk), stdin))
    {
        size_t c_len = strlen(chunk);
        char *tmp = realloc(buffer, len + c_len + 1);
        if (!tmp)
        {
            perror("realloc");
            return 1;
        }
        buffer = tmp;
        memcpy(buffer + len, chunk, c_len);
        len += c_len;
    }
    if (!buffer)
        return 0;
    buffer[len] = '\0';

    long total = 0;
    for (size_t i = 0; buffer[i]; i++)
    {
        if (buffer[i] == 'm' && buffer[i + 1] == 'u' && buffer[i + 2] == 'l' && buffer[i + 3] == '(')
        {
            size_t j = i + 4;
            int n1 = 0, n2 = 0;
            int d1 = 0, d2 = 0;

            while (isdigit((unsigned char)buffer[j]) && d1 < 3)
            {
                n1 = n1 * 10 + (buffer[j++] - '0');
                d1++;
            }
            if (d1 == 0 || buffer[j] != ',')
                continue;
            j++;

            while (isdigit((unsigned char)buffer[j]) && d2 < 3)
            {
                n2 = n2 * 10 + (buffer[j++] - '0');
                d2++;
            }
            if (d2 == 0 || buffer[j] != ')')
                continue;

            total += n1 * n2;
            i = j; // skip to end of this match
        }
    }

    printf("%ld\n", total);
    free(buffer);
    return 0;
}