import openai
import re

# 设置 API 密钥和基本 URL
client = openai.OpenAI(
    api_key="sk-",
    base_url="https://dashscope.aliyuncs.com/compatible-mode/v1"
)

# 初始化对话历史
conversation_history = [
    {"role": "system", "content": """
        你是一个SQL查询生成助手。数据库的表名是emails2，列名和数据类型如下：
        - `Message-ID` (VARCHAR(255)): 邮件的唯一标识符，例如 '<18782981.1075855378110.JavaMail.evans@thyme'。
        - `From` (VARCHAR(255)): 发件人的电子邮件地址，例如 'phillip.allen@enron.co'。
        - `To` (VARCHAR(255)): 收件人的电子邮件地址，例如 'tim.belden@enron.co'。
        - `Subject` (VARCHAR(255)): 邮件的主题，可以为空，例如 'Re: test'。
        - `content` (LONGTEXT): 邮件的内容，可能包含文本、换行符等。
        - `Timed` (DATETIME): 邮件的日期和时间，格式例如 "2001-05-14 16:39:00"。
        
        请确保生成的SQL语句以```sql开头并以```结尾。
    """}
]


def chat_with_model(user_input):
    # 将用户输入添加到对话历史
    conversation_history.append({"role": "user", "content": user_input})

    # 调用大模型进行对话
    response = client.chat.completions.create(
        messages=conversation_history,
        model="qwen-turbo"
    )

    # 获取模型回复
    model_reply = response.choices[0].message.content.strip()

    # 将模型回复添加到对话历史
    conversation_history.append({"role": "assistant", "content": model_reply})

    return model_reply


def extract_sql_query(response):
    # 使用正则表达式提取SQL代码块
    match = re.search(r"```sql(.*?)```", response, re.DOTALL)
    if match:
        sql_query = match.group(1).strip()
        return sql_query
    else:
        raise ValueError("模型返回的SQL语句格式不正确")


def natural_language_to_sql(natural_language_query):
    user_input = f"将以下自然语言查询转换为SQL语句: {natural_language_query}"
    sql_query_response = chat_with_model(user_input)
    sql_query = extract_sql_query(sql_query_response)
    # 预置数据库使用语句
    sql_query = (f"USE myemail;\n"
                 f"{sql_query}")
    return sql_query


# 持续对话
print("开始对话")
while True:
    user_input = input("你: ")
    if user_input.lower() in ["退出", "q", "quit", "exit"]:
        print("对话结束。")
        break

    try:
        # 将自然语言转换为SQL语句
        sql_query = natural_language_to_sql(user_input)
        print(f"{sql_query}")
    except Exception as e:
        print(f"出错了: {e}")
