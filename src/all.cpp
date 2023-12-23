#include <iostream>
#include <cstdint>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <string.h>
#include <mutex>
#include <condition_variable>

namespace number
{
    typedef struct _NumberRange
    {
        int64_t begin;
        int64_t end;
        int32_t idx;
    } NumberRange;

    std::atomic_int64_t total(0);

    void calPairedNumbers(void *param)
    {
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        NumberRange *range = static_cast<NumberRange *>(param);
        int64_t begin = range->begin;
        int64_t end = range->end;
        int64_t nums = 0;
        int64_t number = 0;
        std::vector<uint8_t> rightToLeftNumbers(10);
        for (int64_t idx = begin; idx < end; idx++)
        {
            rightToLeftNumbers.clear();
            number = idx;
            if (number < 10)
            {
                continue;
            }
            while (number)
            {
                rightToLeftNumbers.emplace_back(number % 10);
                number /= 10;
            }

            bool found = true;
            int len = rightToLeftNumbers.size();
            int middle = len / 2;
            for (int i = 0; i < middle; i++)
            {
                if (rightToLeftNumbers[i] != rightToLeftNumbers[len - i - 1])
                {
                    found = false;
                    break;
                }
            }

            if (found)
            {
                nums++;
            }
        }
        total.fetch_add(nums);
        std::chrono::steady_clock::time_point over = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(over - start);
        std::cout << "thread " << range->idx << " found " << nums << ",cost:" << duration.count() << std::endl;
    }

    void TestPairedNumber()
    {
        std::chrono::steady_clock::time_point timeStart = std::chrono::steady_clock::now();
        int32_t threadNum = std::thread::hardware_concurrency();
        int64_t totalTask = 987654321;
        int64_t eachTask = totalTask / threadNum;

        NumberRange ranges[threadNum] = {};
        for (int i = 0; i < threadNum; i++)
        {
            ranges[i].idx = i;
            ranges[i].begin = i * eachTask;
            ranges[i].end = (i + 1) * eachTask - 1;
        }

        std::vector<std::unique_ptr<std::thread>> threads;
        for (int i = 0; i < threadNum; i++)
        {
            std::unique_ptr<std::thread> thread(new std::thread([&ranges, i]() { 
                    calPairedNumbers(&ranges[i]); 
                }
            ));
            
            threads.push_back(std::move(thread));
        }

        NumberRange lastRange;
        int64_t leftTask = totalTask % threadNum;
        lastRange.idx = threadNum;
        lastRange.begin = totalTask - leftTask + 1;
        lastRange.end = totalTask;
        calPairedNumbers(&lastRange);

        for (int i = 0; i < threadNum; i++)
        {
            threads[i]->join();
        }

        std::chrono::steady_clock::time_point timeEnd = std::chrono::steady_clock::now();
        auto totalCost = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);
        std::cout << "total " << total << ",cost " << totalCost.count() << std::endl;
    }
} // namespace number

namespace condition
{
    std::condition_variable cv;
    std::mutex m;
    volatile int goods = 0;
    std::atomic_bool quit{false};
    constexpr int totalGoods = 10;
    void consumer(int n)
    {
        for (int i = 0; i < n; i++)
        {
            std::unique_lock<std::mutex> ul(m);
            cv.wait(ul, []
                    { return (goods != 0 || quit.load()); });
            if (goods > 0)
            {
                goods--;
            }
            std::cout << "consumer goods,left:" << goods << std::endl;
        }
    }
    void TestCondition()
    {
        std::thread worker(consumer, totalGoods);
        for (int i = 0; i < totalGoods; i++)
        {
            while (goods > 0)
            {
                std::this_thread::yield();
            }
            std::unique_lock<std::mutex> ul(m);
            goods++;
            std::cout << "producer goods,left:" << goods << std::endl;
            cv.notify_all();
        }
        worker.join();
    }
}

#include <stdio.h>
#include <pulse/simple.h>
#include <pulse/error.h>
namespace pulse
{
#define SAMPLE_RATE 44100
#define CHANNELS 2
#define BUFFER_SIZE 1024

    int TestPulseAudio()
    {
        pa_sample_spec ss;
        ss.format = PA_SAMPLE_S16LE;
        ss.rate = SAMPLE_RATE;
        ss.channels = CHANNELS;

        pa_simple *input_stream = NULL;
        int error;
        if (!(input_stream = pa_simple_new(NULL, "Mic Input", PA_STREAM_RECORD, NULL, "record", &ss, NULL, NULL, &error)))
        {
            fprintf(stderr, "Failed to create input stream: %s\n", pa_strerror(error));
            return 1;
        }

        // 获取当前音频设备的延迟信息
        pa_usec_t latency = pa_simple_get_latency(input_stream, NULL);
        
        printf("当前音频设备的延迟: %lld 微秒\n", (long long)latency);

        // 创建PulseAudio输出流
        pa_simple *output_stream = NULL;
        if (!(output_stream = pa_simple_new(NULL, "Speaker Output", PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error)))
        {
            fprintf(stderr, "Failed to create output stream: %s\n", pa_strerror(error));
            return 1;
        }

        // 读取并播放音频数据
        uint8_t buffer[BUFFER_SIZE];
        int32_t ret = 0;
        while (true)
        {
            // 从输入流读取音频数据
            ret = pa_simple_read(input_stream, buffer, sizeof(buffer), &error);
            if (ret < 0)
            {
                fprintf(stderr, "Failed to read audio data: %s\n", pa_strerror(error));
                break;
            }
            if (ret > 0)
            {
                fprintf(stderr, "read audio data: %d\n", ret);
            }

            // 将音频数据写入输出流
            ret = pa_simple_write(output_stream, buffer, sizeof(buffer), &error);
            if (ret < 0)
            {
                fprintf(stderr, "Failed to write audio data: %s\n", pa_strerror(error));
                break;
            }
        }

        // 关闭输入流和输出流
        if (input_stream)
            pa_simple_free(input_stream);
        if (output_stream)
            pa_simple_free(output_stream);

        return 0;
    }

}

int main(int argc, char const *argv[])
{
    // number::TestPairedNumber();
    // condition::TestCondition();
    pulse::TestPulseAudio();
    return 0;
}
