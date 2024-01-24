#include <iostream>

#include "monster.hxx"
#include "status.hxx"

using namespace std;

void MonsterStatus_Feroc::Attacked(int power, Monster* mainObj)
{
    int orgLife = mainObj->GetLife();
    if ((orgLife - power) > 400) {
        mainObj->SetLife(orgLife - power);
        std::cout << "怪物处于凶悍状态中，对主角进行疯狂反击!" << std::endl;
        /* 处理其他动作逻辑 */
    } else {
        /* 不管下一个状态是啥，总之不是凶悍状态了，先无条件的转到不安状态 */
        delete mainObj->GetCUrrentState();
        mainObj->SetCurrentState(new MonsterStatus_Worr);
        mainObj->GetCUrrentState()->Attacked(power, mainObj);
    }
}

void MonsterStatus_Worr::Attacked(int power, Monster* mainObj)
{
    int orgLife = mainObj->GetLife();
    if ((orgLife - power) > 100) {
        mainObj->SetLife(orgLife - power);
        std::cout << "怪物处于不安状态中，对主角反击并呼唤支援!" << std::endl;
        /* 处理其他动作逻辑 */
    } else {
        /* 不管下一个状态是啥，总之不是凶悍状态了，先无条件的转到不安状态 */
        delete mainObj->GetCUrrentState();
        mainObj->SetCurrentState(new MonsterStatus_Fear);
        mainObj->GetCUrrentState()->Attacked(power, mainObj);
    }
}

void MonsterStatus_Fear::Attacked(int power, Monster* mainObj)
{
    int orgLife = mainObj->GetLife();
    if ((orgLife - power) > 0) {
        mainObj->SetLife(orgLife - power);
        std::cout << "怪物处于恐惧状态中，怪物逃跑!" << std::endl;
        /* 处理其他动作逻辑 */
    } else {
        /* 不管下一个状态是啥，总之不是凶悍状态了，先无条件的转到不安状态 */
        delete mainObj->GetCUrrentState();
        mainObj->SetCurrentState(new MonsterStatus_Dead);
        mainObj->GetCUrrentState()->Attacked(power, mainObj);
    }
}

void MonsterStatus_Dead::Attacked(int power, Monster* mainObj)
{
    std::cout << "怪物死亡!" << std::endl;
}