#include<stdio.h>

struct inf
{
    int x;
    int y;
    int flag;
}a[100];

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        int len=2*n;
        for(int i=0; i<len; i+=2)
        {
            scanf("%d,%d->%d,%d",
            &a[2*i].x,&a[2*i].y,&a[2*i+1].x,&a[2*i+1].y);
            a[i].flag=1;
            a[i+1].flag=0;
        }
        for(int i=0; i<len-1; i++)
        {
            for(int j=1; j<len; j++)
            {
                if(a[i].flag!=a[j].flag && a[i].x==a[j].x)
                {
                    ;
                }
            }
        }
    }
    return 0;
}

/*
//答案

#include <stdio.h> 
#include <string.h> 
 
struct XXX
{
	int id;
	int name1;
	int name2;
};
//整数n（0<n≤1000），表示截获到的情报数
//最多有1001个 
 
 
 
int main()
{
	int n;
	while(scanf("%d",&n)!=EOF)
	{
		struct XXX xunlei[1005]={0};
		int count=0;	//已有多少人员
	
		for(int i=0;i<n;i++)
		{
			int Ax,Ay,Bx,By;
			scanf("%d,%d->%d,%d",&Ax,&Ay,&Bx,&By);
			//第一次直接创建
			if(i==0)
			{
				xunlei[0].id = Ax;
				xunlei[0].name1 = Ay;
				xunlei[0].name2 =0 ;
				xunlei[1].id = Bx;
				xunlei[1].name1 = By; 
				xunlei[1].name2 =0 ;
				count=2; 
			}
			else
			{
				//查找新数据的A和B的位置
				int posA=-1, posB=-1;
				for(int i=0;i<count;i++)
				{
					if(xunlei[i].id==Ax)		//如果找到已经存在的人员，更新name
					{
						posA=i;
						if(xunlei[i].name1!=Ay)	//如果人员有了新名字，在name2更新
						{
							xunlei[i].name2=Ay;	
						}
					} 
					if(xunlei[i].id==Bx)		//如果找到已经存在的人员，更新name
					{
						posB=i;
						if(xunlei[i].name1!=By)	//如果人员有了新名字，在name2更新
						{
							xunlei[i].name2=By;	
						} 
					}
						
				}
				
				if(posA==-1 && posB!=-1)	//B已存在，A不存在、
				{
					//将A插在B的前面
					for(int i=count-1;i>=posB;i--)
					{
						xunlei[i+1]=xunlei[i];
					}
					xunlei[posB].id=Ax;
					xunlei[posB].name1=Ay;
					xunlei[posB].name2=0;
					count++;
				}
				
				if(posA!=-1 && posB==-1)	//A存在,B不存在
				{
					//把A后面的都往后移，A的后面存放B
					for(int i=count-1;i>=posA+1;i--)
					{
						xunlei[i+1]=xunlei[i];
					}
					xunlei[posA+1].id=Bx;
					xunlei[posA+1].name1=By;
					xunlei[posA+1].name2=0;
					count++;	 
				}
				
				if(posA!=-1 && posB!=-1)
				{
					//可能就是增加了name项,上面已经更新了。
				}
				
				if(posA==-1 && posB==-1)
				{
					//没有关联。不管	
				}
			}
		}
		
		for(int i=0;i<count;i++)
		{
			if(i==0)
			{
				if(xunlei[i].name2==0)
					printf("%d,%d",xunlei[i].id,xunlei[i].name1);
				else
					printf("%d,%d#%d",xunlei[i].id,xunlei[i].name1,xunlei[i].name2); 
			}
			else
			{
				if(xunlei[i].name2==0)
					printf("->%d,%d",xunlei[i].id,xunlei[i].name1);
				else
					printf("->%d,%d#%d",xunlei[i].id,xunlei[i].name1,xunlei[i].name2); 
			}
		}
		printf("\n");
	} 
	 
	return 0;
}
*/