/**
 * @file s1.cxx 备忘录模式初步
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

using namespace std;

/**
 * @brief 玩家主角相关的 备忘录类
 *
 */
class FighterMemento {
private:
    /* 构造函数，用 private 修饰，以防止在外部被随意创建 */
    FighterMemento(int life, int magic, int attack)
        : m_life(life)
        , m_magic(magic)
        , m_attack(attack)
    {
    }
    friend class Fighter; /* 友元，可以访问私有成员函数 */

private:
    int getLife() const { return m_life; }
    void setLife(int life) { m_life = life; }
    int getMagic() const { return m_magic; }
    void setMagic(int magic) { m_magic = magic; }
    int getAttack() const { return m_attack; }
    void setAttack(int attack) { m_attack = attack; }

private:
    /* 玩家要保存的数据 */
    int m_life; /* 生命值 */
    int m_magic; /* 魔法值 */
    int m_attack; /* 攻击力 */
};

/**
 * @brief 玩家主角类
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

public:
    /* 将玩家数据写入备忘录 */
    FighterMemento* createMemento()
    {
        return new FighterMemento(m_life, m_magic, m_attack);
    }

    /* 从备忘录中恢复玩家数据 */
    void restoreMemento(FighterMemento* pfm)
    {
        m_life = pfm->getLife();
        m_magic = pfm->getMagic();
        m_attack = pfm->getAttack();
    }

#if 1 /* 测试代码 */
    void setToDead()
    {
        m_life = 0;
    }

    void displayInfo()
    {
        cout << "玩家当前的生命值: " << m_life << endl;
        cout << "玩家当前的魔法值: " << m_magic << endl;
        cout << "玩家当前的攻击力: " << m_attack << endl;
    }
#endif

private:
    int m_life; /* 生命值 */
    int m_magic; /* 魔法值 */
    int m_attack; /* 攻击力 */
};

int main(void)
{
    // (1) 创建玩家
    Fighter* p_fighter = new Fighter(800, 200, 300);

    // (2) 展示玩家信息
    p_fighter->displayInfo();

    // (3) 保存当前游戏进度
    FighterMemento* p_fm = p_fighter->createMemento();

    // (4) 玩家与 boss 开始战斗
    cout << "---------- 玩家与 boss 开始战斗 ---------- " << endl;

    // (5) 玩家被 boss 揍4️⃣了
    p_fighter->setToDead();
    cout << "---------- 玩家被 boss 揍4️⃣了 ---------- " << endl;
    p_fighter->displayInfo();

    // (6) 恢复玩家主角对象数据
    p_fighter->restoreMemento(p_fm);
    cout << "---------- 恢复检查点 ---------- " << endl;
    p_fighter->displayInfo();

    return 0;
}