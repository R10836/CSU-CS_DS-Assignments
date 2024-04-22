while 1:
    try:
        x = input()
        force, speed, intelligence, rule = x.split(',')

        print("武力是 {:<4} {}".format(force, '*' * (int(force) // 10)))
        print("速度是 {:<4} {}".format(speed, '*' * (int(speed) // 10)))
        print("智力是 {:<4} {}".format(intelligence, '*' * (int(intelligence) // 10)))
        print("统治是 {:<4} {}".format(rule, '*' * (int(rule) // 10)))
    except EOFError:
        break
