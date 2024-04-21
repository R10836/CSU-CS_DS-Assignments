//
// Created by 33712 on 2023/7/31 2：00.
//
//------------------二叉树链式存储--------------------
//s代表的是new_node新结点的意思

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;
typedef char ELemType;
typedef struct BiTNode {
    ELemType data;
    struct BiTNode* left_child; // 指向左子树的指针
    struct BiTNode* right_child; // 指向右子树的指针
} BiTNode, * BiTNode_ptr;

//======================================================
//为了层序遍历的队列类

// 队列节点的定义
typedef struct QueueNode {
    BiTNode_ptr data;
    struct QueueNode* next;
} QueueNode, *QueueNode_ptr;

// 队列的定义
typedef struct Queue {
    QueueNode_ptr front;
    QueueNode_ptr rear;
} Queue, *Queue_ptr;

// 初始化队列
Status InitQueue(Queue_ptr* queue) {
    *queue = (Queue_ptr)malloc(sizeof(Queue));
    if (*queue == NULL) {
        return ERROR;
    }
    (*queue)->front = NULL;
    (*queue)->rear = NULL;
    return OK;
}

// 入队操作
Status Enqueue(Queue_ptr queue, BiTNode_ptr node) {
    QueueNode_ptr new_node = (QueueNode_ptr)malloc(sizeof(QueueNode));
    if (new_node == NULL) {
        return ERROR;
    }
    new_node->data = node;
    new_node->next = NULL;
    if (queue->front == NULL) {
        queue->front = new_node;
    } else {
        queue->rear->next = new_node;
    }
    queue->rear = new_node;
    return OK;
}

// 出队操作
Status Dequeue(Queue_ptr queue, BiTNode_ptr* node) {
    if (queue->front == NULL) {
        return ERROR;
    }
    QueueNode_ptr temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    *node = temp->data;
    free(temp);
    return OK;
}
//==============================================================
//以下是正文：



//自创 通过传入数组先序遍历构建二叉树
//chatgpt改版后注意这个BT是指针的指针！他说：原来的问题在于问题在于在 main 函数中的 BiTNode BT; 定义了一个局部变量 BT 来保存根节点，而在 PreOrderCreateBiTree 函数中，我们传递了根节点的地址指针 BiTNode_ptr BT，这个地址指针会指向我们在 main 函数中定义的局部变量 BT，这样在函数 PreOrderCreateBiTree 中对节点指针的修改并不会反映在 main 函数中。
//https://chat.openai.com/share/8f43b48a-48b5-4d50-a2e6-2c3b6b06b73a
ELemType* PreOrderCreateBiTree(BiTNode_ptr* BT, ELemType* e) {
    if (*e == '_') {
        *BT = NULL; e++;
    } else {
        *BT = (BiTNode_ptr)malloc(sizeof(BiTNode));
        //++++++++++++++核心++++++++++++++
        (*BT)->data = *e; e++;
        e = PreOrderCreateBiTree(&((*BT)->left_child), e);
        e = PreOrderCreateBiTree(&((*BT)->right_child), e);
        //++++++++++++++核心++++++++++++++
    }
    return e;
}

// chatgpt : 中序遍历构建二叉树
BiTNode_ptr InOrderCreateBiTree(ELemType* e) {
    static int index = 0;
    char ch = e[index++];
    if (ch == '_') {
        return NULL;
    } else {
        BiTNode_ptr new_node = (BiTNode_ptr)malloc(sizeof(BiTNode));

        new_node->left_child = InOrderCreateBiTree(e);
        new_node->data = ch;
        new_node->right_child = InOrderCreateBiTree(e);

        return new_node;
    }
}

//修改 来自课本的先序遍历构建二叉树 chatgpt修改，同理上一个函数
Status new_PreOrderCreateBiTree(BiTNode_ptr* BT) {
    ELemType ch;
    printf("Enter a character as node:");
    scanf(" %c", &ch); //前空格不可忽略！

    if (ch == '_') {
        *BT = NULL;
    } else {
        *BT = (BiTNode_ptr)malloc(sizeof(BiTNode));
        //-------------核心---------------
        (*BT)->data = ch;
        new_PreOrderCreateBiTree(&((*BT)->left_child));
        new_PreOrderCreateBiTree(&((*BT)->right_child));
        //-------------核心---------------
    }
    return OK;
}

