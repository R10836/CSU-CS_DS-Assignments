//
// Created by Shawn33712 on 24-8-28.
//

/*
797. 所有可能的路径
中等
相关标签
相关企业
给你一个有 n 个节点的 有向无环图（DAG），请你找出所有从节点 0 到节点 n-1 的路径并输出（不要求按特定顺序）

 graph[i] 是一个从节点 i 可以访问的所有节点的列表（即从节点 i 到节点 graph[i][j]存在一条有向边）。



示例 1：



输入：graph = [[1,2],[3],[3],[]]
输出：[[0,1,3],[0,2,3]]
解释：有两条路径 0 -> 1 -> 3 和 0 -> 2 -> 3
示例 2：



输入：graph = [[4,3,1],[3,2,4],[3],[4],[]]
输出：[[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]


提示：

n == graph.length
2 <= n <= 15
0 <= graph[i][j] < n
graph[i][j] != i（即不存在自环）
graph[i] 中的所有元素 互不相同
保证输入为 有向无环图（DAG）

*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
private:
    vector<vector<int>> result;

    vector<int> path = {0};

public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        int n = graph.size();
        dfs(graph, n, 0);
        return result;
    }

    void dfs(vector<vector<int>>& graph, int n, int x) {
        // 基线
        if (x == n-1) {
            result.push_back(path);
            return;
        }

        // 递归
        for (int i = 0; i < graph[x].size(); i++) {
            path.push_back(graph[x][i]);
            dfs(graph, n, graph[x][i]);
            path.pop_back();
        }
    }
};


int main() {
    Solution solution;

    vector<vector<int>> graph = {{4,3,1},{3,2,4},{3},{4},{}};
    vector<vector<int>> answer = solution.allPathsSourceTarget(graph);
    for (int i = 0; i < answer.size(); i++) {
        for (int j = 0; j < answer[i].size(); j++) {
            cout << answer[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
