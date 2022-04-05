#include <omp.h>
#include <stdint.h>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <memory>

using namespace  std;
using namespace std:: chrono;

void merge(int32_t* data,int32_t start,int32_t mid,int32_t end) {

}
vector<uint64_t> ProduceData(int64_t num,int64_t max_value) {
    return {100,10};
}

void MergeSortNormal(uint64_t* array,int begin,int end) {

}

void verify(vector<uint64_t>& array) {

}

struct A : public std::enable_shared_from_this<A> {
    std::shared_ptr<A> getSelf() {
        return shared_from_this();
    }
    ~A() {
        std::cout << "A is deleted " << std::endl;
    }
};

void func() {
    std::cout <<"func is over" << std::endl;
}

int main(int argc, char const *argv[])
{
    auto time_start = system_clock::now();
    int64_t n = 5e8, max_number = 2e18;
    const auto data = ProduceData(n,max_number);
    auto data_test = data;

    cout << "produce data: " << double(duration_cast<milliseconds>(system_clock::now()-time_start).count());
    time_start = system_clock::now();

    MergeSortNormal(data_test.data(),0,n);
    cout << "normal sort: " << double(duration_cast<milliseconds>(system_clock::now()-time_start).count());
    
    verify(data_test);

    data_test = data;

     int cores = std::thread::hardware_concurrency();
    auto now = system_clock::now();
   usleep(10000);
   auto end = system_clock::now();
    cout << "cores is " << cores << ",now is " << duration_cast<milliseconds>(end-now).count() << endl;

    vector<thread> workers;
   std::weak_ptr<int> wptr;
    {
       auto ptr = std::make_shared<int>(10);
        wptr = ptr;
    }
   auto nptr = wptr.lock();
   if(nptr){
       std::cout << "lock ok" << std::endl;
   } else {
       std::cout << "lock fail" << std::endl;
   }

   auto pa = std::make_shared<A>();
   auto pb = pa->getSelf();
   std::cout <<"over " << pa.use_count() << " " << pb.use_count() << std::endl;

   std::thread t1(func);
   auto t2 = std::move(t1);
  // t1.join();
  // t2.join();
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  t2.join();
    return 0;
}
