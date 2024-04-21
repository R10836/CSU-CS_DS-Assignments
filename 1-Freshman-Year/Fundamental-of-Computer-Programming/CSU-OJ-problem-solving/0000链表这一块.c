#include<stdio.h>
#include<stdlib.h>

struct node *add_to_list(struct node *list, int n);
struct node *delete_from_list(struct node *list, int n);
int cmp(const void *a, const void *b);

struct node
{
	int value;
	struct node *next;
};

int main()
{
	return 0;
}

//往链表中插入结点(list是指向旧列表中首结点的指针,n是需要存储在新结点中的整数)
struct node *add_to_list(struct node *list, int  n)
{
	struct node *new_node;

	new_node=malloc(sizeof(struct node));
	if(new_node == NULL)
	{
		printf("错了。\n");
		exit(EXIT_FAILURE);
	}
	new_node->value=n;
	new_node->next=list;
	return new_node;
}

//从链表删除结点(list是指向旧列表中首结点的指针,n是删除含有n的第一个结点)
struct node *delete_from_list(struct node *list, int n)
{
	struct node *cur, *prev;

	for(cur=list, prev=NULL;
		cur !=NULL && cur->value != n;
		prev=cur, cur=cur->next)
	{
		;
	}

	if(cur == NULL)
	{
		return list;
	}
	if(prev == NULL)
	{
		list=list->next;
	}
	else
	{
		prev->next=cur->next;
	}
	free(cur);
	return list;
}

//运用qsort(数组名a, 要排序元素的数量sz， 每个元素的大小sizeof(arr[0])时，cmp另起一个函数。
int cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);//由小到大排
	//return (*(int *)b - *(int *)a);//由大到小排
}