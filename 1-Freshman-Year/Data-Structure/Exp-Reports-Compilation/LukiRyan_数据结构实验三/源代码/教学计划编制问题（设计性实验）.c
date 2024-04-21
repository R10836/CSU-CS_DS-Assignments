#include <stdio.h>
#include <stdbool.h>

#define MAX_COURSES 30

// 定义课程节点
typedef struct CourseNode {
    int course;  // 课程编号
    struct CourseNode* next;  // 指向下一个课程节点的指针
} CourseNode;

// 定义课程表
typedef struct CourseSchedule {
    CourseNode* adjacencyList[MAX_COURSES];  // 邻接表数组
    int indegree[MAX_COURSES];  // 入度数组
    int numCourses;  // 课程总数
} CourseSchedule;

// 初始化课程表
void initCourseSchedule(CourseSchedule* schedule, int numCourses) {
    for (int i = 0; i < numCourses; i++) {
        schedule->adjacencyList[i] = NULL;
        schedule->indegree[i] = 0;
    }
    schedule->numCourses = numCourses;
}

// 添加先修关系
void addDependency(CourseSchedule* schedule, int course, int prerequisite) {
    CourseNode* newNode = (CourseNode*)malloc(sizeof(CourseNode));
    newNode->course = prerequisite;
    newNode->next = schedule->adjacencyList[course];
    schedule->adjacencyList[course] = newNode;
    schedule->indegree[prerequisite]++;
}

// 拓扑排序算法
bool topologicalSort(CourseSchedule* schedule, int result[]) {
    int numCourses = schedule->numCourses;
    int count = 0;  // 记录已经安排的课程数量
    int queue[MAX_COURSES];  // 使用队列保存入度为0的课程
    int front = 0;  // 队列前指针
    int rear = 0;  // 队列后指针

    // 将入度为0的课程加入队列
    for (int i = 0; i < numCourses; i++) {
        if (schedule->indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front != rear) {
        int course = queue[front++];  // 出队列，表示修完了该课程
        result[count++] = course;  // 将课程添加到结果数组中

        // 更新相邻课程的入度
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

    // 判断是否存在循环依赖
    if (count != numCourses) {
        return false;
    }

    return true;
}

// 打印教学计划
void printCourseSchedule(CourseSchedule* schedule, int result[]) {
    int numCourses = schedule->numCourses;
    int maxSemester = 0;  // 记录最大的学期数，即完成所有课程所需的最短时间

    printf("教学计划：\n");
    for (int i = 0; i < numCourses; i++) {
        int course = result[i];
        int semester = 1;  // 课程默认在第1个学期修读

        // 寻找该课程的先修课程中学期最晚的那个
        CourseNode* curr = schedule->adjacencyList[course];
        while (curr != NULL) {
            int prerequisite = curr->course;
            if (result[prerequisite] >= semester) {
                semester = result[prerequisite] + 1;
            }
            curr = curr->next;
        }

        result[course] = semester;  // 更新课程的修读学期

        // 更新最大学期数
        if (semester > maxSemester) {
            maxSemester = semester;
        }

        printf("学期 %d: 课程 %d\n", semester, course);
    }

    printf("总学期数: %d\n", maxSemester);
}

int main() {
    CourseSchedule schedule;
    int numCourses = 8;

    initCourseSchedule(&schedule, numCourses);

    // 添加先修关系
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

    int result[MAX_COURSES];  // 存储拓扑排序的结果

    if (topologicalSort(&schedule, result)) {
        printCourseSchedule(&schedule, result);
    } else {
        printf("存在循环依赖，无法生成教学计划。\n");
    }

    return 0;
}