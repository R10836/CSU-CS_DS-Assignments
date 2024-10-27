//
// Created by Shawn33712 on 24-8-21.
//

/*
376. 摆动序列
中等
相关标签
相关企业
如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为 摆动序列 。第一个差（如果存在的话）可能是正数或负数。仅有一个元素或者含两个不等元素的序列也视作摆动序列。

例如， [1, 7, 4, 9, 2, 5] 是一个 摆动序列 ，因为差值 (6, -3, 5, -7, 3) 是正负交替出现的。

相反，[1, 4, 7, 2, 5] 和 [1, 7, 4, 5, 5] 不是摆动序列，第一个序列是因为它的前两个差值都是正数，第二个序列是因为它的最后一个差值为零。
子序列 可以通过从原始序列中删除一些（也可以不删除）元素来获得，剩下的元素保持其原始顺序。

给你一个整数数组 nums ，返回 nums 中作为 摆动序列 的 最长子序列的长度 。



示例 1：

输入：nums = [1,7,4,9,2,5]
输出：6
解释：整个序列均为摆动序列，各元素之间的差值为 (6, -3, 5, -7, 3) 。
示例 2：

输入：nums = [1,17,5,10,13,15,10,5,16,8]
输出：7
解释：这个序列包含几个长度为 7 摆动序列。
其中一个是 [1, 17, 10, 13, 10, 16, 8] ，各元素之间的差值为 (16, -7, 3, -3, 6, -8) 。
示例 3：

输入：nums = [1,2,3,4,5,6,7,8,9]
输出：2


提示：

1 <= nums.length <= 1000
0 <= nums[i] <= 1000


进阶：你能否用 O(n) 时间复杂度完成此题?
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    int wiggleMaxLength_Wrong(vector<int>& nums) {
        int length = nums.size();
        if (length == 1) {
            return 1;
        }

        int count = 1;
        int waveNum = nums[0];
        bool waveUp;
        bool initWaveUpFlag = false;
        for (int i = 1; i < length; i++) {
            if (! initWaveUpFlag) {  // 初始化
                if (nums[i] != waveNum) {
                    count++;
                    if (waveNum < nums[i]) {
                        waveUp = true;cout << nums[i] << " ";
                    } else {
                        waveUp = false;cout << nums[i] << " ";
                    }
                    waveNum = nums[i];
                    initWaveUpFlag = true;
                }
            } else {  // 初始化完成后
                if (waveUp) {  // 之前在上升
                    if (waveNum > nums[i]) {
                        count++;
                        waveNum = nums[i];
                        waveUp = false;cout << nums[i] << " ";
                    }
                } else {  // 之前在下降
                    if (waveNum < nums[i]) {
                        count++;
                        waveNum = nums[i];
                        waveUp = true;cout << nums[i] << " ";
                    }
                }
            }
        }
        return count;
    }

    int wiggleMaxLength_Wrong2(vector<int>& nums) {
        // 特殊情况
        int length = nums.size();
        if (length == 1) {
            return 1;
        }
        // 正文
        int count = 1;
        int lastWave = 0; // 上升为1，下降为-1，保持为0。
        for (int i = 1; i < length; i++) {
            int nowWave;
            if (nums[i] > nums[i-1]) {
                nowWave = 1;
            } else if (nums[i] < nums[i-1]) {
                nowWave = -1;
            } else {
                nowWave = 0;
            }
            if (nowWave != lastWave && nowWave != 0) {
                count++;
            }
            lastWave = nowWave;
        }
        // 返回
        return count;
    }

    int wiggleMaxLength(vector<int>& nums) {
        // 特殊情况
        int length = nums.size();
        if (length == 1) {
            return 1;
        }
        // 正文
        int count = 1;
        int lastWave = 0; // 上升为1，下降为-1，保持为0。
        for (int i = 1; i < length; i++) {
            int nowWave;
            if (nums[i] > nums[i-1]) {
                nowWave = 1;
            } else if (nums[i] < nums[i-1]) {
                nowWave = -1;
            } else {
                nowWave = lastWave;  // 直接忽略wave为0的影响（把wave等于0当作wave趋势不变），更为合适。即是nowWave = lastWave而不是nowWave = 0。
            }
            if (nowWave != lastWave && nowWave != 0) {  // wave有变化时才加count
                count++;
            }
            lastWave = nowWave;
        }
        // 返回
        return count;
    }
};


int main() {
    Solution solution;

    vector<int> nums = {9,10,9,8,8,1,9,8,1,2,1,2,1,2,1,2,1,2,10};
//    int i = solution.wiggleMaxLength_Wrong(nums);
//    int i = solution.wiggleMaxLength_Wrong2(nums);
    int i = solution.wiggleMaxLength(nums);
    cout << "\n" << i;

    return 0;
}
