import re
from datetime import datetime

# 样例日期时间字符串
date_str = "Thu, 29 Mar 2001 03:00:00 -0800 (PST"

# 正则表达式
date_pattern = r'\d{1,2} \w{3} \d{4} \d{2}:\d{2}:\d{2}'

# 使用正则表达式匹配
match = re.search(date_pattern, date_str)
if match:
    print("匹配的日期时间字符串:", match.group())
    # 尝试将匹配的字符串转换为 datetime 对象
    parsed_date = datetime.strptime(match.group(), '%d %b %Y %H:%M:%S')
    print("转换后的 datetime 对象:", parsed_date)
else:
    print("没有找到匹配项")
