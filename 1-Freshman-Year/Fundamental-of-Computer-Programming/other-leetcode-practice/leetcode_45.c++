//
// Created by Shawn33712 on 24-9-14.
//

/*
45. 跳跃游戏 II
中等
相关标签
相关企业
给定一个长度为 n 的 0 索引整数数组 nums。初始位置为 nums[0]。

每个元素 nums[i] 表示从索引 i 向前跳转的最大长度。换句话说，如果你在 nums[i] 处，你可以跳转到任意 nums[i + j] 处:

0 <= j <= nums[i]
i + j < n
返回到达 nums[n - 1] 的最小跳跃次数。生成的测试用例可以到达 nums[n - 1]。



示例 1:

输入: nums = [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
示例 2:

输入: nums = [2,3,0,1,4]
输出: 2


提示:

1 <= nums.length <= 104
0 <= nums[i] <= 1000
题目保证可以到达 nums[n-1]
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    int jump(vector<int>& nums) {
        int len = nums.size();

        for (int i = 0; i < len; i++) {
            nums[i] += i;
        }

        vector<int> times(len, 10001);
        times[0] = 0;

        int index = 0;
        while (times[index] != 10001) {
            for (int i = index; i < len && i <= nums[index]; i++) {
                if (times[i] != 0) {
                    times[i] = min(times[i], times[index]+1);
                }
            }

            if (times[len-1] != 10001) {
                return times[len-1];
            }

            index++;
        }
        return 10086;
    }
};


int main() {
    Solution solution;

    vector<int> nums = {2,3,1,1,4};
    cout << solution.jump(nums) << endl;

    return 0;
}
