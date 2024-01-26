/**
 * @file s1.cxx 访问者模式 对象结构
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstdio>
#include <iostream>
#include <list>

using namespace std;

class Visitor; /* 前向声明 */

/**
 * @brief 药品父类
 *
 */
class Medicine {
public:
    virtual string getMdcName() = 0; /* 药品名称 */
    virtual float getPrice() = 0; /* 药品总价格 */

    /**
     * @brief ++ Accept 国际惯例 ++
     *
     * @param pVisitor
     */
    virtual void Accept(Visitor* pVisitor) = 0;

    virtual ~Medicine() { } /* 做父类应该有个虚析构函数 */
};

/**
 * @brief 阿司匹林肠溶片
 *
 */
class M_asplcrp : public Medicine {
public:
    string getMdcName() override
    {
        return "阿司匹林肠溶片";
    }
    float getPrice() override
    {
        return 46.8f;
    }
    /* 类外实现 */
    void Accept(Visitor* pVisitor) override;
};

/**
 * @brief 氟伐他汀缓释片
 *
 */
class M_fftdnhsp : public Medicine {
public:
    string getMdcName() override
    {
        return "氟伐他汀缓释片";
    }
    float getPrice() override
    {
        return 111.3f;
    }
    /* 类外实现 */
    void Accept(Visitor* pVisitor) override;
};

/**
 * @brief 黛力新
 *
 */
class M_dlx : public Medicine {
public:
    string getMdcName() override
    {
        return "黛力新";
    }
    float getPrice() override
    {
        return 120.0f;
    }
    /* 类外实现 */
    void Accept(Visitor* pVisitor) override;
};

/**
 * @brief 访问者父类
 *
 */
class Visitor {
public:
    virtual ~Visitor() { }

public:
    /* 对应的三个 被访问元素 */
    /* FIXME 局限性：要求被访问者固定 */
    /* 当然这三个也是可以 函数名相同 但是参数不同，这也是代表不同的函数 */
    /**
     * @brief 访问元素：阿司匹林肠溶片
     *
     * @param pelem
     */
    virtual void Visit_elm_asplcrp(M_asplcrp* pelem) = 0;

    /**
     * @brief 访问元素：氟伐他汀那缓释片
     *
     * @param pelem
     */
    virtual void Visit_elm_fftdnhsp(M_fftdnhsp* pelem) = 0;

    /**
     * @brief 访问元素：黛力新
     *
     * @param pelem
     */
    virtual void Visit_elm_dlx(M_dlx* pelem) = 0;
};

/**
 * @brief 收费人员访问者
 *
 */
class Visitor_SFRY : public Visitor {
public:
    void Visit_elm_asplcrp(M_asplcrp* pelem) override
    {
        float tmpPrice = pelem->getPrice();
        printf("药品: \"%s\", 的价格为: %.2f\n", pelem->getMdcName().c_str(), tmpPrice);
        m_totalCost += tmpPrice;
    }

    void Visit_elm_dlx(M_dlx* pelem) override
    {
        float tmpPrice = pelem->getPrice();
        printf("药品: \"%s\", 的价格为: %.2f\n", pelem->getMdcName().c_str(), tmpPrice);
        m_totalCost += tmpPrice;
    }

    void Visit_elm_fftdnhsp(M_fftdnhsp* pelem) override
    {
        float tmpPrice = pelem->getPrice();
        printf("药品: \"%s\", 的价格为: %.2f\n", pelem->getMdcName().c_str(), tmpPrice);
        m_totalCost += tmpPrice;
    }

    /**
     * @brief Get the Total Cost object 返回总费用
     *
     * @return float
     */
    float getTotalCost()
    {
        return m_totalCost;
    }

private:
    float m_totalCost = 0.0f; /* 收费人员会涉及到总费用 */
};

/**
 * @brief 取药人员
 *
 */
class Visitor_QYRY : public Visitor {
public:
    void Visit_elm_asplcrp(M_asplcrp* pelem) override
    {
        printf("取药人员将 \"%s\" 拿给了我\n", pelem->getMdcName().c_str());
    }

    void Visit_elm_dlx(M_dlx* pelem) override
    {
        printf("取药人员将 \"%s\" 拿给了我\n", pelem->getMdcName().c_str());
    }

    void Visit_elm_fftdnhsp(M_fftdnhsp* pelem) override
    {
        printf("取药人员将 \"%s\" 拿给了我\n", pelem->getMdcName().c_str());
    }
};

/**
 * @brief 新增营养师
 *
 */
class Visitor_YYS : public Visitor {
public:
    void Visit_elm_asplcrp(M_asplcrp* pelem) override
    {
        printf("营养师建议：多吃粗粮\n");
    }

    void Visit_elm_dlx(M_dlx* pelem) override
    {
        printf("营养师建议：多吃蘑菇、洋葱\n");
    }

    void Visit_elm_fftdnhsp(M_fftdnhsp* pelem) override
    {
        printf("营养师建议：多出去走走\n");
    }
};

/**
 * @brief 对象结构
 *
 */
class ObjectStructor {
public:
    void addMedicine(list<Medicine*> tmpLi)
    {
        m_mdcList.merge(tmpLi);
    }

    void addMedicine(Medicine* p_mdc)
    {
        m_mdcList.push_back(p_mdc);
    }

    void procAction(Visitor* pVisitor)
    {
        for (Medicine* v : m_mdcList) {
            v->Accept(pVisitor);
        }
    }

private:
    list<Medicine*> m_mdcList;
};

/* ---------- 各个药品子类的 Accept 方法的 实现体代码 ---------- */

void M_asplcrp::Accept(Visitor* pVisitor)
{
    pVisitor->Visit_elm_asplcrp(this);
}

void M_fftdnhsp::Accept(Visitor* pVisitor)
{
    pVisitor->Visit_elm_fftdnhsp(this);
}

void M_dlx::Accept(Visitor* pVisitor)
{
    pVisitor->Visit_elm_dlx(this);
}

/* ---------- 各个药品子类的 Accept 方法的 实现体代码 ---------- */

int main(void)
{

    M_asplcrp mdc_a;
    M_fftdnhsp mdc_f;
    M_dlx mdc_d;

    ObjectStructor objStruct;

    objStruct.addMedicine({ &mdc_a, &mdc_d, &mdc_f });

    cout << " ---------- 收费 ---------- " << endl;

    Visitor_SFRY* v_sf = new Visitor_SFRY;
    objStruct.procAction(v_sf);
    cout << "所有药品总价为" << v_sf->getTotalCost() << endl;

    cout << " ---------- 抓药 ---------- " << endl;

    Visitor_QYRY* v_qy = new Visitor_QYRY;
    objStruct.procAction(v_qy);

    cout << " ---------- 营养师 ---------- " << endl;

    Visitor_YYS* v_yys = new Visitor_YYS;
    objStruct.procAction(v_yys);

    return 0;
}