from openai import OpenAI
import os
client = OpenAI(api_key=os.environ.get("replace with your openai key"))
response = client.chat.completions.create(
    model="gpt-4",
    messages=[
        {"role": "system", "content": "You are a helpful assistant."},
        {"role": "user", "content": "Explain Calculus to me like I'm 5"},
    ],
)
print(response.choices[0].message.content)
