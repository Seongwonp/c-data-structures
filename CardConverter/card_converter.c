#include <stdio.h>

// 양의 정수를 2진수 - 36진수로 기수 변환
// x: 변환하고 싶은 양의 정수
// n: 변환하고 싶은 진수
// d: 변환된 진수를 문자열로 저장하기 위한 배열
int card_converter(unsigned int x, int n, char d[]) {
    char dChar[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int digit = 0; // 현재 변환되는 진수의 index 순서
    if (x == 0) {
        d[0] = '0';
        digit++;
    }
    while (x) { // x가 0이 될 때까지 반복한다
        // 위에서 정의한 글자를 배열에 저장한다
        d[digit] = dChar[x % n]; // 나머지 결과를 자리에 저장한다
        digit++; // 다음 자리로 이동한다
        x /= n; // x를 다음 몫으로 변환한다
    }
    return digit; // 읽어야 하는 자릿수를 return
}

void card_converter_main() {
    int number; // 변환할 10진수
    int card; // 변환하고 싶은 진수
    char result[512]; // 변환결과를 저장하는 char 배열

    puts("======== 10진수 기수 변환 프로그램 ========== ");
    printf("변환할 10진수를 입력하세요 >>");
    scanf("%u", &number); // 10진수 입력받기
    printf("몇 진수로 변환할까요? >>");
    scanf("%d", &card);
    // 변환할 숫자와 진수를 전달한 뒤, result에서 print를 시작해야하는 위치를 받아옴
    int digitStartIndex = card_converter(number, card, result);
    printf("변환결과: ");
    for (int i = digitStartIndex - 1; i >= 0; i--) {
        printf("%c", result[i]);
    }
}






