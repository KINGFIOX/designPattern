/**
 * @file s1.cxx 未使用访问者模式
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
#include <ostream>

using namespace std;

/**
 * @brief 药品父类
 *
 */
class Medicine {
public:
    virtual string getMdcName() = 0; /* 药品名称 */
    virtual float getPrice() = 0; /* 药品总价格 */

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
};

// ---------- ----------

/**
 * @brief 针对药品的处理相关类
 *
 */
class MedicineProc {
public:
    /**
     * @brief 增加药品到药品列表中
     *
     * @param p_mdc
     */
    void addMedicine(Medicine* p_mdc)
    {
        m_mdcList.push_back(p_mdc);
    }

    /**
     * @brief 针对费用缴纳 和 取药所做的处理动作
     *
     * @param strvisitor 拿到了药品单的人，不同的人拿到药品单 所要做的事情不同
     */
    void procAction(string strvisitor)
    {
        if (strvisitor == "收费人员") {
            float totalCost = 0.0f; /* 总费用 */
            for (auto v : m_mdcList) {
                float tmpPrice = v->getPrice();
                printf("药品: \"%s\", 的价格为: %.2f\n", v->getMdcName().c_str(), tmpPrice);
                totalCost += tmpPrice;
            }
            printf("所有药品的总价为: %.2f, 收费人员收取了我的费用!\n", totalCost);
        } else if (strvisitor == "取药人员") { /* 取药人员要根据药品单为我拿药 */
            for (auto v : m_mdcList) {
                printf("取药人员将 \"%s\" 拿给了我\n", v->getMdcName().c_str());
            }
        } else if (strvisitor == "营养师") {
            cout << "营养师建议: 不要大鱼大肉, 多吃粗粮" << endl;
        } /* 健身教练、营养师 */
    }

private:
    list<Medicine*> m_mdcList;
};

int main(void)
{
    Medicine* p1 = new M_asplcrp;
    Medicine* p2 = new M_fftdnhsp;
    Medicine* p3 = new M_dlx;

    MedicineProc mdcProcObj;
    mdcProcObj.addMedicine(p1);
    mdcProcObj.addMedicine(p2);
    mdcProcObj.addMedicine(p3);

    mdcProcObj.procAction("收费人员");
    cout << "---------- ----------" << endl;
    mdcProcObj.procAction("取药人员");

    return 0;
}