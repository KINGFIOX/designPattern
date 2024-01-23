/**
 * @file s2.cxx 命令模式
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <list>

using namespace std;

/**
 * @brief 厨师类
 *
 */
class Cook {
public:
    void cook_fish()
    {
        cout << "做一盘红烧鱼菜品" << endl;
    }

    void cook_meat()
    {
        cout << "做一盘锅包肉菜品" << endl;
    }
};

/**
 * @brief 厨师做的每样菜品对应的抽象类
 *
 */
class Command {
public:
    Command(Cook* pcook)
    {
        m_pcook = pcook;
    }
    virtual ~Command()
    {
        if (m_pcook != nullptr) {
            delete m_pcook;
            m_pcook = nullptr;
        }
    }
    virtual void Execute() = 0; /* 函数名 国际惯例 */

protected:
    Cook* m_pcook;
};

/**
 * @brief 做红烧鱼菜品的命令
 *
 */
class CommandFish : public Command {
public:
    CommandFish(Cook* pcook)
        : Command(pcook)
    {
    }

    virtual void Execute() override
    {
        m_pcook->cook_fish();
    }
};

/**
 * @brief 做锅包肉菜品的命令
 *
 */
class CommandMeat : public Command {
public:
    CommandMeat(Cook* pcook)
        : Command(pcook)
    {
    }

    virtual void Execute() override
    {
        m_pcook->cook_meat();
    }
};

/**
 * @brief 服务员类
 *
 */
class Waiter {
public:
    /* 将顾客的便签增加到便签列表中，即便一个便签中包含多个菜品，这样相当于一道一道菜品加入到列表中 */
    void AddCommand(Command* pcommand)
    {
        m_commList.push_back(pcommand);
    }

    void AddCommand(list<Command*> li) /* 这我自己加的 */
    {
        m_commList.merge(li);
    }

    /* 如果顾客想要撤单，则将便签从列表中删除 */
    void DelCommand(Command* pcommand)
    {
        m_commList.remove(pcommand);
    }

    /* 服务员将所有便签一次性交到厨师手里，让厨师开始按顺序做菜 */
    void Notify()
    {
        for (auto v : m_commList) {
            v->Execute();
        }
    }

private:
    /* 为了达到：一个便签上有多道菜，一次搜集多个顾客的便签，一次性通知的效果 */
    list<Command*> m_commList;
};

int main(void)
{
    Waiter* pwaiter = new Waiter();

    Command* pcmd1 = new CommandFish(new Cook);
    Command* pcmd2 = new CommandMeat(new Cook);
    pwaiter->AddCommand({ pcmd1, pcmd2 });
    // pwaiter->AddCommand(pcmd1);
    // pwaiter->AddCommand(pcmd2);
    pwaiter->Notify();

    delete pwaiter;
    return 0;
}