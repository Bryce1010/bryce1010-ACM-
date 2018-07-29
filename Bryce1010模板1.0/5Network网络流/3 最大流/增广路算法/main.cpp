#include <bits/stdc++.h>
using namespace std;
#define clr(a,x) memset(a, x, sizeof(a))
#define mp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define X first
#define Y second
#define fastin ios_base::sync_with_stdio(0);cin.tie(0);
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef vector<int> VI;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
const double eps = 1e-6;

const int maxn = 405;

struct Edge
{
    int from, to, cap, flow;
    Edge(int u, int v, int c, int f): from(u), to(v), cap(c), flow(f) {}
};
struct Dinic
{
    int n, m, s, t;         //��������������������򻡣���Դ���źͻ����
    vector<Edge> edges;     //�߱�edge[e]��edge[e^1]��Ϊ����
    vector<int> G[maxn];    //�ڽӱ�G[i][j]��ʾ�ڵ�i�ĵ�j������e�����е����
    bool vis[maxn];         //BFSʹ��
    int d[maxn];            //����㵽i�ľ���
    int cur[maxn];          //��ǰ���±�
    void init(int n)
    {
        this->n = n;
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }
    void AddEdge(int from, int to, int cap)
    {
        edges.pb(Edge(from, to, cap, 0));
        edges.pb(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].pb(m - 2);
        G[to].pb(m - 1);
    }
    bool BFS()
    {
        clr(vis, 0);
        clr(d, 0);
        queue<int> q;
        q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            for (int i = 0; i < G[x].size(); i++)
            {
                Edge& e = edges[G[x][i]];
                if (!vis[e.to] && e.cap > e.flow)
                {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    int DFS(int x, int a)
    {
        if (x == t || a == 0) return a;
        int flow = 0, f;
        for (int& i = cur[x]; i < G[x].size(); i++)
        {
            //���ϴο��ǵĻ�
            Edge& e = edges[G[x][i]];
            if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0)
            {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }
    int Maxflow(int s, int t)
    {
        this->s = s;
        this->t = t;
        int flow = 0;
        while (BFS())
        {
            clr(cur, 0);
            flow += DFS(s, INF);
        }
        return flow;
    }
} ans;

map <string, int> M;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    fastin
    int T, n, m, k;
    cin >> T;
    while (T--)
    {
        M.clear();
        cin >> n;
        int s = 0, t = 1;
        ans.init(maxn);
        int tot = 2;
        string tmp, dev;
        while (n--)
        {
            //����->�������
            cin >> tmp;
            if (!M[tmp]) M[tmp] = tot++;
            ans.AddEdge(M[tmp], t, 1);
        }
        cin >> m;
        for (int i = 0; i < m; i++)
        {
            //����Դ��->����
            cin >> dev >> tmp;
            if (!M[tmp]) M[tmp] = tot++;
            ans.AddEdge(s, M[tmp], 1);
        }
        cin >> k;
        string u, v;
        while (k--)
        {
            //ת����
            cin >> u >> v;
            if (!M[u]) M[u] = tot++;
            if (!M[v]) M[v] = tot++;
            ans.AddEdge(M[u], M[v], INF);
        }
        cout << m - ans.Maxflow(s, t) << endl;
        if (T) cout << endl;
    }
    return 0;
}
