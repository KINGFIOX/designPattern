#include <cstdio>
#include <iostream>
#include <memory>

using namespace std;

int main(void)
{
    string str1 = "i love china";
    string str2 = str1;
    printf("str1所存储的字符串的地址=%p\n", str1.c_str());
    printf("str2所存储的字符串的地址=%p\n", str2.c_str());
    string str3 = "abc";
    string str4 = str3;
    printf("str3所存储的字符串的地址=%p\n", str3.c_str());
    printf("str4所存储的字符串的地址=%p\n", str4.c_str());
}
