DATA SEGMENT
    MAX_LENGTH DB 50          ; 存储字符串的最大长度为50
    CHAR_COUNT DB ?           ; 存储字符 'A'（或其他指定字符）的出现次数
    CHAR_ARRAY DB 50 DUP (?)  ; 存储从键盘输入的字符串
    SEARCH_CHAR DB 0          ; 要查找的字符，初始化为0
    ADDR_ARRAY DW 3 DUP (?)   ; 存储变量地址的数组
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA

    MAIN PROC FAR
    START:
        PUSH DS
        MOV AX, DATA
        MOV DS, AX

        LEA DX, MAX_LENGTH
        MOV AH, 0AH
        INT 21H             ; 从键盘接收字符串

        LEA SI, CHAR_ARRAY
        LEA DI, ADDR_ARRAY
        MOV CX, 3           ; 循环复制变量地址
        REP MOVSW

        CALL COUNT          ; 计算指定字符的出现次数
        CALL DISPLAY        ; 显示结果

        POP DS
        RET
    MAIN ENDP

    ; 子程序：计算字符出现次数
    COUNT PROC NEAR
        PUSH SI
        PUSH DI
        PUSH AX
        PUSH CX

        MOV DI, ADDR_ARRAY   ; ADDR_ARRAY 地址
        MOV SI, DI           ; CHAR_ARRAY 地址
        ADD SI, 2            ; 跳过 CHAR_COUNT 地址
        MOV CL, BYTE PTR [SI]; CHAR_COUNT 的值
        MOV CH, 0
        ADD SI, 2            ; 移动到 SEARCH_CHAR 地址
        MOV AL, BYTE PTR [SI]; SEARCH_CHAR 的值
        XOR BX, BX           ; 初始化计数器

        AGAIN:
            CMP AL, BYTE PTR [DI] ; 比较字符是否相等
            JNE NOT_FOUND
            INC BX               ; 如果相等，增加计数器
        NOT_FOUND:
            INC DI               ; 指向下一个字符
            LOOP AGAIN

        MOV CHAR_COUNT, BL    ; 将计数器的值存储到 CHAR_COUNT 中

        POP CX
        POP AX
        POP DI
        POP SI
        RET
    COUNT ENDP

    ; 子程序：显示结果
    DISPLAY PROC NEAR
        CALL CRLF            ; 显示回车和换行

        ; 将计数器的值转换成十六进制并显示
        MOV AL, CHAR_COUNT
        AND AL, 0FH
        ADD AL, '0'
        CMP AL, '9'
        JBE PRINT
        ADD AL, 7

    PRINT:
        MOV DL, AL
        INT 21H

        CALL CRLF            ; 显示回车和换行
        RET
    DISPLAY ENDP

    ; 子程序：显示回车和换行
    CRLF PROC NEAR
        MOV DL, 0DH
        MOV AH, 2
        INT 21H

        MOV DL, 0AH
        MOV AH, 2
        INT 21H
        RET
    CRLF ENDP

CODE ENDS
END START
