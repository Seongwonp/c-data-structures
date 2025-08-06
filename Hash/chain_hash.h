#ifndef CHAIN_HASH_H
#define CHAIN_HASH_H

typedef struct chain_node{
    int data;
    struct chain_node *prev; // 노드의 전노드
    struct chain_node *next; // 노드의 다음노드
}CHAIN_NODE;

typedef struct {
    int size; // 해시 테이블의 크기
    CHAIN_NODE **table; // 해시테이블자체. 노드들이 들어있는 배열
}CHAIN_HASH;

#endif //CHAIN_HASH_H
