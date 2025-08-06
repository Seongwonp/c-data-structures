#ifndef LIST_H
#define LIST_H
typedef struct charNode {
    char data; // 실제 노드가 저장하는 데이터
    struct charNode *next; // 이 노드의 다음노드 주소
}CharNode;
///// int 데이터가 들어가는 Node
typedef struct node {
    int data;
    struct node *next;
}Node;
/// Node가 들어있는 List 정의
typedef struct {
    Node *head;
}List;








#endif //LIST_H
