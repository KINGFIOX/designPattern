/**
 * @file s2.cxx 迭代器模式
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

using namespace std;

/**
 * @brief 抽象迭代器类模板
 *
 * @tparam T
 */
template <typename T>
class myIter {
public:
    virtual void First() = 0; // 指向容器中第一个元素
    virtual void Next() = 0; // 指向容器中下一个元素
    virtual bool IsDone() = 0; // 是否遍历完
    virtual T& CurrentItem() = 0; // 获取当前元素
    virtual ~myIter() { } // 做父类时，析构函数应该为虚函数
};

template <typename T>
class myContainer {
public:
    virtual myIter<T>* CreateIterator() = 0; /* 创建迭代器 */
    virtual T& getItem(int index) = 0; // 获取当前元素
    virtual int getSize() = 0;
    virtual ~myContainer() { }

private:
};

/**
 * @brief 具体迭代器类模板
 *
 * @tparam T
 */
template <typename T>
class myVectorIter : public myIter<T> {
public:
    myVectorIter(myContainer<T>* tmpc)
        : myvector(tmpc)
    {
    }

    virtual void First() override
    {
        m_current = 0;
    }

    virtual void Next() override
    {
        m_current++;
    }

    virtual bool IsDone() override
    {
        if (m_current >= myvector->getSize()) {
            return true;
        } else {
            return false;
        }
    }

    virtual T& CurrentItem() override
    {
        return myvector->getItem(m_current);
    }

private:
    myContainer<T>* myvector; // 容器
    int m_current; // 迭代器在当前容器中的位置
};

template <typename T>
class myVector : public myContainer<T> {
public:
    myVector()
    {
        /* 将数组中容器进行初始化 */
        for (int i = 0; i < 10; ++i) {
            m_elem[i] = i;
        }
    }

    /* 工厂模式，注意我们其实传入了参数 this */
    virtual myIter<T>* CreateIterator() override
    {
        return new myVectorIter<T>(this); // TODO 要记得释放
    }

    virtual T& getItem(int index) override
    {
        return m_elem[index];
    }

    virtual int getSize()
    {
        return 10;
    }

private:
    T m_elem[10];
};

int main(void)
{
    myContainer<int>* pContainer = new myVector<int>();
    // myIter<int>* iter = pContainer->CreateIterator();

    /* 栈上 */
    myVectorIter<int> iter(pContainer);

    for (iter.First(); !iter.IsDone(); iter.Next()) {
        cout << iter.CurrentItem() << endl;
    }

    delete pContainer;
}