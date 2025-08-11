#include <stdio.h>
#include <stdlib.h>

#define MAXN 8
#define MAXCCTV 64

typedef struct { int r, c, t; } CCTV;

int N, M;
int A[MAXN][MAXN];
int cover[MAXN][MAXN];
CCTV cams[MAXCCTV];
int cam_cnt = 0;

int empty_total = 0;
int covered = 0;
int best = 1<<30;

const int dr[4] = {-1, 0, 1, 0}; // 상,우,하,좌
const int dc[4] = { 0, 1, 0,-1};

static inline int branch_cnt(int t){
    switch(t){
        case 1: return 4;
        case 2: return 2;
        case 3: return 4;
        case 4: return 4;
        case 5: return 1;
        default: return 0;
    }
}

const int dir_len[6][4] = {
/*0*/ {0,0,0,0},
/*1*/ {1,1,1,1},
/*2*/ {2,2,0,0},
/*3*/ {2,2,2,2},
/*4*/ {3,3,3,3},
/*5*/ {4,0,0,0}
};

const int dir_map[6][4][4] = {
/*0*/ {{0}},
/*1*/ {{0},{1},{2},{3}},
/*2*/ {{0,2},{1,3}},
/*3*/ {{0,1},{1,2},{2,3},{3,0}},
/*4*/ {{0,1,2},{1,2,3},{2,3,0},{3,0,1}},
/*5*/ {{0,1,2,3}}
};

static void paint_line(int r, int c, int d, int delta){
    int nr = r + dr[d], nc = c + dc[d];
    while (0 <= nr && nr < N && 0 <= nc && nc < M && A[nr][nc] != 6) {
        if (A[nr][nc] == 0) {
            if (delta == +1) {
                if (cover[nr][nc] == 0) covered++;
                cover[nr][nc] += 1;
            } else {
                cover[nr][nc] -= 1;
                if (cover[nr][nc] == 0) covered--;
            }
        }
        nr += dr[d]; nc += dc[d];
    }
}

static void apply_cctv(int r, int c, int t, int ori, int delta){
    int k, len = dir_len[t][ori];
    for (k = 0; k < len; k++) {
        int d = dir_map[t][ori][k];
        paint_line(r, c, d, delta);
    }
}

static int cmp_branch(const void* a, const void* b){
    const CCTV *x = (const CCTV*)a, *y = (const CCTV*)b;
    int bx = branch_cnt(x->t), by = branch_cnt(y->t);
    if (bx != by) return bx - by;
    return 0;
}

static void dfs(int idx){
    if (idx == cam_cnt){
        int blind = empty_total - covered;
        if (blind < best) best = blind;
        return;
    }
    int r = cams[idx].r, c = cams[idx].c, t = cams[idx].t;

    int tried = 0;
    for (int ori = 0; ori < 4; ori++){
        int len = dir_len[t][ori];
        if (len == 0) continue;
        // 안되는 회전은 스킵
        tried++;
        apply_cctv(r, c, t, ori, +1);
        dfs(idx + 1);
        apply_cctv(r, c, t, ori, -1);
    }
}

int main(void){

    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            scanf("%d", &A[i][j]);
            if (A[i][j] == 0) empty_total++;
            else if (1 <= A[i][j] && A[i][j] <= 5){
                cams[cam_cnt].r = i;
                cams[cam_cnt].c = j;
                cams[cam_cnt].t = A[i][j];
                cam_cnt++;
            }
        }
    }

    // 작은 분기 카메라만 따로 뺀다.
    qsort(cams, cam_cnt, sizeof(CCTV), cmp_branch);

    dfs(0);
    printf("%d\n", best);
    return 0;
}
