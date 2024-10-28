"""
我想看看phillip.allen@enron.co发给tim.belden@enron.co的全部邮件
给我2000年10月8日12点到22时的所有邮件内容
2000年phillip.allen@enron.co的邮箱有没有谈到有关Enron Energy的内容

MATCH (p1:Person)-[r:SENDS]->(p2:Person)
WHERE r.timed >= datetime("2000-10-08T00:00:00") AND r.timed <= datetime("2000-10-09T02:59:59")
RETURN p1, r, p2
ORDER BY r.timed
"""
# 为了避免混淆，列名全加了d
# ALTER TABLE emails2
# CHANGE COLUMN `Message-ID` `Message-IDd` VARCHAR(255),
# CHANGE COLUMN `From` `Fromd` VARCHAR(255),
# CHANGE COLUMN `To` `Tod` VARCHAR(255),
# CHANGE COLUMN `Subject` `Subjectd` VARCHAR(255),
# CHANGE COLUMN `content` `contentd` LONGTEXT,
# CHANGE COLUMN `Date` `Dated` VARCHAR(50);


import re
from io import BytesIO

import matplotlib.pyplot as plt
import networkx as nx
import openai
import pandas as pd
import streamlit as st
from neo4j import GraphDatabase
from py2neo import Graph
from pyvis.network import Network
from sqlalchemy import create_engine, text
import streamlit.components.v1 as components



# mysql配置
database_username = ''
database_password = ''
database_ip = '127.0.0.1'
database_name = 'myemail'
engine = create_engine(f'mysql+pymysql://{database_username}:{database_password}@{database_ip}/{database_name}')

# Neo4j配置
neo4j_uri = "bolt://localhost:7687"
neo4j_user = "neo4j"
neo4j_password = ""
driver = GraphDatabase.driver(neo4j_uri, auth=(neo4j_user, neo4j_password))
graph = Graph(neo4j_uri, auth=(neo4j_user, neo4j_password))

# 设置 API 密钥和基本 URL
client = openai.OpenAI(
    api_key="sk-",
    base_url="https://dashscope.aliyuncs.com/compatible-mode/v1"
)

# 预制自然语言
sentence_0 = """
        你是一个SQL查询生成助手。数据库的表名是emails2，列如下：
        - `Message-IDd` (VARCHAR(255)): 邮件唯一标识符，例如 '<18782981.1075855378110.JavaMail.evans@thyme'。
        - `Fromd` (VARCHAR(255)): 发件人邮件地址，例如 'phillip.allen@enron.co'。
        - `Tod` (VARCHAR(255)): 收件人邮件地址，例如 'tim.belden@enron.co'。
        - `Subjectd` (VARCHAR(255)): 邮件主题，可以为空，例如 'Re: test'。
        - `contentd` (LONGTEXT): 邮件内容，可能包含文本、换行符等。
        - `Timed` (DATETIME): 邮件日期和时间，格式例如 "2001-05-14 16:39:00"。
        请确保生成的SQL语句以```sql开头并以```结尾。
        """
sentence_1 = """
        你是一个Neo4j Cypher查询生成助手。数据库的图节点和关系如下：
        - 节点只有一种标签: Person
        - 节点属性: 
            - `email` (STRING): 电子邮件地址，例如 'phillip.allen@enron.co'。
        - 关系只有一种类型: SENDS
        - 关系属性:
            - `message_idd` (STRING): 邮件唯一标识符，例如 '<18782981.1075855378110.JavaMail.evans@thyme'。
            - `subjectd` (STRING): 邮件主题，可以为空，例如 'Re: test'。
            - `contentd` (STRING): 邮件内容，可能包含文本、换行符等。
            - `timed` (DATETIME): 邮件日期和时间，格式例如 "2001-05-14T16:39:00"。
            - `weight` (INT): 是发件人和收件人之间的交流次数。
        请确保生成的Cypher语句以```cypher开头并以```结尾。
        """


def chat_with_model(instruct, freestyle):
    # 构造请求内容
    user_input = f"{instruct}{freestyle}"
    # 调用大模型进行对话
    response = client.chat.completions.create(
        messages=[{"role": "user", "content": user_input}],
        model="qwen-turbo"
    )
    # 获取模型回复
    model_reply = response.choices[0].message.content.strip()
    return model_reply


