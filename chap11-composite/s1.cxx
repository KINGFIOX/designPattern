/**
 * @file s1.cxx 输出目录的层次结构（非组合模式）
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
 * @brief 文件相关的类
 *
 */
class File {
public:
    /* 构造函数 */
    File(string name)
        : m_sname(name)
    {
    }

    /**
     * @brief 显示文件
     *
     * @param lvalue 为了显示层次关系的缩进字符串内容
     */
    void ShowName(string lvlstr)
    {
        /* "-" 表示文件，末端节点 */
        cout << lvlstr << "-" << m_sname << endl;
    }

private:
    string m_sname; /* 文件名 */
};

/**
 * @brief 目录相关的类
 *
 */
class Dir {
public:
    Dir(string name)
        : m_sname(name)
    {
    }

    /**
     * @brief 目录中可以增加其他文件
     *
     * @param pfile
     */
    void AddFile(File* pfile)
    {
        m_childFile.push_back(pfile);
    }

    /**
     * @brief 目录中可以增加其他目录
     *
     * @param pdir
     */
    void AddDir(Dir* pdir)
    {
        m_childDir.push_back(pdir);
    }

    /**
     * @brief 显示目录名，同时也要复杂其下面的文件和目录名的展示工作
     *
     * @param lvlstr
     */
    void ShowName(string lvlstr)
    {
        // (1) 输出本目录名
        cout << lvlstr << "+" << m_sname << endl;

        // (2) 输出包含的文件名
        lvlstr += "\t"; // 缩进
        for (auto iter : m_childFile) {
            iter->ShowName(lvlstr); /* 显示文件名 */
        }

        // (3) 输出所包含的子目录名：终止条件，也就是 m_childDir 没有元素
        for (auto iter : m_childDir) {
            iter->ShowName(lvlstr); /* 显示目录名，递归了 */
        }
    }

private:
    string m_sname; /* 目录名 */
    list<File*> m_childFile; /* 目录包含的文件列表 */
    list<Dir*> m_childDir; /* 目录中包含的子目录列表 */
};

int main(void)
{
    Dir* pdir1 = new Dir("root");
    File* pfile1 = new File("common.mk");
    File* pfile2 = new File("config.mk");
    File* pfile3 = new File("makefile");

    Dir* pdir2 = new Dir("app");
    File* pfile4 = new File("nginx.c");
    File* pfile5 = new File("ngx_conf.c");

    Dir* pdir3 = new Dir("signal");
    File* pfile6 = new File("ngx_signal.c");

    Dir* pdir4 = new Dir("include");
    File* pfile7 = new File("ngx_func.c");
    File* pfile8 = new File("ngx_signal.h");

    pdir1->AddFile(pfile1);
    pdir1->AddFile(pfile2);
    pdir1->AddFile(pfile3);

    pdir2->AddFile(pfile4);
    pdir2->AddFile(pfile5);

    pdir3->AddFile(pfile6);

    pdir4->AddFile(pfile7);
    pdir4->AddFile(pfile8);

    pdir1->AddDir(pdir2);
    pdir1->AddDir(pdir3);
    pdir1->AddDir(pdir4);

    pdir1->ShowName("");

    delete pfile8;
    delete pfile7;
    delete pfile6;
    delete pfile5;
    delete pfile4;
    delete pfile3;
    delete pfile2;
    delete pfile1;

    delete pdir1;
    delete pdir2;
    delete pdir3;
    delete pdir4;
}
