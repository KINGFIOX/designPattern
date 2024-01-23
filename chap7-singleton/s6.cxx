/**
 * @file s1.cxx 单例模式的另一种实现方式（饿汉模式）
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <mutex>

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
        return &m_instance;
    }

private:
    static GameConfig m_instance;
};

/* 饿汉模式 */
GameConfig GameConfig::m_instance;

int main(void)
{
    GameConfig* g_gc = GameConfig::getInstance();

    /*
            无法创建出另一个对象
            无法析构对象
    */

    return 0;
}