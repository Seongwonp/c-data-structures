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


// BFS Ž���� ����Ͽ� startNode���� Ž��
void bfs(char startNode) {
    // ��带 �湮�ߴ��� üũ�ϴ� �迭
    bool* visited = (bool*)calloc(12, sizeof(bool));
    /////// Queue�� �����Ѵ� (node�� ������ŭ)
    /// �湮�� ������ ����
    INT_QUEUE* queue = queue_init(100);
    // ���۳�带 �ĺ��� �ְ� �����Ѵ�
    enqueue(queue, startNode);
    // ��� �ĺ� ��带 �湮�Ҷ����� �ݺ��Ѵ�
    while (!is_queue_empty(queue)) {
        char curtNode = (char)dequeue(queue); // �ĺ��ϳ��� �����´� (���� �� ��带 �湮)
        // �� ��尡 �̹� �湮�� ���� �ִ� �����
        if (visited[curtNode-65]) {
            continue; // �湮���� �ʰ� ���� �ĺ� ��带 Ž���Ѵ�
        }
        visited[curtNode-65] = true; // �� ���� �湮�Ǿ��� üũ
        printf("[%c (%d)]�� �湮��\n", curtNode, curtNode);
        // ���� �湮�� ����� �ĺ� �迭�� �����´�
        // ���� �湮�� ���� ����Ǿ� �ִ� ��� ��带 �ĺ��� �߰��Ѵ�
        for (int i = 0; i < graph[curtNode-65][i] != '\0'; i++) {
            char candidate = graph[curtNode-65][i]; // ����� ��带 �����´�
            enqueue(queue, candidate); // �ĺ��� �߰��Ѵ�
        }
        print_char_queue(queue);
    }
}

void dfs(char startNode) {
    // ��带 �湮�ߴ��� üũ�ϴ� �迭
    bool* visited = (bool*)calloc(12, sizeof(bool));
    /////// Queue�� �����Ѵ� (node�� ������ŭ)
    /// �湮�� ������ ����
    INT_STACK stack;
    stack.top = 0;
    stack.size = 100;  // ������ �ִ�ġ�� ����
    /// ���� �����Ͱ� �� �迭 ���� (size ũ���)
    stack.datas = (int*)calloc(stack.size, sizeof(int));

    // ���۳�带 �ĺ��� �ְ� �����Ѵ�
    push(&stack, startNode);
    // ��� �ĺ� ��带 �湮�Ҷ����� �ݺ��Ѵ�
    while (!is_empty(&stack)) {
        char curtNode = (char)pop(&stack); // �ĺ��ϳ��� �����´� (���� �� ��带 �湮)
        // �� ��尡 �̹� �湮�� ���� �ִ� �����
        if (visited[curtNode-65]) {
            continue; // �湮���� �ʰ� ���� �ĺ� ��带 Ž���Ѵ�
        }
        visited[curtNode-65] = true; // �� ���� �湮�Ǿ��� üũ
        printf("[%c(%d)]�� �湮��\n", curtNode, curtNode);
        // ���� �湮�� ����� �ĺ� �迭�� �����´�
        // ���� �湮�� ���� ����Ǿ� �ִ� ��� ��带 �ĺ��� �߰��Ѵ�
        for (int i = 0; i < graph[curtNode-65][i] != '\0'; i++) {
            char candidate = graph[curtNode-65][i]; // ����� ��带 �����´�
            push(&stack, candidate); // �ĺ��� �߰��Ѵ�
        }
    }
}

