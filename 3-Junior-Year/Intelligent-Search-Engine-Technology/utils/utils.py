import configparser


def get_stopwords_set():
    config = configparser.ConfigParser()
    config.read('config.ini', encoding="utf-8")
    filepath = config['DEFAULT']['stopwords_path']
    import os
    if (os.path.exists(filepath)):
        with open(filepath, 'r', encoding='utf-8') as f:
            lst = f.read()
            f.close()
        return set(lst.split('\n'))
    else:
        raise FileNotFoundError


def is_valid_word(word: str):
    from unicodedata import category
    for chrs in word:
        if category(chrs).startswith("P"):
            word = word.replace(chrs, '')
    return not word.isdigit() and word != ''


def get_seq_dict(text: str):
    import jieba
    stopwords_set = get_stopwords_set()
    words_dict: dict[str, list] = {}
    seq_list = jieba.cut(text, cut_all=False)
    position = 0
    for seq in seq_list:
        if seq not in stopwords_set and seq.strip() != '' and is_valid_word(seq):
            if seq not in words_dict.keys():
                words_dict[seq] = [1, [position]]
            else:
                words_dict[seq][0] += 1
                words_dict[seq][1].append(position)
        position += len(seq)
    return words_dict
