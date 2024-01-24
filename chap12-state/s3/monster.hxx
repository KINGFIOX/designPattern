#ifndef __MONSTER_HXX__
#define __MONSTER_HXX__

#include <iostream>

class MonsterStatus; // 前向声明

/**
 * @brief 怪物类
 *
 */
class Monster {
public:
    Monster(int life);

    ~Monster();

public:
    int GetLife()
    {
        return m_life;
    }

    void SetLife(int life)
    {
        m_life = life;
    }

    MonsterStatus* GetCUrrentState()
    {
        return m_pStatus;
    }

    void SetCurrentState(MonsterStatus* pStatus)
    {
        m_pStatus = pStatus;
    }

    void Attacked(int power);

private:
    int m_life; /* 怪物生命 */
    MonsterStatus* m_pStatus; /* 持有状态对象 */
};

#endif