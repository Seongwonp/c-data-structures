#include "open_address.h"
#include "chain_hash.h"

#include <stdio.h>
#include <stdlib.h>

#include "../List/list.h"
/// 해시 함수 (해싱을 통해 해시값을 도출함)
int open_hashing(int key) {
    return key % 13; // 해시값을 return
}

// data를 가지는 노드를 하나 생성하기
OPEN_ADDRESS_NODE* create_open_node(int data) {
    OPEN_ADDRESS_NODE* openNode = (OPEN_ADDRESS_NODE*)calloc(1, sizeof(OPEN_ADDRESS_NODE));
    openNode->data = data;
    openNode->status = NOT_EXISTS;
    return openNode;
}

// 해시 테이블을 생성하고 초기화하기
OPEN_ADDRESS_HASH* open_hash_init(int size) {
    OPEN_ADDRESS_HASH* chain_hash = (OPEN_ADDRESS_HASH*)calloc(1, sizeof(OPEN_ADDRESS_HASH));
    chain_hash->size = size;
    chain_hash->table = (OPEN_ADDRESS_NODE**)calloc(size, sizeof(OPEN_ADDRESS_NODE*));
    // 모든 버킷을 NULL 상태로 변경한다
    for (int i = 0; i < size; i++) {
        chain_hash->table[i] = create_open_node(0);
    }
    return chain_hash;
}

// chain hash에서 원하는 데이터(NODE)를 가져오기
OPEN_ADDRESS_NODE* open_hash_search(OPEN_ADDRESS_HASH* openHash, int data) {
    int hashValue = data;
    while (1) {
        // 1. 탐색할 위치를 추출한다
        hashValue = open_hashing(hashValue);
        // 2. 탐색할 위치의 노드를 가져온다
        OPEN_ADDRESS_NODE* node = openHash->table[hashValue++];
        // 3. 노드의 상태를 확인하면서 다음 위치로 계속 이동한다
        // 그 위치에 데이터가 없더라
        if (node->status == NOT_EXISTS) {
            return node;
        }
        if (node->status == EXISTS && node->data == data) {
            return node;
        }
    }
}

/// 체인 해시에 데이터를 추가하기
void open_hash_add(OPEN_ADDRESS_HASH* openHash, int data) {
    int hashValue = data;
    while (1) {
        // 1. 추가할 위치를 추출한다
        hashValue = open_hashing(hashValue);
        if (hashValue >= openHash->size) {
            puts("Error: 해시가 꽉 차서 더이상 넣을 수 없습니다");
            break;
        }
        // 2. 추가할 위치의 노드를 가져온다
        OPEN_ADDRESS_NODE* node = openHash->table[hashValue];
        // 3. 노드의 상태를 확인하면서 다음 위치로 계속 이동한다
        // 그 위치에 데이터가 없더라
        if (node->status == NOT_EXISTS || node->status == DELETED) {
            // 노드를 이미 만들어놨기 때문에 data랑 status 설정한다
            openHash->table[hashValue]->data = data;
            openHash->table[hashValue]->status = EXISTS;
            printf("[%d] 데이터를 추가하였습니다\n", data);
            break;
        }
        hashValue++;
        // 그 위치에 갔더니 데이터가 있더라 ==> 다음 while로
    }
}


/// 체인 해시에서 노드를 제거하기
void open_hash_remove(OPEN_ADDRESS_HASH* openHash, int data) {
    OPEN_ADDRESS_NODE* node = open_hash_search(openHash, data);
    if (node->status == EXISTS) {
        node->status = DELETED;
        node->data = 0;
    }
}

void open_hash_print(OPEN_ADDRESS_HASH* openHash) {
    puts("========= PRINT ============= ");
    for (int i = 0; i < openHash->size; i++) {
        OPEN_ADDRESS_NODE* node = openHash->table[i];
        if (node->status == NOT_EXISTS) {
            printf("[%d]: 0(NOT_EXISTS)\n", i);
        }
        else if (node->status == DELETED) {
            printf("[%d]: 0(DELETED)\n", i);
        }
        else {
            printf("[%d]: %d\n", i, node->data);
        }
    }
    puts("========= END ============= ");
}

void main() {
    OPEN_ADDRESS_HASH* openHash = open_hash_init(20);
    printf("20짜리 해시를 생성하였음\n");
    open_hash_add(openHash, 5);
    open_hash_add(openHash, 1);
    open_hash_add(openHash, 2);
    ////// key가 중복이 되는 데이터를 추가함
    open_hash_add(openHash, 18); // 5의 위치
    open_hash_add(openHash, 31); // 5의 위치

    open_hash_add(openHash, 19); // 6의 위치
    open_hash_add(openHash, 32); // 6의 위치

    open_hash_add(openHash, 20); // 7의 위치
    open_hash_add(openHash, 33); // 7의 위치

    // 지금까지 추가한 형태를 출력하기
    open_hash_print(openHash);


    /****************************************************/
    CHAIN_NODE* node;
    node = open_hash_search(openHash, 1);
    printf("%d\n", node->data);
    node = open_hash_search(openHash, 2);
    printf("%d\n", node->data);
    node = open_hash_search(openHash, 18);
    printf("%d\n", node->data);
    node = open_hash_search(openHash, 19);
    printf("%d\n", node->data);
    // ////////////////////////////// 노드 제거
    open_hash_remove(openHash, 5); //
    open_hash_remove(openHash, 18); //
    open_hash_remove(openHash, 19); //
    open_hash_remove(openHash, 34); // 없는 데이터
    open_hash_add(openHash, 20);
    open_hash_print(openHash);
}




