#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"
#include "../Queue/queue.h"
#include "../Stack/stack.h"

char graph[][12] = {
    {'B', 'C', 'D'}, // A
    {'A', 'E', 'F'}, // B
    {'A', 'H'}, // C
    {'A', 'I', 'J'}, // D
    {'B', 'K'}, // E
    {'B'}, // F
    {'H'}, // G
    {'C', 'G'}, // H
    {'D'}, // I
    {'J', 'L'}, // J
    {'E'}, // K
    {'J'} // L
};


// BFS 탐색을 사용하여 startNode부터 탐색
void bfs(char startNode) {
    // 노드를 방문했는지 체크하는 배열
    bool* visited = (bool*)calloc(12, sizeof(bool));
    /////// Queue를 생성한다 (node의 개수만큼)
    /// 방문할 노드들을 저장
    INT_QUEUE* queue = queue_init(100);
    // 시작노드를 후보로 넣고 시작한다
    enqueue(queue, startNode);
    // 모든 후보 노드를 방문할때까지 반복한다
    while (!is_queue_empty(queue)) {
        char curtNode = (char)dequeue(queue); // 후보하나를 가져온다 (현재 이 노드를 방문)
        // 이 노드가 이미 방문한 적이 있는 노드라면
        if (visited[curtNode-65]) {
            continue; // 방문하지 않고 다음 후보 노드를 탐색한다
        }
        visited[curtNode-65] = true; // 이 노드는 방문되었음 체크
        printf("[%c (%d)]를 방문함\n", curtNode, curtNode);
        // 현재 방문한 노드의 후보 배열을 가져온다
        // 현재 방문한 노드와 연결되어 있는 모든 노드를 후보로 추가한다
        for (int i = 0; i < graph[curtNode-65][i] != '\0'; i++) {
            char candidate = graph[curtNode-65][i]; // 연결된 노드를 가져온다
            enqueue(queue, candidate); // 후보로 추가한다
        }
        print_char_queue(queue);
    }
}

void dfs(char startNode) {
    // 노드를 방문했는지 체크하는 배열
    bool* visited = (bool*)calloc(12, sizeof(bool));
    /////// Queue를 생성한다 (node의 개수만큼)
    /// 방문할 노드들을 저장
    INT_STACK stack;
    stack.top = 0;
    stack.size = 100;  // 스택의 최대치를 설정
    /// 실제 데이터가 들어갈 배열 생성 (size 크기로)
    stack.datas = (int*)calloc(stack.size, sizeof(int));

    // 시작노드를 후보로 넣고 시작한다
    push(&stack, startNode);
    // 모든 후보 노드를 방문할때까지 반복한다
    while (!is_empty(&stack)) {
        char curtNode = (char)pop(&stack); // 후보하나를 가져온다 (현재 이 노드를 방문)
        // 이 노드가 이미 방문한 적이 있는 노드라면
        if (visited[curtNode-65]) {
            continue; // 방문하지 않고 다음 후보 노드를 탐색한다
        }
        visited[curtNode-65] = true; // 이 노드는 방문되었음 체크
        printf("[%c(%d)]를 방문함\n", curtNode, curtNode);
        // 현재 방문한 노드의 후보 배열을 가져온다
        // 현재 방문한 노드와 연결되어 있는 모든 노드를 후보로 추가한다
        for (int i = 0; i < graph[curtNode-65][i] != '\0'; i++) {
            char candidate = graph[curtNode-65][i]; // 연결된 노드를 가져온다
            push(&stack, candidate); // 후보로 추가한다
        }
    }
}

void recursive_dfs(char curtNode, bool* visited) {
    // 방문한 적이 있는 노드라면 return
    if (visited[curtNode-65]) {
        return;
    }
    // 현재 노드를 방문했다고 체크한다
    visited[curtNode-65] = true;
    printf("[%c(%d)]를 방문함\n", curtNode, curtNode);
    // 자신과 연결되어있는 모든 노드들을 방문
    for (int i = 0; i < graph[curtNode-65][i] != '\0'; i++) {
        char candidate = graph[curtNode-65][i]; // 연결된 노드를 가져온다
        recursive_dfs(candidate, visited);
    }
}

int connected[][3] = {
    {'A', 'B', 2},
    {'C', 'A', 5},
    {'B', 'C', 6},
    {'B', 'D', 1},
    {'D', 'E', 4},
    {'B', 'E', 3},
    {'G', 'E', 9},
    {'G', 'F', 7},
    {'C', 'F', 8}
};
#define INF 999999999 // 무한대 설정
#define EDGE_COUNT 9 // 총 간선의 개수
#define NODE_COUNT 7 // 총 노드의 개수

