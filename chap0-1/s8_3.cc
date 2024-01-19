#include <iostream>

using namespace std;

class ANew {
public:
    ANew()
    {
        f1();
    }
    virtual ~ANew()
    {
        f2();
    }

    virtual void f1()
    {
        cout << "虚函数ANew::f1()执行了" << endl;
    }
    virtual void f2()
    {
        cout << "虚函数ANew::f2()执行了" << endl;
    }

    // 定义普通成员函数，调用虚函数
    void AClassFunc()
    {
        f1();
    }
};

class BNew : public ANew {
public:
    BNew()
    {
        f1();
    }
    virtual ~BNew()
    {
        f2();
    }

    virtual void f1()
    {
        cout << "虚函数BNew::f1()执行了" << endl;
    }
    virtual void f2()
    {
        cout << "虚函数BNew::f2()执行了" << endl;
    }

    // 定义普通成员函数，调用虚函数
    void BClassFunc()
    {
        f1();
    }
};

int main(void)
{
    ANew* pbnew = new BNew();

    cout << "----------"
         << "begin"
         << "----------" << endl;
    pbnew->f1();
    pbnew->f2();
    pbnew->AClassFunc();
    cout << "----------"
         << "end"
         << "----------" << endl;

    delete pbnew;
}