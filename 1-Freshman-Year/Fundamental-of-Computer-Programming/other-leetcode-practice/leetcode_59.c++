//
// Created by Shawn33712 on 24-10-3.
//

/*
59. 螺旋矩阵 II
中等
相关标签
相关企业
给你一个正整数 n ，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。



示例 1：


输入：n = 3
输出：[[1,2,3],[8,9,4],[7,6,5]]
示例 2：

输入：n = 1
输出：[[1]]


提示：

1 <= n <= 20
*/

#include "iostream"
#include "vector"
#include "string"

using namespace std;


class Solution {
public:
    // 暴力
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> mat(n, vector<int>(n, 0));

        int i = 1;
        int x = 0, y = 0;
        vector<string> dic = {"right", "down", "left", "up"};
        int d = 0;

        while (true) {
            if (d == 4) {
                d = 0;
            }

            mat[y][x] = i;
//            printDP(mat, n-1, n-1);

            if (dic[d] == "right") {
                x++;
                if (x >= n || mat[y][x] != 0) {
                    d++;
                    x--;  // 回溯
                    y++;
                }
            } else if (dic[d] == "down") {
                y++;
                if (y >= n || mat[y][x] != 0) {
                    d++;
                    y--;
                    x--;
                }
            } else if (dic[d] == "left") {
                x--;
                if (x < 0 || mat[y][x] != 0) {
                    d++;
                    x++;
                    y--;
                }
            } else if (dic[d] == "up") {
                y--;
                if (y < 0 || mat[y][x] != 0) {
                    d++;
                    y++;
                    x++;
                }
            }

            if (i == n * n) {
                break;
            }
            i++;
        }

        return mat;
    }

    void printDP(vector<vector<int>>& dp, int iMax, int jMax) {
        // 数组最后一个元素为dp[iMax][jMax]
        for (int i = 0; i <= iMax; i++) {
            for (int j = 0; j <= jMax; j++) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};


int main() {
    Solution solution;

    int n;
    cin >> n;
    vector<vector<int>> answer = solution.generateMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << answer[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
