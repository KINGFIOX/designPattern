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
    virtual void Attacked(int power, Monster* mainObj) override;
};

/**
 * @brief 不安状态
 *
 */
class MonsterStatus_Worr : public MonsterStatus {
public:
    virtual void Attacked(int power, Monster* mainObj) override;
};

/**
 * @brief 恐惧
 *
 */
class MonsterStatus_Fear : public MonsterStatus {
public:
    virtual void Attacked(int power, Monster* mainObj) override;
};

/**
 * @brief 死亡
 *
 */
class MonsterStatus_Dead : public MonsterStatus {
public:
    virtual void Attacked(int power, Monster* mainObj) override;
};

#endif