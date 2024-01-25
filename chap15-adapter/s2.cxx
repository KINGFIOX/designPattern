/**
 * @file s1.cxx 适配器模式，重新实现 LogToDataBase
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

using namespace std;

class LogToFile {
public:
    void initFile()
    {
        /* 做日志文件初始化工作，比方说打开文件等 */
    }
    void writeToFile(const char* pContent)
    {
        /* 将日志内容写入文件 */
    }
    void readFromFile()
    {
        /* 从日志中读取一些信息 */
    }
    void closeFile()
    {
        /* 关闭日志文件 */
    }
    // ... 可能还有很多成员函数
};

// 日志操作相关类（数据库版本）

/**
 * @brief 适配器类
 *
 */
class LogToDataBase {
public:
    virtual void initdb() = 0;
    virtual void writedb(const char* pContent) = 0;
    virtual void readFromdb() = 0;
    virtual void closedb() = 0;

    virtual ~LogToDataBase() { }
};

class LogAdapter : public LogToDataBase {
public:
    /**
     * @brief Construct a new Log Adapter object
     *
     * @param p 形参是老接口所属类的指针
     */
    LogAdapter(LogToFile* p)
    {
        m_pfile = p;
    }

    void initdb() override
    {
        cout << "在LogAdapter::initdb() 中适配 LogToFile::initdb()" << endl;
        m_pfile->initFile();
    }

    void writedb(const char* pContent) override
    {
        cout << "在LogAdapter::writedb() 中适配 LogToFile::writeToFile()" << endl;
        m_pfile->writeToFile(pContent);
    }

    void readFromdb() override
    {
        cout << "在LogAdapter::readFromdb() 中适配 LogToFile::readFromFile()" << endl;
        m_pfile->readFromFile();
    }

    void closedb() override
    {
        cout << "在LogAdapter::closedb() 中适配 LogToFile::closeFile()" << endl;
        m_pfile->closeFile();
    }

private:
    LogToFile* m_pfile;
};

int main(void)
{
    LogToFile* plog = new LogToFile;
    plog->initFile();
    plog->writeToFile("向日志文件中写入了一条日志");
    plog->readFromFile();
    plog->closeFile();
    delete plog;

    /* log to db */
}