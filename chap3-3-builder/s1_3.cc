/**
 * @file s1_1.cc 构建者模式（改了），把 Assemble 单独拆到一个新类中（指挥者类），并改名为 Construct
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

using namespace std;

class Monster {
public:
    virtual ~Monster() { } /* 做父类时析构函数应该为虚函数 */
};

class M_Undead : public Monster { };

class M_Element : public Monster { };

class M_Mechanic : public Monster { };

/**
 * @brief 构建器类
 *
 */
class MonsterBuilder {
public:
    virtual ~MonsterBuilder() { }
    virtual void LoadTrunkModel(string strNo) = 0; /* 驱干 */
    virtual void LoadHeadModel(string strNo) = 0; /* 头 */
    virtual void LoadLimbsModel(string strNo) = 0; /* 四肢 */

    /* 返回指向Monster类的成员变量指针m_pMonster，
                当一个复杂的对象构建完成后，可以通过该成员函数把对象返回 */
    Monster* GetResult()
    {
        return m_pMonster;
    }

protected:
    Monster* m_pMonster; /* 指向Monster类的成员变量指针 */
};

/**
 * @brief 指挥者类
 *
 */
class MonsterDirector {
public:
    MonsterDirector(MonsterBuilder* ptmpBuilder) /* 构造函数 */
    {
        m_pMonsterBuilder = ptmpBuilder;
    }

    void SetBuilder(MonsterBuilder* ptmpBuilder) /* 指定新的构建器 */
    {
        m_pMonsterBuilder = ptmpBuilder;
    }

    Monster* Construct(string strModelNo) /* 参数：模型编号，有点模板方法的感觉 */
    {
        /* 载入躯干模型。截取字符，从第4个开始，截取3个字符 */
        m_pMonsterBuilder->LoadTrunkModel(strModelNo.substr(4, 3));

        /* 载入头部模型。并挂接到躯干模型上 */
        m_pMonsterBuilder->LoadHeadModel(strModelNo.substr(7, 3));

        /* 载入四肢模型。并挂接到躯干模型上 */
        m_pMonsterBuilder->LoadLimbsModel(strModelNo.substr(10, 3));

        /* 返回构建后的父类 */
        return m_pMonsterBuilder->GetResult();
    }

private:
    /* 指向所有构建器类父类的指针 */
    MonsterBuilder* m_pMonsterBuilder;
};

/**
 * @brief 亡灵类怪物构建器
 *
 */
class M_UndeadBuilder : public MonsterBuilder {
public:
    M_UndeadBuilder()
    {
        m_pMonster = new M_Undead();
    }

    virtual void LoadTrunkModel(string strNo)
    {
        cout << "载入亡灵类怪物的躯干部位模型，需要调用m_pMonster类或其父类中其他诸多成员函数，逻辑代码略..." << endl;
        /* 读文件啊，之类的 */
    }

    virtual void LoadHeadModel(string strNo)
    {
        cout << "载入亡灵类怪物的头部位模型，需要调用m_pMonster类或其父类中其他诸多成员函数，逻辑代码略..." << endl;
        /* 读文件啊，之类的 */
    }

    virtual void LoadLimbsModel(string strNo)
    {
        cout << "载入亡灵类怪物的四肢部位模型，需要调用m_pMonster类或其父类中其他诸多成员函数，逻辑代码略..." << endl;
    }
};

/**
 * @brief
 *
 */
class M_ElementBuilder : public MonsterBuilder {
public:
    M_ElementBuilder()
    {
        m_pMonster = new M_Element();
    }
    virtual void LoadTrunkModel(string strNo)
    {
        cout << "载入元素类怪物的躯干部位模型，需要调用M_Element类或其父类中其他诸多成员函数，逻辑代码略..." << endl;
        /* 读文件啊，之类的 */
    }

    virtual void LoadHeadModel(string strNo)
    {
        cout << "载入元素类怪物的头部位模型，需要调用M_Element类或其父类中其他诸多成员函数，逻辑代码略..." << endl;
        /* 读文件啊，之类的 */
    }

    virtual void LoadLimbsModel(string strNo)
    {
        cout << "载入元素类怪物的四肢部位模型，需要调用M_Element类或其父类中其他诸多成员函数，逻辑代码略..." << endl;
    }
};

/**
 * @brief
 *
 */
class M_MechanicBuilder : public MonsterBuilder {
public:
    M_MechanicBuilder()
    {
        m_pMonster = new M_Mechanic();
    }

    virtual void LoadTrunkModel(string strNo)
    {
        cout << "载入机械类怪物的躯干部位模型，需要调用M_Mechanic类或其父类中其他诸多成员函数，逻辑代码略..." << endl;
        /* 读文件啊，之类的 */
    }

    virtual void LoadHeadModel(string strNo)
    {
        cout << "载入机械类怪物的头部位模型，需要调用M_Mechanic类或其父类中其他诸多成员函数，逻辑代码略..." << endl;
        /* 读文件啊，之类的 */
    }

    virtual void LoadLimbsModel(string strNo)
    {
        cout << "载入机械类怪物的四肢部位模型，需要调用M_Mechanic类或其父类中其他诸多成员函数，逻辑代码略..." << endl;
    }
};

int main(void)
{
    MonsterBuilder* pMonsterBuilder = new M_UndeadBuilder(); // 创建亡灵类构建器
    MonsterDirector* pDirector = new MonsterDirector(pMonsterBuilder);
    Monster* pMonster = pDirector->Construct("1234567890987654321");

    delete pMonster;
    delete pDirector;
    delete pMonsterBuilder;
}