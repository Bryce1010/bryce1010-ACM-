int d[100005],n;


int lowbit(int x)
{
    return x&(-x);
}
int query(int x)//��ѯǰ׺��
{
    int res=0;
    while(x)
    {
        res+=d[x];
        x-=lowbit(x);
    }
    return res;
}
void add(int x,int v)//����Ӳ���
{
    while(x<=n)
    {
        d[x]+=v;
        x+=lowbit(x);
    }
}


