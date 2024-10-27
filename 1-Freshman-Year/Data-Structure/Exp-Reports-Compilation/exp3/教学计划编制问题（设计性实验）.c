#include <stdio.h>
#include <stdbool.h>

#define MAX_COURSES 30

// ����γ̽ڵ�
typedef struct CourseNode {
    int course;  // �γ̱��
    struct CourseNode* next;  // ָ����һ���γ̽ڵ��ָ��
} CourseNode;

// ����γ̱�
typedef struct CourseSchedule {
    CourseNode* adjacencyList[MAX_COURSES];  // �ڽӱ�����
    int indegree[MAX_COURSES];  // �������
    int numCourses;  // �γ�����
} CourseSchedule;

// ��ʼ���γ̱�
void initCourseSchedule(CourseSchedule* schedule, int numCourses) {
    for (int i = 0; i < numCourses; i++) {
        schedule->adjacencyList[i] = NULL;
        schedule->indegree[i] = 0;
    }
    schedule->numCourses = numCourses;
}

// ������޹�ϵ
void addDependency(CourseSchedule* schedule, int course, int prerequisite) {
    CourseNode* newNode = (CourseNode*)malloc(sizeof(CourseNode));
    newNode->course = prerequisite;
    newNode->next = schedule->adjacencyList[course];
    schedule->adjacencyList[course] = newNode;
    schedule->indegree[prerequisite]++;
}

// ���������㷨
bool topologicalSort(CourseSchedule* schedule, int result[]) {
    int numCourses = schedule->numCourses;
    int count = 0;  // ��¼�Ѿ����ŵĿγ�����
    int queue[MAX_COURSES];  // ʹ�ö��б������Ϊ0�Ŀγ�
    int front = 0;  // ����ǰָ��
    int rear = 0;  // ���к�ָ��

    // �����Ϊ0�Ŀγ̼������
    for (int i = 0; i < numCourses; i++) {
        if (schedule->indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front != rear) {
        int course = queue[front++];  // �����У���ʾ�����˸ÿγ�
        result[count++] = course;  // ���γ���ӵ����������

        // �������ڿγ̵����
        CourseNode* curr = schedule->adjacencyList[course];
        while (curr != NULL) {
            int prerequisite = curr->course;
            schedule->indegree[prerequisite]--;
            if (schedule->indegree[prerequisite] == 0) {
                queue[rear++] = prerequisite;
            }
            curr = curr->next;
        }
    }

    // �ж��Ƿ����ѭ������
    if (count != numCourses) {
        return false;
    }

    return true;
}

// ��ӡ��ѧ�ƻ�
void printCourseSchedule(CourseSchedule* schedule, int result[]) {
    int numCourses = schedule->numCourses;
    int maxSemester = 0;  // ��¼����ѧ��������������пγ���������ʱ��

    printf("��ѧ�ƻ���\n");
    for (int i = 0; i < numCourses; i++) {
        int course = result[i];
        int semester = 1;  // �γ�Ĭ���ڵ�1��ѧ���޶�

        // Ѱ�Ҹÿγ̵����޿γ���ѧ��������Ǹ�
        CourseNode* curr = schedule->adjacencyList[course];
        while (curr != NULL) {
            int prerequisite = curr->course;
            if (result[prerequisite] >= semester) {
                semester = result[prerequisite] + 1;
            }
            curr = curr->next;
        }

        result[course] = semester;  // ���¿γ̵��޶�ѧ��

        // �������ѧ����
        if (semester > maxSemester) {
            maxSemester = semester;
        }

        printf("ѧ�� %d: �γ� %d\n", semester, course);
    }

    printf("��ѧ����: %d\n", maxSemester);
}

int main() {
    CourseSchedule schedule;
    int numCourses = 8;

    initCourseSchedule(&schedule, numCourses);

    // ������޹�ϵ
    addDependency(&schedule, 1, 0);
    addDependency(&schedule, 2, 0);
    addDependency(&schedule, 3, 1);
    addDependency(&schedule, 3, 2);
    addDependency(&schedule, 4, 1);
    addDependency(&schedule, 5, 3);
    addDependency(&schedule, 5, 4);
    addDependency(&schedule, 6, 3);
    addDependency(&schedule, 7, 5);
    addDependency(&schedule, 7, 6);

    int result[MAX_COURSES];  // �洢��������Ľ��

    if (topologicalSort(&schedule, result)) {
        printCourseSchedule(&schedule, result);
    } else {
        printf("����ѭ���������޷����ɽ�ѧ�ƻ���\n");
    }

    return 0;
}