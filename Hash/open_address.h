#ifndef OPEN_ADDRESS_H
#define OPEN_ADDRESS_H

typedef enum {
    EXISTS, NOT_EXISTS, DELETED
}STATUS;

typedef struct open_address_node{
    int data;
    STATUS status;
}OPEN_ADDRESS_NODE;

typedef struct {
    int size; // 해시 테이블의 크기
    OPEN_ADDRESS_NODE **table; // 해시테이블자체. 노드들이 들어있는 배열
}OPEN_ADDRESS_HASH;

#endif //OPEN_ADDRESS_H
