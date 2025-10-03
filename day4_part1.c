#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char buf[10000];
    char **grid = NULL;
    int rows = 0;
    int cols = -1;

    // Read grid lines from stdin
    while (fgets(buf, sizeof(buf), stdin))
    {
        size_t len = strlen(buf);
        while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r'))
            buf[--len] = '\0';
        if (len == 0)
            continue; // skip empty lines

        if (cols == -1)
            cols = (int)len;
        if (cols != (int)len)
        {
            fprintf(stderr, "Error: inconsistent row lengths\n");
            return 1;
        }

        char *row = malloc(len + 1);
        strcpy(row, buf);

        char **tmp = realloc(grid, (rows + 1) * sizeof(char *));
        grid = tmp;
        grid[rows++] = row;
    }

    if (rows == 0 || cols <= 0)
    {
        printf("0\n");
        return 0;
    }

    const char *word = "XMAS";
    int wlen = 4;
    long long count = 0;

    // 8 directions: right, down-right, down, down-left, left, up-left, up, up-right
    int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (grid[r][c] != 'X')
                continue; // only start from 'X'

            for (int dir = 0; dir < 8; dir++)
            {
                int rr = r, cc = c, k;
                for (k = 0; k < wlen; k++)
                {
                    if (rr < 0 || rr >= rows || cc < 0 || cc >= cols)
                        break;
                    if (grid[rr][cc] != word[k])
                        break;
                    rr += dy[dir];
                    cc += dx[dir];
                }
                if (k == wlen)
                    count++;
            }
        }
    }

    printf("%lld\n", count);

    for (int i = 0; i < rows; i++)
        free(grid[i]);
    free(grid);

    return 0;
}