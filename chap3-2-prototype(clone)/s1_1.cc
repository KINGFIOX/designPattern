/**
 * @file s1_1.cc 原型模式
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

public:
    virtual Monster* clone() = 0; // FIXME (1) (具体实现在子类中) (2) 命令为克隆(尊重习惯)

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

    // FIXME (3) 书写拷贝构造函数
    M_Undead(const M_Undead& tmpobj)
        : Monster(tmpobj)
    {
        cout << "调用了M_Undead::M_Undead(const M_Undead& tmpobj)拷贝构造函数创造了一只亡灵类怪物" << endl;
    }

    // FIXME (4) clone 中调用拷贝构造函数
    virtual Monster* clone() override
    {
        return new M_Undead(*this);
    }
};

class M_Element : public Monster {
public:
    M_Element(int life, int magic, int attack)
        : Monster(life, magic, attack)
    {
        cout << "一个 ⚡️ ⚡️ ⚡️ 来到了这个世界" << endl;
    }

    M_Element(const M_Element& tmpobj)
        : Monster(tmpobj)
    {
        cout << "调用了M_Element::M_Element(const M_Element& tmpobj)拷贝构造函数创造了一只元素类怪物" << endl;
    }

    virtual Monster* clone() override
    {
        return new M_Element(*this);
    }
};

class M_Mechanic : public Monster {
public:
    M_Mechanic(int life, int magic, int attack)
        : Monster(life, magic, attack)
    {
        cout << "一个 🤖 🤖 🤖 来到了这个世界" << endl;
    }

    M_Mechanic(const M_Mechanic& tmpobj)
        : Monster(tmpobj)
    {
        cout << "调用了M_Mechanic::M_Mechanic(const M_Mechanic& tmpobj)拷贝构造函数创造了一只机械类怪物" << endl;
    }

    virtual Monster* clone() override
    {
        return new M_Mechanic(*this);
    }
};

void Gbl_CreateMonster(Monster* pMonster)
{
    Monster* ptmpobj = nullptr;
    if (dynamic_cast<M_Undead*>(pMonster) != nullptr) {
        ptmpobj = new M_Undead(300, 50, 80);
    } else if (dynamic_cast<M_Element*>(pMonster) != nullptr) {
        ptmpobj = new M_Element(300, 50, 80);
    } else if (dynamic_cast<M_Mechanic*>(pMonster) != nullptr) {
        ptmpobj = new M_Element(300, 50, 80);
    }

    if (ptmpobj != nullptr) {
        // do something
    }
}

int main(void)
{
    M_Mechanic myPropMecMonst(400, 0, 110); // 创建一只机械类怪物对象作为原型对象以便用于克隆
    Monster* pPropEleMonster = new M_Element(200, 80, 100); // 创建一只元素类怪物对象作为原型对象以便用于克隆
                                                            // 这里可以直接new，也可以通过工厂模式创建原型对象

    Monster* p_CloneObj1 = myPropMecMonst.clone(); // FIXME (5) 使用原型对象克隆出新的机械类怪物对象
    Monster* p_CloneObj2 = pPropEleMonster->clone();

    delete p_CloneObj1;
    delete p_CloneObj2;
    delete pPropEleMonster;

    return 0;
}