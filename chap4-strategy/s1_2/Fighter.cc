#include "Fighter.hxx"
#include "ItemStrategy.hxx"

#include <iostream>

using namespace std;

/**
 * @brief 设置道具使用的策略
 *
 * @param strategy
 */
void Fighter::setItemStrategy(ItemStrategy* strategy)
{
    itemStrategy = strategy;
}

/**
 * @brief 嗑药
 *
 */
void Fighter::UseItem()
{
    itemStrategy->UseItem(this);
}

/**
 * @brief 获取人物生命值
 *
 * @return int
 */
int Fighter::GetLife()
{
    return m_life;
}

/**
 * @brief
 *
 * @param life
 */
void Fighter::SetLife(int life)
{
    m_life = life;
}