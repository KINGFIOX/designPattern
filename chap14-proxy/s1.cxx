/**
 * @file s1.cxx 不引入代理类
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

using namespace std;

class WebAddr {
public:
    virtual void visit() = 0; /* 执行访问网站的动作 */
    virtual ~WebAddr() { } /* 做析构函数时 析构函数 应该为 虚函数 */
};

/**
 * @brief 某购物网站
 *
 */
class WebAddr_Shopping : public WebAddr {
    virtual void visit() override
    {
        /* 访问该购物网站，可能涉及复杂的网络通信 */
        cout << "访问 WebAddr_Shopping 购物网站!" << endl;
    };
};

/**
 * @brief 某视频网站
 *
 */
class WebAddr_Video : public WebAddr {
    virtual void visit() override
    {
        /* 访问该购物网站，可能涉及复杂的网络通信 */
        cout << "访问 WebAddr_Video 购物网站!" << endl;
    };
};

int main(void)
{
    WebAddr* web1 = new WebAddr_Shopping();
    WebAddr* web2 = new WebAddr_Video();

    web1->visit();
    cout << "---------- ----------" << endl;
    web2->visit();

    delete web1;
    delete web2;

    return 0;
}