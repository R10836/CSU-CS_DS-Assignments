//
// Created by Shawn33712 on 24-8-25.
//

/*
698. 划分为k个相等的子集
中等
相关标签
相关企业
提示
给定一个整数数组  nums 和一个正整数 k，找出是否有可能把这个数组分成 k 个非空子集，其总和都相等。



示例 1：

输入： nums = [4, 3, 2, 3, 5, 2, 1], k = 4
输出： True
说明： 有可能将其分成 4 个子集（5），（1,4），（2,3），（2,3）等于总和。
示例 2:

输入: nums = [1,2,3,4], k = 3
输出: false


提示：

1 <= k <= len(nums) <= 16
0 < nums[i] < 10000
每个元素的频率在 [1,4] 范围内
*/

#include "iostream"
#include "vector"
// 如果你想要对容器中的元素求和，可以使用<numeric>库中的std::accumulate函数
#include "numeric"
// 如果你知道一个 vector 中的元素值，并且想要找到它的下标，可以使用标准库中的 std::find 函数。std::find 函数返回一个迭代器，指向找到的元素的位置。然后，你可以通过将该迭代器与 vector 的 begin() 迭代器相减来获得元素的下标。
#include "algorithm"

using namespace std;


class Solution {
private:
    struct rxyType {
        int index;
        int val;
    };

    vector<rxyType> path;

    vector<int> inside;

    vector<vector<int>> outside;

public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        // 准备工作
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0) {
            return false;
        }
        int target = sum / k;

        vector<rxyType> numsPlus;
        for (int i = 0; i < nums.size(); i++) {
            numsPlus.push_back({i, nums[i]});
        }

        // 回溯
        backtracking(numsPlus, target, 0);

        // 打印
//        for (int i = 0; i < numsPlus.size(); i++) {
//            cout << " | " <<  numsPlus[i].index << " ";
//            cout <<  numsPlus[i].val << " | ";
//        }
//        cout << endl;
//
//        for (int i = 0; i < outside.size(); i++) {
//            for (int j = 0; j < outside[i].size(); j++) {
//                cout << outside[i][j] << " ";
//            }
//            cout << endl;
//        }

        // 回溯2
        vector<int> currentCombination;
        vector<bool> used(nums.size()-1, false);
        return backtracking_2(outside, currentCombination, used, 0, nums.size()-1);

        // 返回
    }

    bool backtracking_2(const vector<vector<int>>& outside, vector<int>& currentCombination, vector<bool>& used, int startIndex, int n) {
        // 如果所有数字都被恰好使用一次，则返回 true
        if (allUsed(used, n)) {
            return true;
        }

        // 递归查找
        for (int i = startIndex; i < outside.size(); i++) {
            const vector<int>& inside = outside[i];

            // 检查是否可以使用当前组合
            bool canUse = true;
            for (int num : inside) {
                if (num <= n && used[num]) {
                    canUse = false;
                    break;
                }
            }

            // 如果可以使用
            if (canUse) {
                // 标记已使用的数字
                for (int num : inside) {
                    if (num <= n) {
                        used[num] = true;
                    }
                }

                currentCombination.push_back(i);

                // 递归查找下一步
                if (backtracking_2(outside, currentCombination, used, i + 1, n)) {
                    return true;
                }

                // 回溯：取消标记
                for (int num : inside) {
                    if (num <= n) {
                        used[num] = false;
                    }
                }
                currentCombination.pop_back();
            }
        }

        return false;
    }

    bool allUsed(const vector<bool>& used, int n) const {
        for (int i = 0; i <= n; i++) {
            if (!used[i]) {
                return false;
            }
        }
        return true;
    }

    void backtracking(vector<rxyType>& numsPlus, int target, int startIndex) {
        // 预剪枝
        int valSum = rxyTypeValSum(path);
        if (valSum > target) {
            return;
        }
        // 基线
        if (valSum == target) {
            for (int i = 0; i < path.size(); i++) {
                inside.push_back(path[i].index);
            }
            outside.push_back(inside);
            inside.clear();
            return;
        }

        // 迭代
        for (int i = startIndex; i < numsPlus.size(); i++) {
            path.push_back(numsPlus[i]);
            backtracking(numsPlus, target, i + 1);
            path.pop_back();
        }
    }

    int rxyTypeValSum(vector<rxyType>& v) {
        int sum = 0;
        for (int i = 0; i < v.size(); i++) {
            sum += v[i].val;
        }
        return sum;
    }
};


int main() {
    Solution solution;

    vector<int> nums = {4,4,6,2,3,8,10,2,10,7};
    int k = 4;
    cout << boolalpha << solution.canPartitionKSubsets(nums, k) << endl;

    return 0;
}

/*
class Solution {
private:
    struct rxyType {
        int index;
        int val;
        bool used;
    };

    vector<rxyType> path;

public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        // 准备工作
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0) {
            return false;
        }
        int target = sum / k;

        vector<rxyType> numsPlus;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            numsPlus.push_back({i, nums[i], false});
        }

        // 回溯
        backtracking(numsPlus, target, 0);

        // 返回
        bool virgin = true;
        for (int i = 0; i < numsPlus.size(); i++) {
            cout <<  numsPlus[i].index << " ";
            cout <<  numsPlus[i].val << " ";
            cout << boolalpha << numsPlus[i].used << " | ";
            if (!numsPlus[i].used) {
                virgin = false;
            }
        }
        cout << endl;
        return virgin;
    }

    void backtracking(vector<rxyType>& numsPlus, int target, int startIndex) {
        // 预剪枝
        int valSum = rxyTypeValSum(path);
        if (valSum > target) {
            return;
        }
        // 基线
        if (valSum == target) {
            // for (int i = 0; i < path.size(); i++) {
            //     if (path[i].used) {
            //         return;
            //     }
            // }
            for (int i = 0; i < path.size(); i++) {
                cout << path[i].index << " ";
                numsPlus[path[i].index].used = true;
                path[i].used = true;
            }
            cout << endl;
            return;
        }

        // 迭代
        for (int i = startIndex; i < numsPlus.size(); i++) {
            path.push_back(numsPlus[i]);
            backtracking(numsPlus, target, i + 1);
            path.pop_back();
        }
    }

    int rxyTypeValSum(vector<rxyType>& v) {
        int sum = 0;
        for (int i = 0; i < v.size(); i++) {
            sum += v[i].val;
        }
        return sum;
    }
};
*/
