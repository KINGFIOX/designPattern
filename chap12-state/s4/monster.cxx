#include "monster.hxx"
#include "status.hxx"

using namespace std;

Monster::Monster(int life)
    : m_life(life)
{
    m_pStatus = MonsterStatus_Feroc::GetInstance();
}

Monster::~Monster()
{
}

void Monster::Attacked(int power)
{
    m_pStatus->Attacked(power, this);
}