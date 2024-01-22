#ifndef __FIGHTER_H__
#define __FIGHTER_H__

#include <iostream>

class ItemStrategy; // 前向声明

/**
 * @brief 增加补充生命值道具
 *
 */
enum ItemAddLife {
    LF_BXD, // 补血丹
    LF_DHD, // 大还丹
    LF_SHD // 守护丹
};

/**
 * @brief 定义一个 Figter 父类
 *
 */
class Fighter {
public:
    Fighter(int life, int magic, int attack)
        : m_life(life)
        , m_magic(magic)
        , m_attack(attack)

    {
    }
    virtual ~Fighter() { } // 虚析构

public:
    /* 设置道具使用的策略 */
    void setItemStrategy(ItemStrategy* strategy);

    /* 使用道具 */
    void UseItem();

    /* 获取人物生命值 */
    int GetLife();

    /* 设置人物生命值 */
    void SetLife(int life);

protected:
    int m_life; // 生命值
    int m_magic; // 魔法值
    int m_attack; // 攻击力

    ItemStrategy* itemStrategy = nullptr; /* C++11中支持这样初始化 */
};

/**
 * @brief 战士子类
 *
 */
class F_Warrior : public Fighter {
public:
    /* 委托构造 */
    F_Warrior(int life = 1000, int magic = 0, int attack = 200)
        : Fighter(life, magic, attack)
    {
    }

private:
};

class F_Mage : public Fighter {
public:
    /* 委托构造 */
    F_Mage(int life = 500, int magic = 200, int attack = 200)
        : Fighter(life, magic, attack)
    {
    }
};

#endif