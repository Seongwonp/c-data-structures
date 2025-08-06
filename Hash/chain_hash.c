#include "chain_hash.h"

#include <stdio.h>
#include <stdlib.h>
/// �ؽ� �Լ� (�ؽ��� ���� �ؽð��� ������)
int chain_hashing(int key) {
    return key % 13; // �ؽð��� return
}

// data�� ������ ��带 �ϳ� �����ϱ�
CHAIN_NODE* create_chain_node(int data) {
    CHAIN_NODE* chainNode = (CHAIN_NODE*)calloc(1, sizeof(CHAIN_NODE));
    chainNode->prev = NULL;
    chainNode->next = NULL;
    chainNode->data = data;
    return chainNode;
}

// �ؽ� ���̺��� �����ϰ� �ʱ�ȭ�ϱ�
CHAIN_HASH* chain_hash_init(int size) {
    CHAIN_HASH* chain_hash = (CHAIN_HASH*)calloc(1, sizeof(CHAIN_HASH));
    chain_hash->size = size;
    chain_hash->table = (CHAIN_NODE**)calloc(size, sizeof(CHAIN_NODE*));
    // ��� ��Ŷ�� NULL ���·� �����Ѵ�
    for (int i = 0; i < size; i++) {
        chain_hash->table[i] = NULL;
    }
    return chain_hash;
}

// chain hash���� ���ϴ� ������(NODE)�� ��������
CHAIN_NODE* chain_hash_search(CHAIN_HASH* chainHash, int data) {
    // 1. data�� key�� �ؼ� �ؽ� ���� �����Ѵ�
    int hashValue = chain_hashing(data);
    // 2. ����� �ؽð��� ��ġ�� �ִ� ����� ������(NODE)�� �����´�
    CHAIN_NODE* node = chainHash->table[hashValue];
    // 3. �� ��ġ�� ������ �����Ͱ� �ִ� ������ �̵��Ѵ�
    while (node != NULL) {
        if (node->data == data) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

/// ü�� �ؽÿ� �����͸� �߰��ϱ�
void chain_hash_add(CHAIN_HASH* chainHash, int data) {
    int hashValue = chain_hashing(data); // data�� key�� �ؼ� �ؽ� ���� �����Ѵ�
    // ����� �ؽð��� ��ġ�� �ִ� ����� ������(NODE)�� �����´�
    CHAIN_NODE* node = chainHash->table[hashValue];
    CHAIN_NODE* newNode = create_chain_node(data);
    if (node == NULL) {
        // ���� add �ϴ� data�� ã�� �� �������� �� ��ġ�� �����͸� �߰��ϸ� �ȴ�
        chainHash->table[hashValue] = newNode;
        printf("[%d]�� �߰��Ͽ���\n", data);
        return;
    }
    // ���ο� ���� ��ũ�帮��Ʈ�� �������� �߰��� ���̹Ƿ�, ������ �����Ͱ� �ִ� ������ �̵��Ѵ�
    while (1) {
        if (node->data == data) {
            printf("ERROR: �̹� �ش� ���(%d)�� �����մϴ�: �ߺ�!!\n", data);
            return;
        }
        // �� �������� �߰��Ѵٴ� �� == ������ ����� ������ �߰��Ѵٴ� ��
        if (node->next == NULL) {
            node->next = newNode; // �� ����� ������ ��
            newNode->prev = node; // �� ����� ���� ��
            printf("[%d]�� �߰��Ͽ���\n", data);
            return;
        }
        node = node->next;
    }
}
/// ü�� �ؽÿ��� ��带 �����ϱ�
void chain_hash_remove(CHAIN_HASH* chainHash, int data) {
    CHAIN_NODE* node = chain_hash_search(chainHash, data);
    // ���� ������� �����Ͱ� �����Ѵٸ�
    if (node != NULL) {
        // ���� �� ó�� ��忴�ٴ� ��
        if (node->prev == NULL) {
            // ���� ��ġ�� �ؽ̰����� ã�´�
            int hashValue = chain_hashing(data);
            // �ش� ��ġ�� ù��° ��带 ���� ���� ���� �����Ѵ�
            chainHash->table[hashValue] = node->next;
            node->next->prev = NULL;
            printf("ù ��° ��ġ�� �ִ� [%d] ��带 �����Ͽ����ϴ�\n", data);
        }
        // ���� ������ ��忴�ٴ� ��
        else if (node->next == NULL) {
            // �� ������� ������ ���ٰ� ���ش�
            node->prev->next = NULL;
            printf("������ ��ġ�� �ִ� [%d] ��带 �����Ͽ����ϴ�\n", data);
        }
        // ���� �߰��� �����ִ� ����� ��
        else {
            // �� �� ���� ���� ��带 ���� �̾��ش�
            node->prev = node->next;
            node->next = node->prev;
            printf("�߰� ��ġ�� �ִ� [%d] ��带 �����Ͽ����ϴ�\n", data);
        }
        // �޸𸮿��� �ڽ��� ����� (�ʼ�)
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
    printf("12¥�� �ؽø� �����Ͽ���\n");
    chain_hash_add(chainHash, 5);
    chain_hash_add(chainHash, 6);
    chain_hash_add(chainHash, 7);
    chain_hash_add(chainHash, 5);
    chain_hash_add(chainHash, 6);
    chain_hash_add(chainHash, 5);
    ////// key�� �ߺ��� �Ǵ� �����͸� �߰���
    chain_hash_add(chainHash, 18); // 5�� ��ġ
    chain_hash_add(chainHash, 31); // 5�� ��ġ

    chain_hash_add(chainHash, 19); // 6�� ��ġ
    chain_hash_add(chainHash, 32); // 6�� ��ġ

    chain_hash_add(chainHash, 20); // 7�� ��ġ
    chain_hash_add(chainHash, 33); // 7�� ��ġ

    // ���ݱ��� �߰��� ���¸� ����ϱ�
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
    ////////////////////////////// ��� ����
    chain_hash_remove(chainHash, 5); // ù��°
    chain_hash_remove(chainHash, 18); // �ι�°���µ� ù��°�� �����

    chain_hash_remove(chainHash, 32); // ������ ��ġ

    chain_hash_remove(chainHash, 20); // �߰� ��ġ


}




