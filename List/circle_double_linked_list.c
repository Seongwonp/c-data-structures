#include "circle_double_linked_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/******************************************************/
// 1) 노드를 하나 만들고 반환
static Node* create_node() {
    Node* node = (Node*)calloc(1, sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// is_empty(): 리스트 내에 노드가 존재하는지 true/false로 반환
bool is_empty(CIRCLE_DOUBLE_LINKED_LIST* list) {
    if (list->count == 0) {
        return true;
    }
    return false;
}

// add_node(): 리스트의 맨 뒤에 노드를 하나 추가하기 (tail에 노드를 추가하기)
void add_node(CIRCLE_DOUBLE_LINKED_LIST* list, Node* node) {
    // 리스트가 비었다면
    if (is_empty(list)) {
        list->head = node; // 맨처음이라고 설정
    }
    if (list->count == list->size) {
        list->size *= 2;
        list->head->prev = NULL;
        list->tail->next = NULL;
    }
    // 추가되어있는 노드가 존재했다면 그 뒤에 넣는다
    if (list->tail != NULL) {
        Node* tailNode = list->tail;
        tailNode->next = node; // '원래 마지막'의 뒤로
        node->prev = tailNode; // '추가하는 노드'의 앞이 '원래의 마지막 노드' 설정
    }
    list->tail = node; // 추가를 하면 무조건 맨마지막이니까 설정
    list->count++; // 하나 추가함
    // tail과 head를 연결
    if (list->count == list->size) {
        list->head->prev = list->tail;
        list->tail->next = list->head;
    }
}

// insert(): 리스트의 중간에 노드를 삽입하기 (index 위치에)
// index: List에 삽입할 위치
// Node: 삽입할 노드 데이터
void insert(CIRCLE_DOUBLE_LINKED_LIST* list, int index, Node* node) {
    Node* curtNode = list->head;
    // 내부에 데이터가 없는데 0의 위치로 insert
    if (is_empty(list) && index == 0) {
        list->head = node; // 맨처음이라고 설정
        list->tail = node; // 맨마지막이라고 설정
        return;
    }
    if (index == 0) {
        node->next = curtNode;
        curtNode->prev = node;
        list->head = node;
        return;
    }
    for (int i = 0; i < index; i++) {
        if (curtNode == NULL) {
            printf("ERROR: index out of range\n");
            return;
        }
        curtNode = curtNode->next;
    }
    curtNode->prev->next = node; // 원래전노드의 다음 == 나
    node->prev = curtNode->prev; // 나의 전 == 원래전노드
    node->next = curtNode; // 나의 다음 == 원래노드
    curtNode->prev = node; // 원래노드의 전 == 나
}
//
// void remove_node(List* list, int index) {
//
// }

// 리스트에 존재하는 모든 요소(Node)들을 순서대로 순회
void print_front(CIRCLE_DOUBLE_LINKED_LIST *list) {
    Node* node = list->head;
    int index = 0;
    printf("리스트 최대치: [%d]\n", list->size);
    printf("리스트 내의 노드 개수: [%d]\n", list->count);
    for (int i = 0; i < list->count; i++) {
        printf("[%d] %d\n", i, node->data); // 노드 데이터 출력
        node = node->next; // 다음 노드로 이동
    }
}
// 뒤에서 거꾸로 찾기
void print_rear(CIRCLE_DOUBLE_LINKED_LIST *list) {
    Node* node = list->tail;
    printf("리스트 최대치: [%d]\n", list->size);
    printf("리스트 내의 노드 개수: [%d]\n", list->count);
    for (int i = list->count-1; i >= 0; i--) {
        printf("[%d] %d\n", i, node->data); // 노드 데이터 출력
        node = node->prev; // 다음 노드로 이동
    }
}

////// 선형 리스트 메인
void cdl_main() {
    CIRCLE_DOUBLE_LINKED_LIST list = {
        .head = NULL,
        .tail = NULL,
        .size = 4
    };

    Node* node1 = create_node();
    node1->data = 10;
    add_node(&list, node1); // 리스트에 노드 추가

    Node* node2 = create_node();
    node2->data = 20;
    add_node(&list, node2); // 리스트에 노드 추가

    Node* node3 = create_node();
    node3->data = 30;
    add_node(&list, node3); // 리스트에 노드 추가

    // Node* node4 = create_node();
    // node4->data = 40;
    // insert(&list, 1, node4); // 리스트에 노드 추가

    Node* node5 = create_node();
    node5->data = 50;
    add_node(&list, node5); // 리스트에 노드 추가

    Node* node6 = create_node();
    node6->data = 60;
    add_node(&list, node6); // 리스트에 노드 추가

    print_front(&list); // 노드에 들어있는 데이터 출력
    print_rear(&list);



}









