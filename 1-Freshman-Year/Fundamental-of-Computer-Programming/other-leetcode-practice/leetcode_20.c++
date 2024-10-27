//
// Created by Shawn33712 on 24-8-18.
//

/*
20. 有效的括号
已解答
简单
相关标签
相关企业
提示
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
每个右括号都有一个对应的相同类型的左括号。


示例 1：

输入：s = "()"
输出：true
示例 2：

输入：s = "()[]{}"
输出：true
示例 3：

输入：s = "(]"
输出：false


提示：

1 <= s.length <= 104
s 仅由括号 '()[]{}' 组成
*/

#include "iostream"
#include "string"
#include "stack"

using namespace std;


class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {  // 左括号。则压栈
                stk.push(s[i]);
            } else {
                if (stk.empty()) {return false;}  // 右括号，且栈空。则一定是错的
                char top = stk.top();
                if ((s[i] == ')' && top == '(') || (s[i] == ']' && top == '[') || (s[i] == '}' && top == '{')) {  // 右括号，且与栈顶匹配。则弹栈
                    stk.pop();
                } else {  // 右括号，且与栈顶不匹配。则一定是错的
                    return false;
                }
            }
        }

        return stk.empty();  // 栈空，则匹配完毕。栈不空，则左括号多余。
    }
};


int main() {
    Solution solution;

    string s = "[()])[]({[()()]}";
    cout << boolalpha << solution.isValid(s) << endl;

    return 0;
}
