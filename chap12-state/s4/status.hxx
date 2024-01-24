#ifndef __STATE_HXX__
#define __STATE_HXX__

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

public:
    static MonsterStatus_Feroc* GetInstance()
    {
        static MonsterStatus_Feroc instance;
        return &instance;
    }
};

/**
 * @brief 不安状态
 *
 */
class MonsterStatus_Worr : public MonsterStatus {
public:
    virtual void Attacked(int power, Monster* mainObj) override;

public:
    static MonsterStatus_Worr* GetInstance()
    {
        static MonsterStatus_Worr instance;
        return &instance;
    }
};

/**
 * @brief 恐惧
 *
 */
class MonsterStatus_Fear : public MonsterStatus {
public:
    virtual void Attacked(int power, Monster* mainObj) override;

public:
    static MonsterStatus_Fear* GetInstance()
    {
        static MonsterStatus_Fear instance;
        return &instance;
    }
};

/**
 * @brief 死亡
 *
 */
class MonsterStatus_Dead : public MonsterStatus {
public:
    virtual void Attacked(int power, Monster* mainObj) override;

public:
    static MonsterStatus_Dead* GetInstance()
    {
        static MonsterStatus_Dead instance;
        return &instance;
    }
};

#endif