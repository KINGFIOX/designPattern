/**
 * @file s1.cxx 单例模式
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

class GameConfig {
private:
    GameConfig();
    GameConfig(const GameConfig& tmpobj);
    GameConfig& operator=(const GameConfig& tmpobj);
    ~GameConfig();

public:
    static GameConfig* getInstance()
    {
        if (m_instance == nullptr) {
            m_instance = new GameConfig();
        }
        return m_instance;
    }

private:
    static GameConfig* m_instance; /* 指向本类对象的指针 */
};

/* 在类外，某个.cxx源文件的开头位置，为静态成员变量赋值（定义并赋值） */
GameConfig* GameConfig::m_instance = nullptr;

int main(void)
{
    GameConfig* g_gc = GameConfig::getInstance();

    /*
            无法创建出另一个对象
            无法析构对象
    */

    return 0;
}