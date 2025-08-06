#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>

typedef struct  {
    int size; //큐의 최대 용량
    int front; // 맨 꼭대기 front
    int rear; // 맨 바닥 rear
    int* datas; // 데이터들이 들어있는 실제 큐 배열
}INT_QUEUE;

INT_QUEUE* queue_init(int size);
bool is_queue_empty(INT_QUEUE* queue);
void enqueue(INT_QUEUE* queue, int data);
int dequeue(INT_QUEUE* queue);
int peek_queue(INT_QUEUE* queue);
void print_queue(INT_QUEUE* queue);
void queue_main();
void print_char_queue(INT_QUEUE* queue);

#endif //QUEUE_H
