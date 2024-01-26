/**
 * @file s1.cxx 未使用设计模式的 例子 （典型的网状结构）
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

class CTlParent {
public:
    CTlParent(string caption)
        : m_caption(caption)
    {
    }

    virtual ~CTlParent() { }

public:
    /* 当 UI 控件发生变化时，成员函数会发生变化 */
    virtual void changed(map<string, CTlParent*>& tmpUICtlList) = 0;

    /* 设置 UI 控件是否启用 */
    virtual void Enable(bool sign) = 0;

protected:
    string m_caption;
};

/**
 * @brief 普通按钮类
 *
 */
class Button : public CTlParent {
public:
    Button(string caption)
        : CTlParent(caption)
    {
        /* 构造函数 */
    }

    void Enable(bool sign) override
    {
        if (sign == true) {
            printf("单选按钮 \"%s\" 被设置为了 \"启用\" 状态\n", m_caption.c_str());
        } else {
            printf("单选按钮 \"%s\" 被设置为了 \"禁用\" 状态\n", m_caption.c_str());
        }

        /* 相关业务代码 */
    }

    void changed(map<string, CTlParent*>& tmpUICtlList) override; /* 类外实现 */
};

/**
 * @brief 单选按钮
 *
 */
class RadioBtn : public CTlParent {
public:
    RadioBtn(string caption)
        : CTlParent(caption)
    {
        /* 构造函数 */
    }

    void Enable(bool sign) override
    {
        /* 相关代码 */
    }

    // 设置单选按钮被选中或者取消选中，被选中的单选按钮中间有个黑色的实心圆点
    void Selected(bool sign)
    {
        if (sign == true) {
            printf("单选按钮 \"%s\" \"被选中\" \n", m_caption.c_str());
        } else {
            printf("单选按钮 \"%s\" \"取消选中\" \n", m_caption.c_str());
        }

        /* 相关业务代码 */
    }

    void changed(map<string, CTlParent*>& tmpUICtlList) override; /* 类外实现，被单击时，相关业务 */
};

/**
 * @brief 具体显示编辑框
 *
 */
class EditCtl : public CTlParent {
public:
    EditCtl(string caption)
        : CTlParent(caption)
    {
        /* 构造函数 */
    }

    void Enable(bool sign) override
    {
        if (sign == true) {
            printf("编辑框 \"%s\" 被设置为了 \"启用\" 状态\n", m_caption.c_str());
        } else {
            printf("编辑框 \"%s\" 被设置为了 \"禁用\" 状态\n", m_caption.c_str());
        }

        /* 相关业务代码 */
    }

    bool isContentEmpty()
    {
        return m_content.empty();
    }

    /* 编辑框内容发生变化 */
    void changed(map<string, CTlParent*>& tmpUICtlList) override;

private:
    string m_content = "";
};

/* 按钮被按下的时候，该成员函数会被调用 */
void Button::changed(map<string, CTlParent*>& tmpUICtlList)
{
    if (m_caption == "登录") {
        /* 按下的是登录按钮 */
        cout << "开始游戏登录验证，根据验证结果决定是否进入游戏之中还是验证失败给出提示" << endl;
    } else if (m_caption == "退出") {
        cout << "游戏退出，再见" << endl;
    }
}

void RadioBtn::changed(map<string, CTlParent*>& tmpUICtlList)
{
    if (m_caption == "游客登录") {
        /* 按下的是登录按钮 */
        cout << "开始游戏登录验证，根据验证结果决定是否进入游戏之中还是验证失败给出提示" << endl;
        (static_cast<RadioBtn*>(tmpUICtlList["游客登录"]))->Selected(true);
        (static_cast<RadioBtn*>(tmpUICtlList["账号登录"]))->Selected(false);
        tmpUICtlList["账号"]->Enable(false);
        tmpUICtlList["密码"]->Enable(false);
        tmpUICtlList["登录"]->Enable(true);
    } else if (m_caption == "账号登录") {
        cout << "开始游戏登录验证，根据验证结果决定是否进入游戏之中还是验证失败给出提示" << endl;
        (static_cast<RadioBtn*>(tmpUICtlList["游客登录"]))->Selected(false);
        (static_cast<RadioBtn*>(tmpUICtlList["账号登录"]))->Selected(true);
        tmpUICtlList["账号"]->Enable(true);
        tmpUICtlList["密码"]->Enable(true);
        if ((static_cast<EditCtl*>(tmpUICtlList["账号"]))->isContentEmpty()
            || (static_cast<EditCtl*>(tmpUICtlList["密码"]))->isContentEmpty()) {
            tmpUICtlList["登录"]->Enable(false);
        } else {
            tmpUICtlList["登录"]->Enable(true);
        }
    }
}

void EditCtl::changed(map<string, CTlParent*>& tmpUICtlList)
{
    if ((static_cast<EditCtl*>(tmpUICtlList["账号"]))->isContentEmpty()
        || (static_cast<EditCtl*>(tmpUICtlList["密码"]))->isContentEmpty()) {
        tmpUICtlList["登录"]->Enable(false);
    } else {
        tmpUICtlList["登录"]->Enable(true);
    }
}

int main(void)
{
    /* 创建各种 UI 控件 */
    map<string, CTlParent*> UICtlList;
    UICtlList["登录"] = new Button("登录");
    UICtlList["退出"] = new Button("退出");
    UICtlList["退出"]->Enable(true);
    UICtlList["登录"]->Enable(true);

    UICtlList["游客登录"] = new RadioBtn("游客登录");
    UICtlList["账号登录"] = new RadioBtn("账号登录");
    /* 设置缺省状态 */
    (static_cast<RadioBtn*>(UICtlList["游客登录"]))->Selected(true);
    (static_cast<RadioBtn*>(UICtlList["账号登录"]))->Selected(false);

    UICtlList["账号"] = new EditCtl("账号");
    UICtlList["密码"] = new EditCtl("密码");
    /* 缺省状态 */
    UICtlList["账号"]->Enable(false);
    UICtlList["密码"]->Enable(false);

    cout << "---------- 初始化完毕 ----------" << endl;

    UICtlList["账号登录"]->changed(UICtlList);

    cout << "---------- 切换完毕 ----------" << endl;

    // ---------- 释放资源 ----------
    for (auto v : UICtlList) {
        auto sec = v.second;
        delete sec;
        sec = nullptr;
    }

    return 0;
}