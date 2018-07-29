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
ll tree[21][MAXN];//��ʾÿ��ÿ��λ�õ�ֵ
ll sorted[MAXN];//�Ѿ�����õ���
ll toleft[21][MAXN];//toleft[p][i]��ʾ��i���1��i�ж������������
ll sum[20][MAXN];//sum[dep][i]��¼��dep���i����֮ǰС��sorted[mid]�ĺ�
int cnt[20][MAXN];//cnt[dep][i]��¼��dep�������ߵ�����
ll leftsum;
int leftnum;
ll all[MAXN];
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
    int cnt_small=0;
    ll val=0;
    for(int i=l;i<=r;i++)
    {
        if(tree[dep][i]<sorted[mid])
        {
            cnt_small++;
            val+=tree[dep][i];
            sum[dep][i]=val;
            cnt[dep][i]=cnt_small;
            tree[dep+1][lpos++]=tree[dep][i];

        }

        else if(tree[dep][i]==sorted[mid]&&same)
        {
            cnt_small++;
            val+=tree[dep][i];
            sum[dep][i]=val;
            cnt[dep][i]=cnt_small;
            tree[dep+1][lpos++]=tree[dep][i];
            same--;

        }
        else
        {
            sum[dep][i]=val;
            cnt[dep][i]=cnt_small;
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
    int s,ss;//s��¼L����cnt��ss��¼[L,R]��cnt
    ll val=0;
    if(l==L)s=0,val=sum[dep][R];
    else s=cnt[dep][L-1],val=sum[dep][R]-sum[dep][L-1];
    ss=cnt[dep][R]-s;

    int cnt1=toleft[dep][r]-toleft[dep][l-1];
    if(cnt1>=k)
    {
        int newl=L+toleft[dep][l-1]-toleft[dep][L-1];
        int newr=newl+cnt1-1;
        return query(L,mid,newl,newr,dep+1,k);
    }
    else
    {
        //�������Ӳ��ô��������Һ���ʱ��Ҫ�������ӵ�ֵ
        leftnum+=cnt1;
        leftsum+=val;
        int newr=r+toleft[dep][R]-toleft[dep][r];
        int newl=newr-(r-l-cnt1);
        return query(mid+1,R,newl,newr,dep+1,k-cnt1);
    }
}

int main()
{
    int n,m;
    int t,Case=1;
    scanf("%d",&t);
    while(t--)
    {
        printf("Case #%d:\n",Case++);
        scanf("%d",&n);
        memset(tree,0,sizeof(tree));
        for(int i=1;i<=n;i++)
        {
            scanf("%lld",&tree[0][i]);
            sorted[i]=tree[0][i];
            all[i]=all[i-1]+sorted[i];
        }
        sort(sorted+1,sorted+n+1);
        build(1,n,0);
        int s,t,k,x;
        int k1,k2,x1,x2;
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d%d",&s,&t);
            s++,t++;
            //int mi=s=(s+t)>>1;
            //k=sorted[mi];
            leftnum=leftsum=0;
            int len=(t-s+1);
            if(len%2)
            {
                k=(len+1)>>1;
                x=query(1,n,s,t,0,k);
//                cout<<x<<endl;
            }
            else
            {
                k1=len>>1;

                x=query(1,n,s,t,0,k);
                //x2=query(1,n,s,t,0,k2);
                //x=(x1+x2)/2;
            }
           // cout<<"x:"<<x<<endl;
            ll sum=0;
            sum=x*(leftnum+1)-(leftsum+x)+(all[t]-all[s-1]-(leftsum+x))-(t-s+1-(leftnum+1))*x;
            printf("%lld\n",sum);

//            cout<<"k:"<<k<<endl;
//            printf("%d\n",query(1,n,s,t,0,k));
        }
        printf("\n");
    }
    return 0;
}









