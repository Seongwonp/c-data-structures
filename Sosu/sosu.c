#include <math.h>
#include <stdio.h>
// 1 ~ 100 ������ ���� �� �Ҽ��� print
void bruteforce() {
    puts(" == Brute force �Ҽ� Ž�� == ");
    int count = 0; // ����Ƚ��
    // 1 ~ 100����
    for (int i = 2; i <= 100000; i++) {
        // ���� ���ڰ� �Ҽ��ΰ�?
        int flag = 1; // �ϴ�, ���� ���ڴ� �Ҽ��̴�
        for (int j = 2; j < i; j++) {
            count++;
            if (i % j == 0) { // ���� ���ڰ� j�� �������°�?
                flag = 0; // ��, �Ҽ��� �ƴϿ���.
                break; // ���̻� �� �͵� ����
            }
        }
        if (flag) {
            // printf("%d ", i);
        }
    }
    printf("\n\n�� ����Ƚ��: %d\n", count);
}
/// �����佺�׳׽��� ü
// �ڽ��� ���Ϸ��� �ϴ� ���ڱ��� �迭�� ���� ��, � ���� ������� ��������
void eratosthenes() {
    int count = 0; // ����Ƚ��

    puts(" == �����佺�׳׽��� ü == ");
    int primes[500]; // ���� ���ڵ��� ���� �����ϴ� �迭
    int ptr = 0; // �߰��� �Ҽ��� ���� (index)
    primes[ptr++] = 2; // 2�� �Ҽ��ϱ� ������, index�� ����
    // ¦���� �Ҽ��� �ƴϴϱ� Ȧ���� ����
    for (int i = 3; i <= 100000; i += 2) {
        int flag = 1;
        // i�� �Ҽ����� �Ǵ��Ѵ� (i�� ���� �迭�� ����Ǿ��ִ� �Ҽ���� ���������� Ȯ���Ѵ�)
        for (int j = 0; j < ptr; j++) {
            count++;
            if (i % primes[j] == 0) {
                flag = 0;
                break;
            }
        }
        // i�� �Ҽ����ٸ�
        if (flag) {
            primes[ptr++] = i; // �迭�� �����Ѵ�
        }
    }
    // �� for���� ������ �迭�� �Ҽ��鸸 ����Ǿ�������
    // index�� �迭���� ������ �Ҽ��� ��ġ�� �����ϰ� �ִ�
    for (int i = 0; i < ptr; i++) {
        // printf("%d ", primes[i]);
    }
    printf("\n\n�� ����Ƚ��: %d\n", count);

}

/// ������ Ž��
void sqrt_search() {
    int count = 0; // ����Ƚ��
    puts(" == ������ �Ҽ� Ž�� == ");
    // ���� i�� �Ҽ��ΰ�? Ȯ���ϰ� �ʹ�
    for (int i = 2; i <= 100000; i++) {
        int flag = 1;
        // i�� �����ٱ��� i���� �������� ����� �����ϴ��� ã�� �� �ִ�
        for (int j = 2; j <= sqrt(i); j++) {
            count++;
            if (i % j == 0) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            // printf("%d ", i);
        }
    }
    printf("\n\n�� ����Ƚ��: %d\n", count);

}


void sosu_main() {
    bruteforce();
    eratosthenes();
    sqrt_search();
}