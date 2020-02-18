#include <bits/stdc++.h>

using namespace std;

const int MAXN=10010;
struct Edge
{
    int to,next;
}edge[MAXN*2];


int head[MAXN],tot;//head[v]��ʾ��v��������ͷ��㣬tot��ʾ����������
int top[MAXN];//top[v]��ʾv���ڵ��������˽ڵ�
int fa[MAXN];//���׽ڵ�
int deep[MAXN];//���
int num[MAXN];//num[v]��ʾvΪ���������ڵ���
int p[MAXN];//p[v]��ʾv���丸�׽ڵ���������߶����е�λ��
int fp[MAXN];//��p�����෴����¼�߶�����ĳ��λ�ô������Щ��
int son[MAXN];//�ض���
int pos;

void init()
{
    tot=0;
    memset(head,-1,sizeof(head));
    pos=0;
    memset(son,-1,sizeof(son));
}



void addEdge(int u,int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}
//u��ʾ��ǰ�ڵ㣬pre��ʾ���ڵ㣬d��ʾ��ǰ�ڵ����
//��һ��dfs���fa,deep,num,son
void dfs1(int u,int pre,int d)
{
    deep[u]=d;
    fa[u]=pre;
    num[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int v=edge[i].to;
        //��Ϊ·����˫��ģ����Բ��ܵ��ڸ��ڵ�
        if(v!=pre)
        {
            dfs1(v,u,d+1);
            //����u�ڵ��������Ŀ
            num[u]+=num[v];
            //����ض��ӣ����ж�����size���Ľڵ�v
            if(son[u]==-1||num[v]>num[son[u]])
            {
                son[u]=v;
            }
        }
    }
}

//�ڶ������top��p
void dfs2(int u,int sp)
{
    top[u]=sp;
    p[u]=pos++;
    fp[p[u]]=u;//
    if(son[u]==-1)
    {
        return;
    }
    dfs2(son[u],sp);
    //dfs����
    //���������Ľڵ�
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int v=edge[i].to;
        if(v!=son[u]||v!=fa[u])
        {
            dfs2(v,v);//����ӵ�top[u]=u
        }
    }
}




int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
