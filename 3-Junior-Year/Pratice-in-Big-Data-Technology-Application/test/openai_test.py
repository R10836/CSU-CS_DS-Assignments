import openai

# 设置OpenAI API密钥
openai.api_key = 'sk-'




def test_openai_connection():
    try:
        response = openai.ChatCompletion.create(
            model="gpt-3.5-turbo",
            messages=[
                {"role": "system", "content": "You are a helpful assistant."},
                {"role": "user", "content": "Hello, how are you?"}
            ]
        )
        print("Response from OpenAI:", response['choices'][0]['message']['content'])
    except openai.error.OpenAIError as e:
        print("Failed to connect to OpenAI:", e)
        if "quota" in str(e).lower():
            print("You have exceeded your current quota. Please check your plan and billing details.")
        else:
            print("An error occurred:", e)

if __name__ == "__main__":
    test_openai_connection()
