/**
 * @file s1.cxx 饿汉模式
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
        return m_instance;
    }

private:
    static GameConfig* m_instance; /* 指向本类对象的指针 */
};

/* 初始化就 创建对象 */
GameConfig* GameConfig::m_instance = new GameConfig();

int main(void)
{
    GameConfig* g_gc = GameConfig::getInstance();

    /*
            无法创建出另一个对象
            无法析构对象
    */

    return 0;
}