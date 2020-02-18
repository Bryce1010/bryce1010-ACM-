/*α����
Tarjan(u)//marge��findΪ���鼯�ϲ������Ͳ��Һ���
{
    for each(u,v)    //��������u�ӽڵ�v
    {
        Tarjan(v);        //�������±���
        marge(u,v);    //�ϲ�v��u��
        ���v�����ʹ�;
    }
    for each(u,e)    //�������к�u��ѯ�ʹ�ϵ��e
    {
        ���e�����ʹ�;
        u,e�������������Ϊfind(e);
    }
}

*/
//˼��
/*
1.��ѡһ����Ϊ���ڵ㣬�Ӹ��ڵ㿪ʼ��
2.�����õ�u�����ӽڵ�v���������Щ�ӽڵ�v�ѱ����ʹ���
3.����v�����ӽڵ㣬����2��������һ����
4.�ϲ�v��u�ϡ�
5.Ѱ���뵱ǰ��u��ѯ�ʹ�ϵ�ĵ�v��
6.����v�Ѿ������ʹ��ˣ������ȷ��u��v�������������Ϊv���ϲ����ĸ��׽ڵ�a��
*/

#include<iostream>
#include<algorithm>
#include<string.h>
#include<stdio.h>
#include<math.h>
using namespace std;
#define ll long long


const int MAXN=1010;
const int MAXQ=500010;

//���鼯����
int F[MAXN];//��ʼ��Ϊ-1
int find(int x)
{
    if(F[x]==-1)return x;
    return F[x]=find(F[x]);
}
//merge
void bing(int u,int v)
{
    int t1=find(u);
    int t2=find(v);
    if(t1!=t2)
    {
        F[t1]=t2;
    }
}
//****************
//��ͼ����
bool vis[MAXN];
int ancestor[MAXN];//�洢��ѯ���̽ڵ������
struct Edge
{
    int to,next;
}edge[MAXN<<2];
int head[MAXN],tot;
void add_edge(int u,int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}

//���߲�ѯ����

struct Query
{
    int q,next;
    int index;// ��ѯ���
}query[MAXQ<<1];

int answer[MAXQ];//�洢����ÿ����ѯ�Ĺ�������,�±�0,Q-1
int h[MAXQ];
int tt;int Q;

void add_query(int u,int v,int index)
{
    query[tt].q=v;
    query[tt].next=h[u];
    query[tt].index=index;
    h[u]=tt++;
    query[tt].q=u;
    query[tt].next=h[v];
    query[tt].index=index;
    h[v]=tt++;
}

//LCA����
void init()
{
    tot=0;
    memset(head,-1,sizeof(head));
    tt=0;
    memset(h,-1,sizeof(h));
    memset(vis,false,sizeof(vis));
    memset(F,-1,sizeof(F));
    memset(ancestor,0,sizeof(ancestor));
}

void LCA(int u)
{
    ancestor[u]=u;
    vis[u]=true;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int v=edge[i].to;
        if(vis[v])continue;
        LCA(v);
        bing(u,v);
        ancestor[find(u)]=u;//?
    }
    for(int i=h[u];i!=-1;i=query[i].next)
    {
        int v=query[i].q;
        if(vis[v])
        {
            answer[query[i].index]=ancestor[find(v)];
        }
    }
}

bool flag[MAXN];
int Count_num[MAXN];
int main()
{
    int n;
    int u,v,k;
    while(scanf("%d",&n)==1)
    {
        init();
        memset(flag,false,sizeof(flag));
        for(int i=1;i<=n;i++)
        {
            scanf("%d:(%d)",&u,&k);
            while(k--)
            {
                scanf("%d",&v);
                flag[v]=true;
                add_edge(u,v);
                add_edge(v,u);
            }
        }
        scanf("%d",&Q);
        for(int i=0;i<Q;i++)
        {
            char ch;
            cin>>ch;
            scanf("%d %d)",&u,&v);
            //cin>>ch;
            add_query(u,v,i);
        }
        int root;
        for(int i=1;i<=n;i++)//�ҵ�û����ȵĵ���Ϊroot
        {
            if(!flag[i])
            {
                root=i;
                break;
            }
        }
        LCA(root);
        memset(Count_num,0,sizeof(Count_num));
        for(int i=0;i<Q;i++)
        {
            Count_num[answer[i]]++;
        }
        for(int i=1;i<=n;i++)
        {
            if(Count_num[i]>0)
            {
                printf("%d:%d\n",i,Count_num[i]);
            }
        }
    }
//    getchar();getchar();
    return 0;
}






/*
5
5:(3) 1 4 2
1:(0)
4:(0)
2:(1) 3
3:(0)
6
(1 5) (1 4) (4 2) (2 3) (1 3) (4 3)
*/




















