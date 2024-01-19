#include <iostream>

using namespace std;

class A {
private:
    int m_a;
    long cnt;

public:
    A()
        : m_a(0)
        , cnt(0) {};
    int& getA()
    {
        this->cnt++;
        return this->m_a;
    }
    long getCNT()
    {
        return this->cnt;
    };
};

int main(void)
{
    A aobj1;
    aobj1.getA() = 5;
    cout << aobj1.getA() << endl;
    cout << aobj1.getCNT() << endl;
}