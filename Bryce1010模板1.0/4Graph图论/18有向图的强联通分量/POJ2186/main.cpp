#include <iostream>
#include<vector>
#include<string.h>
#include<algorithm>
#include<stdio.h>
using namespace std;
const int MAXN=5e4+10;


int N,M;
int A[MAXN],B[MAXN];
int V;
vector<int>G[MAXN];//ͼ���ڽӱ��ʾ
vector<int>rG[MAXN];//�ѱ߷�����ͼ
vector<int>vs;//����������Ķ����б�
bool used[MAXN];//���ʱ��
int cmp[MAXN];//����ǿ��ͨ������������
void add_edge(int from,int to)
{
    G[from].push_back(to);
    rG[to].push_back(from);
}
void dfs(int v)
{
    used[v]=true;
    for(int i=0;i<G[v].size();i++)
    {
        if(!used[G[v][i]])dfs(G[v][i]);
    }
    vs.push_back(v);//��Ǻ���
}
void rdfs(int v,int k)
{
    used[v]=true;
    cmp[v]=k;
    for(int i=0;i<rG[v].size();i++)
    {
        if(!used[rG[v][i]])rdfs(rG[v][i],k);
    }
}
int scc()
{
    memset(used,0,sizeof(used));
    vs.clear();
    for(int v=0;v<V;v++)
    {
        if(!used[v])dfs(v);
    }
    memset(used,0,sizeof(used));
    int k=0;
    for(int i=vs.size()-1;i>=0;i--)
    {
        if(!used[vs[i]])rdfs(vs[i],k++);
    }
    return k;
}
void solve()
{
    V=N;
    for(int i=0;i<M;i++)
    {
        add_edge(A[i]-1,B[i]-1);
    }
    int n=scc();

    //ͳ�Ʊ�ѡ��ĸ���
    int u=0,num=0;
    for(int v=0;v<V;v++)
    {
        if(cmp[v]==n-1)
        {
            u=v;
            num++;
        }
    }
    //����Ƿ����е�ɴ�
    memset(used,0,sizeof(used));
    rdfs(u,0);//����ǿ��ͨ�����ֽ�Ĵ��롣
    //����ǿ��ͨ�����Ƿ�����ж���ɴ�
    for(int v=0;v<V;v++)
    {
        if(!used[v])
        {
            //�õ㲻�ɴ�
            num=0;
            break;
        }
    }
    printf("%d\n",num);
}
int main()
{
        cin>>N>>M;
        for(int i=0;i<M;i++)
        {
            cin>>A[i]>>B[i];
        }
        solve();
        return 0;
}
