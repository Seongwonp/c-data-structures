#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//// 간단한 선형 리스트
void char_node_test() {
    ///// 노드를 생성
    CharNode charNode1;
    charNode1.data = 'a';
    CharNode charNode2;
    charNode2.data = 'b';
    CharNode charNode3;
    charNode3.data = 'c';
    CharNode charNode4;
    charNode4.data = 'd';
    ////// 노드의 연결
    // charNode1: Head Node - 앞에 노드가 없음
    // charNode4: Tail Node - 뒤에 노드가 없음
    charNode1.next = &charNode2;
    charNode2.next = &charNode3;
    charNode3.next = &charNode4;
    charNode4.next = NULL;
    //// 노드를 탐색
    CharNode nextNode = *charNode1.next;
    while (nextNode.next != NULL) {
        printf("Head Node의 다음노드 데이터: %c\n", nextNode.data);
        nextNode = *nextNode.next;
    }

    // printf("Head Node의 다음노드 데이터: %c\n", nextNode.data);
    // nextNode = *nextNode.next;
    // printf("NEXT 의 다음노드 데이터: %c\n", nextNode.data);
    // nextNode = *nextNode.next;
    // printf("NEXT 의 다음노드 데이터: %c\n", nextNode.data);
    // nextNode = *nextNode.next;
    // printf("Tail 의 다음노드 데이터: %c\n", nextNode.data);
    // nextNode = *nextNode.next; // Tail에서 다음 노드는 존재하지 않아서 오류
}

/******************************************************/
// 1) 노드를 하나 만들고 반환
static Node* create_node() {
    Node* node = (Node*)calloc(1, sizeof(Node)); // 노드를 생성
    node->next = NULL; // 이 노드의 다음 노드는 없다
    return node; // 생성된 노드를 반환
}

// 2) 만들어진 노드에 실제 데이터를 설정
// node: 기존에 존재하는 노드
// data: 기존에 존재하는 노드에 설정할 실제 데이터
void set_node(Node* node, int data) {
    node->data = data;
}

// is_empty(): 리스트 내에 노드가 존재하는지 true/false로 반환
bool is_empty(List* list) {
    if(list->head == NULL) {
        return true;
    }
    return false;
}

// add_node(): 리스트의 맨 뒤에 노드를 하나 추가하기 (tail에 노드를 추가하기)
void add_node(List* list, Node* node) {
    // 리스트가 비어있다면, 리스트의 head 로서 node를 설정한다
    if (is_empty(list)) {
        list->head = node;
        return;
    }
    // 리스트가 비어있지 않다면, head부터 next가 NULL인 노드까지 (Tail 노드까지) 찾아감
    /// => tail 의 next로 노드를 추가해야 하기 때문
    Node* tailNode = list->head;
    while (tailNode->next != NULL) {
        tailNode = tailNode->next;
    }
    /// while문이 끝났을 때, tailNode는 리스트의 마지막 노드가 된다.
    /// 추가하고 싶은 node를 tailNode의 next(다음 노드)로 설정한다
    tailNode->next = node;
}

// insert(): 리스트의 중간에 노드를 삽입하기 (index 위치에)
// index: List에 삽입할 위치
// Node: 삽입할 노드 데이터
void insert(List* list, int index, Node* node) {
    Node* curtNode = list->head;
    // 첫번째 위치에 insert한다는 것
    if (index == 0) {
        node->next = curtNode; // 새로 넣을 노드의 다음 노드가 원래 Head노드
        list->head = node; // 새로 넣을 노드가 새로운 head노드가 되면 된다
        return;
    }
    // 내가 넣을 위치까지 이동한다 (내가 넣을 위치의 전 노드까지 탐색한다)
    for (int i = 1; i < index; i++) {
        if (curtNode->next == NULL) {
            printf("Error: index 범위를 벗어났습니다\n");
            return;
        }
        curtNode = curtNode->next; // curtNode: i == 1
    }
    Node* nextNode = curtNode->next; // 전 노드의 다음노드 (원래 index위치에 있던 노드)
    curtNode->next = node; // 내가 넣을 위치의 전 노드의 다음 노드는 새로넣을노드다.
    node->next = nextNode; // 새로 넣을 노드의 다음노드는 원래의 전노드 다음노드(원래 index위치에 있던노드)
}

void remove_node(List* list, int index) {
    Node* curtNode = list->head;
    if (is_empty(list)) {
        printf("Error: 리스트가 비었습니다\n");
        return;
    }
    // 첫번째 위치에 insert한다는 것
    if (index == 0) {
        Node* next = list->head->next;
        list->head = next;
        return;
    }

    // 내가 넣을 위치까지 이동한다 (내가 넣을 위치의 전 노드까지 탐색한다)
    for (int i = 1; i < index; i++) {
        if (curtNode->next == NULL) {
            printf("Error: index 범위를 벗어났습니다\n");
            return;
        }
        curtNode = curtNode->next;
    }
    // curtNode는 index위치의 전 노드
    Node* nextNode = curtNode->next->next; // index위치의 다음 노드
    Node* indexNode = curtNode->next; //원래 index위치에 있던 노드
    curtNode->next = nextNode; // 전노드와 다음노드를 이어준다
    free(indexNode); // index위치의 노드는 메모리에서 해제
}

// 리스트에 존재하는 모든 요소(Node)들을 순서대로 순회
void print(List *list) {
    if (is_empty(list)) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (Node* node = list->head; node != NULL; node = node->next) {
        if (node->next == NULL) { // 마지막 데이터라면 , 빼고
            printf("%d", node->data);
        }else {  // 마지막 데이터가 아니면 , 넣고
            printf("%d, ", node->data);
        }
    }
    printf("]");
}


////// 선형 리스트 메인
void main() {
    // char_node_test();
    //// 선형 리스트 생성
    List list = { .head = NULL }; // 후, 초기화
    Node* node = create_node();
    set_node(node, 10);
    add_node(&list, node); // head node로 추가됨

    node = create_node();
    set_node(node, 100);
    add_node(&list, node); // head node의 다음으로 추가됨

    node = create_node();
    set_node(node, 1000);
    add_node(&list, node); // head node의 다음의 다음으로 추가됨

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
