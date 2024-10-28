from http import HTTPStatus
import dashscope

dashscope.api_key = 'sk-'
messages = [{'role': 'system', 'content': 'You are a helpful assistant.'},
            {'role': 'user', 'content': '你是什么东西？'}]

response = dashscope.Generation.call(
    model='qwen-turbo',
    messages=messages,
    result_format='message',  # set the result to be "message" format.
)

if response.status_code == HTTPStatus.OK:
    print(response)
else:
    print('Request id: %s, Status code: %s, error code: %s, error message: %s' % (
        response.request_id, response.status_code,
        response.code, response.message
    ))

"""
{"status_code": 200, "request_id": "1e1ba78d-f9a9-9ec7-88be-719d9472353d", "code": "", "message": "", "output": {"text": null, "finish_reason": null, "choices": [{"finish_reason": "stop", "message": {"role": "assistant", "content": "我是来自阿里云的超大规模语言模型，我叫通义千问。"}}]}, "usage": {"input_tokens": 23, "output_tokens": 17, "total_tokens": 40}}
"""