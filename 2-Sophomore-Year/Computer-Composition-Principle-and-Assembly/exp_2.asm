DATAS SEGMENT
    S1 DB '请输入要输入的数据数量（不超过20）:', 13, 10, '$'
    S2 DB '请输入0~99之间的数据，用空格分隔:', 13, 10, '$'
    S3 DB '排序前:', 13, 10, '$'
    S4 DB '排序后:', 13, 10, '$'
    ARRAY DW 20 DUP(?)
DATAS ENDS

STACKS SEGMENT    
    STACK DB 100H DUP(?)
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES, DS:DATAS, SS:STACKS

    ; 冒泡排序子程序
    PROCEDURE BUBBLESORT
        MOV CX, SI  ; CX 存储元素的数量
        MOV SI, 0

    LOOP1:
        MOV DI, CX
        MOV BX, 0

    LOOP2:
        MOV AX, ARRAY[BX]
        CMP AX, ARRAY[BX + 2]
        JLE CONTINUE
        XCHG AX, ARRAY[BX + 2]
        MOV ARRAY[BX], AX

    CONTINUE:
        ADD BX, 2
        LOOP LOOP2

        MOV CX, DI
        LOOP LOOP1
        RET

    ; 输入数据子程序
    PROCEDURE INPUTDATA
        MOV DX, OFFSET S2
        MOV AH, 09H
        INT 21H ; 输出提示信息

        MOV SI, 0

    L3:
        MOV AH, 01H
        INT 21H ; 输入字符

        CMP AL, 20H ; 检查是否为空格
        JE L4

        SUB AL, 30H
        AND AX, 00FFH
        MOV BX, AX
        MOV AX, DX
        MUL DI
        ADD AX, BX
        MOV DX, AX

        CMP BL, 0DH
        JNE L3

    L4:
        MOV ARRAY[SI], DX
        ADD SI, 2

        MOV DL, 0AH
        MOV AH, 02H
        INT 21H ; 换行

        INC CX
        CMP CX, 20
        JL L3
        RET

    START:
        MOV AX, DATAS
        MOV DS, AX
        XOR CX, CX  ; CX 用于存储输入元素的数量

        MOV DX, OFFSET S1
        MOV AH, 09H
        INT 21H ; 输出提示信息

        MOV DL, 0AH
        MOV AH, 02H
        INT 21H ; 换行

        MOV AH, 01H
        INT 21H ; 输入字符

        SUB AL, 30H
        AND AX, 00FFH
        MOV BH, AL
        MOV AL, CX
        MUL DL ; AX <- AL*DL
        ADD AX, BX
        MOV CX, AX

        ; 调用输入数据子程序
        CALL INPUTDATA

        MOV DX, OFFSET S3
        MOV AH, 09H
        INT 21H ; 输出提示信息

        SHR SI, 1
        MOV CX, SI
        MOV SI, 0

        ; 调用冒泡排序子程序
        CALL BUBBLESORT

        MOV DX, OFFSET S4
        MOV AH, 09H
        INT 21H ; 输出提示信息

    L5:
        MOV AX, ARRAY[SI]
        MOV BH, 10
        MOV BL, 0
        XOR DX, DX

    L6:
        DIV BH
        MOV DL, AH
        ADD DL, 30H
        PUSH DX
        INC BL
        AND AX, 00FFH
        CMP AL, 0
        JNZ L6

    L7:
        POP DX
        MOV AH, 02H
        INT 21H ; 输出字符
        DEC BL
        CMP BL, 0
        JNZ L7

        MOV DL, 32
        MOV AH, 02H
        INT 21H ; 输出空格

        ADD SI, 2
        LOOP L5

        MOV DX, 0AH
        MOV AH, 02H
        INT 21H ; 换行

        MOV AH, 4CH
        INT 21H ; 程序正常结束

CODES ENDS
    END START
