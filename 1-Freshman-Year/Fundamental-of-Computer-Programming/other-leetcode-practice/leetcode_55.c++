//
// Created by Shawn33712 on 24-9-14.
//

/*
55. 跳跃游戏
中等
相关标签
相关企业
给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。



示例 1：

输入：nums = [2,3,1,1,4]
输出：true
解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。
示例 2：

输入：nums = [3,2,1,0,4]
输出：false
解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。


提示：

1 <= nums.length <= 104
0 <= nums[i] <= 105
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    //贪心：那么这个问题就转化为跳跃覆盖范围究竟可不可以覆盖到终点！
    bool canJump(vector<int>& nums) {
        int len = nums.size();
        vector<bool> gone(len, false);
        gone[0] = true;

        int i = 0;
        int end = 0;
        while (i < len) {
            if (gone[i]) {
                end = i + nums[i];
                for (int j = i; j <= end && j < len; j++) {
                    gone[j] = true;
                }
            }
            i++;
        }

        return gone[len-1];
    }
};


int main() {
    Solution solution;

    vector<int> nums = {5,9,3,2,1,0,2,3,3,1,0,0};
    cout << boolalpha << solution.canJump(nums) << endl;

    return 0;
}
