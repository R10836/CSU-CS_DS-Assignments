//
// Created by Shawn33712 on 24-8-29.
//

/*
417. 太平洋大西洋水流问题
中等
相关标签
相关企业
有一个 m × n 的矩形岛屿，与 太平洋 和 大西洋 相邻。 “太平洋” 处于大陆的左边界和上边界，而 “大西洋” 处于大陆的右边界和下边界。

这个岛被分割成一个由若干方形单元格组成的网格。给定一个 m x n 的整数矩阵 heights ， heights[r][c] 表示坐标 (r, c) 上单元格 高于海平面的高度 。

岛上雨水较多，如果相邻单元格的高度 小于或等于 当前单元格的高度，雨水可以直接向北、南、东、西流向相邻单元格。水可以从海洋附近的任何单元格流入海洋。

返回网格坐标 result 的 2D 列表 ，其中 result[i] = [ri, ci] 表示雨水从单元格 (ri, ci) 流动 既可流向太平洋也可流向大西洋 。



示例 1：



输入: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
输出: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
示例 2：

输入: heights = [[2,1],[1,2]]
输出: [[0,0],[0,1],[1,0],[1,1]]


提示：

m == heights.length
n == heights[r].length
1 <= m, n <= 200
0 <= heights[r][c] <= 105
*/

#include "iostream"
#include "vector"
#include "set"

using namespace std;


//优化
//那么我们可以 反过来想，从第一组边界上的节点 逆流而上，将遍历过的节点都标记上。
//同样从第二组边界的边上节点 逆流而上，将遍历过的节点也标记上。
//然后两方都标记过的节点就是既可以流太平洋也可以流大西洋的节点。
class Solution {
public:
    set<pair<int, int>> resultSet;

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        // 准备工作
        int yAxis = heights.size();
        int xAxis = heights[0].size();
        vector<vector<char>> visited(yAxis, vector<char>(xAxis, 'l'));  // land

        // 传染法，这里从边界开始传染
        for (int y = 0; y < yAxis; y++) {
            infect(heights, visited, y, 0, 'p', 0); // pacific ocean
            infect(heights, visited, y, xAxis-1, 'a', 0); // atlantic ocean
        }
        for (int x = 0; x < xAxis; x++) {
            infect(heights, visited, 0, x, 'p', 0); // pacific ocean
            infect(heights, visited, yAxis-1, x, 'a', 0); // atlantic ocean
        }

        // 返回
        // 将结果从 set 转换为 vector
        vector<vector<int>> result;
        for (const auto& p : resultSet) {
            result.push_back({p.first, p.second});
        }
        return result;
    }

    void infect(vector<vector<int>>& heights, vector<vector<char>>& visited, int y, int x, char ocean, int last) {
        // 准备
        int yAxis = heights.size();
        int xAxis = heights[0].size();
        // 基线
        if (y < 0 || y >= yAxis) {
            return;
        }
        if (x < 0 || x >= xAxis) {
            return;
        }
        if (last > heights[y][x]) {
            return;
        }

        // 递归
        char state = visited[y][x];
        if (state == ocean) {
            return; // 剪枝
        }
        if (state == 'l') {
            visited[y][x] = ocean;
        }
        if (state != 'l' && state != ocean) {
            resultSet.insert({y, x});
        }
        visited[y][x] = ocean;

        infect(heights, visited, y+1, x, ocean, heights[y][x]);
        infect(heights, visited, y-1, x, ocean, heights[y][x]);
        infect(heights, visited, y, x-1, ocean, heights[y][x]);
        infect(heights, visited, y, x+1, ocean, heights[y][x]);
    }
};


int main() {
    Solution solution;

    vector<vector<int>> heights = {
            {1,2,2,3,5},
            {3,2,3,4,4},
            {2,4,5,3,1},
            {6,7,1,4,5},
            {5,1,1,2,4}
    };
    vector<vector<int>> answer = solution.pacificAtlantic(heights);
    for (int i = 0; i < answer.size(); i++) {
        for (int j = 0; j < answer[i].size(); j++) {
            cout << answer[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
