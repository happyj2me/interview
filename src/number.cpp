#include <iostream>
#include <iomanip>
#include <stdint.h>
int main(int argc, char const *argv[])
{
    int off = 0;
    uint8_t buf[4] = {0};

    uint8_t pt = 121;
    int ts = 1450;
    int len = 0x2ff;

    std::cout << "ts is " << std::dec << ts << ",hex 0x" << std::setfill('0') << std::setw(4) << std::hex << ts << std::endl;
    std::cout << "len is " << std::dec << len << ",hex 0x" << std::setfill('0') << std::setw(4) << std::hex << len << std::endl;

    buf[off] = pt | 0x80;
    buf[off+1] = ts >> 6;
    buf[off+2] = ((ts & 0x3F) << 2) + ((len >> 8 ) & 0x03);
    buf[off+3] = len & 0xFF;

    int mlen = ((buf[2] & 0x03) << 8 ) ;
    std::cout << "after transfer " << std::endl;
    ts = 0;
    len = 0;

    ts = (buf[1] << 6) + ((buf[2] & 0xFC) >> 2);
    len = ((buf[2] & 0x03) << 8) + buf[3];
    std::cout << "ts is " << std::dec << ts << ",hex 0x" << std::setfill('0') << std::setw(4) << std::hex << ts << std::endl;
    std::cout << "len is " << std::dec << len << ",hex 0x" << std::setfill('0') << std::setw(4) << std::hex << len << std::endl;
    return 0;
}
