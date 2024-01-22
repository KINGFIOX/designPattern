/**
 * @file s1_5.cc 抽象工厂模式（芭比娃娃不同厂商组装）
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

using namespace std;

/**
 * @brief 身体抽象类
 *
 */
class Body {
public:
    virtual void getName() = 0;
    virtual ~Body() { }
};

/**
 * @brief 衣服抽象类
 *
 */
class Clothes {
public:
    virtual void getName() = 0;
    virtual ~Clothes() { }
};

/**
 * @brief 鞋子抽象类
 *
 */
class Shoes {
public:
    virtual void getName() = 0;
    virtual ~Shoes() { }
};

// ---------- 抽象工厂类 ----------

/**
 * @brief 所创建的部件应该稳定的保持这三个部件
 *
 */
class AbstractFactory {
public:
    // 所创建的部件应该满足这三个部件，才适合抽象工厂模式
    virtual Body* createBody() = 0;
    virtual Clothes* createClothes() = 0;
    virtual Shoes* createShoes() = 0;
    virtual ~AbstractFactory() { }
};

/**
 * @brief 芭比娃娃类
 *
 */
class BarbieDoll {
public:
    // 构造函数
    BarbieDoll(Body* tmpbody, Clothes* tmpclothes, Shoes* tmpshoes)
        : body(tmpbody)
        , clothes(tmpclothes)
        , shoes(tmpshoes)
    {
    }

    // 组装
    void Assemble()
    {
        cout << "成功组装了一个芭比娃娃" << endl;
        body->getName();
        clothes->getName();
        shoes->getName();
    }

private:
    Body* body;
    Clothes* clothes;
    Shoes* shoes;
};

// ---------- 中国厂商实现的三个部件 ----------

class China_Body : public Body {
public:
    virtual void getName()
    {
        cout << "中国厂商生产的_身体部件" << endl;
    }
};

class China_Clothes : public Clothes {
public:
    virtual void getName()
    {
        cout << "中国厂商生产的_衣服部件" << endl;
    }
};

class China_Shoes : public Shoes {
public:
    virtual void getName()
    {
        cout << "中国厂商生产的_鞋子部件" << endl;
    }
};

// ---------- 创建一个中国工厂 ----------
class ChinaFactory : public AbstractFactory {
public:
    virtual Body* createBody()
    {
        return new China_Body;
    }
    virtual Clothes* createClothes()
    {
        return new China_Clothes;
    }
    virtual Shoes* createShoes()
    {
        return new China_Shoes;
    }
    virtual ~ChinaFactory() { }
};

// ---------- 日本厂商实现的三个部件  ----------

class Japan_Body : public Body {
public:
    virtual void getName()
    {
        cout << "日本厂商生产的_身体部件" << endl;
    }
};

class Japan_Clothes : public Clothes {
public:
    virtual void getName()
    {
        cout << "日本厂商生产的_衣服部件" << endl;
    }
};

class Japan_Shoes : public Shoes {
public:
    virtual void getName()
    {
        cout << "日本厂商生产的_鞋子部件" << endl;
    }
};

// ---------- 创建一个日本工厂 ----------
class JapanFactory : public AbstractFactory {
public:
    virtual Body* createBody()
    {
        return new Japan_Body;
    }
    virtual Clothes* createClothes()
    {
        return new Japan_Clothes;
    }
    virtual Shoes* createShoes()
    {
        return new Japan_Shoes;
    }
    virtual ~JapanFactory() { }
};

// ---------- 美国厂商实现的三个部件  ----------

class America_Body : public Body {
public:
    virtual void getName()
    {
        cout << "美国厂商生产的_身体部件" << endl;
    }
};

class America_Clothes : public Clothes {
public:
    virtual void getName()
    {
        cout << "美国厂商生产的_衣服部件" << endl;
    }
};

class America_Shoes : public Shoes {
public:
    virtual void getName()
    {
        cout << "美国厂商生产的_鞋子部件" << endl;
    }
};

// ---------- 创建一个美国工厂 ----------
class AmericaFactory : public AbstractFactory {
public:
    virtual Body* createBody()
    {
        return new America_Body;
    }
    virtual Clothes* createClothes()
    {
        return new America_Clothes;
    }
    virtual Shoes* createShoes()
    {
        return new America_Shoes;
    }
    virtual ~AmericaFactory() { }
};

int main(void)
{
    cout << "---------- 创建第一个芭比娃娃 ----------" << endl;

    // (1)创建一个中国工厂
    AbstractFactory* pChinaFactory = new ChinaFactory();

    // (2)创建中国生产的各种部件
    Body* pChinaBody = pChinaFactory->createBody();
    Clothes* pChinaClothes = pChinaFactory->createClothes();
    Shoes* pChinaShoes = pChinaFactory->createShoes();

    // (3)创建芭比娃娃
    BarbieDoll* pbd1obj = new BarbieDoll(pChinaBody, pChinaClothes, pChinaShoes);
    pbd1obj->Assemble();

    cout << "---------- 创建第二个芭比娃娃 ----------" << endl;

    // ---------- 创建第二个芭比娃娃 ----------

    // (1)创建另外两个工厂：日本工厂、美国工厂
    AbstractFactory* pJapanFactory = new JapanFactory;
    AbstractFactory* pAmericaFactory = new AmericaFactory;

    // (2)中国身体、日本衣服、鞋子美国
    Clothes* pJapanClothes = pJapanFactory->createClothes();
    Shoes* pAmericaShoes = pAmericaFactory->createShoes();

    // (3)组装芭比娃娃
    BarbieDoll* pbd2obj = new BarbieDoll(pChinaBody, pJapanClothes, pAmericaShoes);
    pbd2obj->Assemble();

    // ---------- 最后释放内存 ----------
    delete pChinaFactory;
    delete pJapanFactory;
    delete pAmericaFactory;
    delete pChinaBody;
    delete pChinaClothes;
    delete pChinaShoes;
    delete pbd1obj;
    delete pbd2obj;
    delete pJapanClothes;
    delete pAmericaShoes;

    return 0;
}
