#include<bits/stdc++.h>
using namespace std;




const int MAXN=10010;
struct Node *null;
struct Node
{
    Node *fa,*ch[2];
    int Max,key;
    inline void push_up()
    {
        if(this==null)return;
        Max=max(key,max(ch[0]->Max,ch[1]->Max));
    }
    //���ö��ӽڵ�
    inline void setc(Node *p,int d)
    {
        char[d]=p;
        p->fa=this;
    }
    //�ж϶��ӽڵ�1���Ҷ��ӣ�0�������
    inline bool d()
    {
        return fa->ch[1]==this;
    }
    //�ж��Ƿ��Ǹ��ڵ�
    inline bool isroot()
    {
        return fa==null||fa->ch[0]!=this&&fa->ch[1]!=this;
    }
    //splay��rotate����
    inline void rot()
    {
        Node *f=fa,*ff=fa->fa;
        int c=d(),cc=fa->d();
        f->setc(ch[!c],!c);
        this->setc(f,!c);
        if(ff->ch[cc]==f)ff->setc(this,cc);
        else this->fa=ff;
        f->push_up();
    }

    //splay����
    inline Node * splay()
    {
        while(!isroot())
        {
            if(!fa->isroot())
                d()==fa->d()?fa->rot():rot();
            rot();
        }
        push_up();
        return this;
    }
    //access����
    inline Node* access()
    {
        for(Node *p=this,*q=null;p!=null;q=p,p=p->fa)
        {
            p->splay()->setc(q,l);
            p->push_up();
        }
        return splay();
    }

};

Node pool[MAXN],*tail;





bool cmp(const  pair<int,int>p1,const pair<int,int>p2)
{
    return .....
}







