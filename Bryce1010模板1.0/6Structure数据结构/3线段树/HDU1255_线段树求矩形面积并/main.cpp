#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lson l,m,rt<<1
#define rson m,r,rt<<1|1
const int MAXN=1e5+10;

double y[MAXN<<2];
struct Line
{
    double x;//��¼�߶�λ��
    double y_up,y_down;
    int flag;//���߶�Ϊ1�����߶�Ϊ-1
}line[MAXN<<2];

struct Node
{
    double l,r,x;//lά������,rά��������,x��¼��һ��x��λ�ã����������
    bool flag;//���ֻ��һ������Ľڵ㣬��������������ɢ��Ϊ�ڵ�
    int cover;//��¼���ǵ��߶���


}tree[MAXN<<2];

void pushup(int rt)
{
    tree[rt].l=tree[rt>>1].l;
    tree[rt].r=tree[rt>>1|1].r;
}

void build(int l,int r,int rt)
{
    tree[rt].l=y[l];
    tree[rt].r=y[r];
    tree[rt].x=-1;//ǰһ��λ��
    tree[rt].flag=false;//����ֻ��һ������
    tree[rt].cover=0;
    if(l+1==r)//��Ϊ��������������
    {
        tree[rt].flag=true;//Ҷ�ӽڵ�
        return;
    }
    int m=(l+r)>>1;
    build(lson);
    build(rson);//�����������ģ�m����Ҫ+1
}
//flag��ʾ����߶λ����ұ��߶Σ���������߶�+1,�����ұ��߶�-1
double query(double l,double r,int rt,double x,int flag)
{
    //����������䲻�ڷ�Χ��
    if(l>=tree[rt].r||r<=tree[rt].l)
    {
        return 0;
    }
    //�����ֻ��һ������Ľڵ�,Ҷ�ӽڵ�
    if(tree[rt].flag)
    {
        //�۲쵱ǰ��Χ�Ƿ��и�������
        if(tree[rt].cover>1)
        {
            //�������
            double pre=tree[rt].x;
            double ans=(x-pre)*(tree[rt].r-tree[rt].l);
            tree[rt].x=x;//��������ڵ㣬������һ�μ���
            tree[rt].cover+=flag;
            return ans;
        }
        else
        {
            tree[rt].x=x;
            tree[rt].cover+=flag;
            return 0;
        }
    }
    double ans1,ans2;
    ans1=query(l,r,rt<<1,x,flag);
    ans2=query(l,r,rt<<1|1,x,flag);
    return ans1+ans2;
}

bool cmp(Line l1,Line l2)
{
    return l1.x<l2.x;
}

int main()
{
    int t,n;
    double x1,y1,x2,y2;
    cin>>t;
    while(t--)
    {
        cin>>n;
        int cnt=-1;
        for(int i=0;i<n;i++)
        {
            cin>>x1>>y1>>x2>>y2;
            y[++cnt]=y1;
            line[cnt].x=x1;
            line[cnt].y_down=y1;
            line[cnt].y_up=y2;
            line[cnt].flag=1;


            y[++cnt]=y2;
            line[cnt].x=x2;
            line[cnt].y_down=y1;
            line[cnt].y_up=y2;
            line[cnt].flag=-1;
        }
        //�����и߶�����
        sort(y,y+cnt+1);
        //�������߶�����
        sort(line,line+cnt+1,cmp);
        build(0,cnt,1);
        //ɨ����ɨ�����е��߶�
        double area=0;
        for(int i=0;i<=cnt;i++)
        {
            area+=query(line[i].y_down,line[i].y_up,1,line[i].x,line[i].flag);
        }

        printf("%.2f\n",area);

    }


    return 0;
}























