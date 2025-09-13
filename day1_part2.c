#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAXN 100000

// Simple hash table for counting frequencies
typedef struct Node
{
    int key;
    int count;
    struct Node *next;
} Node;

#define HASH_SIZE 131071 // a large prime for hashing

static Node *table[HASH_SIZE];

unsigned hash_int(int x)
{
    // Simple integer hash
    return ((unsigned)x * 2654435761u) % HASH_SIZE;
}

void add_count(int key)
{
    unsigned h = hash_int(key);
    Node *p = table[h];
    while (p)
    {
        if (p->key == key)
        {
            p->count++;
            return;
        }
        p = p->next;
    }
    // new entry
    Node *n = malloc(sizeof(Node));
    n->key = key;
    n->count = 1;
    n->next = table[h];
    table[h] = n;
}

int get_count(int key)
{
    unsigned h = hash_int(key);
    Node *p = table[h];
    while (p)
    {
        if (p->key == key)
            return p->count;
        p = p->next;
    }
    return 0;
}

int main(void)
{
    int left[MAXN], right[MAXN];
    int n = 0;

    // Read input until EOF
    while (scanf("%d %d", &left[n], &right[n]) == 2)
    {
        n++;
        if (n >= MAXN)
        {
            fprintf(stderr, "Increase MAXN for larger input.\n");
            return 1;
        }
    }

    // Build frequency table of right-list numbers
    for (int i = 0; i < n; i++)
    {
        add_count(right[i]);
    }

    // Compute similarity score
    long long score = 0;
    for (int i = 0; i < n; i++)
    {
        int freq = get_count(left[i]);
        score += (long long)left[i] * freq;
    }

    printf("%lld\n", score);
    return 0;
}