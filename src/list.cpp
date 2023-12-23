
#include <iostream>
#include <unistd.h>
#include <unordered_set>

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

void removeFromListByValue(mylist* &head,int value) {
    if(head == nullptr) {
        return;
    }
    listNode* curNode = head;
    while(curNode) {
        if(curNode->value == value) {
            if(curNode == head) {
                head = curNode->next;
            } else {
                if(curNode->next) {
                    curNode->next->pre = curNode->pre;
                }
                if(curNode->pre) {
                    curNode->pre->next = curNode->next;
                }
            }
            listNode* tmp = curNode;
            curNode = curNode->next;
            delete tmp;
        } else {
            curNode = curNode->next;
        }
    }
}

void findCommonValuesFromTowList(
            const mylist* listA,
            const mylist* listB,
            std::unordered_set<int>& values) {
    if(listA == nullptr || listB == nullptr) {
        return;
    }
    std::unordered_set<int> uniqueValuesInAList;
    const listNode* curNode = listA;
    while(curNode) {
        uniqueValuesInAList.insert(curNode->value);
        curNode = curNode->next;
    }
    curNode = listB;
    while(curNode) {
        if(uniqueValuesInAList.find(curNode->value) != uniqueValuesInAList.end()) {
            values.insert(curNode->value);
        }
        curNode = curNode->next;
    }
}

void removeCommonValuesFromTowList(mylist* &listA,mylist* &listB) {
    if(listA == nullptr || listB == nullptr) {
        return;
    }
    std::cout << "before remove:" << std::endl;
    dumpList(listA);
    dumpList(listB);
    std::unordered_set<int> values;
    findCommonValuesFromTowList(listA,listB,values);
    if(values.size() != 0) {
        for(auto& value : values) {
            removeFromListByValue(listA,value);
            removeFromListByValue(listB,value);
        }
    }
    std::cout << "after remove:" << std::endl;
    dumpList(listA);
    dumpList(listB);
}

int main(int argc,char *argv[]) {
    listNode* a = new listNode(1);
    listNode* b = new listNode(2);
    listNode* c = new listNode(3);

    listNode* d = new listNode(3);
    listNode* e = new listNode(3);
    listNode* f = new listNode(3);

    a->next = b;
    b->next = c;
    c->pre = b;
    b->pre = a;

    d->next = e;
    e->next = f;
    f->pre = e;
    e->pre = d;
    
    mylist* listA = a;
    mylist* listB = d;

    removeCommonValuesFromTowList(listA,listB);
    //removeDupNodesFromSortedListA(my);
    //removeDupNodesFromSortedListB(my);
    //removeDupNodesFromUnSortedList(my);

    return 0;
}