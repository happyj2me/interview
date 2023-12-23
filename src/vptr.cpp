#include <map>
#include <iostream>
#include <array>
#include "stdio.h"
#include <memory>
#include <thread>
#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
struct B;
struct A {
    A() {
        std::cout << "A is created" << std::endl;
    }

    virtual ~A() {
        std::cout << "A is destroyed" << std::endl;
    }

    public:
        std::weak_ptr<B> mb;
};
struct B {
    B() {
        std::cout << "B is created" << std::endl;
    }

    virtual ~B() {
        std::cout << "B is destroyed" << std::endl;
    }

    public:
        std::weak_ptr<A> ma;
};
class IBaseA
{
public:
    virtual void fnA() {std::cout << "IBaseA fnA" << std::endl;}

    int m_nTestA;
};

class IBaseB
{
public:
    virtual void fnB() = 0;

    int m_nTestB;
};

class AA : public IBaseA {
public:
    AA() = default;
    virtual ~AA() = default;
    virtual void fnA() {std::cout << "AA fnA" << std::endl;}
};

class CTest : public IBaseA,public IBaseB
{
public:
    virtual void fnA()
    {
        printf("fnA\n");
    }

    virtual void fnB()
    {
        printf("fnB\n");
    }
};
int fuckyou = 1;
int main(int argc, char* argv[])
{
    std::array<int,3> a = {-1,-1,-1};
    std::cout << a[0] << std::endl;
    CTest *pTest = new CTest;
    void *p = (void*)pTest;
    IBaseA *pBaseA = (IBaseA*)p;
    pBaseA->fnA();

    IBaseB *pBaseB = (IBaseB*)p;
    pBaseB->fnB();

    pBaseB = (IBaseB*)pTest;
    pBaseB->fnB();

   std::map<int,int> va;
   for(int i=10;i<20;i++){
       va[i] = i;
   }
   auto iter  = va.lower_bound(1);
   std::cout << "iter == begin " << (iter == va.begin()  ? "true" : "false" ) << std::endl; 
    std::cout << "iter == end " << (iter == va.end()  ? "true" : "false" ) << std::endl; 
   va.erase(va.begin(),iter);
   for(auto item : va) {
       std::cout << item.second << std::endl;
   }
    std::cout << "A and B is created" << std::endl;
    auto aa = std::make_shared<A>();
    auto bb = std::make_shared<B>();
    aa->mb = bb;
    std::cout << "A and B is destroyed" << std::endl;
    std::cout << "size of sptr " << sizeof(aa) << std::endl;
    std::cout << "cpu info " << std::thread::hardware_concurrency() << std::endl;

    //对于基础类型 默认是大顶堆
    priority_queue<int> aq;
    priority_queue<int, vector<int>, greater<int>> cq;  //这样就是小顶堆
    priority_queue<string> bq;

    for (int i = 0; i < 5; i++)
    {
        aq.push(i);
        cq.push(i);
    }
    while (!aq.empty())
    {
        cout << aq.top() << ' ';
        aq.pop();
    }
    cout << endl;

    while (!cq.empty())
    {
        cout << cq.top() << ' ';
        cq.pop();
    }
    cout << endl;

    bq.push("abc");
    bq.push("abcd");
    bq.push("cbd");
    while (!bq.empty())
    {
        cout << bq.top() << ' ';
        bq.pop();
    }
    cout << endl;
    std::vector<int32_t> vec = {0,1,2,3,4,5};

    int fuckyou = fuckyou;
    cout << "fuck is " << fuckyou << endl;

    int i = -9;
    int y = -i;
    cout << "y is " << y << endl;

    char ca[3] = {'a','b'};
    cout << "len of ca is " << strlen(ca) << endl;

    AA ax;
    ax.m_nTestA = 1;
    ax.fnA();
    return 0;
}