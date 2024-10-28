import openai

# 设置 API 密钥和基本 URL
client = openai.OpenAI(
    api_key="sk-",
    base_url="https://dashscope.aliyuncs.com/compatible-mode/v1"
)

# 初始化对话历史
conversation_history = []


def chat_with_model(user_input):
    # 将用户输入添加到对话历史
    conversation_history.append({"role": "user", "content": user_input})

    # 调用大模型进行对话
    response = client.chat.completions.create(
        messages=conversation_history,
        model="qwen-turbo"
    )

    # 获取模型回复
    model_reply = response.choices[0].message.content  # 修改这里

    # 将模型回复添加到对话历史
    conversation_history.append({"role": "assistant", "content": model_reply})

    return model_reply


# 持续对话
print("开始对话（输入[退出\\q\\quit\\exit]结束对话）")
while True:
    user_input = input("你: ")
    if user_input.lower() in ["退出", "q", "quit", "exit"]:
        print("对话结束。")
        break

    model_reply = chat_with_model(user_input)
    print("大模型:", model_reply)
