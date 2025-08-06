#include "union_find.h"

#include <stdio.h>

#include "stdbool.h"

int setDatas[4];
// x �����Ͱ� ���� ������ ��ǥ ����(root)�� ã��
int set_find(int x) {
    // �ڽ��� root�����
    if (setDatas[x] == x) {
        return x; // �ڱ� �ڽ��� return
    }
    // �׷��� �ʴٸ� x�� �θ� ã�Ƽ� ����
    setDatas[x] = set_find(setDatas[x]);
    return setDatas[x];
}
// x�� y�� ���� �� ������ ��ġ��
void set_union(int x, int y){
    int root1 = set_find(x); // x�� root ��带 Ž��
    int root2 = set_find(y); // y�� root ��带 Ž��
    setDatas[root1] = root2; // x�� ���� ������ y�� ���� ���տ� ��ħ
}

void main() {
    // [0, 1, 2]�� ��� 1�� ��� 2�� ���� UNION ������ ���� �Ѵٴ� �ǹ�
    // [1, 1, 3]�� ��� 1�� ��� 3�� ���� ���տ� ���� ������ TRUE, �ƴϸ� FALSE
    // �� ������ ��Ʈ ��带 �������� ��Ʈ ��尡 ���� ��带 �� ū ����� �ڽ����� ����
    // (0: UNION����, 1: FIND ����)
    int operations[][3] = {
        {0, 0, 1},
        {1, 1, 2},
        {0, 1, 2},
        {1, 0, 2}
    };
    // setDatas: �� ��带 ������ �迭
    for (int i = 0; i < 4; i++) {
        setDatas[i] = i; // ó������ �ڱ� �ڽ��� ��Ʈ ����� ����
    }
    // ������ ������ union, find ������ ������� ����
    for (int i = 0; i < 4; i++) {
        // 0: UNION ����
        if (operations[i][0] == 0) {
            set_union(operations[i][1], operations[i][2]);
        }
        // 1: FIND ����
        else {
            // �� ����� ��Ʈ ��尡 ������ Ȯ���Ѵ�
            // (union�� �� �Ǿ��ٸ� true, �װ� �ƴ϶�� false)
            bool result = set_find(operations[i][1]) == set_find(operations[i][2]);
            printf("NODE-%d �� NODE-%d �� %d\n",operations[i][1], operations[i][2], result);
        }
    }







}













