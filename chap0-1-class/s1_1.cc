#include <iostream>
using namespace std;

namespace _ns1 {
class A {
public:
    A()
    {
        this->m_i = 5;
        cout << "A::A()缺省构造函数执行了" << endl;
    }
    ~A()
    {
        cout << "A::A()析构函数执行了" << endl;
    }
    int m_i;
};

/*
class B {
public:
    static A m_sa;
};
A B::m_sa;
*/

class B {
public:
    inline static A m_sa;
};

};

int main(void)
{
    return 0;
}