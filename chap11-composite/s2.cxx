/**
 * @file s2.cxx 输出目录的层次结构（使用组合模式）
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <list>

using namespace std;

/**
 * @brief 文件系统 抽象类
 *
 */
class FileSystem {
public:
    /**
     * @brief 显示名字
     *
     * @param level 用于表示显示的层次
     */
    virtual void ShowName(int level) = 0;

    /**
     * @brief 像当前目录或者子目录 增加文件 或者 子目录
     *
     * @param pfilesys
     * @return int
     */
    virtual int Add(FileSystem* pfilesys) = 0;

    /**
     * @brief 从当前目录中移除 文件 或者 子目录
     *
     * @param pfilesys
     * @return int
     */
    virtual int Remove(FileSystem* pfilesys) = 0;

    virtual ~FileSystem() { }
};

class File : public FileSystem {
public:
    File(string name)
        : m_sname(name)
    {
    }

    virtual void ShowName(int level) override
    {
        for (int i = 0; i < level; ++i) {
            cout << "\t";
        }
        cout << "-" << m_sname << endl;
    }

    /* 文件中 不能包含其他文件和目录 */
    virtual int Add(FileSystem* pfilesys) override
    {
        return -1;
    }

    virtual int Remove(FileSystem* pfilesys) override
    {
        return -1;
    }

private:
    string m_sname; /* 文件名 */
};

/**
 * @brief 目录类
 *
 */
class Dir : public FileSystem {
public:
    Dir(string name)
        : m_sname(name)
    {
    }

    virtual void ShowName(int level) override
    {
        // (1) 显示缩进
        for (int i = 0; i < level; ++i) {
            cout << "\t";
        }

        // (2) 显示本目录名
        cout << "+" << m_sname << endl;

        // (3) 缩进 + 1
        level++;

        // (4) 输出所包含的字内容（可能是文件，也可能是目录）
        for (auto iter : m_child) {
            iter->ShowName(level);
        }
    }

    virtual int Add(FileSystem* pfilesys) override
    {
        m_child.push_back(pfilesys);
        return 0;
    }

    virtual int Remove(FileSystem* pfilesys) override
    {
        m_child.remove(pfilesys);
        return 0;
    }

private:
    string m_sname; /* 目录名 */
    list<FileSystem*> m_child; /* 目录中包含的文件或者其他文件列表 */
};

int main(void)
{
    FileSystem* pdir1 = new Dir("root");
    FileSystem* pfile1 = new File("common.mk");
    FileSystem* pfile2 = new File("config.mk");
    FileSystem* pfile3 = new File("makefile");

    FileSystem* pdir2 = new Dir("app");
    FileSystem* pfile4 = new File("nginx.c");
    FileSystem* pfile5 = new File("ngx_conf.c");

    FileSystem* pdir3 = new Dir("signal");
    FileSystem* pfile6 = new File("ngx_signal.c");

    FileSystem* pdir4 = new Dir("include");
    FileSystem* pfile7 = new File("ngx_func.c");
    FileSystem* pfile8 = new File("ngx_signal.h");

    pdir1->Add(pfile1);
    pdir1->Add(pfile2);
    pdir1->Add(pfile3);

    pdir2->Add(pfile4);
    pdir2->Add(pfile5);

    pdir3->Add(pfile6);

    pdir4->Add(pfile7);
    pdir4->Add(pfile8);

    pdir1->Add(pdir2);
    pdir1->Add(pdir3);
    pdir1->Add(pdir4);

    pdir1->ShowName(0);

    delete pfile8;
    delete pfile7;
    delete pdir4;

    delete pfile6;
    delete pdir3;

    delete pfile5;
    delete pfile4;
    delete pdir2;

    delete pfile3;
    delete pfile2;
    delete pfile1;
    delete pdir1;
}