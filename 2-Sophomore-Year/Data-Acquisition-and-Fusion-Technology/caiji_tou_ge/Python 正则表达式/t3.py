import re

text = input()
# ********** Begin *********#
# 1.匹配以t开头的所有单词并显示
itext = re.finditer(r'\bt\w*', text)
for match in itext:
    print(match.group())

# 2.用空格分割句子
print(re.split(r' ', text))

# 3.用‘-’代替句子中的空格
print(re.sub(r' ', '-', text))

# 4.用‘-’代替句子中的空格，并返回替换次数
replaced_text, count = re.subn(r' ', '-', text)
result_tuple = (replaced_text, count)
print(result_tuple)
# ********** End **********#
