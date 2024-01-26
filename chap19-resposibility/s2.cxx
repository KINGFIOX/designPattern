#include <iostream>

using namespace std;

/**
 * @brief 加薪请求
 *
 */
class RaiseRequest {
public:
    RaiseRequest(const string& sname, int salfigure)
        : m_sName(sname)
        , m_iSalFigure(salfigure)
    {
    }

    const string& getName() const
    {
        return m_sName;
    }

    int getSalFigure() const
    {
        return m_iSalFigure;
    }

private:
    string m_sName;
    int m_iSalFigure;
};

/**
 * @brief 加薪审批者父类
 *
 */
class ParSalApprover {
public:
    ParSalApprover()
        : m_nextChain(nullptr)
    {
    }
    virtual ~ParSalApprover() { } /* 虚析构 */

public:
    /**
     * @brief Set the Next Chain object
     *
     * @param next
     */
    void setNextChain(ParSalApprover* next)
    {
        m_nextChain = next;
    }

    /**
     * @brief 处理加薪请求
     *
     * @param req
     */
    virtual void processRequest(const RaiseRequest& req) = 0; // TODO

protected:
    /**
     * @brief 在链中找下一个对象，并发请求投递给 链的下游
     *
     * @param req
     */
    void sendRequestToNextHandler(const RaiseRequest& req)
    {
        if (m_nextChain != nullptr) {
            /* 把请求传递给链的下一个对象 */
            m_nextChain->processRequest(req);
        } else {
            /* 没找到链中的下一个对象，程序流程不应该走到这 */
            cout << "error: " << req.getName() << "的加薪要求为: " << req.getSalFigure() << endl;
        }
    }

private:
    ParSalApprover* m_nextChain; /* 指向下一个审批者对象 的多态指针，链表 */
};

/**
 * @brief 部门经理
 *
 */
class depManager_SA : public ParSalApprover {
public:
    /* 处理加薪请求 */
    void processRequest(const RaiseRequest& req) override
    {
        int salfigure = req.getSalFigure();
        if (salfigure <= 1000) {
            cout << req.getName() << "的加薪要求为: " << req.getSalFigure() << "元，部门经理审批通过!" << endl;
        } else {
            /* 自己不能处理，找下游处理 */
            sendRequestToNextHandler(req);
        }
    }
};

/**
 * @brief 技术总监
 *
 */
class CTO_SA : public ParSalApprover {
public:
    /* 处理加薪请求 */
    void processRequest(const RaiseRequest& req) override
    {
        int salfigure = req.getSalFigure();
        if (salfigure > 1000 && salfigure <= 5000) {
            cout << req.getName() << "的加薪要求为: " << req.getSalFigure() << "元，技术总监审批通过!" << endl;
        } else {
            /* 自己不能处理，找下游处理 */
            sendRequestToNextHandler(req);
        }
    }
};

/**
 * @brief 总经理
 *
 */
class genManager_SA : public ParSalApprover {
public:
    /* 处理加薪请求 */
    void processRequest(const RaiseRequest& req) override
    {
        int salfigure = req.getSalFigure();
        if (salfigure > 5000) {
            cout << req.getName() << "的加薪要求为: " << req.getSalFigure() << "元，总经理审批通过!" << endl;
        } else {
            /* 自己不能处理，找下游处理 */
            sendRequestToNextHandler(req);
        }
    }
};

int main(void)
{
    // (1) 创建出 职责链 中包含的各个对象
    ParSalApprover* p1 = new depManager_SA();
    ParSalApprover* p2 = new CTO_SA();
    ParSalApprover* p3 = new genManager_SA();

    // (2) 将这些对象串在一起，构成职责链
    p1->setNextChain(p2);
    p2->setNextChain(p3);

    // (3) 请求
    RaiseRequest rr1("张三", 15000);
    p1->processRequest(rr1);

    RaiseRequest rr2("李四", 3500);
    p1->processRequest(rr2);

    RaiseRequest rr3("王五", 800);
    p1->processRequest(rr3);

    // (4)
    delete p3;
    delete p2;
    delete p1;
}