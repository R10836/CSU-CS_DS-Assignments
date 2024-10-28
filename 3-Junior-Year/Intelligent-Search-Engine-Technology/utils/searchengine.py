import threading
from utils.idf import IDFManager


def search_by(by:str,word:str,k=10):
    if(by=='idf'):
        return IDFManager().query(word,k)
    # elif(by=='BM25'):
    return None