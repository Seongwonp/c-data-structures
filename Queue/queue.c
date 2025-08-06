#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 최대 size 만큼을 가지는 큐를 생성하고 반환
INT_QUEUE* queue_init(int size) {
    INT_QUEUE* queue = (INT_QUEUE*)malloc(sizeof(INT_QUEUE));
    queue->front = 0;
    queue->rear = 0;
    queue->datas = (int*)malloc(size * sizeof(int));
    queue->size = size;
    return queue;
}
bool is_queue_empty(INT_QUEUE* queue) {
    if (queue->rear != 0 && queue->rear == queue->front) {
        return true;
    }
    return false;
}
void enqueue(INT_QUEUE* queue, int data) {
    // 최대용량보다 현재 front가 더 높다면 가득 찬거임
    if (queue->size <= queue->front) {
        printf("Error: Queue is full\n");
        return;
    }
    // datas배열의 front 위치(제일 꼭대기)에 데이터를 설정
    queue->datas[queue->front++] = data;
}
int dequeue(INT_QUEUE* queue) {
    if (is_queue_empty(queue)) {
        printf("Error: Queue is empty\n");
        return -1;
    }
    // 현재 큐 datas배열의 rear 위치의 데이터를 가져옴
    int data = queue->datas[queue->rear++];
    return data;
}
int peek_queue(INT_QUEUE* queue) {
    if (is_queue_empty(queue)) {
        printf("Error: Queue is empty\n");
        return -1;
    }
    int data = queue->datas[queue->rear];
    return data;
}
void print_queue(INT_QUEUE* queue) {
    printf("queue: [");
    for (int i = queue->rear; i < queue->front; i++) {
        if (i == queue->front-1) {
            printf("%d", queue->datas[i]);
        }else {
            printf("%d, ", queue->datas[i]);
        }
    }
    printf("]\n");
}
void print_char_queue(INT_QUEUE* queue) {
    printf("queue: [");
    for (int i = queue->rear; i < queue->front; i++) {
        if (i == queue->front-1) {
            printf("%c", queue->datas[i]);
        }else {
            printf("%c, ", queue->datas[i]);
        }
    }
    printf("]\n");
}

void queue_main() {
    INT_QUEUE* queue = queue_init(3);
    enqueue(queue, 10);
    enqueue(queue, 20);
    int data = peek_queue(queue);
    printf("PEEK: %d\n", data);
    enqueue(queue, 30);
    print_queue(queue);
    // full
    enqueue(queue, 40);
    dequeue(queue);
    print_queue(queue);
    dequeue(queue);
    print_queue(queue);
    dequeue(queue);
    print_queue(queue);
    /// empty
    dequeue(queue);
    /// 한번이라도 꽉 채워지고 난 후에는 Enqueue가 불가능하다...
    enqueue(queue, 40);
}
