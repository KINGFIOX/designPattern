#include <iostream>

#include "monster.hxx"
#include "status.hxx"

using namespace std;

Monster::Monster(int life)
    : m_life(life)
{
    m_pStatus = new MonsterStatus_Feroc;
}

Monster::~Monster()
{
    delete m_pStatus;
}

void Monster::Attacked(int power)
{
    m_pStatus->Attacked(power, this);
}