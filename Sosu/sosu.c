#include <math.h>
#include <stdio.h>
// 1 ~ 100 까지의 숫자 중 소수를 print
void bruteforce() {
    puts(" == Brute force 소수 탐색 == ");
    int count = 0; // 실행횟수
    // 1 ~ 100까지
    for (int i = 2; i <= 100000; i++) {
        // 현재 숫자가 소수인가?
        int flag = 1; // 일단, 현재 숫자는 소수이다
        for (int j = 2; j < i; j++) {
            count++;
            if (i % j == 0) { // 현재 숫자가 j로 나눠지는가?
                flag = 0; // 아, 소수가 아니였다.
                break; // 더이상 볼 것도 없네
            }
        }
        if (flag) {
            // printf("%d ", i);
        }
    }
    printf("\n\n총 실행횟수: %d\n", count);
}
/// 에라토스테네스의 체
// 자신이 구하려고 하는 숫자까지 배열에 삽입 후, 어떤 수의 배수들을 지워나감
void eratosthenes() {
    int count = 0; // 실행횟수

    puts(" == 에라토스테네스의 체 == ");
    int primes[500]; // 기존 숫자들을 전부 저장하는 배열
    int ptr = 0; // 발견한 소수의 개수 (index)
    primes[ptr++] = 2; // 2는 소수니까 저장함, index를 증가
    // 짝수는 소수가 아니니까 홀수만 보자
    for (int i = 3; i <= 100000; i += 2) {
        int flag = 1;
        // i가 소수인지 판단한다 (i가 현재 배열에 저장되어있는 소수들로 나눠지는지 확인한다)
        for (int j = 0; j < ptr; j++) {
            count++;
            if (i % primes[j] == 0) {
                flag = 0;
                break;
            }
        }
        // i가 소수였다면
        if (flag) {
            primes[ptr++] = i; // 배열에 저장한다
        }
    }
    // 위 for문이 끝나면 배열에 소수들만 저장되어있을것
    // index는 배열에서 마지막 소수의 위치를 저장하고 있다
    for (int i = 0; i < ptr; i++) {
        // printf("%d ", primes[i]);
    }
    printf("\n\n총 실행횟수: %d\n", count);

}

/// 제곱근 탐색
void sqrt_search() {
    int count = 0; // 실행횟수
    puts(" == 제곱근 소수 탐색 == ");
    // 현재 i가 소수인가? 확인하고 싶다
    for (int i = 2; i <= 100000; i++) {
        int flag = 1;
        // i의 제곱근까지 i에서 나눠보면 약수가 존재하는지 찾을 수 있다
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
    printf("\n\n총 실행횟수: %d\n", count);

}


void sosu_main() {
    bruteforce();
    eratosthenes();
    sqrt_search();
}