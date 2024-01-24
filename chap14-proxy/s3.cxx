/**
 * @file s3.cxx 缓冲代理
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<string> g_fileItemList; /* 全局容器 */

/**
 * @brief 抽象主题
 *
 */
class ReadInfo {
public:
    virtual void read() = 0;
    virtual ~ReadInfo() { }
};

/**
 * @brief 真实主题 --> 从文件中读取
 *
 */
class ReadInfoFromFile : public ReadInfo {
public:
    /**
     * @brief 从文件中读取 test.txt 的内容
     *
     */
    void read() override
    {
        ifstream fin("./test.txt");
        if (!fin) {
            cout << "文件打开失败" << endl;
            return;
        }
        string linebuf;
        while (getline(fin, linebuf)) {
            if (!linebuf.empty()) {
                /* 读文件不是空行 */
                g_fileItemList.push_back(linebuf);
                // 打印调试信息 cout << linebuf << endl;
            }
        }
        fin.close(); /* 关闭文件输入流 */
    }
};

/**
 * @brief 代理类
 *
 */
class ReadInfoProxy : public ReadInfo {
public:
    void read() override
    {
        if (!m_loaded) {
            /* 说明要去读 */
            m_loaded = true;
            ReadInfo* rf = new ReadInfoFromFile();
            rf->read(); /* 从文件中将数据读入全局容器 g_fileItemList */
            delete rf;
            cout << "从文件中读取了如下数据" << endl;
        } else {
            cout << "从缓存中读取了如下数据" << endl;
        }

        // 现在数据一定在 g_fileItemList中，开始显示

        for (auto iter : g_fileItemList) {
            cout << iter << endl;
        }
    }

private:
    bool m_loaded = false; /* false 表示还没有从文件中独处数据到内存 */
};

int main(void)
{
    ReadInfoProxy rip;
    rip.read();
    rip.read();
    rip.read();

    return 0;
}