// chatgpt: 中序遍历构建二叉树，成功
Status new_InOrderCreateBiTree(BiTNode_ptr* BT) {
    ELemType ch;
    printf("Enter a character as node:");
    scanf(" %c", &ch); // 前空格不可忽略！

    if (ch == '_') {
        *BT = NULL;
    } else {
        *BT = (BiTNode_ptr)malloc(sizeof(BiTNode));
        //-------------核心---------------
        new_InOrderCreateBiTree(&((*BT)->left_child));
        (*BT)->data = ch;
        new_InOrderCreateBiTree(&((*BT)->right_child));
        //-------------核心---------------
    }
    return OK;
}

//先序遍历二叉树T，对每个结点调用函数Visit一次且仅一次。
Status PreOrderTraverse(BiTNode_ptr BT) {
    if (BT != NULL) {
        printf("%c ", BT->data);
        PreOrderTraverse(BT->left_child);
        PreOrderTraverse(BT->right_child);
    }
    return OK;
}

//中序遍历二叉树T，对每个结点调用函数Visit一次且仅一次。
Status InOrderTraverse(BiTNode_ptr BT) {
    if (BT != NULL) {
        InOrderTraverse(BT->left_child);
        printf("%c ", BT->data);
        InOrderTraverse(BT->right_child);
    }
    return OK;
}

//后序遍历二叉树T，对每个结点调用函数Visit一次且仅一次。
Status PostOrderTraverse(BiTNode_ptr BT) {
    if (BT != NULL) {
        PostOrderTraverse(BT->left_child);
        PostOrderTraverse(BT->right_child);
        printf("%c ", BT->data);
    }
    return OK;
}

//层序遍历二叉树T，对每个结点调用函数Visit一次且仅一次。
//作者：chatGPT 3.5 ，暂时未理解。
Status LevelOrderTraverse(BiTNode_ptr BT) {
    if (BT == NULL) return ERROR;

    Queue_ptr queue; //先搞一个队列
    InitQueue(&queue);
    Enqueue(queue, BT); //先把根节点入队

    while (queue->front != NULL) { //不断重复，直到队列空为止
        BiTNode_ptr current_node;
        Dequeue(queue, &current_node); //出队一个元素，打印值
        printf("%c ", current_node->data);

        if (current_node->left_child != NULL) { //如果存在左右孩子的话
            Enqueue(queue, current_node->left_child); //记得将左右孩子入队，注意顺序，先左后右
        }

        if (current_node->right_child != NULL) {
            Enqueue(queue, current_node->right_child);
        }
    }

    free(queue);
    return OK;
}



int main() {
    BiTNode_ptr root = NULL; //chatgpt: 在 main 函数中定义了一个指向根节点的指针 BiTNode_ptr root = NULL;，然后将这个指针传递给 PreOrderCreateBiTree 函数，使得在函数中对节点指针的修改可以正确反映在 main 函数中。
//    ELemType tree[] = "abc__de_g__f___"; //套餐1
//    PreOrderCreateBiTree(&root, tree); //套餐1
//    new_PreOrderCreateBiTree(&root); //套餐2

    ELemType tree[] = "AB_C__D__"; //套餐1
    root = InOrderCreateBiTree(tree); //套餐1
//    new_InOrderCreateBiTree(&root); //套餐2


    printf("\n--------PreOrderTraverse--------\n");
    PreOrderTraverse(root);
    printf("\n--------InOrderTraverse--------\n");
    InOrderTraverse(root);
    printf("\n--------PostOrderTraverse--------\n");
    PostOrderTraverse(root);
    printf("\n--------LevelOrderTraverse--------\n");
    LevelOrderTraverse(root);

    return 0;
}
