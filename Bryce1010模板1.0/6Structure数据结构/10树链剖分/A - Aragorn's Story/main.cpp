#include <bits/stdc++.h>

using namespace std;
/*
 *  ���ڵ�Ȩ,��ѯ����ֵ,�޸�·�����ϵĵ�Ȩ
 */
const int MAXN = 50010;
struct Edge
{
    int to, next;
} edge[MAXN * 2];

int head[MAXN], tot;
int top[MAXN];  //  top[v]��ʾv���ڵ������Ķ��˽ڵ�
int fa[MAXN];   //  ���׽ڵ�
int deep[MAXN]; //  ���
int num[MAXN];  //  num[v]��ʾ��vΪ���������Ľڵ���
int p[MAXN];    //  p[v]��ʾv��Ӧ��λ��
int fp[MAXN];   //  fp��p�����෴
int son[MAXN];  //  �ض���
int pos;

void init()
{
    tot = 0;
    memset(head, -1, sizeof(head));
    pos = 1;    //  ʹ����״����,��Ŵ�ͷ1��ʼ
    memset(son, -1, sizeof(son));
    return ;
}

void addedge(int u, int v)
{
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
    return ;
}

void dfs1(int u, int pre, int d)
{
    deep[u] = d;
    fa[u] = pre;
    num[u] = 1;
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v != pre)
        {
            dfs1(v, u, d + 1);
            num[u] += num[v];
            if (son[u] == -1 || num[v] > num[son[u]])
            {
                son[u] = v;
            }
        }
    }
    return ;
}

void getpos(int u, int sp)
{
    top[u] = sp;
    p[u] = pos++;
    fp[p[u]] = u;
    if (son[u] == -1)
    {
        return ;
    }
    getpos(son[u], sp);
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v != son[u] && v != fa[u])
        {
            getpos(v, v);
        }
    }
    return ;
}

//��״����
int lowbit(int x)
{
    return x & (-x);
}

int c[MAXN];
int n;

int sum(int i)
{
    int s = 0;
    while (i > 0)
    {
        s += c[i];
        i -= lowbit(i);
    }
    return s;
}

void add(int i, int val)
{
    while (i <= n)
    {
        c[i] += val;
        i += lowbit(i);
    }
    return ;
}

void Change(int u, int v, int val)  //  u->v��·���ϵ��ֵ�ı�val
{
    int f1 = top[u], f2 = top[v];
    while (f1 != f2)
    {
        if (deep[f1] < deep[f2])
        {
            swap(f1, f2);
            swap(u, v);
        }
        add(p[f1], val);
        add(p[u] + 1, -val);
        u = fa[f1];
        f1 = top[u];
    }
    if (deep[u] > deep[v])
    {
        swap(u, v);
    }
    add(p[u], val);
    add(p[v] + 1, -val);
    return ;
}

int a[MAXN];

int main()
{
    int M, P;
    while (scanf("%d%d%d", &n, &M, &P) == 3)
    {
        int u, v;
        int C1, C2, K;
        char op[10];
        init();
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &a[i]);
        }
        while(M--)
        {
            scanf("%d%d", &u, &v);
            addedge(u, v);
            addedge(v, u);
        }
        dfs1(1, 0, 0);
        getpos(1, 1);
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= n; i++)
        {
            add(p[i],a[i]);
            add(p[i] + 1, -a[i]);
        }
        while (P--)
        {
            scanf("%s", op);
            if (op[0] == 'Q')
            {
                scanf("%d", &u);
                printf("%d\n", sum(p[u]));
            }
            else
            {
                scanf("%d%d%d", &C1, &C2, &K);
                if (op[0] == 'D')
                {
                    K = -K;
                }
                Change(C1, C2, K);
            }
        }
    }
    return 0;
}
