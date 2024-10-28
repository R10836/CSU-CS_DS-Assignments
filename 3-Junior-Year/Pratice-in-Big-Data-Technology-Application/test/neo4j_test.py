from neo4j import GraphDatabase

uri = "bolt://localhost:7687"
username = "neo4j"
password = ""

driver = GraphDatabase.driver(uri, auth=(username, password))


def add_email_interaction(sender, recipient):
    with driver.session() as session:
        session.run("""
            CREATE (a:Person {email: $sender_email})
            CREATE (b:Person {email: $recipient_email})
            CREATE (a)-[:SENT_EMAIL_TO]->(b)
            """, {'sender_email': sender, 'recipient_email': recipient})


add_email_interaction('alice@example.com', 'bob@example.com')

driver.close()
