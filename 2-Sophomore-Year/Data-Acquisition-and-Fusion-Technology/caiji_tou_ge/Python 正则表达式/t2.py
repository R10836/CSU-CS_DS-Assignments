import re

text = input()
# ********** Begin *********#
# 1.用compile方法，匹配所有含字母i的单词
rr = re.compile(r'\b\w*i\w*\b')
print(rr.findall(text))

# 2.在字符串起始位置匹配字符The是否存在，并返回被正则匹配的字符串
print(re.match(r'The', text).group() if re.match(r'The', text) else None)

# 3.在整个字符串查看字符is是否存在，并返回被正则匹配的字符串
print(re.search(r'is', text).group() if re.search(r'is', text) else None)
# ********** End **********#
