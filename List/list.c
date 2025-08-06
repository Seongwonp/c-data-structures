#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//// ������ ���� ����Ʈ
void char_node_test() {
    ///// ��带 ����
    CharNode charNode1;
    charNode1.data = 'a';
    CharNode charNode2;
    charNode2.data = 'b';
    CharNode charNode3;
    charNode3.data = 'c';
    CharNode charNode4;
    charNode4.data = 'd';
    ////// ����� ����
    // charNode1: Head Node - �տ� ��尡 ����
    // charNode4: Tail Node - �ڿ� ��尡 ����
    charNode1.next = &charNode2;
    charNode2.next = &charNode3;
    charNode3.next = &charNode4;
    charNode4.next = NULL;
    //// ��带 Ž��
    CharNode nextNode = *charNode1.next;
    while (nextNode.next != NULL) {
        printf("Head Node�� ������� ������: %c\n", nextNode.data);
        nextNode = *nextNode.next;
    }

    // printf("Head Node�� ������� ������: %c\n", nextNode.data);
    // nextNode = *nextNode.next;
    // printf("NEXT �� ������� ������: %c\n", nextNode.data);
    // nextNode = *nextNode.next;
    // printf("NEXT �� ������� ������: %c\n", nextNode.data);
    // nextNode = *nextNode.next;
    // printf("Tail �� ������� ������: %c\n", nextNode.data);
    // nextNode = *nextNode.next; // Tail���� ���� ���� �������� �ʾƼ� ����
}

/******************************************************/
// 1) ��带 �ϳ� ����� ��ȯ
static Node* create_node() {
    Node* node = (Node*)calloc(1, sizeof(Node)); // ��带 ����
    node->next = NULL; // �� ����� ���� ���� ����
    return node; // ������ ��带 ��ȯ
}

// 2) ������� ��忡 ���� �����͸� ����
// node: ������ �����ϴ� ���
// data: ������ �����ϴ� ��忡 ������ ���� ������
void set_node(Node* node, int data) {
    node->data = data;
}

// is_empty(): ����Ʈ ���� ��尡 �����ϴ��� true/false�� ��ȯ
bool is_empty(List* list) {
    if(list->head == NULL) {
        return true;
    }
    return false;
}

// add_node(): ����Ʈ�� �� �ڿ� ��带 �ϳ� �߰��ϱ� (tail�� ��带 �߰��ϱ�)
void add_node(List* list, Node* node) {
    // ����Ʈ�� ����ִٸ�, ����Ʈ�� head �μ� node�� �����Ѵ�
    if (is_empty(list)) {
        list->head = node;
        return;
    }
    // ����Ʈ�� ������� �ʴٸ�, head���� next�� NULL�� ������ (Tail ������) ã�ư�
    /// => tail �� next�� ��带 �߰��ؾ� �ϱ� ����
    Node* tailNode = list->head;
    while (tailNode->next != NULL) {
        tailNode = tailNode->next;
    }
    /// while���� ������ ��, tailNode�� ����Ʈ�� ������ ��尡 �ȴ�.
    /// �߰��ϰ� ���� node�� tailNode�� next(���� ���)�� �����Ѵ�
    tailNode->next = node;
}

// insert(): ����Ʈ�� �߰��� ��带 �����ϱ� (index ��ġ��)
// index: List�� ������ ��ġ
// Node: ������ ��� ������
void insert(List* list, int index, Node* node) {
    Node* curtNode = list->head;
    // ù��° ��ġ�� insert�Ѵٴ� ��
    if (index == 0) {
        node->next = curtNode; // ���� ���� ����� ���� ��尡 ���� Head���
        list->head = node; // ���� ���� ��尡 ���ο� head��尡 �Ǹ� �ȴ�
        return;
    }
    // ���� ���� ��ġ���� �̵��Ѵ� (���� ���� ��ġ�� �� ������ Ž���Ѵ�)
    for (int i = 1; i < index; i++) {
        if (curtNode->next == NULL) {
            printf("Error: index ������ ������ϴ�\n");
            return;
        }
        curtNode = curtNode->next; // curtNode: i == 1
    }
    Node* nextNode = curtNode->next; // �� ����� ������� (���� index��ġ�� �ִ� ���)
    curtNode->next = node; // ���� ���� ��ġ�� �� ����� ���� ���� ���γ�������.
    node->next = nextNode; // ���� ���� ����� �������� ������ ����� �������(���� index��ġ�� �ִ����)
}

void remove_node(List* list, int index) {
    Node* curtNode = list->head;
    if (is_empty(list)) {
        printf("Error: ����Ʈ�� ������ϴ�\n");
        return;
    }
    // ù��° ��ġ�� insert�Ѵٴ� ��
    if (index == 0) {
        Node* next = list->head->next;
        list->head = next;
        return;
    }

    // ���� ���� ��ġ���� �̵��Ѵ� (���� ���� ��ġ�� �� ������ Ž���Ѵ�)
    for (int i = 1; i < index; i++) {
        if (curtNode->next == NULL) {
            printf("Error: index ������ ������ϴ�\n");
            return;
        }
        curtNode = curtNode->next;
    }
    // curtNode�� index��ġ�� �� ���
    Node* nextNode = curtNode->next->next; // index��ġ�� ���� ���
    Node* indexNode = curtNode->next; //���� index��ġ�� �ִ� ���
    curtNode->next = nextNode; // ������ ������带 �̾��ش�
    free(indexNode); // index��ġ�� ���� �޸𸮿��� ����
}

// ����Ʈ�� �����ϴ� ��� ���(Node)���� ������� ��ȸ
void print(List *list) {
    if (is_empty(list)) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (Node* node = list->head; node != NULL; node = node->next) {
        if (node->next == NULL) { // ������ �����Ͷ�� , ����
            printf("%d", node->data);
        }else {  // ������ �����Ͱ� �ƴϸ� , �ְ�
            printf("%d, ", node->data);
        }
    }
    printf("]");
}


////// ���� ����Ʈ ����
void main() {
    // char_node_test();
    //// ���� ����Ʈ ����
    List list = { .head = NULL }; // ��, �ʱ�ȭ
    Node* node = create_node();
    set_node(node, 10);
    add_node(&list, node); // head node�� �߰���

    node = create_node();
    set_node(node, 100);
    add_node(&list, node); // head node�� �������� �߰���

    node = create_node();
    set_node(node, 1000);
    add_node(&list, node); // head node�� ������ �������� �߰���

    node = create_node();
    set_node(node, 5000);
    insert(&list, 4, node);
    // node = create_node();
    // set_node(node, 500);
    // insert(&list, 3, node);
    //
    // node = create_node();
    // set_node(node, 5000);
    // insert(&list, 4, node);
    //
    // node = create_node();
    // set_node(node, 2000);
    // insert(&list, 1, node);
    // node = create_node();
    // set_node(node, 0);
    // insert(&list, 0, node);
    //
    // remove_node(&list, 2);
    // remove_node(&list, 0);

    print(&list);
}
