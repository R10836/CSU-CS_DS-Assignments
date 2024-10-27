#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 10
#define INFINITY 100

// 邻接表中的节点结构
typedef struct Node {
    int vertex;         // 相邻顶点的索引
    int weight;         // 边的权重
    struct Node* next;  // 指向下一个节点的指针
} Node;

// 邻接表中的顶点结构
typedef struct {
    int key;         // 顶点的索引
    bool visited;    // 是否已访问
    Node* neighbors; // 相邻顶点链表的头指针
} Vertex;

// 图的结构
typedef struct {
    Vertex vertices[MAX_VERTICES]; // 顶点数组
    int numVertices;               // 顶点数量
} Graph;

// 创建新节点
Node* createNode(int vertex, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// 添加边到邻接表
void addEdge(Graph* graph, int src, int dest, int weight) {
    // 添加src到dest的边
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->vertices[src].neighbors;
    graph->vertices[src].neighbors = newNode;

    // 添加dest到src的边
    newNode = createNode(src, weight);
    newNode->next = graph->vertices[dest].neighbors;
    graph->vertices[dest].neighbors = newNode;
}

// Prim算法求解最小生成树
void primMST(Graph* graph) {
    int key[MAX_VERTICES];    // 顶点的键值
    int parent[MAX_VERTICES]; // 顶点的父节点
    bool inMST[MAX_VERTICES]; // 顶点是否在最小生成树中

    // 初始化键值、父节点和是否在最小生成树中的数组
    for (int i = 0; i < graph->numVertices; i++) {
        key[i] = INFINITY;
        parent[i] = -1;
        inMST[i] = false;
    }

    // 从第一个顶点开始构建最小生成树
    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < graph->numVertices - 1; count++) {
        int minKey = INFINITY;
        int minIndex = -1;

        // 找到当前键值最小的顶点
        for (int v = 0; v < graph->numVertices; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        inMST[minIndex] = true;

        // 更新相邻顶点的键值和父节点
        Node* neighbor = graph->vertices[minIndex].neighbors;
        while (neighbor != NULL) {
            int v = neighbor->vertex;
            int weight = neighbor->weight;
            if (!inMST[v] && weight < key[v]) {
                parent[v] = minIndex;
                key[v] = weight;
            }
            neighbor = neighbor->next;
        }
    }

    // 输出最小生成树
    printf("边   权重\n");
    for (int i = 1; i < graph->numVertices; i++) {
        printf("%d - %d   %d\n", parent[i], i, key[i]);
    }
}

int main() {
    Graph graph;
    int numVertices, numEdges;

    printf("请输入顶点数量和边数量：");
    scanf("%d%d", &numVertices, &numEdges);

    graph.numVertices = numVertices;

    // 初始化顶点
    for (int i = 0; i < numVertices; i++) {
        graph.vertices[i].key = i;
        graph.vertices[i].visited = false;
        graph.vertices[i].neighbors = NULL;
    }

    // 输入边的信息
    printf("请输入每条边的起点、终点和权重：\n");
    for (int i = 0; i < numEdges; i++) {
        int src, dest, weight;
        scanf("%d%d%d", &src, &dest, &weight);
        addEdge(&graph, src, dest, weight);
    }

    printf("最小生成树的边集：\n");
    primMST(&graph);

    return 0;
}