import re

text = input()
# ********** Begin *********#
# 1.匹配字符单词 Love
print(re.findall(r'\bLove\b', text))
# 2.匹配以 w 开头的完整单词
print(re.findall(r'\bw\w*', text))
# 3.查找三个字母长的单词（提示：可以使用{m,n}方式）
print(re.findall(r'\b\w{3}\b', text))
# ********** End **********
