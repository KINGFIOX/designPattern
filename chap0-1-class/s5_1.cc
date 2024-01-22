#include <iostream>
using namespace std;

class Human {
public:
    virtual ~Human() { }
};

class Man : private Human {
public:
};

int main(void)
{
    Man mymen;
    Human& myhuman1 = mymen; // 父类引用绑定子类对象
    Human* myhuman2 = new Man; // 父类指针指向子类对象
}