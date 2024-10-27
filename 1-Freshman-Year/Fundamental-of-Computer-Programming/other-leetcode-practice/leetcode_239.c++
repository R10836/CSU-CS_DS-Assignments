//
// Created by Shawn33712 on 24-8-18.
//

/*
239. 滑动窗口最大值
困难
相关标签
相关企业
提示
给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

返回 滑动窗口中的最大值 。



示例 1：

输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
示例 2：

输入：nums = [1], k = 1
输出：[1]


提示：

1 <= nums.length <= 105
-104 <= nums[i] <= 104
1 <= k <= nums.length
*/

#include "iostream"
#include "vector"
#include "deque"

using namespace std;


class Solution {
public:
    // 看错题了
    vector<int> maxSlidingWindowMisread(vector<int>& nums, int k) {
        // 初始化
        int i = 0, j = k - 1;
        vector<int> result = {0};
        for (int l = i; l <= j; l++) {
            result[0] += nums[l];
        }

        // 正文
        for (; j < nums.size(); ) {
            j++;
            int now = result[i] - nums[i] + nums[j];
            result.push_back(now);
            i++;
        }
        result.pop_back();

        // 返回
        return result;
    }

    // 暴力
    vector<int> maxSlidingWindowViolent(vector<int>& nums, int k) {
        // 初始化
        int i = 0, j = k - 1, m = 0;
        for (int l = i; l <= j; l++) {
            if (nums[l] > nums[m]) {
                m = l;
            }
        }
        vector<int> result;
        result.push_back(nums[m]);

        // 正文
        for (; j < nums.size() - 1; ) {
            j++;
            if (m != i) {
                i++;
                if (nums[j] > nums[m]) {
                    m = j;
                }
                result.push_back(nums[m]);
            } else {
                i++;
                m = i;
                for (int l = i; l <= j; l++) {
                    if (nums[l] > nums[m]) {
                        m = l;
                    }
                }
                result.push_back(nums[m]);
            }
        }

        // 返回
        return result;
    }

    // 单调队列
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        deque<int> que;  // 使用deque(双端队列)来实现单调队列

        int i = 0;
        for (; i < k; i++) {
            while (!que.empty() && nums[i] > que.back()) {
                que.pop_back();
            }
            que.push_back(nums[i]);
        }
        result.push_back(que.front());
        for (; i < nums.size(); i++) {
            if (!que.empty() && nums[i - k] == que.front()) {  // 真实队列的第一个 是否等于 单调队列的第一个
                que.pop_front();
            }
            while (!que.empty() && nums[i] > que.back()) {
                que.pop_back();
            }
            que.push_back(nums[i]);
            result.push_back(que.front());
        }

        return result;
    }
};


class SolutionOfCarl {
private:
    class MyQueue { //单调队列（从大到小）
    public:
        deque<int> que; // 使用deque来实现单调队列
        // 每次弹出的时候，比较当前要弹出的数值是否等于队列出口元素的数值，如果相等则弹出。
        // 同时pop之前判断队列当前是否为空。
        void pop(int value) {
            if (!que.empty() && value == que.front()) {
                que.pop_front();
            }
        }
        // 如果push的数值大于入口元素的数值，那么就将队列后端的数值弹出，直到push的数值小于等于队列入口元素的数值为止。
        // 这样就保持了队列里的数值是单调从大到小的了。
        void push(int value) {
            while (!que.empty() && value > que.back()) {
                que.pop_back();
            }
            que.push_back(value);

        }
        // 查询当前队列里的最大值 直接返回队列前端也就是front就可以了。
        int front() {
            return que.front();
        }
    };
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyQueue que;
        vector<int> result;
        for (int i = 0; i < k; i++) { // 先将前k的元素放进队列
            que.push(nums[i]);
        }
        result.push_back(que.front()); // result 记录前k的元素的最大值
        for (int i = k; i < nums.size(); i++) {
            que.pop(nums[i - k]); // 滑动窗口移除最前面元素
            que.push(nums[i]); // 滑动窗口前加入最后面的元素
            result.push_back(que.front()); // 记录对应的最大值
        }
        return result;
    }
};


int main() {
    Solution solution;
    SolutionOfCarl solutionOfCarl;

    vector<int> nums = {1,3,1,2,0,5};
    int k = 3;

//    vector<int> output = solution.maxSlidingWindowMisread(nums, k);
//    vector<int> output = solution.maxSlidingWindowViolent(nums, k);
    vector<int> output = solution.maxSlidingWindow(nums, k);
//    vector<int> output = solutionOfCarl.maxSlidingWindow(nums, k);
    for (int i : output) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
