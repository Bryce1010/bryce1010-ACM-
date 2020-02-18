/* ***********************************************
Author        :kuangbin
Created Time  :2013/8/24 23:28:43
File Name     :F:\2013ACM��ϰ\ר��ѧϰ\splay_tree_2\HDU1890.cpp
************************************************ */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define Key_value ch[ch[root][1]][0]
const int MAXN = 100010;
int pre[MAXN],ch[MAXN][2],root,tot1;
int size[MAXN];//������ģ
int rev[MAXN];//��ת���
int s[MAXN],tot2;//�ڴ�غ�����

//debug����**********************************
void Treavel(int x)
{
    if(x)
    {
        Treavel(ch[x][0]);
        printf("��㣺%2d: ����� %2d �Ҷ��� %2d ����� %2d size = %2d rev = %2d\n",x,ch[x][0],ch[x][1],pre[x],size[x],rev[x]);
        Treavel(ch[x][1]);
    }
}
void debug()
{
    printf("root:%d\n",root);
    Treavel(root);
}
//������debug����**************************************


void NewNode(int &r,int father,int k)
{
    r = k;
    pre[r] = father;
    ch[r][0] = ch[r][1] = 0;
    size[r] = 1;
    rev[r] = 0;
}
//��ת�ĸ���
void Update_Rev(int r)
{
    if(!r)return;
    swap(ch[r][0],ch[r][1]);
    rev[r] ^= 1;
}
inline void push_up(int r)
{
    size[r] = size[ch[r][0]] + size[ch[r][1]] + 1;
}
inline void push_down(int r)
{
    if(rev[r])
    {
        Update_Rev(ch[r][0]);
        Update_Rev(ch[r][1]);
        rev[r] = 0;
    }
}
void Build(int &x,int l,int r,int father)
{
    if(l > r)return;
    int mid = (l+r)/2;
    NewNode(x,father,mid);
    Build(ch[x][0],l,mid-1,x);
    Build(ch[x][1],mid+1,r,x);
    push_up(x);
}
int n;
void Init()
{
    root = tot1 = tot2 = 0;
    ch[root][0] = ch[root][1] = pre[root] = size[root] = rev[root] = 0;
    NewNode(root,0,n+1);
    NewNode(ch[root][1],root,n+2);
    Build(Key_value,1,n,ch[root][1]);
    push_up(ch[root][1]);
    push_up(root);
}
//��ת��0Ϊ������1Ϊ����
inline void Rotate(int x,int kind)
{
    int y = pre[x];
    push_down(y);
    push_down(x);//�Ȱ�y�ı���´����ڰ�x�ı���´�
    ch[y][!kind] = ch[x][kind];
    pre[ch[x][kind]] = y;
    if(pre[y])
        ch[pre[y]][ch[pre[y]][1]==y] = x;
    pre[x] = pre[y];
    ch[x][kind] = y;
    pre[y] = x;
    push_up(y);
}
//Splay��������r��������goal����
inline void Splay(int r,int goal)
{
    push_down(r);
    while(pre[r] != goal)
    {
        if(pre[pre[r]] == goal)
        {
            //�з�ת��������Ҫ��push_down,���ж����Һ���
            push_down(pre[r]);
            push_down(r);
            Rotate(r,ch[pre[r]][0]==r);
        }
        else
        {
            //�з�ת��������Ҫ��push_down
            push_down(pre[pre[r]]);
            push_down(pre[r]);
            push_down(r);
            int y = pre[r];
            int kind = ch[pre[y]][0]==y;
            if(ch[y][kind] == r)
            {
                Rotate(r,!kind);
                Rotate(r,kind);
            }
            else
            {
                Rotate(y,kind);
                Rotate(r,kind);
            }
        }
    }
    push_up(r);
    if(goal == 0) root = r;
}
//�õ���k�����(��Ҫpush_down)
inline int Get_kth(int r,int k)
{
    push_down(r);
    int t = size[ch[r][0]] + 1;
    if(t == k)return r;
    if(t > k)return Get_kth(ch[r][0],k);
    else return Get_kth(ch[r][1],k-t);
}
//��ǰ��(��Ҫpush_down)
inline int Get_pre(int r)
{
    push_down(r);
    if(ch[r][0] == 0)return -1;//������
    r = ch[r][0];
    while(ch[r][1])
    {
        r = ch[r][1];
        push_down(r);
    }
    return r;
}
//�Һ��(��Ҫpush_down)
inline int Get_next(int r)
{
    push_down(r);
    if(ch[r][1] == 0)return -1;
    r = ch[r][1];
    while(ch[r][0])
    {
        r = ch[r][0];
        push_down(r);
    }
    return r;
}

struct Node
{
    int id,val;
}node[MAXN];
bool cmp(Node a,Node b)
{
    if(a.val != b.val)return a.val < b.val;
    else return a.id < b.id;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
     while(scanf("%d",&n) == 1 && n)
    {
        for(int i = 1;i <= n;i++)
        {
            scanf("%d",&node[i].val);
            node[i].id = i;
        }
        sort(node+1,node+n+1,cmp);
        Init();
        for(int i = 1; i <= n;i++)
        {
            Splay(node[i].id,0);
            printf("%d",size[ch[root][0]]);
            if(i < n)printf(" ");
            else printf("\n");
            Splay(Get_kth(root,i),0);
            Splay(Get_next(node[i].id),root);
            Update_Rev(Key_value);
        }
    }
    return 0;
}
