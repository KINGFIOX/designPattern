/**
 * @file s1.cxx 类适配器
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

// 日志操作相关类（数据库版本）:w

class LogToDataBase {
public:
    void initdb()
    {
        /* 做日志文件初始化工作，比方说打开文件等 */
    }
    void writeTodb(const char* pContent)
    {
        /* 将日志内容写入文件 */
    }
    void readFromdb()
    {
        /* 从日志中读取一些信息 */
    }
    void closedb()
    {
        /* 关闭日志文件 */
    }
    // ... 可能还有很多成员函数
};

// ---------- 类适配器 ----------

/**
 * @brief 类适配器，一个私有继承，一个公有继承
 *
 * 其实本质上是一样的，私有继承就是组合关系
 */
class LogAdapter : public LogToDataBase, private LogToFile {
public:
    void initdb()
    {
        cout << "在LogAdapter::initdb() 中适配 LogToFile::initdb()" << endl;
        initFile();
    }

    void writedb(const char* pContent)
    {
        cout << "在LogAdapter::writedb() 中适配 LogToFile::writeToFile()" << endl;
        writeToFile(pContent);
    }

    void readFromdb()
    {
        cout << "在LogAdapter::readFromdb() 中适配 LogToFile::readFromFile()" << endl;
        readFromFile();
    }

    void closedb()
    {
        cout << "在LogAdapter::closedb() 中适配 LogToFile::closeFile()" << endl;
        closeFile();
    }
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