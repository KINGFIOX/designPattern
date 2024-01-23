/**
 * @file s1.cxx 垃圾回收（饿汉模式）
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
    ~GameConfig() = default;

public:
    static GameConfig* getInstance()
    {
        return m_instance;
    }

private:
    /**
     * @brief 释放单例类引入的 GameConfig 类中的 嵌套类（垃圾回收） ++
     *
     */
    class Garbo {
    public:
        ~Garbo()
        {
            if (GameConfig::m_instance != nullptr) {
                delete GameConfig::m_instance;
                GameConfig::m_instance = nullptr;
            }
        }
    };

private:
    static GameConfig* m_instance; /* 指向本类对象的指针 */
    static Garbo garboObj; // ++
};

/* 编译时 创建对象 */
GameConfig* GameConfig::m_instance = new GameConfig();
GameConfig::Garbo GameConfig::garboObj;

int main(void)
{
    GameConfig* g_gc = GameConfig::getInstance();

    return 0;
}