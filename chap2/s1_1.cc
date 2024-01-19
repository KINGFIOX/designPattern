#include <iostream>
using namespace std;

/**
 * @brief 定义一个 战士类
 *
 */
class Warrior {
public:
    Warrior(int life = 1000, int magic = 0, int attack = 200)
        : m_life(life)
        , m_magic(magic)
        , m_attack(attack)

    {
    }

public:
    void SKILL_Burn() /* 燃烧技能 */
    {
        cout << "让所有敌人失去500点生命，相关逻辑代码这里略......" << endl;
        cout << "主角自身失去300点生命值" << endl;
        this->m_life -= 300;
        cout << "播放技能“燃烧”的技能特效给玩家看" << endl;
    }

private:
    int m_life; // 生命值
    int m_magic; // 魔法值
    int m_attack; // 攻击力
};

int main(void)
{
    Warrior mroleobj;
    mroleobj.SKILL_Burn();
    return 0;
}