#include "chain_hash.h"

#include <stdio.h>
#include <stdlib.h>
/// 해시 함수 (해싱을 통해 해시값을 도출함)
int chain_hashing(int key) {
    return key % 13; // 해시값을 return
}

// data를 가지는 노드를 하나 생성하기
CHAIN_NODE* create_chain_node(int data) {
    CHAIN_NODE* chainNode = (CHAIN_NODE*)calloc(1, sizeof(CHAIN_NODE));
    chainNode->prev = NULL;
    chainNode->next = NULL;
    chainNode->data = data;
    return chainNode;
}

// 해시 테이블을 생성하고 초기화하기
CHAIN_HASH* chain_hash_init(int size) {
    CHAIN_HASH* chain_hash = (CHAIN_HASH*)calloc(1, sizeof(CHAIN_HASH));
    chain_hash->size = size;
    chain_hash->table = (CHAIN_NODE**)calloc(size, sizeof(CHAIN_NODE*));
    // 모든 버킷을 NULL 상태로 변경한다
    for (int i = 0; i < size; i++) {
        chain_hash->table[i] = NULL;
    }
    return chain_hash;
}

// chain hash에서 원하는 데이터(NODE)를 가져오기
CHAIN_NODE* chain_hash_search(CHAIN_HASH* chainHash, int data) {
    // 1. data를 key로 해서 해싱 값을 도출한다
    int hashValue = chain_hashing(data);
    // 2. 도출된 해시값의 위치에 있는 저장된 데이터(NODE)를 가져온다
    CHAIN_NODE* node = chainHash->table[hashValue];
    // 3. 그 위치에 마지막 데이터가 있는 곳까지 이동한다
    while (node != NULL) {
        if (node->data == data) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

/// 체인 해시에 데이터를 추가하기
void chain_hash_add(CHAIN_HASH* chainHash, int data) {
    int hashValue = chain_hashing(data); // data를 key로 해서 해싱 값을 도출한다
    // 도출된 해시값의 위치에 있는 저장된 데이터(NODE)를 가져온다
    CHAIN_NODE* node = chainHash->table[hashValue];
    CHAIN_NODE* newNode = create_chain_node(data);
    if (node == NULL) {
        // 내가 add 하는 data를 찾을 수 없었으면 그 위치에 데이터를 추가하면 된다
        chainHash->table[hashValue] = newNode;
        printf("[%d]를 추가하였음\n", data);
        return;
    }
    // 새로운 노드는 링크드리스트의 마지막에 추가할 것이므로, 마지막 데이터가 있는 곳까지 이동한다
    while (1) {
        if (node->data == data) {
            printf("ERROR: 이미 해당 노드(%d)가 존재합니다: 중복!!\n", data);
            return;
        }
        // 맨 마지막에 추가한다는 것 == 마지막 노드의 다음에 추가한다는 것
        if (node->next == NULL) {
            node->next = newNode; // 전 노드의 다음은 나
            newNode->prev = node; // 내 노드의 전은 너
            printf("[%d]를 추가하였음\n", data);
            return;
        }
        node = node->next;
    }
}
/// 체인 해시에서 노드를 제거하기
void chain_hash_remove(CHAIN_HASH* chainHash, int data) {
    CHAIN_NODE* node = chain_hash_search(chainHash, data);
    // 내가 지우려는 데이터가 존재한다면
    if (node != NULL) {
        // 내가 맨 처음 노드였다는 뜻
        if (node->prev == NULL) {
            // 나의 위치를 해싱값으로 찾는다
            int hashValue = chain_hashing(data);
            // 해당 위치의 첫번째 노드를 나의 다음 노드로 설정한다
            chainHash->table[hashValue] = node->next;
            node->next->prev = NULL;
            printf("첫 번째 위치에 있던 [%d] 노드를 제거하였습니다\n", data);
        }
        // 내가 마지막 노드였다는 뜻
        else if (node->next == NULL) {
            // 내 전노드의 다음은 없다고 해준다
            node->prev->next = NULL;
            printf("마지막 위치에 있던 [%d] 노드를 제거하였습니다\n", data);
        }
        // 내가 중간에 끼여있는 노드라는 뜻
        else {
            // 내 전 노드와 다음 노드를 서로 이어준다
            node->prev = node->next;
            node->next = node->prev;
            printf("중간 위치에 있던 [%d] 노드를 제거하였습니다\n", data);
        }
        // 메모리에서 자신을 지운다 (필수)
        free(node);
    }
}

void chain_hash_print(CHAIN_HASH* chain_hash) {
    puts("========= PRINT ============= ");
    for (int i = 0; i < chain_hash->size; i++) {
        printf("[%d]: ", i);
        CHAIN_NODE* node = chain_hash->table[i];
        while (1) {
            if (node == NULL) {
                break;
            }
            printf("%d", node->data);
            node = node->next;
            if (node != NULL) {
                printf(" -> ");
            }
        }
        printf("\n");
    }
    puts("========= END ============= ");
}


void main() {
    CHAIN_HASH* chainHash = chain_hash_init(12);
    printf("12짜리 해시를 생성하였음\n");
    chain_hash_add(chainHash, 5);
    chain_hash_add(chainHash, 6);
    chain_hash_add(chainHash, 7);
    chain_hash_add(chainHash, 5);
    chain_hash_add(chainHash, 6);
    chain_hash_add(chainHash, 5);
    ////// key가 중복이 되는 데이터를 추가함
    chain_hash_add(chainHash, 18); // 5의 위치
    chain_hash_add(chainHash, 31); // 5의 위치

    chain_hash_add(chainHash, 19); // 6의 위치
    chain_hash_add(chainHash, 32); // 6의 위치

    chain_hash_add(chainHash, 20); // 7의 위치
    chain_hash_add(chainHash, 33); // 7의 위치

    // 지금까지 추가한 형태를 출력하기
    chain_hash_print(chainHash);


    /****************************************************/
    CHAIN_NODE* node;
    node = chain_hash_search(chainHash, 1);
    printf("%d\n", node != NULL ? node->data : -1);
    node = chain_hash_search(chainHash, 5);
    printf("%d\n", node != NULL ? node->data : -1);
    node = chain_hash_search(chainHash, 31);
    printf("%d\n", node != NULL ? node->data : -1);
    node = chain_hash_search(chainHash, 18);
    printf("%d\n", node != NULL ? node->data : -1);
    ////////////////////////////// 노드 제거
    chain_hash_remove(chainHash, 5); // 첫번째
    chain_hash_remove(chainHash, 18); // 두번째였는데 첫번째로 변경됨

    chain_hash_remove(chainHash, 32); // 마지막 위치

    chain_hash_remove(chainHash, 20); // 중간 위치


}




