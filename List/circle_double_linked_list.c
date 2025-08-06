#include "circle_double_linked_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/******************************************************/
// 1) ��带 �ϳ� ����� ��ȯ
static Node* create_node() {
    Node* node = (Node*)calloc(1, sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// is_empty(): ����Ʈ ���� ��尡 �����ϴ��� true/false�� ��ȯ
bool is_empty(CIRCLE_DOUBLE_LINKED_LIST* list) {
    if (list->count == 0) {
        return true;
    }
    return false;
}

// add_node(): ����Ʈ�� �� �ڿ� ��带 �ϳ� �߰��ϱ� (tail�� ��带 �߰��ϱ�)
void add_node(CIRCLE_DOUBLE_LINKED_LIST* list, Node* node) {
    // ����Ʈ�� ����ٸ�
    if (is_empty(list)) {
        list->head = node; // ��ó���̶�� ����
    }
    if (list->count == list->size) {
        list->size *= 2;
        list->head->prev = NULL;
        list->tail->next = NULL;
    }
    // �߰��Ǿ��ִ� ��尡 �����ߴٸ� �� �ڿ� �ִ´�
    if (list->tail != NULL) {
        Node* tailNode = list->tail;
        tailNode->next = node; // '���� ������'�� �ڷ�
        node->prev = tailNode; // '�߰��ϴ� ���'�� ���� '������ ������ ���' ����
    }
    list->tail = node; // �߰��� �ϸ� ������ �Ǹ������̴ϱ� ����
    list->count++; // �ϳ� �߰���
    // tail�� head�� ����
    if (list->count == list->size) {
        list->head->prev = list->tail;
        list->tail->next = list->head;
    }
}

// insert(): ����Ʈ�� �߰��� ��带 �����ϱ� (index ��ġ��)
// index: List�� ������ ��ġ
// Node: ������ ��� ������
void insert(CIRCLE_DOUBLE_LINKED_LIST* list, int index, Node* node) {
    Node* curtNode = list->head;
    // ���ο� �����Ͱ� ���µ� 0�� ��ġ�� insert
    if (is_empty(list) && index == 0) {
        list->head = node; // ��ó���̶�� ����
        list->tail = node; // �Ǹ������̶�� ����
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
    curtNode->prev->next = node; // ����������� ���� == ��
    node->prev = curtNode->prev; // ���� �� == ���������
    node->next = curtNode; // ���� ���� == �������
    curtNode->prev = node; // ��������� �� == ��
}
//
// void remove_node(List* list, int index) {
//
// }

// ����Ʈ�� �����ϴ� ��� ���(Node)���� ������� ��ȸ
void print_front(CIRCLE_DOUBLE_LINKED_LIST *list) {
    Node* node = list->head;
    int index = 0;
    printf("����Ʈ �ִ�ġ: [%d]\n", list->size);
    printf("����Ʈ ���� ��� ����: [%d]\n", list->count);
    for (int i = 0; i < list->count; i++) {
        printf("[%d] %d\n", i, node->data); // ��� ������ ���
        node = node->next; // ���� ���� �̵�
    }
}
// �ڿ��� �Ųٷ� ã��
void print_rear(CIRCLE_DOUBLE_LINKED_LIST *list) {
    Node* node = list->tail;
    printf("����Ʈ �ִ�ġ: [%d]\n", list->size);
    printf("����Ʈ ���� ��� ����: [%d]\n", list->count);
    for (int i = list->count-1; i >= 0; i--) {
        printf("[%d] %d\n", i, node->data); // ��� ������ ���
        node = node->prev; // ���� ���� �̵�
    }
}

////// ���� ����Ʈ ����
void cdl_main() {
    CIRCLE_DOUBLE_LINKED_LIST list = {
        .head = NULL,
        .tail = NULL,
        .size = 4
    };

    Node* node1 = create_node();
    node1->data = 10;
    add_node(&list, node1); // ����Ʈ�� ��� �߰�

    Node* node2 = create_node();
    node2->data = 20;
    add_node(&list, node2); // ����Ʈ�� ��� �߰�

    Node* node3 = create_node();
    node3->data = 30;
    add_node(&list, node3); // ����Ʈ�� ��� �߰�

    // Node* node4 = create_node();
    // node4->data = 40;
    // insert(&list, 1, node4); // ����Ʈ�� ��� �߰�

    Node* node5 = create_node();
    node5->data = 50;
    add_node(&list, node5); // ����Ʈ�� ��� �߰�

    Node* node6 = create_node();
    node6->data = 60;
    add_node(&list, node6); // ����Ʈ�� ��� �߰�

    print_front(&list); // ��忡 ����ִ� ������ ���
    print_rear(&list);



}









