DSEG SEGMENT
    ARRAY DW 3 DUP ()  ; 定义一个包含3个16位字的数组
DSEG ENDS

CSEG SEGMENT
    MAIN PROC FAR
    ASSUME CS: CSEG, DS: DSEG  ; 设置代码段和数据段寄存器的关联
    START:
        PUSH DS  ; 保存数据段寄存器
        SUB AX, AX
        PUSH AX
        MOV AX, DSEG
        MOV DS, AX  ; 设置数据段寄存器为DSEG
        BEGIN:
            LEA SI, ARRAY  ; 将数组的地址加载到SI寄存器
            MOV DX, 0  ; 初始化结果计数器
            MOV AX, [SI]  ; 将数组中的第一个元素加载到AX
            MOV BX, [SI+2]  ; 将数组中的第三个元素加载到BX
            CALL COMPARE  ; 调用比较子程序
            CMP DX, 3  ; 比较结果计数器和3
            JNE DISP  ; 如果不等于3，跳转到DISP
            ADD DL, '0'  ; 结果为0，转换为ASCII码 '0'
            JMP SHOW_RESULT  ; 跳转到显示结果的子程序

        DISP:
            ADD DL, '1'  ; 结果为1，转换为ASCII码 '1'

        SHOW_RESULT:
            MOV AH, 2  ; 设置显示字符的DOS功能号
            INT 21H  ; 调用DOS中断21H，显示结果
            RET  ; 返回

        COMPARE:
            CMP AX, BX  ; 比较第一和第二个元素
            JNE NEXT1  ; 如果不相等，跳转到NEXT1
            INC DX  ; 相等则增加计数器
        NEXT1:
            CMP [SI+4], AX  ; 比较第一和第三个元素
            JNE NEXT2  ; 如果不相等，跳转到NEXT2
            INC DX  ; 相等则增加计数器
        NEXT2:
            CMP [SI+4], BX  ; 比较第二和第三个元素
            JNE NUM  ; 如果不相等，跳转到NUM
            INC DX  ; 相等则增加计数器
        NUM:
            RET  ; 返回

    MAIN ENDP
CSEG ENDS

END START  ; 程序的入口
