#include "heap.h"

#include <stdio.h>

int compare(char c1, char c2) {
    // if (c1 < c2) {
    //     return 1;
    // }else if (c2 == c1) {
    //     return 0;
    // }
    // return -1;

    return -(c1 - c2);
}

// 최초 힙을 생성 (초기화)
void heap_init(HEAP* heap, priority_compare compare) {
    heap->count = 0;
    heap->compare = compare;
}
// 부모 노드의 인덱스를 구하기
int get_parent_index(int nodeIndex) {
    return nodeIndex / 2; // 자신의 절반
}
// 왼쪽 자식 인덱스를 구하기
int get_left_index(int nodeIndex) {
    return nodeIndex * 2;
}
// 오른쪽 자식 인덱스를 구하기
int get_right_index(int nodeIndex) {
    return nodeIndex * 2 + 1;
}
// 높은 우선순위의 자식 인덱스를 가져오기
int get_priority_child_index(HEAP* heap, int index) {
    // 자식 노드가 존재하지 않는다면 (나의 왼쪽 자식의 index가 현재개수보다 크다면)
    if (get_left_index(index) > heap->count) {
        return 0;
    }
    // 왼쪽 자식 노드가 마지막 노드라면
    else if (get_left_index(index) == heap->count) {
        return get_left_index(index); // 마지막 노드를 가져온다
    }
    // 자식 노드가 존재한다면, 왼쪽 자식 노드와 오른쪽 자식 노드의 우선순위를 비교한다
    // 오른쪽 자식의 우선순위가 클 경우 (왼쪽과 오른쪽 비교시 음수가 발생함)
    if (heap->compare(
        heap->datas[get_left_index(index)],
        heap->datas[get_right_index(index)]) < 0
    ) {
        return get_right_index(index); // 오른쪽 자식을 가져감
    }
    return get_left_index(index);  // 왼쪽 자식을 가져감
}

void heap_insert(HEAP* heap, char data) {
    // 1) 자식이 삽입되는 첫 위치를 가져온다
    int index = heap->count + 1;
    // 2) 부모와 교체작업을 반복한다
    while (index != 1) { // 내가 최상위 노드가 아니라면
        int parentIndex = get_parent_index(index); // 부모의 인덱스를 가져온다
        char parentData = heap->datas[parentIndex]; // 부모의 데이터를 가져온다
        /// 현재 삽입할 내 데이터와 기존의 부모 데이터 중 우선순위가 높은것은?
        /// 자식의 우선순위가 높다면
        if (heap->compare(data, parentData) > 0) {
            // 부모와 교체작업
            heap->datas[index] = parentData;
            index = parentIndex;
        }else { // 자식의 우선순위가 같거나 낮으면 그 자리가 노드의 자리가 된다
            break;
        }
    }
    heap->datas[index] = data; // 적절한 위치를 찾았으면 노드 데이터를 설정한다
    heap->count++; // 현재 개수 +1
}

char heap_delete(HEAP* heap) {
    // 삭제할 데이터를 임시로 저장한다
    char data = heap->datas[1]; // root 노드
    char lastData = heap->datas[heap->count]; // 현재 힙에서의 마지막 데이터
    int parentIndex = 1; // root 노드의 index
    int childIndex; // 왼쪽과 오른쪽 자식에서 우선순위가 높은 자식의 index
    while (childIndex = get_priority_child_index(heap, parentIndex)) {
        if (lastData < heap->datas[childIndex]) {
            break;
        }
        // 부모와 자식의 교환 작업
        heap->datas[parentIndex] = heap->datas[childIndex];
        parentIndex = childIndex;
    }
    heap->datas[parentIndex] = lastData;
    heap->count--;
    return data;
}

int heap_is_empty(HEAP* heap) {
    if (heap->count == 0) {
        return 1;
    }
    return 0;
}

void main() {
    HEAP heap;
    heap_init(&heap, compare);
    heap_insert(&heap, 'A');
    heap_insert(&heap, 'C');
    heap_insert(&heap, 'B');
    printf("%c\n", heap_delete(&heap));

    heap_insert(&heap, 'D');
    heap_insert(&heap, 'F');
    heap_insert(&heap, 'E');
    printf("%c\n", heap_delete(&heap));

    while (!heap_is_empty(&heap)) {
        printf("%c\n", heap_delete(&heap));
    }
}














