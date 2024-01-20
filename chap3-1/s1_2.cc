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

/**
 * @brief 怪物工厂类
 *
 */
class MonsterFactory {
public:
    Monster* createMonster(string strmontype)
    {
        Monster* ptrnobj = nullptr;
        // 笑了，c++的switch没有匹配字符串
        if (strmontype == "udd") { /* 代表创建亡灵类 */
            ptrnobj = new M_Undead(300, 50, 80);
        } else if (strmontype == "ele") {
            ptrnobj = new M_Element(200, 80, 100);
        } else if (strmontype == "mon") {
            ptrnobj = new M_Mechanic(400, 0, 110);
        }
        return ptrnobj;
    }
};

int main(void)
{
    MonsterFactory facobj;
    Monster* pM1 = facobj.createMonster("udd"); /* 创建了一个亡灵 */
    Monster* pM2 = facobj.createMonster("ele"); /* 创建了一个元素 */
    Monster* pM3 = facobj.createMonster("mon"); /* 创建了一个机械 */

    delete pM1;
    delete pM2;
    delete pM3;
}