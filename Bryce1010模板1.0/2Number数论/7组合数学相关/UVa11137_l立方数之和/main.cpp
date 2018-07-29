/*
(i,j)��ʾ������i�������������ĺ�Ϊj
d(i,j)��ʾ(0,0)��(i,j)��·���ж���

*/
#include <bits/stdc++.h>

using namespace std;
#define ll long long

const int MAXI=22;
const int MAXN=10000+5;

ll d[MAXI+10][MAXN+10];
void solve()
{
    memset(d,0,sizeof(d));
    d[0][0]=1;
    for(int i=1;i<MAXI;i++)
    {
        for(int j=0;j<MAXN;j++)
        {
            for(int a=0;j+a*i*i*i<MAXN;a++)
            {
                d[i][j+a*i*i*i]+=d[i-1][j];
            }
        }
    }
}
int main()
{
    ll n;
    solve();
    while(cin>>n)
    {
        ll cnt=0;
        cout<<d[22][n]<<endl;
    }
    return 0;
}
