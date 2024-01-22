#include <iostream>
using namespace std;

class A {
public:
    A() = default;
    A(const A& tmp) = delete;
    A& operator=(const A&) = delete;
};

int main(void)
{
    A aobj1;
    A aobj2(aobj1); // call to deleted constructor of 'A'
    A aobj3;
    aobj3 = aobj2; // overload resolution selected deleted operator '='
    return 0;
}