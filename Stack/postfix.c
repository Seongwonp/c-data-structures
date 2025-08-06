#include "postfix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
// 연산자의 우선순위를 가져오기
OPERATOR get_operator_priority(char operator) {
    switch (operator) {
        case '+': return isp[PLUS];
        case '-': return isp[MINUS];
        case '*': return isp[MULTIPLY];
        case '/': return isp[DIVIDE];
        case '%': return isp[MODULUS];
        case '(': return isp[LPAREN];
        case ')': return isp[RPAREN];
        default: return -1; // 미등록 연산자!
    }
}
// 현재 문자가 연산자인가? 숫자인가? 아니면 . 인가 판단
int check_token(char token) {
    switch (token) {
        case '+':case '-':case '*':case '/':case '%':
            return OPERAND;
        case '.':
            return DOT;
        case '(': return LPAREN;
        case ')': return RPAREN;
        case ' ': return EOS;
        // 위에 정의한 애들 말고는 전부 숫자라고 판단
        default: return NUMBER;
    }
}
/// expression: 변환할 수식 (중위식)
char* change_postfix(char expression[]) {
    int len = (int)strlen(expression); // 중위식 표현의 문자열 길이
    INT_STACK stack;
    stack.top = 0;
    stack.size = len;
    stack.datas = (int*)calloc(stack.size, sizeof(int));
    // result: 중위식을 후위식으로 변환 완료한 후위식 문자열
    char* result = (char*)calloc((len * 2) + 1, sizeof(char));
    int resultIndex = 0; // 결과 후위식 배열의 index
    /// 중위식의 문자를 하나씩 순회한다
    for (int i = 0; i < len; i++) {
        char token = expression[i]; // 현재 문자를 가져온다
        // 현재 문자가 숫자인가 문자인가 등 판단
        switch (check_token(token)) {
            case LPAREN: // ( 괄호라면 - Stack에 무조건 push
                push(&stack, token);
                break;
            case RPAREN: // ) 괄호라면 - Stack에 있는 ( 괄호가 나올때까지 pop한 뒤 추가
                while (1) {
                    char operator = pop(&stack);
                    if (check_token(operator) == LPAREN) {
                        break;
                    }
                    result[resultIndex++] = ' '; // 띄어쓰기 하나 넣고
                    result[resultIndex++] = operator; // 후위식에 추가
                }
                break;
            case OPERAND: // 연산자라면 - push 혹은 result에 추가
                // Stack이 비어있지 않고,
                // stack에 저장된 마지막 연산자가 우선순위가 더 크다면
                while(
                    !is_empty(&stack) &&
                    get_operator_priority(token) <= get_operator_priority(peek(&stack))
                ) {
                    // stack에 저장된 연산자를 꺼내와서
                    result[resultIndex++] = ' '; // 띄어쓰기 하나 넣고
                    result[resultIndex++] = pop(&stack); // 후위식에 추가
                }
                // 내가 우선순위가 높으면 Stack에 Push하면 됨
                result[resultIndex++] = ' ';
                push(&stack, token); // 현재 token을 push
                break;
            case EOS: // 띄어쓰기라면 - 버린다
                break;
            // 이 친구들은 띄어쓰기 넣으면 안됨
            case DOT: // . 이라면
            case NUMBER: // 숫자라면
                result[resultIndex++] = token; // 후위식 문자열에 추가한다
        }
    }
    //// for 가 끝난 후, stack에 남은 연산자들을 그대로 pop해서 result에 추가
    while (!is_empty(&stack)) {
        result[resultIndex++] = ' '; // 띄어쓰기 하나 넣고
        result[resultIndex++] = pop(&stack); // 후위식에 추가
    }
    // 변환끝난 후위식 문자열을 반환
    return result;
}
// 후위식을 출력
void print_postfix(char* postfix) {
    for (int i = 0; i < strlen(postfix); i++) {
        printf("%c", postfix[i]);
    }
    printf("\n");
}

void postfix_main() {
    char* result = change_postfix("3+4*2");
    print_postfix(result);

    result = change_postfix("( a / (b-c+d) ) * (e-a) * c");
    print_postfix(result);

    result = change_postfix("a / b - c + d * e - a * c");
    print_postfix(result);

    result = change_postfix("35-4.2*4");
    print_postfix(result);

    result = change_postfix("3+4*2");
    print_postfix(result);
}







