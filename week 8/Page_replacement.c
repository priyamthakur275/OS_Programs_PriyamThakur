#include <stdio.h>
#include <stdbool.h>

#define MAX_REF  100      /* maximum reference‑string length   */
#define MAX_FRM  20       /* maximum number of page frames     */


int read_reference(int ref[])
{
    int n = 0;
    printf("Enter reference string (space‑separated, -1 to end): ");
    while (n < MAX_REF)
    {
        int x;
        if (scanf("%d", &x) != 1 || x == -1) break;
        ref[n++] = x;
    }
    return n;
}


int find(int frames[], int fcount, int page)
{
    for (int i = 0; i < fcount; ++i)
        if (frames[i] == page)
            return i;
    return -1;
}

/* FIFO algorithm */
int fifo(int ref[], int len, int fcount)
{
    int frames[MAX_FRM];
    for (int i = 0; i < fcount; ++i) frames[i] = -1;
    int next = 0, faults = 0;

    for (int i = 0; i < len; ++i)
    {
        if (find(frames, fcount, ref[i]) == -1)
        {
            /* replace oldest */
            frames[next] = ref[i];
            next = (next + 1) % fcount;
            ++faults;
        }
    }
    return faults;
}

/* LRU algorithm */
int lru(int ref[], int len, int fcount)
{
    int frames[MAX_FRM], lastUsed[MAX_FRM];
    for (int i = 0; i < fcount; ++i) { frames[i] = -1; lastUsed[i] = -1; }

    int faults = 0;
    for (int t = 0; t < len; ++t)
    {
        int page = ref[t];
        int idx = find(frames, fcount, page);

        if (idx != -1)
        {
            lastUsed[idx] = t;            
        }
        else
        {                                   
            int victim = 0;
            for (int i = 1; i < fcount; ++i)
                if (frames[i] == -1 || lastUsed[i] < lastUsed[victim])
                    victim = i;
            frames[victim] = page;
            lastUsed[victim] = t;
            ++faults;
        }
    }
    return faults;
}

/* Optimal algorithm */
int optimal(int ref[], int len, int fcount)
{
    int frames[MAX_FRM];
    for (int i = 0; i < fcount; ++i) frames[i] = -1;

    int faults = 0;
    for (int t = 0; t < len; ++t)
    {
        int page = ref[t];
        if (find(frames, fcount, page) != -1) continue; 

        /
        int victim = -1, farthest = -1;
        for (int i = 0; i < fcount; ++i)
        {
            int nextUse = -1;
            for (int j = t + 1; j < len; ++j)
                if (ref[j] == frames[i]) { nextUse = j; break; }

            if (frames[i] == -1) { victim = i; break; }      
            if (nextUse == -1) { victim = i; break; }        
            if (nextUse > farthest) { farthest = nextUse; victim = i; }
        }
        frames[victim] = page;
        ++faults;
    }
    return faults;
}

int main(void)
{
    int ref[MAX_REF], len, frames;

    len = read_reference(ref);
    if (len == 0) { puts("Empty reference string."); return 0; }

    printf("Number of frames (<= %d): ", MAX_FRM);
    scanf("%d", &frames);

    int f_fifo = fifo(ref, len, frames);
    int f_lru  = lru (ref, len, frames);
    int f_opt  = optimal(ref, len, frames);

    puts("\nPage‑fault counts:");
    printf(" FIFO   : %d\n", f_fifo);
    printf(" LRU    : %d\n", f_lru);
    printf(" Optimal: %d\n", f_opt);

    return 0;
}
/* output :

$ gcc pager.c -o pager
$ ./pager
Enter reference string (space‑separated, -1 to end): 7 0 1 2 0 3 0 4 2 3 0 3 2 -1
Number of frames (<= 20): 3

Page‑fault counts:
 FIFO   : 9
 LRU    : 9
 Optimal: 7
*/
