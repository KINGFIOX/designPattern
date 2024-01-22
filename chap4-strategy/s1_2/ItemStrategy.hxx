#ifndef __ITEMSTRATEGY_H__
#define __ITEMSTRATEGY_H__

#include "Fighter.hxx"

/**
 * @brief
 *
 */
class ItemStrategy {
public:
    virtual void UseItem(Fighter* mainobj) = 0;
    virtual ~ItemStrategy() { }
};

/**
 * @brief 补血丹策略类
 *
 */
class ItemStrategy_BXD : public ItemStrategy {
public:
    /* 如果能够递归（继承）的设置为友元，那该有多好啊 */
    virtual void UseItem(Fighter* mainobj) override
    {
        mainobj->SetLife(mainobj->GetLife() + 200);
        std::cout << "主角吃 补血丹" << std::endl;
    }
};

/**
 * @brief 补血丹策略类
 *
 */
class ItemStrategy_DHD : public ItemStrategy {
public:
    virtual void UseItem(Fighter* mainobj) override
    {
        mainobj->SetLife(mainobj->GetLife() + 300);
        std::cout << "主角吃 大还丹" << std::endl;
    }
};

/**
 * @brief 补血丹策略类
 *
 */
class ItemStrategy_SHD : public ItemStrategy {
public:
    virtual void UseItem(Fighter* mainobj) override
    {
        mainobj->SetLife(mainobj->GetLife() + 500);
        std::cout << "主角吃 守护丹" << std::endl;
    }
};

#endif