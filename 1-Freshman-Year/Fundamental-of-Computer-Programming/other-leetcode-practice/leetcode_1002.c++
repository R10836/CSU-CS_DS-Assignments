//
// Created by Shawn33712 on 24-8-16.
//

/*
1002. 查找共用字符
简单
相关标签
相关企业
给你一个字符串数组 words ，请你找出所有在 words 的每个字符串中都出现的共用字符（包括重复字符），并以数组形式返回。你可以按 任意顺序 返回答案。


示例 1：

输入：words = ["bella","label","roller"]
输出：["e","l","l"]
示例 2：

输入：words = ["cool","lock","cook"]
输出：["c","o"]


提示：

1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] 由小写英文字母组成
*/


#include "iostream"
#include "vector"
#include "string"

using namespace std;


class Solution {
public:
    vector<string> commonChars(vector<string>& words) {
        // 初始化
        int hash_0[26] = {0};
        for (int i = 0; i < words[0].size(); ++i) {
            hash_0[words[0][i] - 'a']++;
        }

        // 两两比较共用
        for (int k = 1; k < words.size(); k++) {
            int hash_1[26] = {0};
            for (int i = 0; i < words[k].size(); i++) {
                hash_1[words[k][i] - 'a']++;
            }
            for (int m = 0; m < 26; m++) {
                hash_0[m] = min(hash_0[m], hash_1[m]);
            }
        }

        // 结果
        vector<string> result = {};
        for (int m = 0; m < 26; m++) {
            if (hash_0[m] > 0) {
                for (int n = 0; n < hash_0[m]; n++) {
                    string s(1, char(m + 'a'));
                    result.push_back(s);
                };
            }
        }
        return result;
    }
};


int main() {
    vector<string> words = {"bella","label","roller"};
    Solution sol;
    vector<string> output = sol.commonChars(words);
    for (int i = 0; i < output.size(); i++) {
        cout << output[i] << " ";
    }
    return 0;
}
