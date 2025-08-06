#ifndef STACK_H
#define STACK_H
#include "stdbool.h"
typedef struct {
    int size; // 스택의 용량
    int top; // 스택의 맨 꼭대기. stack 배열의 현재 index (peek 혹은 pop의 대상)
    int* datas; // 스택의 맨 바닥이며, 스택 자체, 배열. (맨 처음에 넣은 데이터)
}INT_STACK;

bool is_empty(INT_STACK* stack);
void push(INT_STACK* stack, int data);
int pop(INT_STACK* stack);
int peek(INT_STACK* stack);

#endif //STACK_H
