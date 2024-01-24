#include <iostream>

using namespace std;

/**
 * @brief 状态
 *
 */
enum MonsterState {
    MonS_Fer, /* 凶悍 */
    MonS_Worr, /* 不安 */
    MonS_Fear, /* 恐惧 */
    MonS_Dead, /* 死亡 */
};

class Monster {
public:
    Monster(int life)
        : m_life(500)
        , m_status(MonS_Fer)
    {
    }

public:
    /**
     * @brief 怪物被攻击
     *
     * @param power
     */
    void Attacked(int power)
    {
        m_life -= power;
        switch (m_status) {
        case MonS_Fer:
        case MonS_Fear:
        case MonS_Worr:
            if (m_life > 400) {
                cout << "怪物受到" << power << "点伤害并对主角进行疯狂的反击!" << endl;
                /* 处理其他动作逻辑，例如反击 */
                m_status = MonS_Fer;
            } else if (m_life <= 400 && m_life > 100) {
                cout << "怪物受到" << power << "点伤害并对主角反击! 并且召唤其他怪物!" << endl;
                m_status = MonS_Fear;
            } else if (m_life <= 100 && m_life > 0) {
                cout << "怪物受到" << power << "点伤害并开始逃跑!" << endl;
                m_status = MonS_Worr;
            } else {
                cout << "怪物受到" << power << "点伤害!怪物死亡!" << endl;
                m_status = MonS_Dead;
            }
            break;
        case MonS_Dead:
            cout << "怪物已经死亡，不能再被攻击!" << endl;
            break;
        default:
            break;
        }
    }

private:
    int m_life; /* 血量 */
    MonsterState m_status; /* 初始状态 */
};

int main(void)
{
    Monster m(500);
    cout << "怪物出生，当前处于凶悍状态，500点🩸!" << endl;

    m.Attacked(100);
    m.Attacked(120);
    m.Attacked(220);
    m.Attacked(100);
}