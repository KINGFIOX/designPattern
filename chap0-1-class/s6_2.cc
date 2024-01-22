#include <iostream>
using namespace std;

class A {
public:
    A() = default;
    A(const A& tmp) = default;

private:
    A& operator=(const A&) = default;
};

int main(void)
{
    A aobj1;
    A aobj2(aobj1);
    A aobj3;
    aobj3 = aobj2; // 'operator=' is a private member of 'A'
    return 0;
}