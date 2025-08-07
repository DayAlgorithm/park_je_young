#ifdef _MSC_VER
#define getchar_unlocked _getchar_nolock
#endif
//By_Using_GNU
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int getNum(void) {
    int c, n = 0;
    while ((c = getchar_unlocked()) < '0');
    do {
        n = n*10 + (c - '0');
        c = getchar_unlocked();
    } while (c >= '0' && c <= '9');
    return n;
}// Using this function at main-bodyline 

int countPeople(char *map, int width, int *q, int start) {
    int front = 0, rear = 0, cnt = 0;
    q[rear++] = start;
    map[start] = 'X';

    while (front < rear) {
        int pos = q[front++];
        int np;
        np = pos + 1;
		//R -> L -> U -> D
        if (map[np] != 'X') {
            if (map[np] == 'P') cnt++;
            map[np] = 'X';
            q[rear++] = np;
        }
        np = pos - 1;
        if (map[np] != 'X') {
            if (map[np] == 'P') cnt++;
            map[np] = 'X';
            q[rear++] = np;
        }
        np = pos + width;
        if (map[np] != 'X') {
            if (map[np] == 'P') cnt++;
            map[np] = 'X';
            q[rear++] = np;
        }
        np = pos - width;
        if (map[np] != 'X') {
            if (map[np] == 'P') cnt++;
            map[np] = 'X';
            q[rear++] = np;
        }
    }
    return cnt;
}

int main(void) {
    int N = getNum(), M = getNum();
    int width = M + 1, height = N + 2;
	//Literally, Make Total size
    size_t total = (size_t)width * height;

    char *map = (char*)malloc(total);
    memset(map, 'X', width);
    fread(map + width, 1, (size_t)N * width, stdin);
    for (int i = 1; i <= N; i++) {
        map[i*width - 1] = 'X';
    }
    memset(map + (size_t)(N+1) * width, 'X', width);

    int start = 0;

    for (size_t i = width; i < width*(N+1); i++) {
        if (map[i] == 'I') { start = (int)i; break; }
    }

    int *q = (int*)malloc((size_t)N * M * sizeof(int));
    int friends = countPeople(map, width, q, start);
	// Counting_Real_Friends

    if (friends > 0) {

        char buf[12]; int len = 0;
        char tmp[12]; int tl = 0;

        while (friends) {
            tmp[tl++] = '0' + (friends % 10);
            friends /= 10;
        }

        if (!tl) tmp[tl++] = '0';

        while (tl--) buf[len++] = tmp[tl];
		//Count

        buf[len] = '\0';

        fputs(buf, stdout);

    } else {
        fputs("TT", stdout);
    }

    free(map);
    free(q);
    return 0;
}
