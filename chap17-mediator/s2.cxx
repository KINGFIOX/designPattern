/**
 * @file s1.cxx 中介者模式
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

class CTlParent;

/**
 * @brief 中介者父类
 *
 */
class Mediator {
public:
    Mediator() { }

    /* 当某个 UI 控件发生变化时，调用中介者对象的该成员函数来通知 中介者 */
    virtual void ctlChanged(CTlParent*);

    virtual void creatCtrl() = 0; /* 创建所有需用用到的 UI 控件 */

    virtual ~Mediator() { }
};

// ---------- 控件相关代码 ----------

/**
 * @brief 控件类的父类
 *
 */
class CTlParent {
public:
    CTlParent(Mediator* ptmpMediator, string caption)
        : m_caption(caption)
        , m_pMediator(ptmpMediator)
    {
    }

    virtual ~CTlParent() { }

public:
    /* 当 UI 控件发生变化时，成员函数会发生变化 */
    virtual void changed()
    {
        m_pMediator->ctlChanged(this);
    }

    /* 设置 UI 控件是否启用 */
    virtual void Enable(bool sign) = 0;

protected:
    string m_caption;
    Mediator* m_pMediator; /* 指向中介类的指针 */
};

/**
 * @brief 普通按钮类
 *
 */
class Button : public CTlParent {
public:
    Button(Mediator* ptmpMediator, string caption)
        : CTlParent(ptmpMediator, caption)
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
};

/**
 * @brief 单选按钮
 *
 */
class RadioBtn : public CTlParent {
public:
    RadioBtn(Mediator* ptmpMediator, string caption)
        : CTlParent(ptmpMediator, caption)
    {
        /* 构造函数 */
    }

    void Enable(bool sign) override
    {
        /* 相关代码略，因为单选按钮是始终开启的 */
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
};

/**
 * @brief 具体显示编辑框
 *
 */
class EditCtl : public CTlParent {
public:
    EditCtl(Mediator* ptmpMediator, string caption)
        : CTlParent(ptmpMediator, caption)
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

private:
    string m_content = "";
};

// ---------- 具体中介者 ----------

class ConcreteMediator : public Mediator {
public: /* 为了方便外界使用，这里以 public 修饰 */
    Button* mp_login = nullptr; // 登录按钮
    Button* mp_logout = nullptr; // 退出按钮

    RadioBtn* mp_rbtn1 = nullptr; // 游客登录
    RadioBtn* mp_rbtn2 = nullptr; // 游客登录

    EditCtl* mp_edtctl1 = nullptr; // 账号编辑框
    EditCtl* mp_edtctl2 = nullptr; // 密码编辑框

public:
    ConcreteMediator() { }

public:
    virtual void creatCtrl()
    {
        mp_login = new Button(this, "登录");
        mp_logout = new Button(this, "登录");

        mp_rbtn1 = new RadioBtn(this, "游客登录");
        mp_rbtn2 = new RadioBtn(this, "账号登录");

        mp_edtctl1 = new EditCtl(this, "账号");
        mp_edtctl2 = new EditCtl(this, "密码");

        /* 设置缺省状态 */
        mp_login->Enable(true);
        mp_logout->Enable(true);

        mp_rbtn1->Selected(true);
        mp_rbtn2->Selected(false);

        mp_edtctl1->Enable(false);
        mp_edtctl2->Enable(false);
    }

    virtual ~ConcreteMediator()
    {
        if (mp_login) {
            delete mp_login;
            mp_login = nullptr;
        }
        if (mp_logout) {
            delete mp_logout;
            mp_logout = nullptr;
        }

        if (mp_rbtn1) {
            delete mp_rbtn1;
            mp_rbtn1 = nullptr;
        }
        if (mp_rbtn2) {
            delete mp_rbtn2;
            mp_rbtn2 = nullptr;
        }

        if (mp_edtctl1) {
            delete mp_edtctl1;
            mp_edtctl1 = nullptr;
        }
        if (mp_edtctl2) {
            delete mp_edtctl2;
            mp_edtctl2 = nullptr;
        }
    }

    /**
     * @brief 某个控件状态改变 （喵的，这就是屎山）
     *
     */
    virtual void ctlChanged(CTlParent* p_ctrl)
    {
        if (p_ctrl == mp_login) {
            cout << "开始游戏登录验证，根据验证结果决定是否进入游戏之中还是验证失败给出提示" << endl;
        } else if (p_ctrl == mp_logout) {
            cout << "游戏退出，再见" << endl;
        } else if (p_ctrl == mp_rbtn1) {
            cout << "开始游戏登录验证，根据验证结果决定是否进入游戏之中还是验证失败给出提示" << endl;
            mp_rbtn1->Selected(true);
            mp_rbtn2->Selected(false);
            mp_edtctl1->Enable(false);
            mp_edtctl2->Enable(false);
            mp_login->Enable(true);
        } else if (p_ctrl == mp_rbtn2) {
            cout << "开始游戏登录验证，根据验证结果决定是否进入游戏之中还是验证失败给出提示" << endl;
            mp_rbtn1->Selected(false);
            mp_rbtn2->Selected(true);
            mp_edtctl1->Enable(true);
            mp_edtctl2->Enable(true);
            if (mp_edtctl1->isContentEmpty()
                || mp_edtctl2->isContentEmpty()) {
                mp_rbtn1->Enable(false);
            } else {
                mp_rbtn1->Enable(true);
            }
        } else {
            if (mp_edtctl1->isContentEmpty()
                || mp_edtctl2->isContentEmpty()) {
                mp_login->Enable(false);
            } else {
                mp_login->Enable(true);
            }
        }
    }
};

int main(void)
{
    /* 创建各种 UI 控件 */
    ConcreteMediator mymedia; /* 创建中介者 */
    mymedia.creatCtrl();

    cout << "---------- 初始化完毕 ----------" << endl;

    mymedia.mp_rbtn2->changed();

    cout << "---------- 切换完毕 ----------" << endl;

    // ---------- 释放资源 ----------

    return 0;
}