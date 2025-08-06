#ifndef HEAP_H
#define HEAP_H
typedef int priority_compare(char c1, char c2);
typedef struct heap {
    priority_compare* compare; // 힙 자신이 정렬하려고 하는 정렬 방식을 정의
    int count; // 힙이 저장하고 있는 데이터 개수
    char datas[100]; // 힙 자체. 실제 데이터를 저장함
}HEAP;


#endif //HEAP_H
