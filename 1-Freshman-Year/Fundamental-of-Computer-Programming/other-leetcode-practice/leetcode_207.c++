//
// Created by Shawn33712 on 24-9-1.
//

/*
207. 课程表
中等
相关标签
相关企业
提示
你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。

例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。



示例 1：

输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
示例 2：

输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
输出：false
解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。


提示：

1 <= numCourses <= 2000
0 <= prerequisites.length <= 5000
prerequisites[i].length == 2
0 <= ai, bi < numCourses
prerequisites[i] 中的所有课程对 互不相同
*/

#include "iostream"
#include "vector"
#include "unordered_map"
#include "deque"

using namespace std;


class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // 数据结构定义
        vector<int> courses(numCourses, 0);  // 这个变量将用于存储每门课程所需的前置课程数。
        unordered_map<int, vector<int>> needUnlock;  // map记录所有need->target。建：某门课程编号int。值：需要前置课程的课程列表vector<int>。

        // 第〇步：构建依赖关系图
        for (int i = 0; i < prerequisites.size(); i++) {
            int target = prerequisites[i][0];
            int need = prerequisites[i][1];
            needUnlock[need].push_back(target);  //添加键值对：need -> target1、target2...
            courses[target]++;  // target的前置课程+1。
        }

        // 第一步：找到所有没有前置课程的课程，并加入dq
        deque<int> dq;  // 用于存放可以学习的课程
        for (int i = 0; i < numCourses; i++) {
            if (courses[i] == 0) {
                dq.push_back(i);
            }
        }

        // 第二步：拓扑排序：
        // 逐渐消灭在队列中(即没有前置)的节点，直到没有节点在队列中
        while (!dq.empty()) {
            int c = dq.front();
            dq.pop_front();
            // 检查needUnlock以修改courses
            if (needUnlock.count(c)) {  // 如果needUnlock中有c这个need
                for (int i = 0; i < needUnlock[c].size(); i++) {  // 将所有依赖于c的target数courses[thisTarget]减1。
                    int thisTarget = needUnlock[c][i];
                    if (courses[thisTarget] > 0) {
                        courses[thisTarget]--;
                    }
                    if (courses[thisTarget] == 0) {
                        dq.push_back(thisTarget);  // 如果课程 course 的前置课程数量变为 0，则可以将其加入到队列中。
                    }
                }
            }
            needUnlock.erase(c);
        }

        // 第三步：检查是否全部消灭
        for (int i = 0; i < courses.size(); i++) {
            if (courses[i] != 0) {
                return false;
            }
        }
        return true;
    }
};


int main() {
    Solution solution;

    int numCourses = 2;
    vector<vector<int>> prerequisites = {
            {1,0},
            {0,1}
    };
    cout << boolalpha << solution.canFinish(numCourses, prerequisites) << endl;

    return 0;
}
