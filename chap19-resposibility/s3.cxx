#include <iostream>

using namespace std;

/**
 * @brief 敏感词过滤器 父类
 *
 */
class ParWordFilter {
public:
    ParWordFilter()
        : m_nextChain(nullptr)
    {
    }

    virtual ~ParWordFilter() { }

public:
    void setNextChain(ParWordFilter* next)
    {
        m_nextChain = next;
    }

    virtual string processRequest(string strWord) = 0;

protected:
    /* 找到链中的下一个对象 */
    string sendRequestToNextHandler(string strWord)
    {
        /* FIXME 最后兜底的 */
        if (m_nextChain != nullptr) {
            return m_nextChain->processRequest(strWord);
        }
        return strWord;
    }

private:
    ParWordFilter* m_nextChain;
};

/**
 * @brief 性敏感词汇过滤器
 *
 */
class SexWordFilter : public ParWordFilter {
public:
    string processRequest(string strWord) override
    {
        cout << "通过与词库对比，在 strWord 中查找 \"性\" 敏感词并用 xxx 来替换" << endl;
        /* 实现逻辑略 */ strWord += "xxx";
        return sendRequestToNextHandler(strWord); /* 往下处理 */
    }
};

/**
 * @brief 脏话过滤器
 *
 */
class DirtyWordFilter : public ParWordFilter {
public:
    string processRequest(string strWord) override
    {
        cout << "通过与词库对比，在 strWord 中查找 \"脏话\" 敏感词并用 yyy 来替换" << endl;
        /* 实现逻辑略 */ strWord += "yyy";
        return sendRequestToNextHandler(strWord); /* 往下处理 */
    }
};

/**
 * @brief 政治敏感词
 *
 */
class PoliticsWordFilter : public ParWordFilter {
    string processRequest(string strWord) override
    {
        cout << "通过与词库对比，在 strWord 中查找 \"政治\" 敏感词并用 zzz 来替换" << endl;
        /* 实现逻辑略 */ strWord += "zzz";
        return sendRequestToNextHandler(strWord); /* 往下处理 */
    }
};

int main(void)
{
    // (1) 创建 职责链
    ParWordFilter* p1 = new SexWordFilter();
    ParWordFilter* p2 = new DirtyWordFilter();
    ParWordFilter* p3 = new PoliticsWordFilter();

    // (2) 连接职责链
    p1->setNextChain(p2);
    p2->setNextChain(p3);
    p3->setNextChain(nullptr);

    // (3) 测试
    cout << " ---------- 范例 ---------- " << endl;
    string strWordFilterResult = p1->processRequest("你好，这里是过滤敏感词测试范例");
    cout << "过滤的结果为: " << strWordFilterResult << endl;

    delete p3;
    delete p2;
    delete p1;

    return 0;
}