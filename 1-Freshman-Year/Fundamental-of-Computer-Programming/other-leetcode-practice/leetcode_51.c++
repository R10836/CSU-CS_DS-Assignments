//
// Created by Shawn33712 on 24-8-27.
//

/*
51. N 皇后
困难
相关标签
相关企业
按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。

n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。

每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。



示例 1：


输入：n = 4
输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
解释：如上图所示，4 皇后问题存在两个不同的解法。
示例 2：

输入：n = 1
输出：[["Q"]]


提示：

1 <= n <= 9

*/

#include "iostream"
#include "vector"
#include "string"

using namespace std;


class Solution {
public:
    vector<vector<string>> result;

    vector<vector<string>> solveNQueens(int n) {
        vector<string> chessBoard(n, string(n, '.'));
        backtracking(chessBoard, n, 0);
        return result;
    }

    void backtracking(vector<string>& chessBoard, int n, int row) {
        // 基线
        if (row == n) {
            result.push_back(chessBoard);
            return;
        }

        // 递归
        for (int col = 0; col < n; col++) {
            if (isChessBoardValid(chessBoard, n, row, col)) {
                chessBoard[row][col] = 'Q';
                backtracking(chessBoard, n, row + 1);
                chessBoard[row][col] = '.';
            }
        }
    }

    bool isChessBoardValid(vector<string>& chessBoard, int n, int row, int col) {
        // 抄的：
        // 检查列
        for (int i = 0; i < row; i++) { // 这是一个剪枝
            if (chessBoard[i][col] == 'Q') {
                return false;
            }
        }
        // 检查 45度角是否有皇后
        for (int i = row - 1, j = col - 1; i >=0 && j >= 0; i--, j--) {
            if (chessBoard[i][j] == 'Q') {
                return false;
            }
        }
        // 检查 135度角是否有皇后
        for(int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (chessBoard[i][j] == 'Q') {
                return false;
            }
        }
        return true;
    }
};


int main() {
    Solution solution;

    vector<vector<string>> answer = solution.solveNQueens(4);
    for (int i = 0; i < answer.size(); i++) {
        for (int j = 0; j < answer[i].size(); j++) {
            cout << answer[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}
