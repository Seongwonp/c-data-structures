#include "recursive.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 8 // 현재 체크판의 크기 (8 x 8)
bool flag_a[SIZE]; // 각 행에 퀸을 배치했는지 체크하는 배열 (T / F)
bool flag_b[SIZE * 2 - 1]; // 대각선 '/'에 퀸을 배치했는지 체크하는 배열 (T / F)
bool flag_c[SIZE * 2 - 1]; // 대각선 '\'에 퀸을 배치했는지 체크하는 배열 (T / F)
int position[SIZE]; // 현재 각 열에 퀸이 어느 행에 위치해있는지 체크하는 배열 (실제 row위치)
int count = 0; // 체스판을 꽉채운 횟수 (방법의 수)

// 현재 퀸의 배치를 출력
void n_queen_print() {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", position[i]);
    }
    printf("\n");
}

/// SIZE 크기만큼의 체스판에 서로 공격할 수 없도록 퀸을 놓는 모든 방법
/// col: 현재 배치하고 있는 열
void n_queen(int col) {
    // 현재열의 모든 행에 대해서 퀸을 놓을 수 있는지 검사한다
    for (int row = 0; row < SIZE; row++) {
        // flag_a[col]: 현재 (row, col)에 퀸이 놓여있는가?
        // flag_b[row + col]: 현재 row, col 자리와 겹치는 '/' 자리에 퀸이 있는가?
        // flag_c[7 - row + col]: 현재 row, col 자리와 겹치는 '\' 자리에 퀸이 있는가?
        // 다 검사해 봤는데 퀸이 없더라
        if (!flag_a[row] && !flag_b[row + col] && !flag_c[7 - row + col]) {
            position[col] = row; //현재 (row, col) 위치에 퀸을 놓음
            // 퀸을 놓았는데 마지막 열 위치에 놓았다면, 모든 열에 배치를 마친 것
            if (col == SIZE - 1) {
                n_queen_print();
                count++; // 놓는 방법 + 1
            }
            // 아직 col이 다 채워지지 않았다면
            else {
                // 현재 놓은 퀸 위치와 동일 선상에 있는 모든 위치에 퀸이 존재한다고 설정
                flag_a[row] = flag_b[row + col] = flag_c[7 - row + col] = true;
                n_queen(col + 1);
                // 바로 윗줄에서 새로 퀸을 놓은 것 포함 다음의 col으로 갔다 온 모든 부분을 취소
                flag_a[row] = flag_b[row + col] = flag_c[7 - row + col] = false;
            }
        }
    }
}


// 5! = 5 * 4 * 3 * 2 * 1
// n = 5
int factorial(int n) {
    if (n == 1) return 1;
    return n * factorial(n - 1);
}

// a와 b의 최대 공약수를 구하기
int gcd(int a, int b) {
    if (a % b == 0) return b;
    return gcd(b, a % b);
}
// 최소공배수 = 두 수 곱 / 최대공약수
int lcm(int a, int b) {
    return a * b / gcd(a, b);
}
// goal: 내가 원하는 항
// n: 현재 항
// n1, n2: 현재 두 숫자
int pibonacci(int n1, int n2, int n, int goal) {
    if (n == goal) { // 원하는 항에 도달하였음
        return n2;
    }
    return pibonacci(n2, n1 + n2, n + 1, goal);
}
#define GOAL 5
void pibonacci_arr(int goal) {
    int arr[goal];
    arr[0] = 1; // 1번째 항
    arr[1] = 1; // 2번째 항
    // 3번째 항부터 값을 넣는다
    for (int i = 2; i < goal; i++) {
        arr[i] = arr[i-1] + arr[i-2];
    }
    printf("%d\n", arr[goal-1]);
}

void hanoi_tower_move(int n, char from, char by, char to) {
    if (n == 1) {
        printf("원판 [%d]를 %c => %c로 이동\n",n, from, to);
    }else {
        // 원판 1개를 A에서 (C를 거쳐서) B로 이동시켜라
        hanoi_tower_move(n-1, from, to, by);
        printf("원판 [%d]를 %c => %c로 이동\n",n, from, to);
        hanoi_tower_move(n-1, by, from, to);
    }
}

