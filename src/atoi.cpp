#include <iostream>
#include <unistd.h>

using namespace std;

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

int main(int argc, char const *argv[])
{
    char tmp[100] = {0};
    my_itoa(120,tmp);
    my_itoa(-12039,tmp);
    return 0;
}
