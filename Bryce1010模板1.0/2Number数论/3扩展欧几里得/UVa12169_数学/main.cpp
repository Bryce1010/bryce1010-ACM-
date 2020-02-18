/*UVa12169 - Disgruntled Judge
--a,b����10000���ڣ���������ö��a��ֵ��Ȼ�����x1��x3�����b��ֵ���ٱ�������X�ж������Ƿ�Ϸ�
--�����׵õ�x3=(a*a*x1+(a+1)*b)%10001;����һ�¿��Եõ���(a+1)*b+10001*k=x3-a*a*x1;ֱ��������չŷ������㷨
���b��[0,10000]��Ψһ�⡣
*/
#define _CRT_SECURE_NO_DEPRECATE
#include<bits/stdc++.h>
using namespace std;
const int maxn =100 + 10;
const int mod = 10001;
typedef long long LL;
LL F[maxn * 2];

//��չŷ������㷨�����ax+by=gcd(a,b)ϵ��
void extendEuclid(LL a, LL b, LL &d, LL &x, LL&y){
    if (!b){ d = a; x = 1; y = 0; }
    else{ extendEuclid(b
                       , a%b, d, y, x); y -= x*(a / b); }
}
//��ax+by=n��һ����(x0,y0)
//���н�Ϊ(x0+t*b,y0-t*a),t����������
LL solveLiner(LL a, LL b, LL n, LL&x, LL&y){
    LL d;
    extendEuclid(a, b, d, x, y);
    if (n%d)return 0;  //�޽�
    x = (n / d)*x; y = (n / d)*y;
    return 1;
}

inline LL answer(LL a, LL b, LL x){ return (a*x + b) % mod; }

int main(){
    int T,i;
    LL a, b,k;
    while (~scanf("%d", &T)){
        for (i = 1; i <= 2 * T - 1; i += 2)
            scanf("%d", &F[i]);
        for (a = 0; a < mod; a++){
            solveLiner(a + 1, mod, F[3] - a*a*F[1], b, k);
            b = (b%mod + mod) % mod; //�����b��[0,10000]�Ľ�
            for (i = 2; i <= 2 * T; i++){
                LL temp = answer(a, b, F[i - 1]);
                if (i & 1 && temp != F[i])break;
                F[i] = temp;
            }
            if (i == 2 * T + 1)break;
        }
        for (i = 2; i <= 2 * T; i += 2)
            printf("%lld\n", F[i]);
    }
    return 0;
}
