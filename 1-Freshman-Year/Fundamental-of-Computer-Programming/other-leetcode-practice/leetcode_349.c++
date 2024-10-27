//
// Created by Shawn33712 on 24-8-16.
//

/*
 *349. 两个数组的交集
简单
相关标签
相关企业
给定两个数组 nums1 和 nums2 ，返回 它们的
交集
 。输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序 。



示例 1：

输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2]
示例 2：

输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出：[9,4]
解释：[4,9] 也是可通过的


提示：

1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 1000
 * */

#include "iostream"
#include "vector"
#include "unordered_set"

using namespace std;


class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        // 初始化
        unordered_set<int> result;
        unordered_set<int> nums_set(nums1.begin(), nums1.end());  // 将 nums1 转换为 set

        // 正文
        for (int num : nums2) {
            if (nums_set.find(num) != nums_set.end()) {  // 如果 nums2 的元素在 nums_set 中存在
                result.insert(num);
            }
        }

        // 返回
        return vector<int>(result.begin(), result.end());  // 将 set 转换为 vector 并返回
    }
};


int main() {
    Solution sol;

    vector<int> nums1 = {1,2,2,1};
    vector<int> nums2 = {2,2};

    vector<int> result = sol.intersection(nums1, nums2);
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }

    return 0;
}

//但是要注意，**使用数组来做哈希的题目，是因为题目都限制了数值的大小。**
//
//而这道题目没有限制数值的大小，就无法使用数组来做哈希表了。

//本题后面 力扣改了 题目描述 和 后台测试数据，增添了 数值范围：
//
//* 1 <= nums1.length, nums2.length <= 1000
//* 0 <= nums1[i], nums2[i] <= 1000
//
//所以就可以 使用数组来做哈希表了， 因为数组都是 1000以内的。
