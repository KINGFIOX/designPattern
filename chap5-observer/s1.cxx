/**
 * @file s1.cxx 不好的实现
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <list>

using namespace std;

class Fighter; // 前向声明

list<Fighter*> g_playerList; // 每个玩家来到游戏以后，加入列表中

/**
 * @brief 玩家类
 *
 */
class Fighter {
public:
    Fighter(int tmpID, string tmpName)
        : m_iPlayerID(tmpID)
        , m_sPlayerName(tmpName)
    {
    }

    virtual ~Fighter() { } // 虚析构，因为有不同职业

public:
    /* 加入家族的时候，设置家族 ID */
    void setFamilyID(int tmpID)
    {
        this->m_iFamilyID = tmpID;
    }

public:
    void SayWords(string tmpContent) // 玩家说了某句话
    {
        if (this->m_iFamilyID != -1) {
            // 该玩家属于某个家族，应该把聊天信息传送给家族的其他玩家
            for (auto iter : g_playerList) {
                if (this->m_iFamilyID == iter->m_iFamilyID) {
                    // 同一个家族的其他玩家也应该收到聊天信息
                    NotifyWords(iter, tmpContent);
                }
            }
        }
    }

private:
    // 其他玩家收到了当前玩家的聊天信息
    void NotifyWords(Fighter* otherPlayer, string tmpContent)
    {
        cout << "玩家: " << otherPlayer->m_sPlayerName
             << "收到了玩家: " << this->m_sPlayerName
             << "发送的聊天信息: " << tmpContent << endl;
    }

private:
    int m_iPlayerID; /* 玩家id */
    string m_sPlayerName; /* 玩家名字 */
    int m_iFamilyID { -1 }; /* 家族ID */
};

/**
 * @brief 战士类
 *
 */
class F_Warrior : public Fighter {
public:
    F_Warrior(int tmpID, string tmpName)
        : Fighter(tmpID, tmpName)
    {
    }
};

/**
 * @brief 法师类
 *
 */
class F_Mage : public Fighter {
public:
    F_Mage(int tmpID, string tmpName)
        : Fighter(tmpID, tmpName)
    {
    }
};

int main(void)
{
    Fighter* pplayerObj1 = new F_Warrior(10, "张三");
    pplayerObj1->setFamilyID(100);
    g_playerList.push_back(pplayerObj1);

    Fighter* pplayerObj2 = new F_Warrior(11, "李四");
    pplayerObj2->setFamilyID(100);
    g_playerList.push_back(pplayerObj2);

    Fighter* pplayerObj3 = new F_Warrior(12, "王五");
    pplayerObj3->setFamilyID(100);
    g_playerList.push_back(pplayerObj3);

    Fighter* pplayerObj4 = new F_Warrior(13, "赵六");
    pplayerObj4->setFamilyID(50);
    g_playerList.push_back(pplayerObj4);

    // 当某个玩家聊天的时候，同族人都应该收到该信息
    pplayerObj1->SayWords("我是傻逼");

    delete pplayerObj4;
    delete pplayerObj3;
    delete pplayerObj2;
    delete pplayerObj1;
}