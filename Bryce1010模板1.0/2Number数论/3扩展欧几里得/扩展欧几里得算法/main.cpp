/**************
*��չŷ������㷨
*����d=gcd(a,b)���Ͷ�Ӧ��ʽax+by=d�е�x,y
*/
long long extend_gcd(long long a,long long b,long long &x,long long &y)
{
    if(a==0&&b==0)return -1;//�����Լ��
    if(b==0){x=1;y=0;return a;}
    long long d=extend_gcd(b,a%b,y,x);
    y-=a/b*x;
}


