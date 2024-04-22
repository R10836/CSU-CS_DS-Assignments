def put_row(r):
    for _ in range(2):
        print('+', end='')
        for _ in range(r):
            print('- ', end='')
    print('+')


def put_blank(r):
    for _ in range(2):
        print('1', end='')
        for _ in range(r):
            print('  ', end='')
    print('1')


while 1:
    try:
        rows = int(input())

        put_row(rows)
        for _ in range(rows):
            put_blank(rows)
        put_row(rows)
        for _ in range(rows):
            put_blank(rows)
        put_row(rows)
    except EOFError:
        break
