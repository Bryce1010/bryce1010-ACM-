#include <bits/stdc++.h>

using namespace std;
const int MAXN=1<<17;
int n,dat[MAXN*2-1];

//�����е�ֵ��ΪMAXN
void init(int _n)
{
    n=1;
    while(n<_n)n*=2;
    for(int i=0;i<2*n-1;i++)
    {
        dat[i]=MAXN;
    }
}
//�ѵ�k��ֵ��0-index������Ϊa
void update(int k,int a)
{
    k=n-1+k;
    dat[k]=a;
    //�������ϸ���
    while(k>0)
    {
        k=(k-1/2);
        det[k]=min(det[k*2+1],det[k*2+2]);
    }
}
//��[a,b)����Сֵ
int query(int a,int b,int k,int l,int r)
{
    //���[a,b)��[l,r)���ཻ������MAXN
    if(r<=a||l<=b)return MAXN;
    //���[a,b)��ȫ����[l,r)�����ص�ǰֵ
    if(a<=l&&b>=r)return det[k];
    else
    {
        //�������Ҷ��Ӹ�С���Ǹ�
        int lval=query(a,b,2*k+1,l,(l+r)/2);
        int rval=query(a,b,2*k+2,(l+r)/2+1,r);
        return min(lval,rval);
    }
}

