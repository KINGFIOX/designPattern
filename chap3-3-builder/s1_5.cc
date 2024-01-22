/**
 * @file s1_5.cc 使用 构建者模式，exportTXT 与 exportXML
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/**
 * @brief 日报的 “标题” 部分
 *
 */
class DailyHeaderData {
public:
    /* 构造函数 */
    DailyHeaderData(string strDepName, string strGenDate)
        : m_strDepName(strDepName)
        , m_strGenDate(strGenDate)
    {
    }

    /* 获取部门名称 */
    string getDepName()
    {
        return m_strDepName;
    }

    /* 获取日报生成日期 */
    string getExportDate()
    {
        return m_strGenDate;
    }

private:
    string m_strDepName; /* 部门名称 */
    string m_strGenDate; /* 日报生成日期 */
};

class DailyContentData {
public:
    /* 构造函数 */
    DailyContentData(string strContent, double dspendTime)
        : m_strContent(strContent)
        , m_dspendTime(dspendTime)
    {
    }

    /* 完成该项工作内容描述 */
    string getContent()
    {
        return m_strContent;
    }

    /* 完成工作花费的时间 */
    double getSpendTime()
    {
        return m_dspendTime;
    }

private:
    string m_strContent; /* 该想工作内容描述 */
    double m_dspendTime; /* 完成该想工作花费的时间 */
};

class DailyFooterData {
public:
    DailyFooterData(string strUserName)
        : m_strUserName(strUserName)
    {
    }

    string getUserName()
    {
        return m_strUserName;
    }

private:
    string m_strUserName;
};

/**
 * @brief 抽象构建器类（文件构建器父类）
 *
 */
class FileBuilder {
public:
    FileBuilder()
        : m_strResult("")
    {
    }
    virtual ~FileBuilder() { }

public:
    virtual void buildHeader(DailyHeaderData* dailyHeadObj) = 0;
    virtual void buildBody(vector<DailyContentData*>& vec_daily) = 0;
    virtual void buildFooter(DailyFooterData* dailyFooterObj) = 0;

    string GetResult()
    {
        return m_strResult;
    }

protected:
    string m_strResult;
};

/**
 * @brief 纯文本文件构建器类
 *
 */
class TXTBuilder : public FileBuilder {
public:
    virtual void buildHeader(DailyHeaderData* dailyHeadObj) override
    {
        // (1) 拼接标题
        m_strResult += dailyHeadObj->getDepName() + "," + dailyHeadObj->getExportDate() + "\n";
    }
    virtual void buildBody(vector<DailyContentData*>& vec_daily) override
    {
        // (2) 拼接内容主体
        for (auto iter : vec_daily) {
            ostringstream oss;
            oss << iter->getSpendTime();
            m_strResult += iter->getContent() + ": (花费的时间: " + oss.str() + "小时)" + "\n";
        }
    }
    virtual void buildFooter(DailyFooterData* dailyFooterObj) override
    {
        // (3) 拼接结尾
        m_strResult += "报告人: " + dailyFooterObj->getUserName() + "\n";
    }
};

/**
 * @brief xml文件构建器类
 *
 */
class XMLBuilder : public FileBuilder {
public:
    virtual void buildHeader(DailyHeaderData* dailyHeadObj) override
    {
        // (1) 拼接标题
        m_strResult += "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
        m_strResult += "<DailyReport>\n";
        m_strResult += "\t<Header>\n";
        m_strResult += "\t\t<DepName>" + dailyHeadObj->getDepName() + "</DepName>\n";
        m_strResult += "\t\t<GenDate>" + dailyHeadObj->getExportDate() + "</GenDate>\n";
        m_strResult += "\t</Header>\n";
    }
    virtual void buildBody(vector<DailyContentData*>& vec_daily) override
    {
        // (2) 拼接内容主体
        m_strResult += "\t<Body>\n";
        for (auto iter : vec_daily) {
            ostringstream oss;
            oss << iter->getSpendTime();
            m_strResult += "\t\t<Content>" + iter->getContent() + "</Content>\n";
            m_strResult += "\t\t<SpendTime>花费的时间: " + oss.str() + "小时" + "</SpendTime>\n";
        }
        m_strResult += "\t</Body>\n";
    }
    virtual void buildFooter(DailyFooterData* dailyFooterObj) override
    {
        // (3) 拼接结尾
        m_strResult += "\t<Footer>\n";
        m_strResult += "\t\t<UserName>报告人: " + dailyFooterObj->getUserName() + "</UserName>\n";
        m_strResult += "\t</Footer>\n";
        m_strResult += "</DailyReport>\n";
    }
};

/**
 * @brief 文件指挥者类
 *
 */
class FileDirector {
public:
    /* 指挥者构造函数，传入参数builder */
    FileDirector(FileBuilder* ptmpBuilder)
    {
        m_pFileBuilder = ptmpBuilder;
    }

    // 组装文件
    string Construct(DailyHeaderData* dailyHeadObj, vector<DailyContentData*>& vec_dailyContObj, DailyFooterData* dailyFooterData)
    {
        /* 有事指挥者需要和 构建器 通过参数传递的方式交换数据，
                        这里指挥者通过委托的方式把功能交给构建器完成 */
        m_pFileBuilder->buildHeader(dailyHeadObj);
        m_pFileBuilder->buildBody(vec_dailyContObj);
        m_pFileBuilder->buildFooter(dailyFooterData);

        return m_pFileBuilder->GetResult();
    }

private:
    FileBuilder* m_pFileBuilder; /* 指向所有构建器类的父类 */
};

int main(void)
{
    FileBuilder* pfb = new XMLBuilder();
    FileDirector* pDtr = new FileDirector(pfb);

    /* 头 */
    DailyHeaderData* pdhd = new DailyHeaderData("研发一部", "11月1日");

    /* 内容 */
    DailyContentData* pdcd1 = new DailyContentData("完成A项目的需求分析工作", 3.5);
    DailyContentData* pdcd2 = new DailyContentData("完成B项目的需求分析工作", 5.5);
    vector<DailyContentData*> vec_dcd;
    vec_dcd.push_back(pdcd1);
    vec_dcd.push_back(pdcd2);

    /* 尾 */
    DailyFooterData* pdfd = new DailyFooterData("小李");

    /* 指挥者 构建 */
    string result = pDtr->Construct(pdhd, vec_dcd, pdfd);
    cout << result << endl;

    delete pdhd;
    for (auto v : vec_dcd) {
        delete v;
    }
    delete pdfd;
    delete pDtr;
    delete pfb;
}