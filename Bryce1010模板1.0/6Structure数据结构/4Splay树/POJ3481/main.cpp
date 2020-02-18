#include<bits/stdc++.h>
using namespace std;



const int MAXN=100010;
struct Node;
Node *null;
struct Node
{
    Node *ch[2],*fa;
    int ssize;
    int rev;
    Node()
    {
        ch[0]=ch[1]=fa=null;rev=0;
    }
    inline void push_up()
    {
        if(this==null)return;
        ssize=ch[0]->ssize+ch[1]->ssize+1;
    }
    inline void setc(Node *p,int d)
    {
        ch[d]=p;
        p->fa=this;
    }
    inline bool d()
    {
        return fa->ch[1]==this;
    }


    void Update_Rev()
    {
        if(this==null)
        {
            return;
        }
        swap(ch[0],ch[1]);
        rev^=1;
    }
    inline void push_down()
    {
        if(this==null)
        {
            return;
        }
        if(rev)
        {
            ch[0]->Update_Rev();
            ch[1]->Update_Rev();
            rev=0;
        }
    }







};
//ch[0]��ʾ��ڵ�ָ�룬ch[1]��ʾ�ҽڵ�ָ��
//��ת������c=0��ʾ������c=1��ʾ����
inline void Rotate(Node *x)
{
    Node *f=x->fa,*ff=x->fa->fa;
    f->push_down();
    x->push_down();
    int c=x->d(),cc=f->d();
    f->setc(x->ch[!c],c);
    x->setc(f,!c);
    if(ff->ch[cc]==f)ff->setc(x,cc);
    else x->fa=ff;
    f->push_up();
}
//Splay��������ʾ�ѽڵ�xת���ڵ�goal������
inline void splay(Node* &root,Node* x,Node* goal)//��x
{
    while(x->fa!=goal)
    {
        if(x->fa->fa==goal)Rotate(x);//����
        else
        {
            x->fa->fa->push_down();
            x->fa->push_down();
            x->push_down();
            bool f=x->fa->d();
            x->d()==f?Rotate(x->fa):Rotate(x);
            Rotate(x);
        }
    }
    x->push_up();
    if(goal==null)root=x;
}







