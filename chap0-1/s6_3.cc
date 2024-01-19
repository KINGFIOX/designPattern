#include <iostream>
using namespace std;

class A {
public:
    A() = default;

public:
    void func(const A& aobj)
    {
        *this = aobj;
        A obj2(aobj);
        return;
    }

private:
    A(const A& tmp);
    A& operator=(const A&);
};

int main(void)
{
    A aobj1;
    A aobj2;
    aobj1.func(aobj2);
    return 0;
}