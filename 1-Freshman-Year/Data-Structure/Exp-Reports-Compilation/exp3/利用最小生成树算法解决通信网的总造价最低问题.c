#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 10
#define INFINITY 100

// �ڽӱ��еĽڵ�ṹ
typedef struct Node {
    int vertex;         // ���ڶ��������
    int weight;         // �ߵ�Ȩ��
    struct Node* next;  // ָ����һ���ڵ��ָ��
} Node;

// �ڽӱ��еĶ���ṹ
typedef struct {
    int key;         // ���������
    bool visited;    // �Ƿ��ѷ���
    Node* neighbors; // ���ڶ��������ͷָ��
} Vertex;

// ͼ�Ľṹ
typedef struct {
    Vertex vertices[MAX_VERTICES]; // ��������
    int numVertices;               // ��������
} Graph;

// �����½ڵ�
Node* createNode(int vertex, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// ��ӱߵ��ڽӱ�
void addEdge(Graph* graph, int src, int dest, int weight) {
    // ���src��dest�ı�
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->vertices[src].neighbors;
    graph->vertices[src].neighbors = newNode;

    // ���dest��src�ı�
    newNode = createNode(src, weight);
    newNode->next = graph->vertices[dest].neighbors;
    graph->vertices[dest].neighbors = newNode;
}

// Prim�㷨�����С������
void primMST(Graph* graph) {
    int key[MAX_VERTICES];    // ����ļ�ֵ
    int parent[MAX_VERTICES]; // ����ĸ��ڵ�
    bool inMST[MAX_VERTICES]; // �����Ƿ�����С��������

    // ��ʼ����ֵ�����ڵ���Ƿ�����С�������е�����
    for (int i = 0; i < graph->numVertices; i++) {
        key[i] = INFINITY;
        parent[i] = -1;
        inMST[i] = false;
    }

    // �ӵ�һ�����㿪ʼ������С������
    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < graph->numVertices - 1; count++) {
        int minKey = INFINITY;
        int minIndex = -1;

        // �ҵ���ǰ��ֵ��С�Ķ���
        for (int v = 0; v < graph->numVertices; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        inMST[minIndex] = true;

        // �������ڶ���ļ�ֵ�͸��ڵ�
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

    // �����С������
    printf("��   Ȩ��\n");
    for (int i = 1; i < graph->numVertices; i++) {
        printf("%d - %d   %d\n", parent[i], i, key[i]);
    }
}

int main() {
    Graph graph;
    int numVertices, numEdges;

    printf("�����붥�������ͱ�������");
    scanf("%d%d", &numVertices, &numEdges);

    graph.numVertices = numVertices;

    // ��ʼ������
    for (int i = 0; i < numVertices; i++) {
        graph.vertices[i].key = i;
        graph.vertices[i].visited = false;
        graph.vertices[i].neighbors = NULL;
    }

    // ����ߵ���Ϣ
    printf("������ÿ���ߵ���㡢�յ��Ȩ�أ�\n");
    for (int i = 0; i < numEdges; i++) {
        int src, dest, weight;
        scanf("%d%d%d", &src, &dest, &weight);
        addEdge(&graph, src, dest, weight);
    }

    printf("��С�������ı߼���\n");
    primMST(&graph);

    return 0;
}