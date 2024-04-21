//
// Created by 33712 on 2023/8/1.
//
//------------------线索二叉树--------------------
//线索化的规则为：
//* 结点的左指针，指向其当前遍历顺序的前驱结点。
//* 结点的右指针，指向其当前遍历顺序的后继结点。

#include <stdio.h>
#include <stdlib.h>



#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE (-1)
#define OVERFLOW (-2)



typedef int Status; //Status是函数的类型，其值是函数结果状态代码
typedef char ELemType; //ELemType是表里元素的类型
typedef struct Thread_Binary_Tree_Node { //二叉树的二叉线索存储表示
    struct Thread_Binary_Tree_Node* left_child;
    int left_tag;
    ELemType data;
    int right_tag;
    struct Thread_Binary_Tree_Node* right_child;
} BiThrNode, * BiThrTree_ptr;
//课本源码：
//typedef enum PointerTag { Link, Thread } Tag; //Link==0：孩子结点指针   Thread==1：线索
//typedef struct Thread_Binary_Tree_Node {
//    struct Thread_Binary_Tree_Node* l_child;
//    Tag l_tag;
//    ELemType data;
//    Tag r_tag;
//    struct Thread_Binary_Tree_Node* r_child;
//} BiThrNode, * BiThrTree;



//中序线索化：

//中序遍历建立线索二叉树 (中序线索化二叉树)
BiThrTree_ptr InOrderCreate_ThreadingBiTree(ELemType* e) {
    static int index = 0;
    char ch = e[index++];
    if (ch == '_') {
        return NULL;
    } else {
        BiThrTree_ptr new_node = (BiThrTree_ptr ) malloc(sizeof(BiThrNode ));

        new_node->left_child = InOrderCreate_ThreadingBiTree(e);
        new_node->data = ch; new_node->left_tag = new_node->right_tag = 0; //唯一区别，默认全置0。
        new_node->right_child = InOrderCreate_ThreadingBiTree(e);

        return new_node; //
    }
}

//中序遍历对二叉树线索化的递归算法
//外部传入时now和last保持一致，last表示刚刚访问过的结点，now指向正在访问的结点
BiThrTree_ptr InThreading(BiThrTree_ptr now, BiThrTree_ptr last) {
    if (now != NULL) {
        last = InThreading(now->left_child, last);
        if (now->left_child == NULL) { // 左子树为空，建立前驱线索
            now->left_child = last;
            now->left_tag = 1;
        }
        if (last != NULL && last->right_child == NULL) { // 右子树为空，建立后继线索
            last->right_child = now;
            last->right_tag = 1;
        }
        last = now; // 标记当前结点为刚刚访问过的结点
        last = InThreading(now->right_child, last);
    }
    return last;
}



//中序线索二叉树的遍历
//中序遍历二叉树T，对每个结点调用函数Visit一次且仅一次。
Status InOrderTraverse_ThreadingBiTree(BiThrTree_ptr now) {
    BiThrTree_ptr current = now;
    while (current != NULL) {
        // 寻找中序遍历的第一个结点（最左边的结点）
        while (current->left_tag == 0) {
            current = current->left_child;
        }

        // 访问结点
        printf("%c ", current->data);

        // 寻找后继结点并访问
        while (current->right_tag == 1) {
            current = current->right_child;
            printf("%c ", current->data);
        }

        // 移动到右子树的根节点
        current = current->right_child;
    }
}

//
void inOrder(BiThrTree_ptr root){
    while (root) {   //因为中序遍历需要先完成左边，所以说要先走到最左边才行
        while (root && root->left_tag == 0)    //如果左边一直都不是线索，那么就一直往左找，直到找到一个左边是线索的为止，表示到头了
            root = root->left_child;

        printf("%c ", root->data);   //到最左边了再打印，中序开始

        while (root && root->right_tag == 1) {   //打印完就该右边了，右边如果是线索化之后的结果，表示是下一个结点，那么就一路向前，直到不是为止
            root = root->right_child;
            printf("%c ", root->data);   //注意按着线索往下就是中序的结果，所以说沿途需要打印
        }
        root = root->right_child;  //最后继续从右结点开始，重复上述操作
    }
}

//普通。中序遍历二叉树T
Status InOrderTraverse(BiThrTree_ptr BT) {
    if (BT != NULL) {
        InOrderTraverse(BT->left_child);
        printf("%c ", BT->data);
        InOrderTraverse(BT->right_child);
    }
    return OK;
}

int main() {

    BiThrTree_ptr root = NULL;

    ELemType TREE[] = "AB_C__D__";
    root = InOrderCreate_ThreadingBiTree(TREE);

    BiThrTree_ptr lost = NULL;
    lost = InThreading(root, lost);
    lost->right_child = NULL;
    lost->right_tag = 0;


    printf("------------------------------\n");
//    InOrderTraverse(root); //普通
    printf("\n------------------------------\n");
    inOrder(root);
//    InOrderTraverse_ThreadingBiTree(root);

    printf("\n------------------------------\n");
}