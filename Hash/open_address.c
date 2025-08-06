#include "open_address.h"
#include "chain_hash.h"

#include <stdio.h>
#include <stdlib.h>

#include "../List/list.h"
/// �ؽ� �Լ� (�ؽ��� ���� �ؽð��� ������)
int open_hashing(int key) {
    return key % 13; // �ؽð��� return
}

// data�� ������ ��带 �ϳ� �����ϱ�
OPEN_ADDRESS_NODE* create_open_node(int data) {
    OPEN_ADDRESS_NODE* openNode = (OPEN_ADDRESS_NODE*)calloc(1, sizeof(OPEN_ADDRESS_NODE));
    openNode->data = data;
    openNode->status = NOT_EXISTS;
    return openNode;
}

// �ؽ� ���̺��� �����ϰ� �ʱ�ȭ�ϱ�
OPEN_ADDRESS_HASH* open_hash_init(int size) {
    OPEN_ADDRESS_HASH* chain_hash = (OPEN_ADDRESS_HASH*)calloc(1, sizeof(OPEN_ADDRESS_HASH));
    chain_hash->size = size;
    chain_hash->table = (OPEN_ADDRESS_NODE**)calloc(size, sizeof(OPEN_ADDRESS_NODE*));
    // ��� ��Ŷ�� NULL ���·� �����Ѵ�
    for (int i = 0; i < size; i++) {
        chain_hash->table[i] = create_open_node(0);
    }
    return chain_hash;
}

// chain hash���� ���ϴ� ������(NODE)�� ��������
OPEN_ADDRESS_NODE* open_hash_search(OPEN_ADDRESS_HASH* openHash, int data) {
    int hashValue = data;
    while (1) {
        // 1. Ž���� ��ġ�� �����Ѵ�
        hashValue = open_hashing(hashValue);
        // 2. Ž���� ��ġ�� ��带 �����´�
        OPEN_ADDRESS_NODE* node = openHash->table[hashValue++];
        // 3. ����� ���¸� Ȯ���ϸ鼭 ���� ��ġ�� ��� �̵��Ѵ�
        // �� ��ġ�� �����Ͱ� ������
        if (node->status == NOT_EXISTS) {
            return node;
        }
        if (node->status == EXISTS && node->data == data) {
            return node;
        }
    }
}

/// ü�� �ؽÿ� �����͸� �߰��ϱ�
void open_hash_add(OPEN_ADDRESS_HASH* openHash, int data) {
    int hashValue = data;
    while (1) {
        // 1. �߰��� ��ġ�� �����Ѵ�
        hashValue = open_hashing(hashValue);
        if (hashValue >= openHash->size) {
            puts("Error: �ؽð� �� ���� ���̻� ���� �� �����ϴ�");
            break;
        }
        // 2. �߰��� ��ġ�� ��带 �����´�
        OPEN_ADDRESS_NODE* node = openHash->table[hashValue];
        // 3. ����� ���¸� Ȯ���ϸ鼭 ���� ��ġ�� ��� �̵��Ѵ�
        // �� ��ġ�� �����Ͱ� ������
        if (node->status == NOT_EXISTS || node->status == DELETED) {
            // ��带 �̹� �������� ������ data�� status �����Ѵ�
            openHash->table[hashValue]->data = data;
            openHash->table[hashValue]->status = EXISTS;
            printf("[%d] �����͸� �߰��Ͽ����ϴ�\n", data);
            break;
        }
        hashValue++;
        // �� ��ġ�� ������ �����Ͱ� �ִ��� ==> ���� while��
    }
}


/// ü�� �ؽÿ��� ��带 �����ϱ�
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
    printf("20¥�� �ؽø� �����Ͽ���\n");
    open_hash_add(openHash, 5);
    open_hash_add(openHash, 1);
    open_hash_add(openHash, 2);
    ////// key�� �ߺ��� �Ǵ� �����͸� �߰���
    open_hash_add(openHash, 18); // 5�� ��ġ
    open_hash_add(openHash, 31); // 5�� ��ġ

    open_hash_add(openHash, 19); // 6�� ��ġ
    open_hash_add(openHash, 32); // 6�� ��ġ

    open_hash_add(openHash, 20); // 7�� ��ġ
    open_hash_add(openHash, 33); // 7�� ��ġ

    // ���ݱ��� �߰��� ���¸� ����ϱ�
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
    // ////////////////////////////// ��� ����
    open_hash_remove(openHash, 5); //
    open_hash_remove(openHash, 18); //
    open_hash_remove(openHash, 19); //
    open_hash_remove(openHash, 34); // ���� ������
    open_hash_add(openHash, 20);
    open_hash_print(openHash);
}




