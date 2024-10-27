//
// Created by Shawn33712 on 24-8-30.
//

/*
542. 01 矩阵
中等
相关标签
相关企业
给定一个由 0 和 1 组成的矩阵 mat ，请输出一个大小相同的矩阵，其中每一个格子是 mat 中对应位置元素到最近的 0 的距离。

两个相邻元素间的距离为 1 。



示例 1：



输入：mat = [[0,0,0],[0,1,0],[0,0,0]]
输出：[[0,0,0],[0,1,0],[0,0,0]]
示例 2：



输入：mat = [[0,0,0],[0,1,0],[1,1,1]]
输出：[[0,0,0],[0,1,0],[1,2,1]]


提示：

m == mat.length
n == mat[i].length
1 <= m, n <= 104
1 <= m * n <= 104
mat[i][j] is either 0 or 1.
mat 中至少有一个 0
*/

#include "iostream"
#include "vector"
#include "queue"

using namespace std;


class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int rows = mat.size();
        int cols = mat[0].size();

        vector<vector<int>> result(rows, vector<int>(cols, INT_MAX));

        queue<pair<int, int>> q;
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                if (mat[y][x] == 0) {
                    result[y][x] = 0;
                    // 如果是逐个从 1 位置开始搜索，我们可能需要多次重复地遍历矩阵中的位置，从而导致不必要的重复计算和低效的运行时间。将 0 入队后，BFS 一次性解决了所有距离计算的问题。
                    q.push({y, x});
                }
            }
        }
        bfs(result, q);

        return result;
    }

    void bfs(vector<vector<int>>& result, queue<pair<int, int>>& q) {
        int rows = result.size();
        int cols = result[0].size();

        int dis[4][2] = {
                {1, 0},
                {-1, 0},
                {0, -1},
                {0, 1}
        };

        while (!q.empty()) {
            pair<int, int> current = q.front();
            q.pop();
            int y = current.first;
            int x = current.second;

            for (int i = 0; i < 4; i++) {
                int newY = y + dis[i][0];
                int newX = x + dis[i][1];

                if (newY >= 0 && newY < rows && newX >= 0 && newX < cols) {
                    if (result[newY][newX] > result[y][x] + 1) {
                        result[newY][newX] = result[y][x] + 1;
                        q.push({newY, newX});
                    }
                }
            }
        }
    }
};


int main() {
    Solution solution;

    vector<vector<int>> mat = {
            {0,0,0},
            {0,1,0},
            {1,1,1}
    };
    vector<vector<int>> answer = solution.updateMatrix(mat);
    for (int i = 0; i < answer.size(); ++i) {
        for (int j = 0; j < answer[i].size(); ++j) {
            cout << answer[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
