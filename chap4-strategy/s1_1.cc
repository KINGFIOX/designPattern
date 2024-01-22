#include <iostream>

#include "Fighter.hxx"

using namespace std;

int main(void)
{
    /* 这里没有用工厂模式，因为只创建一个对象 */
    Fighter* prole_war = new F_Warrior(1000, 0, 200);

    prole_war->UseItem(LF_DHD);

    delete prole_war;
}