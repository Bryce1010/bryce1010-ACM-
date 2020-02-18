/*
���⣺
���������Ǹ�����a��b��������n��0<=a,b<2^64��1<=n<=1000��,��������Ǽ���f(a^b)����n������������f(0)=f(1)=1;
�Ҷ������зǸ�����i��f(i+2)=f(i+1)+f(i)��

˼·��
����n=3������F[i]��ǰ10��Ϊ1,1,2,0,2,2,1,0,1,1
���������й��ɵģ����ݵ��ƹ�ʽ����ʮһ�����ڵ�3���12�����ڵ�4��
��Ϊ�������n�֣��������n^2��ͻ��ظ����֡�������ΪM����ֻ������f[0]~f[n^2]�������M��Ȼ���ÿ��������a^b����������F[a^b]������һ���

*/

#include<iostream>
using namespace std;
typedef unsigned long long ULL;
const int maxn = 1000+10;

ULL F[maxn*maxn];

ULL quick_pow_mod(ULL a,ULL n,ULL m){
    if (n == 0)return 1;
    ULL res = 1;
    while (n > 0){
        if (n & 1)
            res = res*a%m;
        a = (a%m)*(a%m)%m;
        n >>= 1;
    }
    return res;
}
int main(){
    ULL a, b, n,t,T,i;
    cin >> t;
    while (t--){
        cin >> a >> b >> n;
        F[0] = 0; F[1] = 1;
        if (n == 1){ printf("0\n"); continue; }
        for (i = 2;i<n*n; i++){
            F[i] = (F[i - 1] + F[i - 2]) % n;
            if (F[i] == 1 && F[i - 1] == 0)break; //�ҵ�����
        }
        T = i - 1; //����
        ULL id = quick_pow_mod(a, b, T);
        cout << F[id] << endl;
    }
    return 0;
}
