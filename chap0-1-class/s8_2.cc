#include <iostream>

using namespace std;

class A {
public:
    void myfunc() /* 非虚拟接口 */
    {
        /* myfunc函数是myvirfunc函数的一行通道性质的代码 */
        myvirfunc();
    }
    virtual ~A() { }

private:
    virtual void myvirfunc()
    {
        cout << "A::myvirfunc()执行了!" << endl;
    }
};

class B : public A {
private:
    virtual void myvirfunc()
    {
        cout << "B::myvirfunc()执行了!" << endl;
    }
};

int main(void)
{
    A* paobj = new B();
    paobj->myfunc(); // B::myvirfunc()执行了!
    delete paobj;
}