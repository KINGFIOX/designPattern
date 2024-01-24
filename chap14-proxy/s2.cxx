/**
 * @file s2.cxx 引入代理类
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
public:
    void visit() override
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
    void visit() override
    {
        /* 访问该购物网站，可能涉及复杂的网络通信 */
        cout << "访问 WebAddr_Video 购物网站!" << endl;
    };
};

/**
 * @brief 网站代理类，这个有点 状态模式 的感觉
 *
 */
class WebAddrProxy : public WebAddr {
public:
    WebAddrProxy(WebAddr* pwebAddr)
        : mp_webAddr(pwebAddr)
    {
    }

public:
    void visit() override
    {
        /* 可以在这行代码之前做很多事情，流量检查，访问合法性检查，日志记录 */

        mp_webAddr->visit();

        /* 可以在这里针对返回数据的过滤 */
    }

private:
    WebAddr* mp_webAddr; /* 代码要访问的网站 */
};

class WebAddr_Shopping_Proxy : public WebAddr {
public:
    void visit() override
    {
        WebAddr_Shopping* pwebAddr = new WebAddr_Shopping();
        pwebAddr->visit();
        delete pwebAddr;
    }
};

int main(void)
{
    WebAddr* web1 = new WebAddr_Shopping();
    WebAddr* web2 = new WebAddr_Video();

    WebAddrProxy* webPorxy1 = new WebAddrProxy(web1);
    WebAddrProxy* webPorxy2 = new WebAddrProxy(web2);

    web1->visit();
    cout << " ---------- ---------- " << endl;
    web2->visit();

    cout << " ---------- 通过代理 ---------- " << endl;

    webPorxy1->visit();
    webPorxy2->visit();

    cout << " ---------- 购物代理 ---------- " << endl;

    WebAddr* webSPorxy = new WebAddr_Shopping_Proxy();
    webSPorxy->visit();

    delete webSPorxy;

    delete webPorxy1;
    delete webPorxy2;

    delete web1;
    delete web2;

    return 0;
}