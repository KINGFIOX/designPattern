/**
 * @file s2.cxx 观察者模式的实现
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
#include <map>
#include <utility>

using namespace std;

class Fighter; // 前向声明

/**
 * @brief 通知器父类
 *
 */
class Notifier {
public:
    virtual ~Notifier() = default;

public:
    virtual void addToList(Fighter* player) = 0; /* 把要被通知的玩家加入到列表中 */
    virtual void removeFromList(Fighter* player) = 0; /* 把不通知的玩家从列表中移除 */
    virtual void notify(Fighter* talker, string tmpContent) = 0; /* 通知的一些细节信息 */
};

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

    /* 获取家族 ID */
    int GetFamilyID()
    {
        return m_iFamilyID;
    }

public:
    void SayWords(string tmpContent, Notifier* notifier) // 玩家说了某句话
    {
        notifier->notify(this, tmpContent);
    }

public:
    // 通知该玩家接收到其他玩家发送来的信息，虚函数，子类可以覆盖以实现不同的功能
    virtual void NotifyWords(Fighter* otherPlayer, string tmpContent)
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

/**
 * @brief 聊天信息通知器
 *
 */
class TalkNotifier : public Notifier {
public:
    // 将玩家增加到家族列表中
    virtual void addToList(Fighter* player) override
    {
        int tmpFamilyID = player->GetFamilyID();
        if (tmpFamilyID != -1) {
            auto iter = m_familyList.find(tmpFamilyID);
            if (iter != m_familyList.end()) {
                // 如果家族已经注册过了，那么直接添加玩家即可
                iter->second.push_back(player);
            } else {
                list<Fighter*> tmpPlayerList;
                tmpPlayerList.push_back(player);
                m_familyList.insert(make_pair(player->GetFamilyID(), tmpPlayerList));
            }
        }
    }

    // 将玩家从家族列表中删除
    virtual void removeFromList(Fighter* player) override
    {
        int tmpFamilyID = player->GetFamilyID();
        if (tmpFamilyID != -1) {
            auto iter = m_familyList.find(player->GetFamilyID());
            if (iter != m_familyList.end()) {
                m_familyList[tmpFamilyID].remove(player);
            }
        }
    }

    // 家族中，某玩家说了句话，调用该函数来通知家族中所有人
    virtual void notify(Fighter* talker, string tmpContent)
    {
        int tmpFamilyID = talker->GetFamilyID();
        if (tmpFamilyID != -1) {
            auto iter = m_familyList.find(tmpFamilyID);
            if (iter != m_familyList.end()) {
                for (auto iter : m_familyList[tmpFamilyID]) {
                    // 同一个家族的其他玩家也应该收到聊天信息
                    iter->NotifyWords(talker, tmpContent);
                }
            }
        }
    }

private:
    // (familyID, 玩家列表)
    map<int, list<Fighter*>> m_familyList;
};

int main(void)
{
    Fighter* pplayerObj1 = new F_Warrior(10, "张三");
    pplayerObj1->setFamilyID(100);

    Fighter* pplayerObj2 = new F_Warrior(11, "李四");
    pplayerObj2->setFamilyID(100);

    Fighter* pplayerObj3 = new F_Warrior(12, "王五");
    pplayerObj3->setFamilyID(100);

    Fighter* pplayerObj4 = new F_Warrior(13, "赵六");
    pplayerObj4->setFamilyID(50);

    Notifier* pTalkNotify = new TalkNotifier();
    pTalkNotify->addToList(pplayerObj1);
    pTalkNotify->addToList(pplayerObj2);
    pTalkNotify->addToList(pplayerObj3);
    pTalkNotify->addToList(pplayerObj4);

    pplayerObj1->SayWords("我是傻逼", pTalkNotify);

    delete pTalkNotify;
    delete pplayerObj4;
    delete pplayerObj3;
    delete pplayerObj2;
    delete pplayerObj1;
}