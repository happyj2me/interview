
#include <iostream>
#include <unistd.h>
#include <set>

using namespace std;
typedef struct  listNode
{
    listNode(int v):value(v),next(nullptr),pre(nullptr) {}
    ~listNode() { cout << "node " << value << " is deleted" << endl;}
    int value;
    struct listNode* next;
    struct listNode* pre;
}mylist;

void dumpList(const mylist* head) {
    while(head) {
        cout << head->value << " ";
        head = head->next;
    }
    cout << endl;
}
/**
 * cur 代表遍历的当前位置
 * p   从当前位置的下一个位置查找和cur相等的元素
 * pre 指向p的前一个元素
*/
void removeDupNodesFromUnSortedList(mylist* head) {
    listNode* cur = head;
    while(cur && cur->next) {
        listNode* pre = cur;
        listNode* p = cur->next;
        
        while(p) {
            if(cur->value == p->value) {
                listNode* tmp = p;
                pre->next = p->next;
                p = p->next;
                delete tmp;
            } else {
                pre = p;
                p = p->next;
            }
        }

        cur = cur->next;
    }
}
/**
 *  A  B  B  C  D  E
 *  设置两个指针，一前一后，比较后一起往后挪动
*/
void removeDupNodesFromSortedListA(mylist* head) {
    if(head == nullptr)return;
    listNode* cur = head, *next;
    while(cur->next) {
        next = cur->next;
        if(cur->value == next->value) {
            cur->next = next->next;
            delete next;
        } else {
            cur = cur->next;
        }
    }
}

void removeDupNodesFromSortedListB(mylist* head) {
    listNode* cur = head;
    while(cur && cur->next) {
        listNode* p = cur->next;
        while(p && (p->value == cur->value)) {
            listNode* tmp = p;
            p = p->next;
            delete tmp;
        }
        cur->next = p;
        cur = p;
    }
}

void removeDupNodesFromTwoList(mylist* headA,mylist* headB) {
    if(nullptr == headA || nullptr == headB) {
        return;
    }
    listNode* p = headA;
    listNode* q;
    listNode* n;
    while(p) {
        //遍历B队列
        q = headB;
        while(q && q->value != p->value)q=q->next;
        
        //没找到一样的元素
        if(q == nullptr) {
            p = p->next;
        } else {
            int value = q->value;
            //从A队列删除等于value的所有节点
            n = p;
            while(n) {
                if(n->value == value) {
                    if(n == headA) {
                        
                    } else {

                    }
                } else {
                    n = n->next;
                }
            }
            //从B队列删除等于的所有节点
        }
    }
}

int main(int argc,char *argv[]) {
    listNode* a = new listNode(1);
    listNode* b = new listNode(2);
    listNode* c = new listNode(3);
    listNode* d = new listNode(4);
    listNode* e = new listNode(4);
    listNode* f = new listNode(4);
    a->next = b;
    b->next = c;
    c->next = d;
    d->next = e;
    e->next = f;
    
    mylist* my = a;
    dumpList(my);
    removeDupNodesFromSortedListA(my);
    //removeDupNodesFromSortedListB(my);
    //removeDupNodesFromUnSortedList(my);
    dumpList(my);

    return 0;
}