void recursive_dfs(char curtNode, bool* visited) {
    // �湮�� ���� �ִ� ����� return
    if (visited[curtNode-65]) {
        return;
    }
    // ���� ��带 �湮�ߴٰ� üũ�Ѵ�
    visited[curtNode-65] = true;
    printf("[%c(%d)]�� �湮��\n", curtNode, curtNode);
    // �ڽŰ� ����Ǿ��ִ� ��� ������ �湮
    for (int i = 0; i < graph[curtNode-65][i] != '\0'; i++) {
        char candidate = graph[curtNode-65][i]; // ����� ��带 �����´�
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
#define INF 999999999 // ���Ѵ� ����
#define EDGE_COUNT 9 // �� ������ ����
#define NODE_COUNT 7 // �� ����� ����

// ��� ��尡 �湮�Ǿ��ִ��� Ȯ�� (���� ��� ����)
bool is_all_visited(bool visited[]) {
    for (int i = 0; i < NODE_COUNT; i++) {
        if (!visited[i]) return false; // �ϳ��� �湮�Ǿ����� ������ false
    }
    return true; // ��� ��带 �湮�ߴٸ� true
}
// �ĺ� ���(�湮�Ǿ����� ���� ����) ��, ���� cost�� ���� ��带 ã��
char find_next_node(bool visited[], int costs[]) {
    int smallest_cost = INF; // �ּҰ��� ���ؼ� �־�� ����.
    char findNode = '\0'; // ������ ������ �ĺ��� ���ؼ� �־�� ����.
    for (int i = 0; i < NODE_COUNT; i++) {
        // �湮�Ǿ����� �����鼭, ���� �ּҰ����� �� ���� cost�� �߰��ߴٸ�
        if (!visited[i] && costs[i] < smallest_cost) {
            smallest_cost = costs[i]; // �� cost�� ���� �ּҰ��̴�.
            findNode = (char)(i + 65); // �� cost�� ������ node�� ������ ������ �ĺ��̴�.
        }
    }
    return findNode;
}


void dijkstra(char startNode) {
    bool visited[NODE_COUNT]  = {false, false, false, false, false, false};
    // ��� ��带 ���� cost�� �����ϰ� ����
    int costs[NODE_COUNT] = {INF, INF, INF, INF, INF, INF, INF};
    // �ڱ� �ڽ� ���� ���� �ִܰŸ��� 0���� ����
    costs[startNode-65] = 0;
    // ���� ��� ���� (������ �湮�� �ĺ����)
    char curtNode = startNode;
    // ��� �ĺ� ��带 ��ȸ�ϸ鼭 �ݺ��Ѵ�. (������ �湮�� �ĺ���尡 NULL�̸� ���� �湮�Ѱ��̴�.)
    while (curtNode != '\0') {
        // ���� ���� �湮�ߴٰ� üũ���ش�
        visited[curtNode-65] = true;
        printf("�湮�� �ĺ�:%c\n", curtNode);
        // ������ ����(����Ǿ��ִ� �� �� ����)��ŭ ��ȸ�ϸ�, ���� ���� ����� �ٸ� ������ Ž��
        for (int i = 0; i < EDGE_COUNT; i++) {
            int cost = connected[i][2]; // ����� cost
            // ���� ����Ǿ��ִ� ������, ���� ��� �� �ϳ��� ���� ����� (�������� ������� ã�Ҵٸ�)
            // ����, �ݴ��� ���� �湮�� ���� ���� ��忩�� �Ѵ�
            if (connected[i][0] == curtNode && !visited[connected[i][1]-65]) {
                // 2) �ݴ��� ������ ���� �ִ� cost�� �����Ѵ�
                // 2-1) �ĺ� ��尡 ������ �ִ� ����Ȳ �ִ� cost ����, ���ݰ��� ���� �� �������� Ȯ��
                int existsCost = costs[connected[i][1]-65]; // ������ ������ �ִ� �ݴ��� ����� ���
                int nowCost = costs[curtNode-65] + cost; // ���� ��忡�� �ݴ��� ���� ���� ���
                if (existsCost > nowCost) { // ���ݰ��� ���� �� ������ζ�� (����� ������)
                    costs[connected[i][1]-65] = nowCost; // �����Ѵ�
                }
            }
            else if (connected[i][1] == curtNode && !visited[connected[i][0]-65]) {
                // 2) �ݴ��� ������ ���� �ִ� cost�� �����Ѵ�
                // 2-1) �ĺ� ��尡 ������ �ִ� ����Ȳ �ִ� cost ����, ���ݰ��� ���� �� �������� Ȯ��
                int existsCost = costs[connected[i][0]-65]; // ������ ������ �ִ� �ݴ��� ����� ���
                int nowCost = costs[curtNode-65] + cost; // ���� ��忡�� �ݴ��� ���� ���� ���
                if (existsCost > nowCost) { // ���ݰ��� ���� �� ������ζ�� (����� ������)
                    costs[connected[i][0]-65] = nowCost; // �����Ѵ�
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
        // printf("������ �湮�� �ĺ�:%c\n", curtNode);
    }
}


void graph_main() {
    // bfs('A');
    // dfs('A');
    // recursive_dfs('A', calloc(12, sizeof(bool)));
    dijkstra('A');
}


