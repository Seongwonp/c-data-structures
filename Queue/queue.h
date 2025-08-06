#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>

typedef struct  {
    int size; //ť�� �ִ� �뷮
    int front; // �� ����� front
    int rear; // �� �ٴ� rear
    int* datas; // �����͵��� ����ִ� ���� ť �迭
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
