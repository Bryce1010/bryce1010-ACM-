
/*
���⣺����n������(n<=1000),ÿ�������������10000������
ÿ�����ķ�ΧΪ1~10000������q��ѯ��(q<=200000),
ÿ�θ���������u��v�ж��Ƿ���һ��������ͬʱ����u��v������
*/
#include<iostream>
#include<bitset>
#include<stdio.h>
using namespace std;

bitset<1001>b[10010];

int main()
{
    int n,c,q;
    int p,x,y;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&c);
        for(int j=1;j<=c;j++)
        {
            scanf("%d",&p);
            b[p].set(i);
        }
    }
    cin>>q;
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d",&x,&y);
        int flag=0;
        if((b[x]&b[y]).any())flag=1;
        if(flag)cout<<"Yes"<<endl;
        else cout<<"No"<<endl;

    }

    return 0;
}