// 모든 노드가 방문되어있는지 확인 (현재 사용 안함)
bool is_all_visited(bool visited[]) {
    for (int i = 0; i < NODE_COUNT; i++) {
        if (!visited[i]) return false; // 하나라도 방문되어있지 않으면 false
    }
    return true; // 모든 노드를 방문했다면 true
}
// 후보 노드(방문되어있지 않은 노드들) 중, 가장 cost가 작은 노드를 찾기
char find_next_node(bool visited[], int costs[]) {
    int smallest_cost = INF; // 최소값을 구해서 넣어둘 변수.
    char findNode = '\0'; // 다음에 가야할 후보를 구해서 넣어둘 변수.
    for (int i = 0; i < NODE_COUNT; i++) {
        // 방문되어있지 않으면서, 현재 최소값보다 더 작은 cost를 발견했다면
        if (!visited[i] && costs[i] < smallest_cost) {
            smallest_cost = costs[i]; // 그 cost가 이제 최소값이다.
            findNode = (char)(i + 65); // 그 cost를 가지는 node가 다음에 가야할 후보이다.
        }
    }
    return findNode;
}


void dijkstra(char startNode) {
    bool visited[NODE_COUNT]  = {false, false, false, false, false, false};
    // 모든 노드를 무한 cost로 설정하고 시작
    int costs[NODE_COUNT] = {INF, INF, INF, INF, INF, INF, INF};
    // 자기 자신 노드로 가는 최단거리는 0으로 설정
    costs[startNode-65] = 0;
    // 현재 노드 설정 (다음에 방문할 후보노드)
    char curtNode = startNode;
    // 모든 후보 노드를 순회하면서 반복한다. (다음에 방문할 후보노드가 NULL이면 전부 방문한것이다.)
    while (curtNode != '\0') {
        // 현재 노드는 방문했다고 체크해준다
        visited[curtNode-65] = true;
        printf("방문한 후보:%c\n", curtNode);
        // 간선의 개수(연결되어있는 선 총 개수)만큼 순회하며, 현재 노드와 연결된 다른 노드들을 탐색
        for (int i = 0; i < EDGE_COUNT; i++) {
            int cost = connected[i][2]; // 연결된 cost
            // 현재 연결되어있는 선에서, 양쪽 노드 중 하나가 현재 노드라면 (누군가와 연결됨을 찾았다면)
            // 또한, 반대쪽 노드는 방문한 적이 없는 노드여야 한다
            if (connected[i][0] == curtNode && !visited[connected[i][1]-65]) {
                // 2) 반대쪽 노드까지 가는 최단 cost를 갱신한다
                // 2-1) 후보 노드가 가지고 있는 현상황 최단 cost 보다, 지금가는 길이 더 최적인지 확인
                int existsCost = costs[connected[i][1]-65]; // 기존에 가지고 있던 반대쪽 노드의 비용
                int nowCost = costs[curtNode-65] + cost; // 지금 노드에서 반대쪽 노드로 가는 비용
                if (existsCost > nowCost) { // 지금가는 길이 더 최적경로라면 (비용이 낮으면)
                    costs[connected[i][1]-65] = nowCost; // 갱신한다
                }
            }
            else if (connected[i][1] == curtNode && !visited[connected[i][0]-65]) {
                // 2) 반대쪽 노드까지 가는 최단 cost를 갱신한다
                // 2-1) 후보 노드가 가지고 있는 현상황 최단 cost 보다, 지금가는 길이 더 최적인지 확인
                int existsCost = costs[connected[i][0]-65]; // 기존에 가지고 있던 반대쪽 노드의 비용
                int nowCost = costs[curtNode-65] + cost; // 지금 노드에서 반대쪽 노드로 가는 비용
                if (existsCost > nowCost) { // 지금가는 길이 더 최적경로라면 (비용이 낮으면)
                    costs[connected[i][0]-65] = nowCost; // 갱신한다
                }
            }
        }
        printf("visited: ");
        for (int i = 0; i < NODE_COUNT; i++) {
            printf("%c ", visited[i] == 1 ? 'T' : 'F');
        }
        printf("\n");
        printf("costs: ");
        for (int i = 0; i < NODE_COUNT; i++) {
            printf("%d ", costs[i]);
        }
        printf("\n\n");
        curtNode = find_next_node(visited, costs);
        // printf("다음에 방문할 후보:%c\n", curtNode);
    }
}


void graph_main() {
    // bfs('A');
    // dfs('A');
    // recursive_dfs('A', calloc(12, sizeof(bool)));
    dijkstra('A');
}


