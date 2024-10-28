import pandas as pd
from datetime import datetime
from neo4j import GraphDatabase

# 构建测试数据
data = {
    'Message-ID': ['1', '2', '3', '4', '5', '6', '7'],
    'From': [
        'alice@example.com', 'bob@example.com', 'alice@example.com',
        'carol@example.com', 'alice@example.com', 'bob@example.com', 'carol@example.com'
    ],
    'To': [
        'bob@example.com', 'alice@example.com', 'carol@example.com',
        'alice@example.com', 'bob@example.com', 'carol@example.com', 'bob@example.com'
    ],
    'Subject': [
        'Meeting request', 'Re: Meeting request', 'Project update',
        'Re: Project update', 'Next steps', 'Final review', 'Re: Next steps'
    ],
    'Content': [
        'Can we meet tomorrow?', 'Sure, what time?', 'Project X will be delivered by Q3.',
        'Thanks for the update!', 'Let’s discuss the next steps.', 'Please review the final documents.', 'Will do by tonight.'
    ],
    'Date': [
        datetime(2021, 1, 1), datetime(2021, 1, 2), datetime(2021, 1, 3),
        datetime(2021, 1, 4), datetime(2021, 1, 5), datetime(2021, 1, 6), datetime(2021, 1, 7)
    ]
}

df = pd.DataFrame(data)

# 连接到 Neo4j 数据库
uri = "bolt://localhost:7687"
user = "neo4j"
password = ""
driver = GraphDatabase.driver(uri, auth=(user, password))

def add_email(tx, message_id, sender, recipient, subject, content, date):
    query = """
    MERGE (p1:Person {email: $sender})
    MERGE (p2:Person {email: $recipient})
    MERGE (p1)-[r:SENDS]->(p2)
    ON CREATE SET r.weight = 1, r.subjects = [$subject], r.contents = [$content], r.dates = [$date]
    ON MATCH SET r.weight = r.weight + 1, r.subjects = coalesce(r.subjects, []) + $subject, r.contents = coalesce(r.contents, []) + $content, r.dates = coalesce(r.dates, []) + $date
    """
    tx.run(query, sender=sender, recipient=recipient, subject=subject, content=content, date=date.strftime('%Y-%m-%d'))

# 将 DataFrame 中的数据添加到 Neo4j
with driver.session() as session:
    for index, row in df.iterrows():
        session.execute_write(add_email, row['Message-ID'], row['From'], row['To'], row['Subject'], row['Content'], row['Date'])

driver.close()
