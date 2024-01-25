/**
 * @file s1.cxx
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