def extract_sql_query(complex_str):
    # 使用正则表达式提取SQL代码块
    match = re.search(r"```sql(.*?)```", complex_str, re.DOTALL)
    if match:
        sql_query = match.group(1).strip()
        return sql_query
    else:
        raise ValueError("模型返回的SQL语句格式不正确")


def extract_cypher_query(complex_str):
    # 使用正则表达式提取Cypher代码块
    match = re.search(r"```cypher(.*?)```", complex_str, re.DOTALL)
    if match:
        cypher_query = match.group(1).strip()
        return cypher_query
    else:
        raise ValueError("模型返回的Cypher语句格式不正确")


def execute_sql_get_df(sql_query):
    sql_query = sql_query.replace("\n", " ")
    sql_statements = sql_query.split(";")
    with engine.connect() as connection:
        for statement in sql_statements:
            if statement.strip():
                result = connection.execute(text(statement.strip()))
        df = pd.DataFrame(result.fetchall(), columns=result.keys())
        return df


def execute_cypher_get_df(cypher_query):
    with driver.session() as session:
        result = session.run(cypher_query)
        df = process_cypher_result(result)
        return df


def process_cypher_result(result):
    data = []
    for record in result:
        row = {}
        for key, value in record.items():
            if hasattr(value, 'items'):  # 检查是否为嵌套结构
                for sub_key, sub_value in value.items():
                    row[f"{key}_{sub_key}"] = sub_value
            else:
                row[key] = value
        data.append(row)
    return pd.DataFrame(data)


def plot_graph(cypher_query):
    results = graph.run(cypher_query).data()
    if not results:
        return None
    G = nx.Graph()
    for record in results:
        nodes = set()
        for key, value in record.items():
            if isinstance(value, dict) and 'email' in value:
                nodes.add(value['email'])
            elif isinstance(value, list):
                for item in value:
                    if isinstance(item, dict) and 'email' in item:
                        nodes.add(item['email'])
        for node in nodes:
            G.add_node(node)
        if 'r' in record:
            G.add_edge(record['r'].start_node['email'], record['r'].end_node['email'])
    plt.figure(figsize=(12, 12))
    pos = nx.spring_layout(G, k=0.8, iterations=16)  # 调整k值和iterations来让节点之间更紧密
    labels = {node: node.split('@')[0] for node in G.nodes()}  # 处理节点标签，只保留@字符前的内容
    nx.draw(G, pos, labels=labels, node_size=56, node_color="skyblue", font_size=8, font_weight="light", edge_color='red')
    buf = BytesIO()
    plt.savefig(buf, format="png")
    buf.seek(0)
    return buf


# Streamlit 应用
st.title("2024 邮件分析任务")
option = st.selectbox("选择功能:", ["<此处下拉菜单以选择功能>", "大模型邮件总结", "特定主题的邮件查询", "特定发件人的邮件聚合"])


if option == "<此处下拉菜单选择功能>":
    pass


elif option == "大模型邮件总结":
    st.markdown("# 大模型邮件总结")
    st.markdown("""
    * 利用Qwen等大语言模型，对检索到的邮件内容进行智能总结与生成,可以使用ollama结合qwen 0.5b的模型在本地运行。
    * 根据用户输入的检索条件(如关键词、时间范围、发件人等)，返回符合条件的邮件总结结果。
    * 总结结果要突出重点，忠实原文，语言通顺自然
    """)
    user_input = st.text_input("请在此输入:")

    if st.button("执行检索"):
        try:
            st.markdown("## SQL 语句:")
            user_input_2 = f"\n按照自然语言语义给出MySql语句：{user_input}"
            rough_sql_query = chat_with_model(sentence_0, user_input_2)
            sql_query = extract_sql_query(rough_sql_query)
            st.code(sql_query, language='sql')

            st.markdown("## 检索结果:")
            df_1 = execute_sql_get_df(sql_query)  # 返回的DataFrame有无限操作可能性
            st.dataframe(df_1)

            st.markdown("## 内容总结:")
            if 'contentd' in df_1.columns:
                all_content = "\n".join(df_1['contentd'].tolist())[:2000]  # 调整参数可以提高总结质量，但降低速度
                user_say = f"请概括性地总结这几封邮件内容: "
                model_say = chat_with_model(user_say, all_content)
                st.markdown(model_say)
            else:
                st.markdown("这个不需要总结。")

        except Exception as e:
            st.markdown(f"报错:\n{e}")


