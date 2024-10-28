import openai

# 设置 API 密钥和基本 URL
client = openai.OpenAI(
    api_key="sk",
    base_url="https://dashscope.aliyuncs.com/compatible-mode/v1"
)

# 使用特定模型进行聊天完成请求
response = client.chat.completions.create(
    messages=[
        {
            "role": "user",
            "content": "你是谁?"
        }
    ],
    model="qwen-turbo"
)

# 打印响应结果
print(response)

"""
ChatCompletion(id='chatcmpl-378af854-0054-9a3d-a489-31d483f07bc7', choices=[Choice(finish_reason='stop', index=0, logprobs=None, message=ChatCompletionMessage(content='我是通义千问，由阿里云开发的AI助手。我被设计用来回答各种问题、提供信息和与用户进行对话。有什么我可以帮助你的吗？', role='assistant', function_call=None, tool_calls=None))], created=1721298604, model='qwen-turbo', object='chat.completion', service_tier=None, system_fingerprint=None, usage=CompletionUsage(completion_tokens=36, prompt_tokens=11, total_tokens=47))
"""