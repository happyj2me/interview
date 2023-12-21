#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
/**
求两个字符串的最长公共子串
问题：有两个字符串str和str2，求出两个字符串中最长公共子串长度。
比如：str=acbcbcef，str2=abcbced，则str和str2的最长公共子串为bcbce，最长公共子串长度为5。

算法思路：
1、把两个字符串分别以行和列组成一个二维矩阵。
2、比较二维矩阵中每个点对应行列字符中否相等，相等的话值设置为1，否则设置为0。
3、通过查找出值为1的最长对角线就能找到最长公共子串。

优化细节:
计算某个二维矩阵的值的时候顺便计算出来当前最长的公共子串的长度，
即某个二维矩阵元素的值由record[i][j]=1演变为record[i][j]=1 +record[i-1][j-1]，
这样就避免了后续查找对角线长度的操作了
 **/
string getLCS(string& str1,string& str2) {
    int maxLen = 0;
    int maxIdx = 0;
    vector<vector<int>> indexs(str1.length(),vector<int>(str2.length()));
    for(int i=0;i<str1.length();i++)
        for(int j=0;j<str2.length();j++) {
             if(str1[i] == str2[j]) {
                 if(i==0 || j==0){
                     indexs[i][j] = 1;
                 } else {
                     indexs[i][j] = indexs[i-1][j-1] +1;
                 }
             } else {
                  indexs[i][j] = 0;
             }
            if(maxLen < indexs[i][j]) {
                maxLen = indexs[i][j];
                maxIdx = i;
            }
        }
    return str1.substr(maxIdx-maxLen+1,maxLen);
};
/**
最大公共子序列:
和getLCS的区别在于，最大公共子序列不要该序列中的元素在原序列中具有连续性
 **/
string getLSS(string& str1,string& str2) {
    int maxLen = 0;
    int maxI = 0;
    int maxJ = 0;
    vector<vector<int>> indexs(str1.length(),vector<int>(str2.length()));
    for(int i=0;i<str1.length();i++)
        for(int j=0;j<str2.length();j++) {
             if(str1[i] == str2[j]) {
                 if(i==0 || j==0){
                     indexs[i][j] = 1;
                 } else {
                     int k=i-1,l=j-1;
                     while(k>0 && l>0){
                         if(indexs[k][l] > 0) {
                              break;
                         }
                         if(k>0)k--;
                         if(l>0)l--;
                     }
                    indexs[i][j] = indexs[k][l] +1;
                 }
             } else {
                  indexs[i][j] = 0;
            }
            if(maxLen < indexs[i][j]) {
                maxLen = indexs[i][j];
                maxI= i;
                maxJ = j;
            }
        }
    stringstream oss;
    int j=0;
    for(int i=0;i<=maxI && j<=maxJ;i++) {
         if(indexs[i][j] > 0) {
             oss << str1[i];
        }
        if(j<maxJ)j++;
    }
    return oss.str();
};
int main(int argc, char const *argv[])
{
    string str1 = "abcdedfdeafadwefef";
    string str2 = "abdecdaefeaoefewewe";
    cout << "str1 " << str1 << std::endl;
    cout << "str2 " << str2 << std::endl;
    cout << "longgest sub str is " << getLCS(str1,str2) << std::endl;
    cout << "longgest sub seq is " << getLSS(str1,str2) << std::endl;
    return 0;
}
