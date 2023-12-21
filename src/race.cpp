#include <iostream>
#define TOTAL_TIME 600
int total_score(int score,int time) {
    int left_time = TOTAL_TIME - time ;
    if(left_time < 0) {
        left_time = 0;
    }
    return score * 0.8 + left_time * 0.2;
}
int main(int argc,char* argv[]) {
    int score = 0;
    int time = 0;
    std::cout << "输入分数和时间，输出综合得分，分数核时间用空格隔开，比如：98 200" << std::endl;

    std::cout << "请输入家骏的分数和时间 " << std::endl;
    std::cin >> score >> time;
    std::cout << "家骏的综合得分 " << total_score(score,time) << std::endl;

    std::cout << std::endl;
    std::cout << "请输入家航的分数和时间 " << std::endl;
    std::cin >> score >> time;
    std::cout << "家航的综合得分 " << total_score(score,time) << std::endl;
    
    std::cout << std::endl;
    std::cout << "请输入爸爸的分数和时间 " << std::endl;
    std::cin >> score >> time;
    std::cout << "爸爸的综合得分 " << total_score(score,time) << std::endl;

    std::cout << std::endl;
    std::cout << "请输入妈妈的分数和时间 " << std::endl;
    std::cin >> score >> time;
    std::cout << "妈妈的综合得分 " << total_score(score,time) << std::endl;

    return 0;
}