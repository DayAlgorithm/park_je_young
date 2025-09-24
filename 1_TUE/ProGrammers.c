#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


int returnTime(const char* r[]){
    
}

char* returnNumber(const char* r[]){
    char tmp[4] = { 0 };
    for(int u = 0; u < 4; u++){
        char tmp[u] = r[6 - u];
    }
    return pos;
}

int RNTI(const char* numbers[]){
    int s = 0;
    for(int i = 0; i < 4; i++){
        s = s*10 + (number[i] - '0');
    } return s;
}

int* solution(int fees[], size_t fees_len, const char* records[], size_t records_len) {

    int* answer = (int*)malloc(1);
    
    /*
        fee[i]
            i = 0 : 기본 시간
            i = 1 : 기본 요금
            i = 2 : 단위 시간
            i = 3 : 단위 요금
            records : <시각> <차량번호> <내역>
                    : <HH:MM> <XXXX> <IN, OUT>
    */
    
    int carInfo[10000][2] = {0}; // carInfo[차량번호][0 : IN / 1 : OUT]
    
    int sz = (int)records_len;
    
    for(int i = 0 ; i < sz - 1; i++){
        char pos[4] = { 0 };
        pos = returnNumber(records);
        for(int j = i + 1; j < sz; j++){
            char tmp[4] = { 0 };
            tmp = returnNumber(records);
            if(strcmp(pos, tmp) == 1){
                int carNumber = RNTI(tmp);
                // 시간 차분 계산.
                carInfo[carNumber][0] = records
                break;
            }
        }
    }
    
    //
    
    return answer;
}