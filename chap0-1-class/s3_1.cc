#include <iostream>
using namespace std;

class A { };
class B : public A { };
class C : public B { };

void myfunc(A tmpa)
{
    cout << "myfunc(A tmpa)执行了" << endl;
}

void myfunc(C tmpc)
{
    cout << "myfunc(C tmpc)执行了" << endl;
}

int main(void)
{
    B myobjB;
    myfunc(myobjB); // myfunc(A tmpa)执行了

    C myobjC;
    myfunc(myobjC); // myfunc(C tmpc)执行了
    return 0;
}
