

const int MAXN=2005+5;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
int sum[MAXN<<2];//��ʾ�߶����ڵ㣬��Ҫ�������ֵ���ı�
void push_up(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
//����
void build(int l,int r,int rt=1)
{
    //����������һ������l~r����ȫ������
    if(l==r)
    {
        sum[rt]=0;
        return;
    }
    int m=(l+r)>>1;
    build(l,m,rt);
    build(m+1,r,rt);
    push_up(rt);//�ɵ����ϸ���
}


//���µ�Ͱ������֦
void update(int pos,int val,int l,int r,int rt=1)
{
    //posΪ���µ�λ�ã�valΪ���ӵ�ֵ������ӣ������
    //l,rΪ�����˵�ֵ
    if(l==r)
    {
        sum[rt]+=val;
        return;
    }
    int m=(r+l)>>1;
    if(pos<=m)//pos��������
    {
        update(pos,val,l,mid,rt);
    }
    else
    {
        update(pos,val,mid+1,r,rt);
    }
    //���°����õ��һϵ������
    push_up(rt);

}
//��ѯ�������
int query(int L,int R,int l,int r,int rt=1)
{
    //L,RΪ����ѯ���䣬l,rΪ��ǰ����������
    //������������ǰ����������
    if(L<=l&&R>=r)
    {
        return sum[rt];//���ص�ǰ����ĺ�
    }
    int mid=(l+r)>>1;
    int res=0;
    if(L<=m)
    {
        res+=query(L,R,l,mid,rt);
    }
    else
    {
        res+=query(L,R,mid+1,r,rt);
    }
    return res;
}
