#include <iostream>
using namespace std;

class A { };
class B : public A { };
class C : public B { };

void myfunc(A tmpa)
{
    cout << "myfunc(A tmpa)执行了" << endl;
}

void myfunc(B tmpB)
{
    cout << "myfunc(B tmpb)执行了" << endl;
}

int main(void)
{
    C myobjC;
    myfunc(myobjC); // myfunc(B tmpb)执行了
    return 0;
}
