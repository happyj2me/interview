#include <iostream>
#include <unistd.h>

using namespace std;
namespace my {
void my_itoa(int32_t value,char* buf) {
    if(buf == nullptr)return;
    int idx = 0;
    if(value < 0) {
        buf[idx++] = '-';
        value = -value;
    }
    
    //从尾数往前一个个送入buf
    while (value) {
        buf[idx++] = (value % 10) + '0';
        value /= 10;
    }

    //翻转
    idx--;
    int beg = (buf[0] == '-' ? 1 : 0);
    for(int i=beg;i<idx;i++,idx--) {
        int tmp = buf[idx];
        buf[idx] = buf[i];
        buf[i] = tmp; 
    }
    cout << buf << endl;
}
}

namespace gpt {
#include <iostream>
#include <string>

std::string intToString(int num) {
    if (num == 0) {
        return "0";
    }

    std::string str;
    bool isNegative = false;

    if (num < 0) {
        isNegative = true;
        num = -num; // Make the number positive for processing
    }

    while (num > 0) {
        char digit = '0' + (num % 10);
        str = digit + str;
        num /= 10;
    }

    if (isNegative) {
        str = "-" + str;
    }

    return str;
}

}

int main() {
    int positiveNumber = 123;
    int negativeNumber = -456;

    std::string positiveStr = gpt::intToString(positiveNumber);
    std::string negativeStr = gpt::intToString(negativeNumber);

    std::cout << "Positive number as string: " << positiveStr << std::endl;
    std::cout << "Negative number as string: " << negativeStr << std::endl;

    return 0;
}
