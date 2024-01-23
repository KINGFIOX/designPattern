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
    virtual ~Command() { } /* 做父类时析构函数为 虚函数 */
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
    /* 顾客把便签交给了服务员 */
    void SetCommand(Command* pcommand)
    {
        m_pcommand = pcommand;
    }

    /* 服务员将便签交给厨师，让厨师开始做菜 */
    void Notify()
    {
        m_pcommand->Execute();
    }

private:
    Command* m_pcommand; /* 服务员手中我这顾客书写菜品的便签 */
};

int main(void)
{
    Cook* pcook = new Cook();
    Waiter* pwaiter = new Waiter();

    /* 做红烧鱼 */
    Command* pcmd1 = new CommandFish(pcook); /* 顾客把菜品写在便签上，这里的顾客就是 main 了，客户端 */
    pwaiter->SetCommand(pcmd1); /* 顾客把便签交给服务员 */
    pwaiter->Notify(); /* 服务员把便签交给厨师 */

    /* 做锅包肉 */
    Command* pcmd2 = new CommandMeat(pcook);
    pwaiter->SetCommand(pcmd2);
    pwaiter->Notify();

    delete pcmd1;
    delete pcmd2;
    delete pwaiter;
    delete pcook;
    return 0;
}