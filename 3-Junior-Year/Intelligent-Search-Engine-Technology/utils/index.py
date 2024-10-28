import pickle


class DocRecord:
    def __init__(self) -> None:
        self.wordnum_in_doc = 0
        self.position: list[int] = []

    def insert(self, position: int | list[int]):
        if isinstance(position, list):
            for p in position:
                self.insert(p)
        elif isinstance(position, int):
            if position not in self.position:
                self.position.append(position)
                self.wordnum_in_doc += 1
        else:
            raise TypeError("TypeError")


class WordRecord:

    def __init__(self, word) -> None:
        self.word = word
        self.doc_num = 0
        self.doc_record_dict: dict[int, DocRecord] = {}

    def insert(self, doc_index: int, position: int | list[int]):
        if doc_index not in self.doc_record_dict.keys():
            self.doc_record_dict[doc_index] = DocRecord()
        self.doc_record_dict[doc_index].insert(position)
        self.doc_num += 1
    def get_doc_index_lst(self):
        return list(self.doc_record_dict.keys())

class InvertedIndex:

    def __init__(self, filepath: str = None) -> None:
        if filepath:
            import os
            if not os.path.isfile(filepath):
                raise FileNotFoundError
            else:
                with open(filepath, 'rb') as f:
                    self = pickle.loads(f)
        else:
            self.dictionary: set[str] = set()
            self.posting_list: dict[str, WordRecord] = {}
            self.url_index_dict: dict[str, int] = {}

    def query(self, word: str):
        return self.posting_list[word].get_doc_index_lst()

    def insert(self, word: str, url: str, position: int | list[int]):
        if word not in self.dictionary:
            self.dictionary.add(word)
            self.posting_list[word] = WordRecord(word)
        self.posting_list[word].insert(self.url_index_dict[url], position)

    def puts_url(self, id: int, url: str):
        self.url_index_dict[url] = id

    def write_in_file(self, filepath: str):
        with open(filepath, 'wb') as f:
            pickle.dump(self, f)
            f.close()
