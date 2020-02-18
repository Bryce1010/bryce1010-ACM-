/*
�ֳ��������ۣ�A�����һ�в��B�������һ�в��C�����һ�в��D�������һ�в���
S����ȫ��,�����ݳ�ԭ��

*/


#include <bits/stdc++.h>

using namespace std;
#define ll long long
const ll MAXN=500;
const ll MOD=1000007;
ll C[MAXN+20][MAXN+20];

void init()
{
    memset(C,0,sizeof(C));
    C[0][0]=1;
    for(ll i=0;i<=MAXN;i++)
    {
        C[i][0]=C[i][i]=1;
        for(ll j=1;j<i;j++)
        {
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
        }
    }

}



int main()
{
    init();
//#ifndef online_jduge
//    freopen("in.txt","r",stdin);
//#endif // online_jduge
    ll n,m,k;
    ll t,Case=1;
    cin>>t;

    while(t--)
    {
        cin>>n>>m>>k;
        ll r=m,c=n,b=0,sum=0;
        init();
        //ö��16�ַ���S��ʾȫ����A��ʾ��һ�У�B��ʾ���һ�У�C��ʾ��һ�У�D��ʾ���һ��
        for(ll i=0;i<16;i++)
        {
            b=0,r=m,c=n;
            if(i&1)
            {
                r--,b++;
            }
            if(i&2)
            {
                r--,b++;
            }
            if(i&4)
            {
                c--,b++;
            }
            if(i&8)
            {
                c--,b++;
            }
            if(b&1)//������ -
            {
                sum=(sum+MOD-C[r*c][k])%MOD;
            }
            else//ż���� +
            {
                sum=(sum+C[r*c][k])%MOD;
            }
        }
        cout<<"Case "<<Case++<<": "<<sum<<endl;
    }
    //cout << "Hello world!" << endl;
    return 0;
}

