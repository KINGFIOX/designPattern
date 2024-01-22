/**
 * @file s2.cxx 水果饮料
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
 * @brief 抽象饮料类
 *
 */
class Beverage {
public:
    virtual int GetPrice() = 0;
};

/**
 * @brief 水果饮料类
 *
 */
class FruitBeverage : public Beverage {
public:
    virtual int GetPrice() override
    {
        return 10; // 一杯单纯的水果饮料，10块钱
    }
};

/**
 * @brief 抽象装饰器类
 *
 */
class Decorator : public Beverage {
public:
    Decorator(Beverage* tmpbvg)
        : m_pbvg(tmpbvg)
    {
    }
    virtual int GetPrice() override
    {
        return m_pbvg->GetPrice();
    }

private:
    Beverage* m_pbvg;
};

/**
 * @brief 加入糖
 *
 */
class SugarDec : public Decorator {
public:
    SugarDec(Beverage* tmpbvg)
        : Decorator(tmpbvg)
    {
    }

    virtual int GetPrice() override
    {
        int price = Decorator::GetPrice();
        return price + 1; // 额外加多 1 块钱
    }
};

/**
 * @brief 加入牛奶
 *
 */
class MilkDec : public Decorator {
public:
    MilkDec(Beverage* tmpbvg)
        : Decorator(tmpbvg)
    {
    }

    virtual int GetPrice() override
    {
        int price = Decorator::GetPrice();
        return price + 2;
    }
};

/**
 * @brief 加入珍珠
 *
 */
class BubbleDec : public Decorator {
public:
    BubbleDec(Beverage* tmpbvg)
        : Decorator(tmpbvg)
    {
    }

    virtual int GetPrice() override
    {
        int price = Decorator::GetPrice();
        return price + 2;
    }
};

int main(void)
{
    // (1) 先创建一个本体
    Beverage* pFruit = new FruitBeverage();

    // (2) 加入糖
    Decorator* pFruit_s = new SugarDec(pFruit);

    // (3) 加入珍珠
    Decorator* pFruit_s_b = new SugarDec(pFruit_s);
    cout << pFruit_s_b->GetPrice() << endl;

    cout << "----------" << endl;

    // (4) 加入牛奶
    Decorator* pFruit_s_b_m = new SugarDec(pFruit_s_b);
    cout << pFruit_s_b_m->GetPrice() << endl;

    delete pFruit_s_b_m;
    delete pFruit_s_b;
    delete pFruit_s;
    delete pFruit;

    return 0;
}