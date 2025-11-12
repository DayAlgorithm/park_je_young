#include <stdio.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX3(a, b, c) MAX(MAX(a, b), c)
#define MIN3(a, b, c) MIN(MIN(a, b), c)

static inline int readInt() {
    int res = 0;
    int c = getchar();
    
    while (c < '0' || c > '9') {
        c = getchar();
    }

    while (c >= '0' && c <= '9') {
        res = res * 10 + (c - '0');
        c = getchar();
    }
    return res;
}

int main() {
    int n = readInt();

    int prevMax[3], prevMin[3];
    int currMax[3], currMin[3];
    int a, b, c;

    prevMax[0] = readInt();
    prevMax[1] = readInt();
    prevMax[2] = readInt();
    memcpy(prevMin, prevMax, sizeof(prevMax));

    for (int i = 1; i < n; i++) {
        a = readInt();
        b = readInt();
        c = readInt();

        currMax[0] = a + MAX(prevMax[0], prevMax[1]);
        currMax[1] = b + MAX3(prevMax[0], prevMax[1], prevMax[2]);
        currMax[2] = c + MAX(prevMax[1], prevMax[2]);

        currMin[0] = a + MIN(prevMin[0], prevMin[1]);
        currMin[1] = b + MIN3(prevMin[0], prevMin[1], prevMin[2]);
        currMin[2] = c + MIN(prevMin[1], prevMin[2]);

        memcpy(prevMax, currMax, sizeof(currMax));
        memcpy(prevMin, currMin, sizeof(currMin));
    }
    int answerMax = MAX3(prevMax[0], prevMax[1], prevMax[2]);
    int answerMin = MIN3(prevMin[0], prevMin[1], prevMin[2]);

    printf("%d %d", answerMax, answerMin);

    return 0;
}