// n번째 원반을 x기둥에서 y기둥으로 옮긴다
// x,y : A,B,C 기둥을 의미
// x: 'A' == 1, 'B' == 2, y: 'C' == 3
void hanoi_tower(int n, int x, int y) {
    if (n > 1) {
        hanoi_tower(n - 1, x, 6 - x - y); // 하나의 그룹을 시작기둥에서 중간 기둥으로
    }
    printf("원판 [%d]를 %d에서 %d로 옮겼다 \n", n, x, y);
    if (n > 1) {
        hanoi_tower(n - 1, 6 - x - y, y); // 그룹을 중간 기둥에서 목표 기둥으로
    }
}

///// 'ABC'
// 'ABC'에서 중복을 허용해서 만들 수 있는 3글자 조합은?
// => AAA, AAB, AAC, ABA, ABB, ... CCC
/// A 부터 AA AAA , AB ABA .. 이런식으로 ori의 문자열을 빼와서 result에 하나씩 문자를 붙인다
/// ori: 조합을 생성할 오리지널 문자열 'ABC' (여기서 하나씩 가져옴. 고정임.)
/// result: 정답이 될 새로운 문자열
/// len: 현재 정답이 될 result가 몇글자까지 만들어져 있는지 확인하는 용도 (현재 len이 result의 index가 된다)
void duplicated_combination(char* ori, char* result, int len) { // 중복 허용하는 조합
    printf("%s\n", result);
    if (len == 3) { // 내가 목표하는 글자수까지 문자열이 생성되었다면
        return;
    }
    // 해당 글자 크기만큼의 문자열을 하나 만든다
    char* new_len = (char*)calloc(len, sizeof(char));
    // 새로운 문자열에 지금까지의 문자열을 옮겨 담는다
    for (int i = 0; i < len; i++) {
        new_len[i] = result[i];
    }
    // ori 문자열을 순회하면서 새로운 result가 될 문자열에 한글자씩 뒤에 붙인다
    for (int i = 0; i < 3; i++) {
        new_len[len] = ori[i];
        duplicated_combination(ori, new_len, len + 1);
    }
}
// 'AABBCC'
// 'ABC'에서 중복을 허용하지 않고, 만들 수 있는 3글자 조합은? (순열) 3! = 6개
// => ABC, ACB, BAC, BCA, CAB, CBA
// => AB, AC, BA, BC, CA, CB
void permutation(char* ori, char* result, bool* visited, int len) {
    // 아직 사용하지 않은 문자가 있는지 visited로 체크
    bool flag = true;
    for (int i = 0; i < strlen(visited); i++) {
        if (!visited[i]) {
            flag = false;
        }
    }
    // 모든 문자를 사용했다면
    if (flag) {
        printf("%s\n", result); // 출력
        return;
    }

    // ori 문자열을 순회하면서 새로운 result가 될 문자열에 한글자씩 뒤에 붙인다
    for (int i = 0; i < strlen(ori); i++) {
        if (!visited[i]) {
            // 지금까지의 방문과 결과까지를 새로운 배열에 옮겨담음
            bool* new_visited = (bool*)calloc(len, sizeof(bool));
            char* new_result = (char*)calloc(len, sizeof(char));
            memcpy(new_visited, visited, strlen(visited) * sizeof(bool));
            memcpy(new_result, result, strlen(result) * sizeof(char));

            new_result[len] = ori[i]; // 현재 문자를 결과에 붙인다
            new_visited[i] = true; // 현재 문자를 사용했다고 체크

            // 옮겨담은 새로운 배열을 전달해서 문자 조합을 생성
            permutation(ori, new_result, new_visited, len + 1);
        }
    }
}




int main() {
    char c[5] = {'a','b','c','d','\0'};
    /*****************************************************/
    // int result = factorial(5);
    // printf("%d\n", result);
    /*****************************************************/
    // result = gcd(12, 6);
    // printf("%d\n", result);
    // result = lcm(12, 6);
    // printf("%d\n", result);
    /*****************************************************/
    // result = pibonacci(1, 1, 2, 30);
    // printf("%d\n", result);
    // pibonacci_arr(30);
    /*****************************************************/
    // 3개의 원판을 'A'에서 'C'로 옮기겠다
    // hanoi_tower(3, 1, 3);
    // hanoi_tower_move(3, 'A', 'B', 'C');
    /*****************************************************/
    // n_queen(0); // 시작은 무조건 0열부터
    // printf("모든 방법의 수: %d개\n", count);
    /*****************************************************/
    // duplicated_combination("ABC", (char*)calloc(3, sizeof(char)), 0);
    permutation(
        "ABC",
        (char*)calloc(3, sizeof(char)),
        (bool*)calloc(3, sizeof(bool)),
        0);
}


