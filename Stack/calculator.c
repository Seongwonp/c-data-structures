#include "calculator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "postfix.h"
#include "stack.h"

char operators[] = {'+', '-', '*', '/', '%'};
/// �������� ���� ���ڰ� �������� ���, � ���������� �Ǵ�
int check_operator(char token) {
    // ���� ���ڰ� ������ ������ operators�� �ϳ��ΰ�?
    for (int i = 0; i < strlen(operators); i++) {
        if (token == operators[i]) {
            return i;
        }
    }
    return -1; // �̵�� ������ == ���ڶ�� ��
}
/// �Ǵܵ� �����ڷ� �� ���ڸ� �����ϴ� ���� ���
int calculate(char operator, int n1, int n2) {
    switch (operator) {
        case '+': return n1 + n2;
        case '-': return n1 - n2;
        case '*': return n1 * n2;
        case '/': return (int)(n1 / n2);
        case '%': return (int)n1 % (int)n2;
        default: return 0; // �̵�� ������
    }
}
/// �������� �޾ƿͼ� ó���� �ϴ� ��
int evaluate(char* postfix) {
    INT_STACK stack;
    stack.top = 0;
    stack.size = (int)strlen(postfix);
    stack.datas = (int*)malloc(sizeof(int) * stack.size);
    //// ���� �������� ������
    char* token = strtok(postfix, " ");
    // ���� �������� ���� ��ҵ��� ���� �����Ѵٸ�
    while (token != NULL) {
        // ���ڶ��, float����(�Ǽ�)�� ��¥ ���ڷ� ��ȯ�ؼ� push
        if (check_operator(*token) == -1) {
           push(&stack, atoi(token));
        }else {
            // ���ڰ� �ƴ϶�� stack�� ����� �� ���ڸ� �����ͼ� ��� ��, �ٽ� push
            int n1 = pop(&stack);
            int n2 = pop(&stack);
            int result = calculate(*token, n1, n2); // ���
            push(&stack, result); // ��� �� �� push
        }
        token = strtok(NULL, " "); // �������� ���� ��ġ�� �̵�
    }
    // �������� stack�� ���� �ϳ��� �����ִµ�, �װ� ������ ��� �����
    return pop(&stack);
}

void calculator_main() {
    // 1) �������� ����������
    char* postfix = change_postfix("3 + 4 * 2");
    // 2) �������� ���
    int result = evaluate(postfix);
    printf("��� ���: %d\n", result);
}


