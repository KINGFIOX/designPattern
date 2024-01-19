#include <iostream>
using namespace std;

class A {
public:
    void funca()
    {
        cout << "funca()被调用了" << endl;
    }
};

class B {
public:
    B(A* tmpa)
        : m_pa(tmpa)
    {
    }
    void funcb()
    {
        m_pa->funca();
    }

private:
    A* m_pa;
};

int main(void)
{
    A* pa = new A;
    B* pb = new B(pa);

    pb->funcb(); // funca()被调用了

    delete pa;
    delete pb;
}