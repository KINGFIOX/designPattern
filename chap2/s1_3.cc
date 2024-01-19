#include <iostream>
using namespace std;

/**
 * @brief 定义一个 Figter 父类
 *
 */
class Fighter {
public:
    Fighter(int life = 1000, int magic = 0, int attack = 200)
        : m_life(life)
        , m_magic(magic)
        , m_attack(attack)

    {
    }
    virtual ~Fighter() { } // 虚析构

public:
    void SKILL_Burn() /* 燃烧技能 */
    {
        if (canUseSKILL() == false) {
            return;
        }
        effect_enemy(); // 对敌人产生影响
        effect_self(); // 对主角自身产生影响
        burn_play(); // 播放技能 燃烧 的技能特效
    }

private:
    virtual void effect_enemy() = 0;
    virtual void effect_self() = 0;
    virtual bool canUseSKILL() = 0;

private:
    void burn_play()
    {
        /* 所有燃烧的效果 */
        cout << "播放技能特效：🔥 🔥 🔥" << endl;
    }

protected:
    int m_life; // 生命值
    int m_magic; // 魔法值
    int m_attack; // 攻击力
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
    void effect_enemy() override
    {
        cout << "让所有敌人失去500点生命，相关逻辑代码这里略......" << endl;
    }
    void effect_self() override
    {
        cout << "主角自身失去300点生命值" << endl;
        this->m_life -= 300;
    }
    bool canUseSKILL() override
    {
        if (this->m_life < 300) {
            return false;
        } else {
            return true;
        }
    }
};

class F_Mage : public Fighter {
public:
    /* 委托构造 */
    F_Mage(int life = 500, int magic = 200, int attack = 200)
        : Fighter(life, magic, attack)
    {
    }

private:
    void effect_enemy() override
    {
        cout << "让所有敌人失去500点生命，相关逻辑代码这里略......" << endl;
    }
    void effect_self() override
    {
        cout << "主角自身失去150点魔法值" << endl;
        this->m_magic -= 150;
    }
    bool canUseSKILL() override
    {
        if (this->m_magic < 100) {
            return false;
        } else {
            return true;
        }
    }
};

int main(void)
{
    F_Warrior mroleobj;
    mroleobj.SKILL_Burn();
    cout << "------------" << endl;
    F_Mage mage;
    mage.SKILL_Burn();
    cout << "------------" << endl;
    Fighter* p1 = new F_Warrior;
    p1->SKILL_Burn();
    cout << "------------" << endl;
    Fighter* p2 = new F_Mage;
    p2->SKILL_Burn();

    return 0;
}