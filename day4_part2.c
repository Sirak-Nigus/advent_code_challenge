#include <stdio.h>
#include <string.h>

#define MAX 1000

char grid[MAX][MAX];
int ROWS = 0, COLS = 0;

void read_grid()
{
    char line[MAX];
    while (fgets(line, sizeof(line), stdin))
    {
        int len = strlen(line);
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';
        strcpy(grid[ROWS], line);
        ROWS++;
    }
    COLS = strlen(grid[0]);
}

int in_bounds(int r, int c)
{
    return r >= 0 && r < ROWS && c >= 0 && c < COLS;
}

int check_xmas(int r, int c)
{
    if (grid[r][c] != 'A')
        return 0;

    int ok = 1;

    // Top-left to bottom-right diagonal
    if (!(in_bounds(r - 1, c - 1) && in_bounds(r + 1, c + 1)))
        return 0;
    char tl = grid[r - 1][c - 1], br = grid[r + 1][c + 1];
    if (!((tl == 'M' && br == 'S') || (tl == 'S' && br == 'M')))
        return 0;

    // Top-right to bottom-left diagonal
    if (!(in_bounds(r - 1, c + 1) && in_bounds(r + 1, c - 1)))
        return 0;
    char tr = grid[r - 1][c + 1], bl = grid[r + 1][c - 1];
    if (!((tr == 'M' && bl == 'S') || (tr == 'S' && bl == 'M')))
        return 0;

    return 1;
}

int main()
{
    read_grid();
    int total = 0;

    for (int r = 1; r < ROWS - 1; r++)
    {
        for (int c = 1; c < COLS - 1; c++)
        {
            total += check_xmas(r, c);
        }
    }

    printf("%d\n", total);
    return 0;
}