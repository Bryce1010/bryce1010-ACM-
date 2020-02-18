/*
d(i,j)��ʾ������Si,Si+1,...,Sk��Ӧ�����ĸ���
��1���߽�����d(1,1��=1��d(i,j)=0
��2����i��jɨ�裬���S[i]==s[k]������һ����֧�ص���
��d(i+1,k-1)��ʾ��ʣ�ಿ��ΪSk....Sj����d(k,j)��ʾ(i+2<=k<=j)

*/
#include <iostream>
#include<string.h>
#include<algorithm>
#include<stdio.h>
using namespace std;

const int MAXN=300+10;
const int MOD=1000000000;

#define ll long long
char str[MAXN];
ll d[MAXN][MAXN];




ll dp(int i,int j)
{
    if(i==j)return 1;
    if(str[i]!=str[j])return 0;//d(i,j)=0
    ll &ans=d[i][j];
    if(ans>=0)return ans%MOD;
    ans=0;
    for(int k=i+2;k<=j;k++)
    {
        if(str[i]==str[k])
        {
            ans=(ans+dp(i+1,k-1)*dp(k,j))%MOD;
        }
    }
    return ans;
}

int main()
{
    while(scanf("%s",str)==1)
    {
        memset(d,-1,sizeof(d));
        cout<<dp(0,strlen(str)-1)<<endl;
    }
    return 0;
}
