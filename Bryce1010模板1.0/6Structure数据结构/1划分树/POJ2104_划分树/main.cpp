/*������
��ѯ�����K��

*/

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<math.h>
using namespace std;

#define ll long long
const int MAXN=100009;
int tree[21][MAXN];//��ʾÿ��ÿ��λ�õ�ֵ
int sorted[MAXN];//�Ѿ�����õ���
int toleft[21][MAXN];//toleft[p][i]��ʾ��i���1��i�ж������������

/*����
same��ʾ����sorted[mid]�ĸ���,��ʼ��Ϊmid-l+1��ɨ���ÿ����һ����С��ֵ����1
����same��ʾҪ��������ߵ����м�ֵ�ĸ���
���������������
1�����tree[[dep][i]<sorted[mid]�������
2�����tree[dep][i]==sorted[mid],same>0�Ļ��������
3��������ǻ����ұ�
*/

void build(int l,int r,int dep)
{
    if(l==r)return;
    int mid=(l+r)>>1;
    int same=mid-l+1;
    for(int i=l;i<=r;i++)
    {
        if(tree[dep][i]<sorted[mid])
        {
            same--;
        }
    }
    int lpos=l;
    int rpos=mid+1;
    for(int i=l;i<=r;i++)
    {
        if(tree[dep][i]<sorted[mid])
            tree[dep+1][lpos++]=tree[dep][i];
        else if(tree[dep][i]==sorted[mid]&&same)
        {
            tree[dep+1][lpos++]=tree[dep][i];
            same--;
        }
        else
        {
            tree[dep+1][rpos++]=tree[dep][i];
        }
        toleft[dep][i]=toleft[dep][l-1]+lpos-l;
    }
    build(l,mid,dep+1);
    build(mid+1,r,dep+1);
}
/*��ѯ����
��ѯ�����K��ֵ��[L,R]�Ǵ����䣬[l,r]��Ҫ��ѯ��С����
cnt��¼������ߵĸ���
1�����cnt>=k��˵����K����������
2������˵����K����������
*/
int query(int L,int R,int l,int r,int dep,int k)
{
    if(l==r)return tree[dep][l];
    int mid=(L+R)>>1;
    int cnt=toleft[dep][r]-toleft[dep][l-1];
    if(cnt>=k)
    {
        int newl=L+toleft[dep][l-1]-toleft[dep][L-1];
        int newr=newl+cnt-1;
        return query(L,mid,newl,newr,dep+1,k);
    }
    else
    {
        int newr=r+toleft[dep][R]-toleft[dep][r];
        int newl=newr-(r-l-cnt);
        return query(mid+1,R,newl,newr,dep+1,k-cnt);
    }
}

int main()
{
    int n,m;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        memset(tree,0,sizeof(tree));
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&tree[0][i]);
            sorted[i]=tree[0][i];
        }
        sort(sorted+1,sorted+n+1);
        build(1,n,0);
        int s,t,k;
        while(m--)
        {
            scanf("%d%d%d",&s,&t,&k);
            printf("%d\n",query(1,n,s,t,0,k));
        }
    }
    return 0;
}









