#ifndef QUEUE_H
#define QUEUE_H

typedef struct  {
    int count; // 현재 큐에 들어있는 데이터 개수
    int size; // 큐의 최대 용량
    int front; // 맨 꼭대기 front
    int rear; // 맨 바닥 rear
    int* datas; // 데이터들이 들어있는 실제 큐 배열
}INT_RING_QUEUE;

#endif //QUEUE_H
