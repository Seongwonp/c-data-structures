#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_empty(INT_STACK* stack) {
    return stack->top <= 0; // 현재 위치가 0이하다 == 데이터가 없다
}

void push(INT_STACK* stack, int data) {
    // 스택 범위를 벗어나서 push 하려고 한다
    if (stack->top >= stack->size) {
        printf("Error: Stack is full\n");
        return;
    }
    // stack이 가지는 실제 데이터가 들어간 배열인 datas의 top위치에 데이터를 설정
    stack->datas[stack->top++] = data;
    // printf("PUSH: [%d]\n", data);
}
/// top이 보고 있는 위치의 데이터를 꺼내온다
int pop(INT_STACK* stack) {
    if (is_empty(stack)) {
        printf("Error: Stack is empty\n");
        return -1;
    }
    return stack->datas[--stack->top];
}

int peek(INT_STACK* stack) {
    if (is_empty(stack)) {
        printf("Error: Stack is empty\n");
        return -1;
    }
    return stack->datas[stack->top - 1];
}

void stack_main() {
    INT_STACK stack; // 스택을 생성
    stack.top = 0;
    stack.size = 3;  // 스택의 최대치를 설정
    /// 실제 데이터가 들어갈 배열 생성 (size 크기로)
    stack.datas = (int*)calloc(stack.size, sizeof(int));
    int data;

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    data = peek(&stack);
    printf("PEEK: [%d]\n", data);
    push(&stack, 40);
    data = peek(&stack);
    printf("PEEK: [%d]\n", data);

    data = pop(&stack);
    printf("POP: [%d]\n", data);
    data = pop(&stack);
    printf("POP: [%d]\n", data);
    data = pop(&stack);
    printf("POP: [%d]\n", data);
    data = pop(&stack);
    printf("POP: [%d]\n", data);
    data = pop(&stack);
    printf("POP: [%d]\n", data);

}








