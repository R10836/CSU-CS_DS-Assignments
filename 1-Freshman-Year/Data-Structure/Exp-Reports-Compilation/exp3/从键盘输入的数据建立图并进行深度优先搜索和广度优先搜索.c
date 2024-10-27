#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 30

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    Node* adjList[MAX_NODES];
    int numNodes;
    bool visited[MAX_NODES];
} Graph;

// �����½ڵ�
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// ��ӱߵ�ͼ��
void addEdge(Graph* graph, int src, int dest) {
    // ���Դ�ڵ㵽Ŀ��ڵ�ı�
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // ���Ŀ��ڵ㵽Դ�ڵ�ı�
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// ��ʼ��ͼ
void initGraph(Graph* graph) {
    int i;
    graph->numNodes = 0;
    for (i = 0; i < MAX_NODES; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = false;
    }
}

// ������ȱ���
void DFS(Graph* graph, int vertex) {
    Node* adjNode = graph->adjList[vertex];
    graph->visited[vertex] = true;
    printf("%d ", vertex);

    while (adjNode != NULL) {
        int connectedVertex = adjNode->vertex;

        if (!graph->visited[connectedVertex]) {
            DFS(graph, connectedVertex);
        }

        adjNode = adjNode->next;
    }
}

// ������ȱ���
void BFS(Graph* graph, int startVertex) {
    int queue[MAX_NODES];
    int front = 0, rear = 0;
    Node* adjNode;
    int currentVertex, connectedVertex;

    // �����ʼ�ڵ�Ϊ�ѷ��ʲ����
    graph->visited[startVertex] = true;
    queue[rear++] = startVertex;

    while (front != rear) {
        // ���ӵ�ǰ�ڵ�
        currentVertex = queue[front++];
        printf("%d ", currentVertex);

        adjNode = graph->adjList[currentVertex];

        while (adjNode != NULL) {
            connectedVertex = adjNode->vertex;

            if (!graph->visited[connectedVertex]) {
                // ������ӽڵ�Ϊ�ѷ��ʲ����
                graph->visited[connectedVertex] = true;
                queue[rear++] = connectedVertex;
            }

            adjNode = adjNode->next;
        }
    }
}

// ��ӡ�������ı߼�
void printSpanningTree(Graph* graph) {
    int i;
    Node* adjNode;

    printf("\n�������ı߼�:\n");

    for (i = 0; i < graph->numNodes; i++) {
        adjNode = graph->adjList[i];

        while (adjNode != NULL) {
            if (i < adjNode->vertex) {
                printf("(%d, %d)\n", i, adjNode->vertex);
            }

            adjNode = adjNode->next;
        }
    }
}

int main() {
    Graph graph;
    int choice, src, dest, startVertex;

    initGraph(&graph);

    while (1) {
        printf("\n-- ����ͼ���� --\n");
        printf("1. ����ͼ\n");
        printf("2. ������ȱ���\n");
        printf("3. ������ȱ���\n");
        printf("0. ����\n");
        printf("����������ѡ��: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("������ͼ�Ľ������: ");
                scanf("%d", &graph.numNodes);

                if (graph.numNodes <= 0 || graph.numNodes > MAX_NODES) {
                    printf("��Ч�Ľ��������\n");
                    break;
                }

                printf("���������бߣ���-1, -1�������룩:\n");
                while (1) {
                    scanf("%d %d", &src, &dest);
                    if (src == -1 && dest == -1) {
                        break;
                    }
                    if (src < 0 || src >= graph.numNodes || dest < 0 || dest >= graph.numNodes) {
                        printf("��Ч�ıߣ�\n");
                        continue;
                    }
                    addEdge(&graph, src, dest);
                }
                break;
            case 2:
                printf("��������ʼ���: ");
                scanf("%d", &startVertex);
                if (startVertex < 0 || startVertex >= graph.numNodes) {
                    printf("��Ч����ʼ��㣡\n");
                    break;
                }
                printf("������ȱ������: ");
                DFS(&graph, startVertex);
                printSpanningTree(&graph);
                break;
            case 3:
                printf("��������ʼ���: ");
                scanf("%d", &startVertex);
                if (startVertex < 0 || startVertex >= graph.numNodes) {
                    printf("��Ч����ʼ��㣡\n");
                    break;
                }
                printf("������ȱ������: ");
                BFS(&graph, startVertex);
                printSpanningTree(&graph);
                break;
            case 0:
                printf("���������\n");
                exit(0);
            default:
                printf("��Ч��ѡ��\n");
        }
    }

    return 0;
}
