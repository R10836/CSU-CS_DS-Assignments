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

// 创建新节点
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// 添加边到图中
void addEdge(Graph* graph, int src, int dest) {
    // 添加源节点到目标节点的边
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // 添加目标节点到源节点的边
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// 初始化图
void initGraph(Graph* graph) {
    int i;
    graph->numNodes = 0;
    for (i = 0; i < MAX_NODES; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = false;
    }
}

// 深度优先遍历
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

// 广度优先遍历
void BFS(Graph* graph, int startVertex) {
    int queue[MAX_NODES];
    int front = 0, rear = 0;
    Node* adjNode;
    int currentVertex, connectedVertex;

    // 标记起始节点为已访问并入队
    graph->visited[startVertex] = true;
    queue[rear++] = startVertex;

    while (front != rear) {
        // 出队当前节点
        currentVertex = queue[front++];
        printf("%d ", currentVertex);

        adjNode = graph->adjList[currentVertex];

        while (adjNode != NULL) {
            connectedVertex = adjNode->vertex;

            if (!graph->visited[connectedVertex]) {
                // 标记连接节点为已访问并入队
                graph->visited[connectedVertex] = true;
                queue[rear++] = connectedVertex;
            }

            adjNode = adjNode->next;
        }
    }
}

// 打印生成树的边集
void printSpanningTree(Graph* graph) {
    int i;
    Node* adjNode;

    printf("\n生成树的边集:\n");

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
        printf("\n-- 无向图遍历 --\n");
        printf("1. 建立图\n");
        printf("2. 深度优先遍历\n");
        printf("3. 广度优先遍历\n");
        printf("0. 结束\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("请输入图的结点数量: ");
                scanf("%d", &graph.numNodes);

                if (graph.numNodes <= 0 || graph.numNodes > MAX_NODES) {
                    printf("无效的结点数量！\n");
                    break;
                }

                printf("请输入所有边（以-1, -1结束输入）:\n");
                while (1) {
                    scanf("%d %d", &src, &dest);
                    if (src == -1 && dest == -1) {
                        break;
                    }
                    if (src < 0 || src >= graph.numNodes || dest < 0 || dest >= graph.numNodes) {
                        printf("无效的边！\n");
                        continue;
                    }
                    addEdge(&graph, src, dest);
                }
                break;
            case 2:
                printf("请输入起始结点: ");
                scanf("%d", &startVertex);
                if (startVertex < 0 || startVertex >= graph.numNodes) {
                    printf("无效的起始结点！\n");
                    break;
                }
                printf("深度优先遍历结果: ");
                DFS(&graph, startVertex);
                printSpanningTree(&graph);
                break;
            case 3:
                printf("请输入起始结点: ");
                scanf("%d", &startVertex);
                if (startVertex < 0 || startVertex >= graph.numNodes) {
                    printf("无效的起始结点！\n");
                    break;
                }
                printf("广度优先遍历结果: ");
                BFS(&graph, startVertex);
                printSpanningTree(&graph);
                break;
            case 0:
                printf("程序结束。\n");
                exit(0);
            default:
                printf("无效的选择！\n");
        }
    }

    return 0;
}
