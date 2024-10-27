#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 10
#define INF INT_MAX

typedef struct {
    int weight;  // �ߵ�Ȩֵ
    int destination;  // �ߵ�Ŀ�궥��
    struct Node* next;  // ��һ����
} Node;

typedef struct {
    Node* head;  // �ڽӱ�ͷ���
} AdjList[MAX_VERTICES];

typedef struct {
    AdjList adjList;  // �ڽӱ�
    int numVertices;  // ��������
} Graph;

// ����ͼ���ڽӱ�
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    for (int i = 0; i < numVertices; i++) {
        graph->adjList[i].head = NULL;
    }

    return graph;
}

// ��ӱߵ�ͼ��
void addEdge(Graph* graph, int source, int destination, int weight) {
    // �����µı߽ڵ�
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->destination = destination;
    newNode->weight = weight;
    newNode->next = NULL;

    // ���߽ڵ���ӵ�Դ������ڽӱ�ͷ��
    newNode->next = graph->adjList[source].head;
    graph->adjList[source].head = newNode;
}

// Dijkstra�㷨�����·��
void dijkstra(Graph* graph, int source, int destination) {
    int dist[MAX_VERTICES];  // �洢Դ���㵽���������̾���
    bool visited[MAX_VERTICES];  // ��Ƕ����Ƿ��ѷ���

    // ��ʼ��dist�����visited����
    for (int i = 0; i < graph->numVertices; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    // ����Դ���㵽�������̾���Ϊ0
    dist[source] = 0;

    // Ѱ�����·��
    for (int count = 0; count < graph->numVertices - 1; count++) {
        int minDist = INF;
        int minVertex;

        // ѡ�������С�Ķ���
        for (int v = 0; v < graph->numVertices; v++) {
            if (visited[v] == false && dist[v] <= minDist) {
                minDist = dist[v];
                minVertex = v;
            }
        }

        // ���ѡ�еĶ����ѷ���
        visited[minVertex] = true;

        // ������ѡ�ж������ڵĶ������̾���
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

    // ������·��
    printf("�Ӷ��� %d ������ %d �����·��Ϊ��%d\n", source, destination, dist[destination]);
}

// Floyd�㷨�����·��
void floyd(Graph* graph, int source, int destination) {
    int dist[MAX_VERTICES][MAX_VERTICES];  // �洢������������֮�����̾���

    // ��ʼ��dist����
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = INF;
            }
        }
    }

    // ��ʼ��dist����Ϊ�ߵ�Ȩֵ
    for (int i = 0; i < graph->numVertices; i++) {
        Node* currentNode = graph->adjList[i].head;
        while (currentNode != NULL) {
            int destination = currentNode->destination;
            int weight = currentNode->weight;
            dist[i][destination] = weight;
            currentNode = currentNode->next;
        }
    }

    // ʹ��Floyd�㷨�������·��
    for (int k = 0; k < graph->numVertices; k++) {
        for (int i = 0; i < graph->numVertices; i++) {
            for (int j = 0; j < graph->numVertices; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // ������·��
    printf("�Ӷ��� %d ������ %d �����·��Ϊ��%d\n", source, destination, dist[source][destination]);
}

int main() {
    int numVertices = 6;
    Graph* graph = createGraph(numVertices);

    // ��ӱ�
    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 2, 4);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 7);
    addEdge(graph, 2, 4, 3);
    addEdge(graph, 3, 4, 1);
    addEdge(graph, 3, 5, 5);
    addEdge(graph, 4, 5, 2);

    // ��ѯ������Ϣ
    // ...

    // ��ѯ����������������·��
    dijkstra(graph, 0, 5);  // ʹ��Dijkstra�㷨
    floyd(graph, 0, 5);  // ʹ��Floyd�㷨

    // ѡ���������·��
    // ...

    return 0;
}