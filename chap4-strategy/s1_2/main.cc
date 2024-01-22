#include "Fighter.hxx"
#include "ItemStrategy.hxx"
#include <iostream>

using namespace std;

int main(void)
{
    // (1) 创建主角（当然也可以用一个简单工厂模式啦）
    Fighter* prole_war = new F_Warrior(1000, 0, 200);

    // (2) 吃一颗大还丹
    ItemStrategy* strategy1 = new ItemStrategy_DHD(); // 创建一个大还丹策略
    prole_war->setItemStrategy(strategy1);
    prole_war->UseItem();

    // (3) 再吃一个补血丹
    ItemStrategy* strategy2 = new ItemStrategy_BXD();
    prole_war->setItemStrategy(strategy2);
    prole_war->UseItem();

    return 0;
}