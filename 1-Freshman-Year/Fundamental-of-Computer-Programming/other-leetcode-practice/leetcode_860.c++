//
// Created by Shawn33712 on 24-9-16.
//

/*
860. 柠檬水找零
已解答
简单
相关标签
相关企业
在柠檬水摊上，每一杯柠檬水的售价为 5 美元。顾客排队购买你的产品，（按账单 bills 支付的顺序）一次购买一杯。

每位顾客只买一杯柠檬水，然后向你付 5 美元、10 美元或 20 美元。你必须给每个顾客正确找零，也就是说净交易是每位顾客向你支付 5 美元。

注意，一开始你手头没有任何零钱。

给你一个整数数组 bills ，其中 bills[i] 是第 i 位顾客付的账。如果你能给每位顾客正确找零，返回 true ，否则返回 false 。



示例 1：

输入：bills = [5,5,5,10,20]
输出：true
解释：
前 3 位顾客那里，我们按顺序收取 3 张 5 美元的钞票。
第 4 位顾客那里，我们收取一张 10 美元的钞票，并返还 5 美元。
第 5 位顾客那里，我们找还一张 10 美元的钞票和一张 5 美元的钞票。
由于所有客户都得到了正确的找零，所以我们输出 true。
示例 2：

输入：bills = [5,5,10,10,20]
输出：false
解释：
前 2 位顾客那里，我们按顺序收取 2 张 5 美元的钞票。
对于接下来的 2 位顾客，我们收取一张 10 美元的钞票，然后返还 5 美元。
对于最后一位顾客，我们无法退回 15 美元，因为我们现在只有两张 10 美元的钞票。
由于不是每位顾客都得到了正确的找零，所以答案是 false。


提示：

1 <= bills.length <= 105
bills[i] 不是 5 就是 10 或是 20
*/

#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;


class Solution {
public:
    // 标准简单方法
    bool lemonadeChange(vector<int>& bills) {
        int len = bills.size();
        int b5 = 0, b10 = 0;

        for (int i = 0; i < len; i++) {
            if (bills[i] == 5) {
                b5++;
            } else if (bills[i] == 10) {
                if (b5 >= 1) {
                    b5--;
                    b10++;
                } else {
                    return false;
                }
            } else if (bills[i] == 20) {
                if (b10 >= 1 && b5 >= 1) {
                    b10--; b5--;
                } else if (b5 >= 3) {
                    b5 -= 3;
                } else {
                    return false;
                }
            }
        }
        return true;
    }

    // 自写复杂方法
    bool lemonadeChange2(vector<int>& bills) {
        int len = bills.size();
        vector<int> save;

        for (int i = 0; i < len; i++) {
            int need = bills[i] - 5;
            if (need == 0) {
                save.push_back(bills[i]);
            } else {
                sort(save.begin(), save.end());
                while (need != 0) {
                    if (save.empty()) {
                        return false;
                    }
                    int index = save.size() - 1;
                    while (index >= 0 && need - save[index] < 0) {
                        index--;
                    }
                    if (index < 0) {return false;}
                    need -= save[index];
                    save.erase(save.begin() + index);
                }
                save.push_back(bills[i]);
            }
        }

        return true;
    }
};

int main() {}