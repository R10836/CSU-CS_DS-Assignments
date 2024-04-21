#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 10
#define INF INT_MAX

typedef struct {
    int weight;  // 边的权值
    int destination;  // 边的目标顶点
    struct Node* next;  // 下一条边
} Node;

typedef struct {
    Node* head;  // 邻接表头结点
} AdjList[MAX_VERTICES];

typedef struct {
    AdjList adjList;  // 邻接表
    int numVertices;  // 顶点数量
} Graph;

// 创建图的邻接表
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    for (int i = 0; i < numVertices; i++) {
        graph->adjList[i].head = NULL;
    }

    return graph;
}

// 添加边到图中
void addEdge(Graph* graph, int source, int destination, int weight) {
    // 创建新的边节点
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->destination = destination;
    newNode->weight = weight;
    newNode->next = NULL;

    // 将边节点添加到源顶点的邻接表头部
    newNode->next = graph->adjList[source].head;
    graph->adjList[source].head = newNode;
}

// Dijkstra算法求最短路径
void dijkstra(Graph* graph, int source, int destination) {
    int dist[MAX_VERTICES];  // 存储源顶点到各顶点的最短距离
    bool visited[MAX_VERTICES];  // 标记顶点是否已访问

    // 初始化dist数组和visited数组
    for (int i = 0; i < graph->numVertices; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    // 设置源顶点到自身的最短距离为0
    dist[source] = 0;

    // 寻找最短路径
    for (int count = 0; count < graph->numVertices - 1; count++) {
        int minDist = INF;
        int minVertex;

        // 选择距离最小的顶点
        for (int v = 0; v < graph->numVertices; v++) {
            if (visited[v] == false && dist[v] <= minDist) {
                minDist = dist[v];
                minVertex = v;
            }
        }

        // 标记选中的顶点已访问
        visited[minVertex] = true;

        // 更新与选中顶点相邻的顶点的最短距离
        Node* currentNode = graph->adjList[minVertex].head;
        while (currentNode != NULL) {
            int adjacentVertex = currentNode->destination;
            int weight = currentNode->weight;
            if (visited[adjacentVertex] == false && dist[minVertex] != INF &&
                dist[minVertex] + weight < dist[adjacentVertex]) {
                dist[adjacentVertex] = dist[minVertex] + weight;
            }
            currentNode = currentNode->next;
        }
    }

    // 输出最短路径
    printf("从顶点 %d 到顶点 %d 的最短路径为：%d\n", source, destination, dist[destination]);
}

// Floyd算法求最短路径
void floyd(Graph* graph, int source, int destination) {
    int dist[MAX_VERTICES][MAX_VERTICES];  // 存储任意两个顶点之间的最短距离

    // 初始化dist数组
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = INF;
            }
        }
    }

    // 初始化dist数组为边的权值
    for (int i = 0; i < graph->numVertices; i++) {
        Node* currentNode = graph->adjList[i].head;
        while (currentNode != NULL) {
            int destination = currentNode->destination;
            int weight = currentNode->weight;
            dist[i][destination] = weight;
            currentNode = currentNode->next;
        }
    }

    // 使用Floyd算法计算最短路径
    for (int k = 0; k < graph->numVertices; k++) {
        for (int i = 0; i < graph->numVertices; i++) {
            for (int j = 0; j < graph->numVertices; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // 输出最短路径
    printf("从顶点 %d 到顶点 %d 的最短路径为：%d\n", source, destination, dist[source][destination]);
}

int main() {
    int numVertices = 6;
    Graph* graph = createGraph(numVertices);

    // 添加边
    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 2, 4);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 7);
    addEdge(graph, 2, 4, 3);
    addEdge(graph, 3, 4, 1);
    addEdge(graph, 3, 5, 5);
    addEdge(graph, 4, 5, 2);

    // 查询景点信息
    // ...

    // 查询任意两个景点的最短路径
    dijkstra(graph, 0, 5);  // 使用Dijkstra算法
    floyd(graph, 0, 5);  // 使用Floyd算法

    // 选择最佳游览路径
    // ...

    return 0;
}