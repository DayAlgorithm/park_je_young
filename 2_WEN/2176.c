#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000
#define MAXIMIZE 2147483647

typedef struct {
    int to;
    int w;
    int next;
} Edge;

int nodeCount, edgeCount;
int *headPtr;
Edge *edges;
int edgeIndex;

int *distToTarget;
int *heapNode, *heapDist, heapSize;
long long *waysCount;
int *orderIndex;

void addEdge(int u, int v, int w) {
    edges[edgeIndex].to = v;
    edges[edgeIndex].w = w;
    edges[edgeIndex].next = headPtr[u];
    headPtr[u] = edgeIndex++;
}

void swapHeap(int i, int j) {
    int tn = heapNode[i], td = heapDist[i];
    heapNode[i] = heapNode[j]; 
    heapDist[i] = heapDist[j];
    heapNode[j] = tn; 
    heapDist[j] = td;
}

void pushHeap(int node, int dist) {
    int i = ++heapSize;//1based
    heapNode[i] = node;
    heapDist[i] = dist;
    while (i > 1) {
        int p = i >> 1;
        if (heapDist[p] <= heapDist[i]) break;
        swapHeap(p, i);
        i = p;
    }
}

int popHeap(int *node, int *dist) {
    if (heapSize == 0) return 0;
    *node = heapNode[1]; 
    *dist = heapDist[1];
    heapNode[1] = heapNode[heapSize];
    heapDist[1] = heapDist[heapSize];
    heapSize--;
    int i = 1;
    while (1) {
        int l = i << 1, r = l + 1, m = i;
        if (l <= heapSize && heapDist[l] < heapDist[m]) 
            m = l;
        if (r <= heapSize && heapDist[r] < heapDist[m]) 
            m = r;
        if (m == i) break;
        swapHeap(i, m);
        i = m;
    }
    return 1;
}

void runDijkstraFromTarget(int target) {
    for (int i = 1; i <= nodeCount; i++) distToTarget[i] = INF;
    heapSize = 0;
    distToTarget[target] = 0;
    pushHeap(target, 0);
    while (heapSize) {
        int u, d;
        popHeap(&u, &d);
        if (d != distToTarget[u]) continue;
        for (int ei = headPtr[u]; ei != -1; ei = edges[ei].next) {
            int v = edges[ei].to;
            int nd = d + edges[ei].w;
            if (nd < distToTarget[v]) {
                distToTarget[v] = nd;
                pushHeap(v, nd);
            }
        }
    }
}

int cmpIndexByDist(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    int da = distToTarget[ia];
    int db = distToTarget[ib];
    if (da < db) return -1;
    if (da > db) return 1;
    return ia - ib;
}

void allocation() {
    headPtr = (int*)malloc((nodeCount + 1) * sizeof(int));
    edges = (Edge*)malloc((edgeCount * 2 + 5) * sizeof(Edge));
    distToTarget = (int*)malloc((nodeCount + 1) * sizeof(int));
    waysCount = (long long*)malloc((nodeCount + 1) * sizeof(long long));
    orderIndex = (int*)malloc((nodeCount + 1) * sizeof(int));
    heapNode = (int*)malloc((2 * edgeCount + nodeCount + 20) * sizeof(int));
    heapDist = (int*)malloc((2 * edgeCount + nodeCount + 20) * sizeof(int));
}

int main(void) {
    scanf("%d %d", &nodeCount, &edgeCount);

    allocation();

    for (int i = 1; i <= nodeCount; i++) 
        headPtr[i] = -1;
    edgeIndex = 0;

    for (int i = 0; i < edgeCount; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        addEdge(a, b, c);
        addEdge(b, a, c);
    }

    runDijkstraFromTarget(2);

    for (int i = 1; i <= nodeCount; i++) 
        orderIndex[i] = i;
    qsort(orderIndex + 1, nodeCount, sizeof(int), cmpIndexByDist);

    for (int i = 1; i <= nodeCount; i++) waysCount[i] = 0;

    waysCount[2] = 1;

    for (int k = 1; k <= nodeCount; k++) {
        int u = orderIndex[k];
        if (distToTarget[u] == INF) continue;
        for (int ei = headPtr[u]; ei != -1; ei = edges[ei].next) {
            int v = edges[ei].to;
            if (distToTarget[v] > distToTarget[u]) {
                waysCount[v] += waysCount[u];
                if (waysCount[v] > MAXIMIZE) 
                    waysCount[v] = MAXIMIZE;
            }
        }
    }

    printf("%d", (int)waysCount[1]);

    free(headPtr);
    free(edges);
    free(distToTarget);
    free(waysCount);
    free(orderIndex);
    free(heapNode);
    free(heapDist);
    return 0;
}
