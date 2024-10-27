//
// Created by Shawn33712 on 24-8-19.
//

/*
17. 电话号码的字母组合
中等
相关标签
相关企业
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。





示例 1：

输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
示例 2：

输入：digits = ""
输出：[]
示例 3：

输入：digits = "2"
输出：["a","b","c"]


提示：

0 <= digits.length <= 4
digits[i] 是范围 ['2', '9'] 的一个数字。
*/

#include "iostream"
#include "vector"
#include "string"

using namespace std;


class Solution {
public:
    vector<string> result;

    string path;

    int where = 0;

    vector<string> letterCombinations(string digits) {
        if (digits == "") return result;  // 如果输入为空，直接返回空结果（result是vector类型）。如果不加这句，返回将是一个包含一个空字符串的列表。但根据题意，当digit为空时应该返回空列表。
        backtracking(digits);
        return result;
    }

    void backtracking(string digits) {
        // 基线
        if (path.size() == digits.size()) {
            result.push_back(path);
            return;
        }
        // 递归
        string s = translate(digits[where]);
        for (int i = 0; i < s.size(); i++) {
            path.push_back(s[i]); where++;
            backtracking(digits);
            path.pop_back(); where--;
        }
    }

    string translate(char number) {
        if (number == '2') {return "abc";}
        if (number == '3') {return "def";}
        if (number == '4') {return "ghi";}
        if (number == '5') {return "jkl";}
        if (number == '6') {return "mno";}
        if (number == '7') {return "pqrs";}
        if (number == '8') {return "tuv";}
        if (number == '9') {return "wxyz";}
        return "你妈了个逼的";
        /*
        在题目明确保证 digits[i] 是范围 ['2', '9'] 之间的数字时，理论上不会出现其他情况。
        因此，按照题意，translate 函数实际上不需要处理 '2' 到 '9' 以外的输入。
        但是，编译器在检查代码时，只会看代码的逻辑流程，而不会考虑题目描述。
        因此，编译器会认为在所有代码路径上，函数必须有返回值。
        即使你知道程序运行时不会遇到 '2' 到 '9' 之外的字符，编译器仍然要求所有分支路径都能返回值，否则它会认为你的代码逻辑可能存在漏洞，从而报错。
         */
    }
};


int main() {
    Solution solution;

    string digits = "";
    cout << solution.translate();
    vector<string> v = solution.letterCombinations(digits);
    for (int i = 0; i < v.size(); i++) {
//        cout << i + 1 << ": "<< v[i] << "; ";
        cout << v[i] << " ";
    }

    return 0;
}
