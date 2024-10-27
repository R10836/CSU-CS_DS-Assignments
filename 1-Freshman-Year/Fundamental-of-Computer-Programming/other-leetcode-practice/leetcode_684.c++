//
// Created by Shawn33712 on 24-8-31.
//

/*
684. 冗余连接
中等
相关标签
相关企业
树可以看成是一个连通且 无环 的 无向 图。

给定往一棵 n 个节点 (节点值 1～n) 的树中添加一条边后的图。添加的边的两个顶点包含在 1 到 n 中间，且这条附加的边不属于树中已存在的边。图的信息记录于长度为 n 的二维数组 edges ，edges[i] = [ai, bi] 表示图中在 ai 和 bi 之间存在一条边。

请找出一条可以删去的边，删除后可使得剩余部分是一个有着 n 个节点的树。如果有多个答案，则返回数组 edges 中最后出现的那个。



示例 1：



输入: edges = [[1,2], [1,3], [2,3]]
输出: [2,3]
示例 2：



输入: edges = [[1,2], [2,3], [3,4], [1,4], [1,5]]
输出: [1,4]


提示:

n == edges.length
3 <= n <= 1000
edges[i].length == 2
1 <= ai < bi <= edges.length
ai != bi
edges 中无重复元素
给定的图是连通的
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    // （集）
    vector<int> father;

    // 初始化并查集
    void initUF(int n) {
        father.resize(n+1, 0);
        for (int i = 1; i < n+1; i++) {
            father[i] = i;  // 自己是自己的父亲
        }
    }
// 给定往一棵 n 个节点 (节点值 1～n)

    // 寻根（查）
    int findRoot(int u) {
        if (u == father[u]) {  // 当自己是自己的父亲时，
            return u;  // 即根就是自己，返回。
        } else {  // 当自己不是自己的父亲时,
            return findRoot(father[u]);  // 那就找自己父亲的父亲...等祖宗，直到某个祖宗自己是自己的父亲（为根）为止，返回即为u的始祖。
        }
    }

    // 合体（并）
    void unionRoot(int u, int v) {
        int rootU = findRoot(u);
        int rootV = findRoot(v);
        if (rootU != rootV) {
            father[rootV] = rootU;  // v对应的父亲是u (v和u连通了)
        }
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        // 准备工作
        int n = edges.size();
        initUF(n);

        // 遍历，合并，查找冗余
        for (int i = 0; i < n; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            if (findRoot(u) == findRoot(v)) {
//                for (int j = 1; j < father.size(); j++) {
//                    cout << father[j] << " ";
//                }
//                cout << endl;
                return edges[i];  // 如果两个节点已经在同一集合，说明这条边是冗余的，题目说明
            } else {
                unionRoot(u, v);
            }
        }

        return {};  // 日你妈
    }
};


int main() {
    Solution solution;

    vector<vector<int>> edges = {
            {1,2},
            {2,3},
            {3,4},
            {1,4},
            {1,5}
    };
    vector<int> result = solution.findRedundantConnection(edges);
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
