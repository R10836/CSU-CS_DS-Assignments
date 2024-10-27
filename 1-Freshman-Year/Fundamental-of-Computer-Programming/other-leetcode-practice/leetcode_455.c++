//
// Created by Shawn33712 on 24-8-20.
//

/*
455. 分发饼干
简单
相关标签
相关企业
假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。

对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j，都有一个尺寸 s[j] 。如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。


示例 1:

输入: g = [1,2,3], s = [1,1]
输出: 1
解释:
你有三个孩子和两块小饼干，3个孩子的胃口值分别是：1,2,3。
虽然你有两块小饼干，由于他们的尺寸都是1，你只能让胃口值是1的孩子满足。
所以你应该输出1。
示例 2:

输入: g = [1,2], s = [1,2,3]
输出: 2
解释:
你有两个孩子和三块小饼干，2个孩子的胃口值分别是1,2。
你拥有的饼干数量和尺寸都足以让所有孩子满足。
所以你应该输出2.


提示：

1 <= g.length <= 3 * 104
0 <= s.length <= 3 * 104
1 <= g[i], s[j] <= 231 - 1
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        if (s.empty()) {
            return 0;
        }

        int sInitSize = s.size();

        quickSort(s, 0, sInitSize - 1);

        for (int i = 0; i < g.size(); i++) {
            for (int j = 0; j < s.size(); j++) {
                if (g[i] <= s[j]) {
                    s.erase(s.begin() + j);
                    break;
                }
            }
        }
        return sInitSize - s.size();
    }

    void quickSort(vector<int>& sample, int left, int right) {
        // 基线
        if (left >= right) return;

        // 选择基准值
        int pivot = sample[left];

        // 分成大小两个子数组
        int i = left + 1;
        int j = right;
        while (i <= j) {  // 当i==j时，意味着所有小于基准值的元素已经被移动到左边，大于基准值的元素已经被移动到右边。而多此一举的原因是为找到基准值应该放的位置。
            while (i <= j && sample[i] <= pivot) {
                i++;
            }
            while (i <= j && sample[j] > pivot) {
                j--;
            }
            if (i < j) {
                swap(sample[i], sample[j]);
            }
        }
        swap(sample[left], sample[j]);  // 把基准值放中间

        // 对这两个数组执行同样的操作(递归)
        quickSort(sample, left, j - 1);
        quickSort(sample, j + 1, right);
    }
};


int main() {
    Solution solution;

    vector<int> g = {2,3,0,1,4};
    vector<int> s = {5,4,3,2,1};
    cout << solution.findContentChildren(g, s);

    return 0;
}