elif option == "特定主题的邮件查询":
    st.markdown("# 特定主题的邮件查询")
    st.markdown("* 针对特定主题的邮件查询，如\"最近一个月xxx@xxx.com的邮箱有没有谈到xxx内容\"。")
    user_input = st.text_input("请在此输入:")

    if st.button("执行查询"):
        try:
            st.markdown("## SQL 语句:")
            user_input_2 = f"\n按照自然语言的需求给出MySql语句：{user_input}"
            rough_sql_query = chat_with_model(sentence_0, user_input_2)
            sql_query = extract_sql_query(rough_sql_query)
            st.code(sql_query, language='sql')

            st.markdown("## 查询结果:")
            df_2 = execute_sql_get_df(sql_query)  # 返回的DataFrame有无限操作可能性
            st.dataframe(df_2)

            st.markdown("## 问题回答:")
            all_content = "\n".join(df_2['contentd'].tolist())[:2000]  # 调整参数可以提高总结质量，但降低速度
            user_say = f"回答问题“{user_input}”，参考下述文本：\n"
            model_say = chat_with_model(user_say, all_content)
            st.markdown(model_say)

        except Exception as e:
            st.markdown(f"报错:\n{e}")


elif option == "特定发件人的邮件聚合":
    st.markdown("# 特定发件人的邮件聚合")
    st.markdown("* 针对特定发件人的邮件聚合，如\"罗列出最近一个月xxx@xxx.com邮箱与其他人讨论的主要事项的前因后果\"，将完整的邮件沟通链条提取并进行总结,其中涉及内容的前因后果。")
    user_input = st.text_input("请在此输入:")

    if st.button("提取总结"):
        try:
            st.markdown("## Cypher 语句:")
            user_input_2 = f"\n按以下自然语言的需求给出Neo4j的Cypher语句：\n{user_input}"
            rough_cypher = chat_with_model(sentence_1, user_input)
            cypher_query = extract_cypher_query(rough_cypher)
            st.code(cypher_query, language='cypher')

            st.markdown("## 查询结果:")
            df_3 = execute_cypher_get_df(cypher_query)
            st.dataframe(df_3)

            st.markdown("## 图形视图:")
            graph_image = plot_graph(cypher_query)
            if graph_image:
                st.image(graph_image, use_column_width=True)
            else:
                st.markdown("此次查询并没有图形视图。")

            st.markdown("## 问题回答:")
            if 'r_contentd' in df_3.columns:
                all_content = "\n".join(df_3['r_contentd'].tolist())[:2000]
                user_say = f"概括性地总结这几封邮件涉及内容的前因后果: "
                model_say = chat_with_model(user_say, all_content)
                st.markdown(model_say)
            else:
                st.markdown("这个不需要概括。")

        except Exception as e:
            st.markdown(f"报错:\n{e}")


# 侧边栏
st.sidebar.markdown("""
    <style>
    @keyframes example {
        0%   {color: red;}
        25%  {color: orange;}
        50%  {color: blue;}
        100% {color: green;}
    }
    .animated-header {
        font-size: 2em;
        font-weight: bold;
        animation-name: example;
        animation-duration: 10s;
        animation-iteration-count: infinite;
    }
    </style>
    <div class="animated-header">项目说明</div>
    <p>这是与大语言模型的交互实现，包括大模型邮件总结、特定主题的邮件查询、特定发件人的邮件聚合</p>
    <div class="animated-header">作者</div>
    <p>R</p>
    <div class="animated-header">大致思路</div>
    """, unsafe_allow_html=True)
st.sidebar.markdown("![1](https://raw.githubusercontent.com/LukiRyan/TyporaImageBox/main/img/202407191058169.png)")
