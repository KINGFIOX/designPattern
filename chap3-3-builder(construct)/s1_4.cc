/**
 * @file s1_4.cc 不使用设计模式的时候，exportTXT 与 exportXML
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
 * @brief 将日报导出到纯文本格式文件 相关的类
 *
 */
class ExportToTXTFile {
public:
    void doExport(DailyHeaderData* dailyHeadObj, vector<DailyContentData*>& vec_dailyContObj, DailyFooterData* dailyFooterData)
    {
        string strtmp = "";
        // (1) 拼接标题
        strtmp += dailyHeadObj->getDepName() + "," + dailyHeadObj->getExportDate() + "\n";

        // (2) 拼接内容主体
        for (auto iter : vec_dailyContObj) {
            ostringstream oss;
            oss << iter->getSpendTime();
            strtmp += iter->getContent() + ": (花费的时间: " + oss.str() + "小时)" + "\n";
        }

        // (3) 拼接结尾
        strtmp += "报告人: " + dailyFooterData->getUserName() + "\n";

        // (4) 只展示在屏幕上文件的内容
        cout << strtmp;
    }
};

class ExportToXMLFile {
public:
    void doExport(DailyHeaderData* dailyHeadObj, vector<DailyContentData*>& vec_dailyContObj, DailyFooterData* dailyFooterData)
    {
        string strtmp = "";
        // (1) 拼接标题
        strtmp += "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
        strtmp += "<DailyReport>\n";
        strtmp += "\t<Header>\n";
        strtmp += "\t\t<DepName>" + dailyHeadObj->getDepName() + "</DepName>\n";
        strtmp += "\t\t<GenDate>" + dailyHeadObj->getExportDate() + "</GenDate>\n";
        strtmp += "\t</Header>\n";

        // (2) 拼接内容主体
        strtmp += "\t<Body>\n";
        for (auto iter : vec_dailyContObj) {
            ostringstream oss;
            oss << iter->getSpendTime();
            strtmp += "\t\t<Content>" + iter->getContent() + "</Content>\n";
            strtmp += "\t\t<SpendTime>花费的时间: " + oss.str() + "小时" + "</SpendTime>\n";
        }
        strtmp += "\t</Body>\n";

        // (3) 拼接结尾
        strtmp += "\t<Footer>\n";
        strtmp += "\t\t<UserName>报告人: " + dailyFooterData->getUserName() + "</UserName>\n";
        strtmp += "\t</Footer>\n";
        strtmp += "</DailyReport>\n";

        // (4) 只展示在屏幕上文件的内容
        cout << strtmp;
    }
};

int main(void)
{
    /* 头 */
    DailyHeaderData* pdhd = new DailyHeaderData("研发一部", "11月1日");

    /* 内容 */
    DailyContentData* pdcd1 = new DailyContentData("完成A项目的需求分析工作", 3.5);
    DailyContentData* pdcd2 = new DailyContentData("完成B项目的需求分析工作", 5.5);
    vector<DailyContentData*> vec_dcd;
    vec_dcd.push_back(pdcd1);
    vec_dcd.push_back(pdcd2);

    DailyFooterData* pdfd = new DailyFooterData("小李");

    // ExportToTXTFile file_ettxt;
    // file_ettxt.doExport(pdhd, vec_dcd, pdfd);

    ExportToXMLFile file_etxml;
    file_etxml.doExport(pdhd, vec_dcd, pdfd);

    delete pdhd;
    for (auto v : vec_dcd) {
        delete v;
    }
    delete pdfd;

    return 0;
}