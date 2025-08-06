#include "recursive.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 8 // ���� üũ���� ũ�� (8 x 8)
bool flag_a[SIZE]; // �� �࿡ ���� ��ġ�ߴ��� üũ�ϴ� �迭 (T / F)
bool flag_b[SIZE * 2 - 1]; // �밢�� '/'�� ���� ��ġ�ߴ��� üũ�ϴ� �迭 (T / F)
bool flag_c[SIZE * 2 - 1]; // �밢�� '\'�� ���� ��ġ�ߴ��� üũ�ϴ� �迭 (T / F)
int position[SIZE]; // ���� �� ���� ���� ��� �࿡ ��ġ���ִ��� üũ�ϴ� �迭 (���� row��ġ)
int count = 0; // ü������ ��ä�� Ƚ�� (����� ��)

// ���� ���� ��ġ�� ���
void n_queen_print() {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", position[i]);
    }
    printf("\n");
}

/// SIZE ũ�⸸ŭ�� ü���ǿ� ���� ������ �� ������ ���� ���� ��� ���
/// col: ���� ��ġ�ϰ� �ִ� ��
void n_queen(int col) {
    // ���翭�� ��� �࿡ ���ؼ� ���� ���� �� �ִ��� �˻��Ѵ�
    for (int row = 0; row < SIZE; row++) {
        // flag_a[col]: ���� (row, col)�� ���� �����ִ°�?
        // flag_b[row + col]: ���� row, col �ڸ��� ��ġ�� '/' �ڸ��� ���� �ִ°�?
        // flag_c[7 - row + col]: ���� row, col �ڸ��� ��ġ�� '\' �ڸ��� ���� �ִ°�?
        // �� �˻��� �ôµ� ���� ������
        if (!flag_a[row] && !flag_b[row + col] && !flag_c[7 - row + col]) {
            position[col] = row; //���� (row, col) ��ġ�� ���� ����
            // ���� ���Ҵµ� ������ �� ��ġ�� ���Ҵٸ�, ��� ���� ��ġ�� ��ģ ��
            if (col == SIZE - 1) {
                n_queen_print();
                count++; // ���� ��� + 1
            }
            // ���� col�� �� ä������ �ʾҴٸ�
            else {
                // ���� ���� �� ��ġ�� ���� ���� �ִ� ��� ��ġ�� ���� �����Ѵٰ� ����
                flag_a[row] = flag_b[row + col] = flag_c[7 - row + col] = true;
                n_queen(col + 1);
                // �ٷ� ���ٿ��� ���� ���� ���� �� ���� ������ col���� ���� �� ��� �κ��� ���
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

// a�� b�� �ִ� ������� ���ϱ�
int gcd(int a, int b) {
    if (a % b == 0) return b;
    return gcd(b, a % b);
}
// �ּҰ���� = �� �� �� / �ִ�����
int lcm(int a, int b) {
    return a * b / gcd(a, b);
}
// goal: ���� ���ϴ� ��
// n: ���� ��
// n1, n2: ���� �� ����
int pibonacci(int n1, int n2, int n, int goal) {
    if (n == goal) { // ���ϴ� �׿� �����Ͽ���
        return n2;
    }
    return pibonacci(n2, n1 + n2, n + 1, goal);
}
#define GOAL 5
void pibonacci_arr(int goal) {
    int arr[goal];
    arr[0] = 1; // 1��° ��
    arr[1] = 1; // 2��° ��
    // 3��° �׺��� ���� �ִ´�
    for (int i = 2; i < goal; i++) {
        arr[i] = arr[i-1] + arr[i-2];
    }
    printf("%d\n", arr[goal-1]);
}

void hanoi_tower_move(int n, char from, char by, char to) {
    if (n == 1) {
        printf("���� [%d]�� %c => %c�� �̵�\n",n, from, to);
    }else {
        // ���� 1���� A���� (C�� ���ļ�) B�� �̵����Ѷ�
        hanoi_tower_move(n-1, from, to, by);
        printf("���� [%d]�� %c => %c�� �̵�\n",n, from, to);
        hanoi_tower_move(n-1, by, from, to);
    }
}

// n��° ������ x��տ��� y������� �ű��
// x,y : A,B,C ����� �ǹ�
// x: 'A' == 1, 'B' == 2, y: 'C' == 3
void hanoi_tower(int n, int x, int y) {
    if (n > 1) {
        hanoi_tower(n - 1, x, 6 - x - y); // �ϳ��� �׷��� ���۱�տ��� �߰� �������
    }
    printf("���� [%d]�� %d���� %d�� �Ű�� \n", n, x, y);
    if (n > 1) {
        hanoi_tower(n - 1, 6 - x - y, y); // �׷��� �߰� ��տ��� ��ǥ �������
    }
}

///// 'ABC'
// 'ABC'���� �ߺ��� ����ؼ� ���� �� �ִ� 3���� ������?
// => AAA, AAB, AAC, ABA, ABB, ... CCC
/// A ���� AA AAA , AB ABA .. �̷������� ori�� ���ڿ��� ���ͼ� result�� �ϳ��� ���ڸ� ���δ�
/// ori: ������ ������ �������� ���ڿ� 'ABC' (���⼭ �ϳ��� ������. ������.)
/// result: ������ �� ���ο� ���ڿ�
/// len: ���� ������ �� result�� ����ڱ��� ������� �ִ��� Ȯ���ϴ� �뵵 (���� len�� result�� index�� �ȴ�)
void duplicated_combination(char* ori, char* result, int len) { // �ߺ� ����ϴ� ����
    printf("%s\n", result);
    if (len == 3) { // ���� ��ǥ�ϴ� ���ڼ����� ���ڿ��� �����Ǿ��ٸ�
        return;
    }
    // �ش� ���� ũ�⸸ŭ�� ���ڿ��� �ϳ� �����
    char* new_len = (char*)calloc(len, sizeof(char));
    // ���ο� ���ڿ��� ���ݱ����� ���ڿ��� �Ű� ��´�
    for (int i = 0; i < len; i++) {
        new_len[i] = result[i];
    }
    // ori ���ڿ��� ��ȸ�ϸ鼭 ���ο� result�� �� ���ڿ��� �ѱ��ھ� �ڿ� ���δ�
    for (int i = 0; i < 3; i++) {
        new_len[len] = ori[i];
        duplicated_combination(ori, new_len, len + 1);
    }
}
// 'AABBCC'
// 'ABC'���� �ߺ��� ������� �ʰ�, ���� �� �ִ� 3���� ������? (����) 3! = 6��
// => ABC, ACB, BAC, BCA, CAB, CBA
// => AB, AC, BA, BC, CA, CB
void permutation(char* ori, char* result, bool* visited, int len) {
    // ���� ������� ���� ���ڰ� �ִ��� visited�� üũ
    bool flag = true;
    for (int i = 0; i < strlen(visited); i++) {
        if (!visited[i]) {
            flag = false;
        }
    }
    // ��� ���ڸ� ����ߴٸ�
    if (flag) {
        printf("%s\n", result); // ���
        return;
    }

    // ori ���ڿ��� ��ȸ�ϸ鼭 ���ο� result�� �� ���ڿ��� �ѱ��ھ� �ڿ� ���δ�
    for (int i = 0; i < strlen(ori); i++) {
        if (!visited[i]) {
            // ���ݱ����� �湮�� ��������� ���ο� �迭�� �Űܴ���
            bool* new_visited = (bool*)calloc(len, sizeof(bool));
            char* new_result = (char*)calloc(len, sizeof(char));
            memcpy(new_visited, visited, strlen(visited) * sizeof(bool));
            memcpy(new_result, result, strlen(result) * sizeof(char));

            new_result[len] = ori[i]; // ���� ���ڸ� ����� ���δ�
            new_visited[i] = true; // ���� ���ڸ� ����ߴٰ� üũ

            // �Űܴ��� ���ο� �迭�� �����ؼ� ���� ������ ����
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
    // 3���� ������ 'A'���� 'C'�� �ű�ڴ�
    // hanoi_tower(3, 1, 3);
    // hanoi_tower_move(3, 'A', 'B', 'C');
    /*****************************************************/
    // n_queen(0); // ������ ������ 0������
    // printf("��� ����� ��: %d��\n", count);
    /*****************************************************/
    // duplicated_combination("ABC", (char*)calloc(3, sizeof(char)), 0);
    permutation(
        "ABC",
        (char*)calloc(3, sizeof(char)),
        (bool*)calloc(3, sizeof(bool)),
        0);
}


