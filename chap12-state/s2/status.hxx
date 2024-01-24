#ifndef __STATE_HXX__
#define __STATE_HXX__

#include <iostream>

class Monster; // 类前向声明

/**
 * @brief 抽象类，状态
 *
 */
class MonsterStatus {
public:
    virtual void Attacked(int power, Monster* mainObj) = 0;
    virtual ~MonsterStatus() { }
};

/**
 * @brief 凶悍
 *
 */
class MonsterStatus_Feroc : public MonsterStatus {
public:
    virtual void Attacked(int power, Monster* mainObj) override
    {
        std::cout << "怪物处于凶悍状态中，对主角进行疯狂反击!" << std::endl;
    }
};

/**
 * @brief 不安状态
 *
 */
class MonsterStatus_Worr : public MonsterStatus {
public:
    virtual void Attacked(int power, Monster* mainObj) override
    {
        std::cout << "怪物处于不安状态中，对主角反击并呼唤支援!" << std::endl;
    }
};

/**
 * @brief 恐惧
 *
 */
class MonsterStatus_Fear : public MonsterStatus {
public:
    virtual void Attacked(int power, Monster* mainObj) override
    {
        std::cout << "怪物处于恐惧状态中，处于逃跑之中!" << std::endl;
    }
};

/**
 * @brief 死亡
 *
 */
class MonsterStatus_Dead : public MonsterStatus {
public:
    virtual void Attacked(int power, Monster* mainObj) override
    {
        std::cout << "怪物死亡!" << std::endl;
    }
};

#endif