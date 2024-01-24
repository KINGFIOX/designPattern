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
    int orgLife = m_life; /* 站村原来怪物的血量，用于后续比较 */
    m_life -= power;
    if (orgLife > 400) {
        if (m_life > 400) {
            /* 状态不变 */
            m_pStatus->Attacked(power, this); /* 其他逻辑代码被 Monster 类 委托给了 具体状态类 来处理 */
        } else if (m_life > 100) {
            /* 不安 */
            delete m_pStatus;
            m_pStatus = new MonsterStatus_Worr;
            m_pStatus->Attacked(power, this);
        } else if (m_life > 0) {
            /* 恐惧 */
            delete m_pStatus;
            m_pStatus = new MonsterStatus_Fear;
            m_pStatus->Attacked(power, this);
        } else {
            /* 死亡 */
            delete m_pStatus;
            m_pStatus = new MonsterStatus_Dead;
            m_pStatus->Attacked(power, this);
        }
    } else if (orgLife > 100) {
        if (m_life > 100) {
            /* 不安 */
            m_pStatus->Attacked(power, this);
        } else if (m_life > 0) {
            /* 恐惧 */
            delete m_pStatus;
            m_pStatus = new MonsterStatus_Fear;
            m_pStatus->Attacked(power, this);
        } else {
            /* 死亡 */
            delete m_pStatus;
            m_pStatus = new MonsterStatus_Dead;
            m_pStatus->Attacked(power, this);
        }
    } else if (orgLife > 0) {
        if (m_life > 0) {
            /* 恐惧 */
            m_pStatus->Attacked(power, this);
        } else {
            /* 死亡 */
            delete m_pStatus;
            m_pStatus = new MonsterStatus_Dead;
            m_pStatus->Attacked(power, this);
        }
    } else {
        m_pStatus->Attacked(power, this);
    }
}