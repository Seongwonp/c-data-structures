#include "calculator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "postfix.h"
#include "stack.h"

char operators[] = {'+', '-', '*', '/', '%'};
/// 후위식의 현재 문자가 연산자일 경우, 어떤 연산자인지 판단
int check_operator(char token) {
    // 현재 문자가 위에서 정의한 operators중 하나인가?
    for (int i = 0; i < strlen(operators); i++) {
        if (token == operators[i]) {
            return i;
        }
    }
    return -1; // 미등록 연산자 == 숫자라는 것
}
/// 판단된 연산자로 두 숫자를 연산하는 실제 계산
int calculate(char operator, int n1, int n2) {
    switch (operator) {
        case '+': return n1 + n2;
        case '-': return n1 - n2;
        case '*': return n1 * n2;
        case '/': return (int)(n1 / n2);
        case '%': return (int)n1 % (int)n2;
        default: return 0; // 미등록 연산자
    }
}
/// 후위식을 받아와서 처리를 하는 곳
int evaluate(char* postfix) {
    INT_STACK stack;
    stack.top = 0;
    stack.size = (int)strlen(postfix);
    stack.datas = (int*)malloc(sizeof(int) * stack.size);
    //// 띄어쓰기 기준으로 나눈다
    char* token = strtok(postfix, " ");
    // 띄어쓰기 기준으로 나눈 요소들이 아직 존재한다면
    while (token != NULL) {
        // 숫자라면, float형태(실수)의 진짜 숫자로 변환해서 push
        if (check_operator(*token) == -1) {
           push(&stack, atoi(token));
        }else {
            // 숫자가 아니라면 stack에 저장된 두 숫자를 가져와서 계산 후, 다시 push
            int n1 = pop(&stack);
            int n2 = pop(&stack);
            int result = calculate(*token, n1, n2); // 계산
            push(&stack, result); // 계산 후 재 push
        }
        token = strtok(NULL, " "); // 나누었던 다음 위치로 이동
    }
    // 마지막에 stack에 숫자 하나가 남아있는데, 그게 후위식 계산 결과임
    return pop(&stack);
}

void calculator_main() {
    // 1) 중위식을 후위식으로
    char* postfix = change_postfix("3 + 4 * 2");
    // 2) 후위식을 계산
    int result = evaluate(postfix);
    printf("계산 결과: %d\n", result);
}


