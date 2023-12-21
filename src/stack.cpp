#include <iostream>
#include <cstdint>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>

typedef struct  _NumberRange {
    int64_t begin;
    int64_t end;
    int32_t idx;
}NumberRange;

std::atomic_int64_t total(0);

void calPairedNumbers(void* param) {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    NumberRange *range = static_cast<NumberRange*>(param);
    int64_t begin = range->begin;
    int64_t end = range->end;
    int64_t nums = 0;
    int64_t number = 0;
    std::vector<uint8_t> rightToLeftNumbers(10);
    for(int64_t idx = begin;idx < end; idx++) {
        rightToLeftNumbers.clear();
        number = idx;
        if(number < 10) {
            continue;
        }
        while(number) {
            rightToLeftNumbers.emplace_back(number % 10);
            number /= 10;
        }
        
        bool found = true;
        int len = rightToLeftNumbers.size();
        int middle = len / 2;
        for(int i=0;i<middle;i++) {
            if(rightToLeftNumbers[i] != rightToLeftNumbers[len - i -1]) {
                found = false;
                break;
            }
        }

        if(found) {
            nums++;
        }
    }
    total.fetch_add(nums);
    std::chrono::steady_clock::time_point over = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(over - start);
    std::cout << "thread " << range->idx << " found " << nums <<",cost:" << duration.count() << std::endl;

}

int main(int argc, char const *argv[])
{
    std::chrono::steady_clock::time_point timeStart = std::chrono::steady_clock::now();
    int32_t threadNum = std::thread::hardware_concurrency();
    int64_t totalTask = 987654321;
    int64_t eachTask = totalTask / threadNum;
    
    NumberRange ranges[threadNum] = {0};
    for(int i=0;i<threadNum;i++) {
        ranges[i].idx = i;
        ranges[i].begin = i*eachTask;
        ranges[i].end = (i+1)*eachTask -1;
    }

    std::vector<std::unique_ptr<std::thread>> threads;
    for(int i=0;i<threadNum;i++) {
        auto thread = std::make_unique<std::thread>(calPairedNumbers,&ranges[i]);
        threads.push_back(std::move(thread));
    }
    
    NumberRange lastRange;
    int64_t leftTask = totalTask % threadNum;
    lastRange.idx = threadNum;
    lastRange.begin = totalTask - leftTask + 1;
    lastRange.end = totalTask;
    calPairedNumbers(&lastRange);

    for(int i=0;i<threadNum;i++) {
        threads[i]->join();
    }

    std::chrono::steady_clock::time_point timeEnd = std::chrono::steady_clock::now();
    auto totalCost = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd-timeStart);
    std::cout << "total " << total <<",cost " << totalCost.count() << std::endl;
    return 0;
}
