/*

Problem_Solving_time PM 03:15 - 03:45

1 : sk // ������ sk

2 : 1 1 -> cy // ������ cy

3 : 3 -> sk // ������ sk 
2 1 -> sk


4 : 4 -> sk



5 : 3 1 1 -> sk

6 : 4 1 1 -> sk

7 
: 4 3 -> cy
: 3 4 -> cy
: 1 4 1 1 -> cy
������ cy

�׷� 7�� ��� �Ǵ� 7�� ����� 2�� ����

������ ������ cy���� �� �� �����Ƿ�,

�̿� ���� ���� ����.

*/

#include<stdio.h>
#pragma warning(disable:4996)

int main(long long n) {
    scanf("%lld", &n);
    printf("%s", (n % 7 == 0 || n % 7 == 2) ? "CY" : "SK");
    return 0;
}