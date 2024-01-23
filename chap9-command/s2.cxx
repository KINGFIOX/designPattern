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

int main(void)
{
    Cook* pcook = new Cook();

    // 有一种创建一个 便签的感觉，并且这个便签还指定了是哪一个厨师
    Command* pcmd1 = new CommandFish(pcook);
    pcmd1->Execute();

    Command* pcmd2 = new CommandMeat(pcook);
    pcmd2->Execute();

    delete pcmd2;
    delete pcmd1;
    delete pcook;

    return 0;
}