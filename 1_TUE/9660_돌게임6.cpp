/*

Problem_Solving_time PM 03:15 - 03:45

1 : sk // 무조건 sk

2 : 1 1 -> cy // 무조건 cy

3 : 3 -> sk // 무조건 sk 
2 1 -> sk


4 : 4 -> sk



5 : 3 1 1 -> sk

6 : 4 1 1 -> sk

7 
: 4 3 -> cy
: 3 4 -> cy
: 1 4 1 1 -> cy
무조건 cy

그럼 7의 배수 또는 7의 배수에 2를 더한

정수가 무조건 cy임을 알 수 있으므로,

이에 맞춰 조건 설정.

*/

#include<stdio.h>
#pragma warning(disable:4996)

int main(long long n) {
    scanf("%lld", &n);
    printf("%s", (n % 7 == 0 || n % 7 == 2) ? "CY" : "SK");
    return 0;
}