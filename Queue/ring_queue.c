#include "ring_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 최대 size 만큼을 가지는 큐를 생성하고 반환
static INT_RING_QUEUE* ring_queue_init(int size) {
    INT_RING_QUEUE* queue = (INT_RING_QUEUE*)malloc(sizeof(INT_RING_QUEUE));
    queue->front = 0;
    queue->rear = 0;
    queue->datas = (int*)malloc(size * sizeof(int));
    queue->size = size;
    queue->count = 0;
    return queue;
}
bool is_ring_queue_empty(INT_RING_QUEUE* queue) {
    if (queue->count == 0) {
        return true;
    }
    return false;
}
void ring_enqueue(INT_RING_QUEUE* queue, int data) {
    // 최대용량보다 현재 front가 더 높다면 가득 찬거임
    if (
        queue->count == queue->size
    ) {
        printf("Error: Queue is full\n");
        return;
    }
    // index 범위를 벗어났다면 0부터 다시 시작
    if (queue->front == queue->size) {
        queue->front = 0;
    }
    // datas배열의 front 위치(제일 꼭대기)에 데이터를 설정
    queue->datas[queue->front++] = data;
    queue->count++;
}
int ring_dequeue(INT_RING_QUEUE* queue) {
    if (is_ring_queue_empty(queue)) {
        printf("Error: Queue is empty\n");
        return -1;
    }
    // index 범위를 벗어났다면 맨 위 index에 있는 내용을 꺼내기
    if (queue->rear == queue->size) {
        queue->rear = 0;
    }
    // 현재 큐 datas배열의 rear 위치의 데이터를 가져옴
    int data = queue->datas[queue->rear++];
    queue->count--;
    return data;
}
int ring_peek_queue(INT_RING_QUEUE* queue) {
    if (is_ring_queue_empty(queue)) {
        printf("Error: Queue is empty\n");
        return -1;
    }
    int data = queue->datas[queue->rear];
    return data;
}
void print_ring_queue(INT_RING_QUEUE* queue) {
    printf("queue: [");
    int index = queue->rear;
    for (int i = 0; i < queue->count; i++, index++) {
        if (index == queue->size) {
            index = 0;
        }
        if (i == queue->count-1) {
            printf("%d", queue->datas[index]);
        }else {
            printf("%d, ", queue->datas[index]);
        }
    }
    printf("]\n");
}

void ring_queue_main() {
    INT_RING_QUEUE* queue = ring_queue_init(3);
    ring_enqueue(queue, 10);
    ring_enqueue(queue, 20);
    int data = ring_peek_queue(queue);
    printf("PEEK: %d\n", data);
    ring_enqueue(queue, 30);
    print_ring_queue(queue);
    // full
    ring_enqueue(queue, 40);
    ring_dequeue(queue);
    print_ring_queue(queue);
    ring_dequeue(queue);
    print_ring_queue(queue);
    ring_dequeue(queue);
    print_ring_queue(queue);
    /// empty
    ring_dequeue(queue);
    /// 한번이라도 꽉 채워지고 난 후에는 Enqueue가 불가능하다...
    ring_enqueue(queue, 40);
    ring_enqueue(queue, 50);
    ring_enqueue(queue, 60);
    print_ring_queue(queue);
    ring_dequeue(queue);
    ring_enqueue(queue, 70);
    print_ring_queue(queue);
}
