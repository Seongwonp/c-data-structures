#include "union_find.h"

#include <stdio.h>

#include "stdbool.h"

int setDatas[4];
// x 데이터가 속한 집합의 대표 원소(root)를 찾기
int set_find(int x) {
    // 자신이 root노드라면
    if (setDatas[x] == x) {
        return x; // 자기 자신을 return
    }
    // 그렇지 않다면 x의 부모를 찾아서 저장
    setDatas[x] = set_find(setDatas[x]);
    return setDatas[x];
}
// x와 y가 속한 두 집합을 합치기
void set_union(int x, int y){
    int root1 = set_find(x); // x의 root 노드를 탐색
    int root2 = set_find(y); // y의 root 노드를 탐색
    setDatas[root1] = root2; // x가 속한 집합을 y가 속한 집합에 합침
}

void main() {
    // [0, 1, 2]는 노드 1과 노드 2에 대해 UNION 연산을 수행 한다는 의미
    // [1, 1, 3]는 노드 1과 노드 3이 같은 집합에 속해 있으면 TRUE, 아니며 FALSE
    // 각 집합의 루트 노드를 기준으로 루트 노드가 작은 노드를 더 큰 노드의 자식으로 연결
    // (0: UNION연산, 1: FIND 연산)
    int operations[][3] = {
        {0, 0, 1},
        {1, 1, 2},
        {0, 1, 2},
        {1, 0, 2}
    };
    // setDatas: 각 노드를 가지는 배열
    for (int i = 0; i < 4; i++) {
        setDatas[i] = i; // 처음에는 자기 자신이 루트 노드라고 설정
    }
    // 위에서 정의한 union, find 연산을 순서대로 수행
    for (int i = 0; i < 4; i++) {
        // 0: UNION 연산
        if (operations[i][0] == 0) {
            set_union(operations[i][1], operations[i][2]);
        }
        // 1: FIND 연산
        else {
            // 두 노드의 루트 노드가 같은지 확인한다
            // (union이 잘 되었다면 true, 그게 아니라면 false)
            bool result = set_find(operations[i][1]) == set_find(operations[i][2]);
            printf("NODE-%d 와 NODE-%d 는 %d\n",operations[i][1], operations[i][2], result);
        }
    }







}













