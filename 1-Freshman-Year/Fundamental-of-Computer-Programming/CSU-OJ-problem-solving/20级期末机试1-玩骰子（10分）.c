#include<stdio.h>//30min

int main()
{
    int t;
    while(scanf("%d",&t)!=EOF)
    {
        for(int j=0; j<t; j++)
        {
            char k[6];
            int m;
            int a[6]={0,0,0,0,0,0};
            scanf("%s %d",k,&m);//%s遇到空格或换行符时结束
            for(int i=0; i<6; i++)
            {
                if(k[i]=='1')
                {
                    a[0]++;
                    a[1]++;
                    a[2]++;
                    a[3]++;
                    a[4]++;
                    a[5]++;
                }
                if(k[i]=='2')
                {
                    a[1]++;
                }
                if(k[i]=='3')
                {
                    a[2]++;
                }
                if(k[i]=='4')
                {
                    a[3]++;
                }
                if(k[i]=='5')
                {
                    a[4]++;
                }
                if(k[i]=='6')
                {
                    a[5]++;
                }
            }
            int n,kk;
            for(int i=0; i<m; i++)
            {
                scanf("%d %d",&n,&kk);
                if(a[kk-1] >= n)
                {
                    printf("%d:true\n",i+1);//要是不会打字就复制！！！！！！！！！！！！！！！！！！！
                }
                else
                {
                    printf("%d:false\n",i+1);
                }
            }
            printf("\n");
        }
    }
    return 0;
}

/*
#include<stdio.h>

int main()
{
    int t;
    while(scanf("%d",&t)!=EOF)
    {
        for(int j=0; j<t; j++)
        {
            char k[6];
            int m;
            int a[6]={0,0,0,0,0,0};
            scanf("%s %d",k,&m);
            for(int i=0; i<6; i++)
            {
                if(k[i]=='1')
                {
                    a[0]++;
                    a[1]++;
                    a[2]++;
                    a[3]++;
                    a[4]++;
                    a[5]++;
                }
                if(k[i]=='2')
                {
                    a[1]++;
                }
                if(k[i]=='3')
                {
                    a[2]++;
                }
                if(k[i]=='4')
                {
                    a[3]++;
                }
                if(k[i]=='5')
                {
                    a[4]++;
                }
                if(k[i]=='6')
                {
                    a[5]++;
                }
            }
            int n,kk;
            for(int i=0; i<m; i++)
            {
                scanf("%d %d",&n,&kk);
                if(a[kk-1] >= n)
                {
                    printf("%d:true\n",i+1);
                }
                else
                {
                    printf("%d:false\n",i+1);
                }
            }
            printf("\n");
        }
    }
}
*/