#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

#define a 3
#define b 3						//
#define ElemType int            //结点存储的数据域类型

//定义链表结点结构�?
typedef struct LNode
{
	ElemType data;              //结点的数据域
	struct LNode *next;         //结点的指针域
}LNode,*LinkList;               //Linklist为指向结构体LNode的指针类�?

//创建新结�?
#define newNode (LNode*)malloc(sizeof(LNode))

//打印链表
void printList(LinkList L) {
    LinkList p = L->next;           // 从第一个结点开始遍�?
    while (p) {
        cout << p->data << " ";
        p = p->next;                // 移动到下一个结�?
    }
    cout << endl;
}

//生成新链�?
void create(LinkList L,int n)
{//逆位序输入n个元素的值，建立带表头结点的单链表L
      
	L->next=NULL;                   //先建立一个带头结点的空链�?
	for(int i=0;i<n;++i)
	{
		LinkList p = newNode;                  //生成新结�?*p
		cin>>p->data;               //输入元素值赋给新结点*p的数据域
		p->next=L->next;L->next=p;  //将新结点*p插入到头结点之后
	}
}

//合并操作
void MergeList_L(LinkList LA, LinkList LB, LinkList LC)
{
    LinkList pa = LA->next;
    LinkList pb = LB->next;
    LC = LA;
    LinkList pc = LC;

    while (pa && pb) {
        if (pa->data <= pb->data) {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        } else {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }

    pc->next = pa ? pa : pb;
    delete LB;

    // 去除重复元素
    LinkList p = LC->next;
    while (p && p->next) {
        if (p->data == p->next->data) {
            LinkList temp = p->next;
            p->next = temp->next;
            delete temp;
        } else {
            p = p->next;
        }
    }
}

//交集操作
void Intersection_L(LinkList LA, LinkList LB, LinkList LC)
{//已知LA，LB的元素按值非递减排列
	LinkList pa=LA->next;	LinkList pb=LB->next;        //pa和pb分别指向首元结点
	LC=LA;                              				 //用LA的头结点作为LC的头结点
	LinkList pc=LC;                              		 //pc的初值指向LC的头结点
	int flag=0;                        					 //判断是否是交集里的元�?
	while(pa)
	{//遍历LB删去交集之外的元�?
		pb=LB->next;
		while(pb)
		{//遍历LB查找相同元素
			flag=0;
			if(pa->data==pb->data)
			{	
				pc->next=pa;                //pa所指向的结点连接到pc所指结点的后面
				pc=pa;                      //pc向后挪，指向pa
				pa=pa->next;                //pa挪到LA下一个结�?
				flag=1;break;
			}else{pb=pb->next;}	
		}                                   //while(pb)
		if(flag==0)
		{
			LinkList q=pa;
			pc->next=pa->next;
			pa=pa->next;                    //pa挪到LA下一个结�?
			delete q;
		}
	} 
}


int main()
{
    LNode *LA=newNode; LNode *LB=newNode; LinkList LC;
    create(LA,a);
	create(LB,b);
	cout << "请输入你所需要的操作\n求并�?:1\n求交�?:2\n" ;
	int flag;
	cin>>flag;
	switch(flag)
	{
		case 1:	MergeList_L(LA,LB,LC);break;

		case 2: Intersection_L(LA, LB, LC);break;

	}
	printList(LA);
}