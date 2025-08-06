#ifndef CIRCLE_DOUBLE_LINKED_LIST_H
#define CIRCLE_DOUBLE_LINKED_LIST_H

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
}Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;  // 원형 링크드 리스트에 들어갈 최대 node 개수
    int count; // 현재 들어가있는 노드 개수
}CIRCLE_DOUBLE_LINKED_LIST;

#endif //CIRCLE_DOUBLE_LINKED_LIST_H
