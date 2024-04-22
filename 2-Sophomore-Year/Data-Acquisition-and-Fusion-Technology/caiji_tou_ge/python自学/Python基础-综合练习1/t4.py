while 1:
    try:
        letter = input()

        start_ascii = ord('A')
        end_ascii = ord(letter)
        num_rows = end_ascii - start_ascii + 1
        for i in range(1, num_rows + 1):
            for _ in range(0, num_rows - start_ascii):
                print(' ', end='')
            print(chr(start_ascii) * i)
            start_ascii += 1
    except EOFError:
        break
