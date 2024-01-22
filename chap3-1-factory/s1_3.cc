/**
 * @file s1_3.cc 工厂方法模式
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

class M_Undead : public Monster {
public:
    M_Undead(int life, int magic, int attack)
        : Monster(life, magic, attack)
    {
        cout << "一个 👻 👻 👻 来到了这个世界" << endl;
    }
};

class M_Element : public Monster {
public:
    M_Element(int life, int magic, int attack)
        : Monster(life, magic, attack)
    {
        cout << "一个 ⚡️ ⚡️ ⚡️ 来到了这个世界" << endl;
    }
};

class M_Mechanic : public Monster {
public:
    M_Mechanic(int life, int magic, int attack)
        : Monster(life, magic, attack)
    {
        cout << "一个 🤖 🤖 🤖 来到了这个世界" << endl;
    }
};

class M_Beast : public Monster {
public:
    M_Beast(int life, int magic, int attack)
        : Monster(life, magic, attack)
    {
        cout << "一只 🐒 🐒 🐒 来到了这个世界" << endl;
    }
};

/**
 * @brief 父类，抽象类
 *
 */
class M_ParFactory {
public:
    virtual Monster* createMonster() = 0; /* 具体的实现在子类中进行 */
    virtual ~M_ParFactory() { } /* 做父类时，虚析构 */
};

/**
 * @brief 创建亡灵类怪物，怪物工厂
 *
 */
class M_UndeadFactory : public M_ParFactory {
public:
    virtual Monster* createMonster() override
    {
        return new M_Undead(300, 50, 80);
    }
};

/**
 * @brief 创建元素类怪物，怪物工厂
 *
 */
class M_ElementFactory : public M_ParFactory {
public:
    virtual Monster* createMonster() override
    {
        return new M_Element(100, 50, 80);
    }
};

/**
 * @brief 创建机械类怪物，怪物工厂
 *
 */
class M_MechanicFactory : public M_ParFactory {
public:
    virtual Monster* createMonster() override
    {
        return new M_Mechanic(350, 50, 80);
    }
};

// ++ 野兽类工厂 ++
class M_BeastFactory : public M_ParFactory {
public:
    virtual Monster* createMonster() override
    {
        return new M_Beast(350, 50, 80);
    }
};

template <typename T>
class M_ChildFactory : public M_ParFactory {
public:
    virtual Monster* createMonster() override
    {
        /* 但是这样就没法写出变化了 */
        return new T(300, 50, 80);
    }
};

/**
 * @brief 全局的，用于创建怪物对象的函数
 * 			这样，我所有的变化的部分，都只是在这个参数中体现了
 * @param factory 工厂父类型的指针
 * @return Monster* 怪物父类类型的指针
 */
Monster* Gbl_CreateMonster(M_ParFactory* factory)
{
    return factory->createMonster();
}

int main(void)
{
    /* 创建多态工厂 */
    M_ParFactory* p_eln_fy = new M_ElementFactory();
    /* 通过多态工厂创建怪物 */
    Monster* pM2 = Gbl_CreateMonster(p_eln_fy); /* 创建了一只元素类怪物 */

    /* 调用模板类 */
    M_ParFactory* p_udd_fy = new M_ChildFactory<M_Undead>;
    Monster* pM4 = p_udd_fy->createMonster();

    /* 释放资源 */
    delete pM2;
    delete p_eln_fy;
    delete pM4;
    delete p_udd_fy;
    return 0;
}