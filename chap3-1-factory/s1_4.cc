/**
 * @file s1_4.cc 抽象工厂模式，不同场景的不同怪物
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

using namespace std;

class Monster {
public:
    Monster(int life, int magic, int attack)
        : m_attack(attack)
        , m_life(life)
        , m_magic(magic)
    {
    }
    virtual ~Monster() { }

protected:
    int m_attack;
    int m_life;
    int m_magic;
};

// ---------------- 抽象工厂 ----------------

/* 沼泽 */
class M_Undead_Swamp : public Monster {
public:
    M_Undead_Swamp(int life, int magic, int attack)
        : Monster(life, magic, attack)
    {
        cout << "一个 沼泽的 亡灵类 怪物来到了游戏世界" << endl;
    }
};

class M_Element_Swamp : public Monster {
public:
    M_Element_Swamp(int life, int magic, int attack)
        : Monster(life, magic, attack)
    {
        cout << "一个 沼泽的 元素类 怪物来到了游戏世界" << endl;
    }
};

class M_Mechanic_Swamp : public Monster {
public:
    M_Mechanic_Swamp(int life, int magic, int attack)
        : Monster(life, magic, attack)
    {
        cout << "一个 沼泽的 机械类 怪物来到了游戏世界" << endl;
    }
};

/* 山脉 */
class M_Undead_Mount : public Monster {
public:
    M_Undead_Mount(int life, int magic, int attack)
        : Monster(life, magic, attack)
    {
        cout << "一个 山脉的 亡灵类 怪物来到了游戏世界" << endl;
    }
};

class M_Element_Mount : public Monster {
public:
    M_Element_Mount(int life, int magic, int attack)
        : Monster(life, magic, attack)
    {
        cout << "一个 山脉的 元素类 怪物来到了游戏世界" << endl;
    }
};

class M_Mechanic_Mount : public Monster {
public:
    M_Mechanic_Mount(int life, int magic, int attack)
        : Monster(life, magic, attack)
    {
        cout << "一个 山脉的 机械类 怪物来到了游戏世界" << endl;
    }
};

/* 城镇 */
class M_Undead_Town : public Monster {
public:
    M_Undead_Town(int life, int magic, int attack)
        : Monster(life, magic, attack)
    {
        cout << "一个 城镇的 亡灵类 怪物来到了游戏世界" << endl;
    }
};

class M_Element_Town : public Monster {
public:
    M_Element_Town(int life, int magic, int attack)
        : Monster(life, magic, attack)
    {
        cout << "一个 城镇的 元素类 怪物来到了游戏世界" << endl;
    }
};

class M_Mechanic_Town : public Monster {
public:
    M_Mechanic_Town(int life, int magic, int attack)
        : Monster(life, magic, attack)
    {
        cout << "一个 城镇的 机械类 怪物来到了游戏世界" << endl;
    }
};

// -------------- 创建一个工厂父类和三个工厂子类 --------------

/**
 * @brief 工厂父类
 *
 */
class M_ParFactory {
public:
    virtual Monster* createMonster_Undead() = 0;
    virtual Monster* createMonster_Element() = 0;
    virtual Monster* createMonster_Mechanic() = 0;

    virtual ~M_ParFactory() { } // 虚析构函数
};

class M_Factory_Swamp : public M_ParFactory {
public:
    virtual Monster* createMonster_Undead() override
    {
        return new M_Undead_Swamp(300, 50, 120);
    }
    virtual Monster* createMonster_Element() override
    {
        return new M_Undead_Swamp(300, 50, 120);
    }
    virtual Monster* createMonster_Mechanic() override
    {
        return new M_Undead_Swamp(300, 50, 120);
    }
};

class M_Factory_Mount : public M_ParFactory {
public:
    virtual Monster* createMonster_Undead() override
    {
        return new M_Undead_Mount(300, 50, 120);
    }
    virtual Monster* createMonster_Element() override
    {
        return new M_Undead_Mount(300, 50, 120);
    }
    virtual Monster* createMonster_Mechanic() override
    {
        return new M_Undead_Mount(300, 50, 120);
    }
};

class M_Factory_Town : public M_ParFactory {
public:
    virtual Monster* createMonster_Undead() override
    {
        return new M_Undead_Town(300, 50, 120);
    }
    virtual Monster* createMonster_Element() override
    {
        return new M_Undead_Town(300, 50, 120);
    }
    virtual Monster* createMonster_Mechanic() override
    {
        return new M_Undead_Town(300, 50, 120);
    }
};

int main(void)
{
    M_ParFactory* p_mou_fy = new M_Factory_Mount(); /* 创建多态工厂 */
    Monster* pMU = p_mou_fy->createMonster_Undead();
    delete pMU;
    delete p_mou_fy;
    return 0;
}