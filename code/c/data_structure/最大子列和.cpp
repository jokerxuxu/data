#include <iostream>
#include <cstdio>
using namespace std;

namespace LIST
{

    struct NODE {
        int num;
        NODE *next;
        NODE():next(NULL){}
        NODE(const int &n,NODE *ne = NULL):num(n),next(ne){}
    };

    NODE *head;
    int len = 0;

    void init() {
        head = new NODE(0,head);

    }
    NODE* move(int i) {
        if(i<0) return head;
        NODE *p = head -> next;
        for(int j=0;j<i;++j) p = p -> next;
        return p;
    }
    void insert(int i, int x) {
        NODE *p = move(i-1);
        p -> next = new NODE(x,p -> next);
        ++len;
    }
    void remove(int i) {
        NODE *p = move(i-1);
        NODE *q = p -> next;
        p -> next = q -> next;
        delete q;
        --len;
    }
    void remove_insert(int i) {
        NODE *p = move(i-1);
        NODE *q = p -> next;
        move(i-1) -> next = q -> next;
        move(len-2) -> next = q;
        q -> next = head;
    }
    void get_length() {
        cout<<len<<endl;
    }
    void query(int i) {
        if (i>=len) cout<<"-1"<<endl;
        else cout<<move(i) -> num<<endl;
    }
    void get_max(){
        int x=0,i=0;
        if(len==0) cout<<"-1"<<endl;
         else {  for(;i<len;++i)
                    {if( move(i) -> num > x) x = move(i) -> num;}
               cout<<x<<endl;}
    }
    void clear() {
        while (len > 0) remove(0);
    }

}
int n;
int main()
{
    cin >> n;
    int op, x, p;
    LIST::init();
    for (int i = 0; i < n; ++i)
    {
        cin >> op;
        switch(op) {
            case 0:
                LIST::get_length();
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p,x);
                break;
            case 2:
                cin >> p;
                LIST::query(p);
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                cin >> p;
                LIST::remove_insert(p);
                break;
            case 5:
                LIST::get_max();
                break;
        }
    }
    LIST::clear();
    return 0;
}