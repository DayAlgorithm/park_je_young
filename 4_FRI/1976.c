#include <stdio.h>
unsigned char parent[200];
unsigned char queue[1000];

unsigned char find(unsigned char A[], short x) {
    return A[x] == x ? x : (A[x] = find(A, A[x]));
}

void unite(unsigned char A[], short i, short j) {
    unsigned char Ri = find(A, i);
    unsigned char Rj = find(A, j);

    if(Ri != Rj) A[Rj] = Ri;
}

int main(void) {
    short n, m;
    scanf("%hd %hd", &n, &m);

    for(short i = 0; i < n; i++) {
        parent[i] = i;
    }
    for(short i = 0; i < n; i++) {
        for(short j = 0; j < n; j++) {
            short connection;
            scanf("%hd", &connection);
            if(connection == 1 && j > i) {
                unite(parent, i, j);
            }
        }
    }
    for(short u = 0; u < m; u++) {
        short temp_city;
        scanf("%hd", &temp_city);
        queue[u] = (unsigned char)(temp_city - 1); 
    }

    char condition = 0;
    for(short x = 0, y = 1; y < m; x++, y++) {
        if(find(parent, queue[x]) != find(parent, queue[y])) {
            condition = 1;
            break;
        }
    }
    printf("%s", (condition ? "NO" : "YES"));
    return 0;
}