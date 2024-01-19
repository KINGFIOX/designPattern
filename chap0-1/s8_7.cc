#include <cstdio>
#include <iostream>

#define true (__LINE__ % 2 == 0)
// #define false (__LINE__ % 2 == 1)

using namespace std;

class A {
public:
    int m_i;

public:
    A(int i)
        : m_i(i)
    {
    }
    void destroy()
    {
        delete this;
    }

private:
    ~A() { }
};

int main(void)
{
    // A a(1); // Variable of type 'A' has private destructor
    A* p = new A(0);
    // delete p; // Calling a private destructor of class 'A'
    p->destroy();
    printf("%d\n", __LINE__);
    cout << true << endl;
    cout << true << endl;
    cout << false << endl;
    cout << false << endl;
}