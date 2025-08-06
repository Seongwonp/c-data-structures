#include "binary_tree.h"

#include <stdio.h>
#include <stdlib.h>

BTREE_NODE *create_node(int data) {
    BTREE_NODE *node = (BTREE_NODE *)malloc(sizeof(BTREE_NODE));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}
/// 해당 노드의 왼쪽 자식을 가져오기
BTREE_NODE* get_left(BTREE_NODE* node) {
    return node->left;
}
/// 해당 노드의 오른쪽 자식을 가져오기
BTREE_NODE* get_right(BTREE_NODE* node) {
    return node->right;
}
void set_left(BTREE_NODE* parent, BTREE_NODE* child) {
    if (parent->left == NULL) {
        parent->left = child;
    }
}
void set_right(BTREE_NODE* parent, BTREE_NODE* child) {
    if (parent->right == NULL) {
        parent->right = child;
    }
}
void preorder(BTREE_NODE* node) {
    printf("%c ", node->data);
    BTREE_NODE* left = get_left(node);
    if (left != NULL) {
        preorder(left);
    }
    BTREE_NODE* right = get_right(node);
    if (right != NULL) {
        preorder(right);
    }
}

void inorder(BTREE_NODE* node) {
    BTREE_NODE* left = get_left(node);
    if (left != NULL) {
        inorder(left);
    }
    printf("%c ", node->data);
    BTREE_NODE* right = get_right(node);
    if (right != NULL) {
        inorder(right);
    }
}
void postorder(BTREE_NODE* node) {
    BTREE_NODE* left = get_left(node);
    if (left != NULL) {
        postorder(left);
    }
    BTREE_NODE* right = get_right(node);
    if (right != NULL) {
        postorder(right);
    }
    printf("%c ", node->data);
}


void main() {
    BTREE_NODE* aNode = create_node('A'); // 최상위
    BTREE_NODE* bNode = create_node('B'); // 왼쪽
    BTREE_NODE* cNode = create_node('C'); // 오른쪽
    BTREE_NODE* dNode = create_node('D');
    BTREE_NODE* eNode = create_node('E');
    BTREE_NODE* fNode = create_node('F');
    BTREE_NODE* gNode = create_node('G');
    BTREE_NODE* hNode = create_node('H');
    BTREE_NODE* iNode = create_node('I');
    BTREE_NODE* jNode = create_node('J');
    BTREE_NODE* kNode = create_node('K');
    BTREE_NODE* lNode = create_node('L');

    set_left(aNode, bNode);
    set_right(aNode, cNode);

    set_left(bNode, dNode);
    set_right(bNode, eNode);

    set_left(dNode, hNode);

    set_left(eNode, iNode);
    set_right(eNode, jNode);

    set_left(cNode, fNode);
    set_right(cNode, gNode);

    set_left(fNode, kNode);
    set_right(fNode, lNode);
    // 최상위 노드인 A노드부터 시작해서 전위순회
    preorder(aNode);
    printf("\n");
    inorder(aNode);
    printf("\n");
    postorder(aNode);
}




