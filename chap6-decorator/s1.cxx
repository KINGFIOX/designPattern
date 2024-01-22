/**
 * @file s1.cxx 装饰器模式
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

using namespace std;

/**
 * @brief 抽象控件类
 *
 */
class Control {
public:
    virtual ~Control() = default;
    virtual void draw() = 0; // 将自身绘制到屏幕上
};

/**
 * @brief 列表控件类
 *
 */
class ListCtrl : public Control {
public:
    virtual void draw() override
    {
        cout << "绘制普通的列表控件!" << endl; /* 具体可以用 openGL 来绘制 */
    }
};

/**
 * @brief 抽象的装饰器类
 *
 */
class Decorator : public Control {
public:
    Decorator(Control* tmpCtrl)
        : m_control(tmpCtrl)
    {
    }

    virtual void draw() override
    {
        m_control->draw(); /* 虚函数，调用的是哪个draw，取决于 m_control 指向的对象 */
    }

private:
    Control* m_control; /* 需要被装饰的其他控件，这里用的是 Control *，比方说这里指向 ListCtrl */
};

// ---------- 具体的装饰器类 ----------

/**
 * @brief 边框装饰器类
 *
 */
class BorderDec : public Decorator {
public:
    BorderDec(Control* tmpCtrl)
        : Decorator(tmpCtrl)
    {
    }

    virtual void draw() override
    {
        Decorator::draw(); /* 调用父类的 draw，这个是装饰模式的典型写法，保持以往已经绘制出的内容 */
        drawBorder(); // 也要绘制自己的内容
    }

private:
    void drawBorder()
    {
        cout << "绘制边框!" << endl;
    }
};

/**
 * @brief 绘制垂直滚动条
 *
 */
class VerScrollBarDec : public Decorator {
public:
    VerScrollBarDec(Control* tmpCtrl)
        : Decorator(tmpCtrl)
    {
    }

    virtual void draw() override
    {
        Decorator::draw();
        DrawVerScrollBar();
    }

private:
    void DrawVerScrollBar()
    {
        cout << "绘制垂直滚动条" << endl;
    }
};

/**
 * @brief 绘制水平滚动条
 *
 */
class HorScrollBarDec : public Decorator {
public:
    HorScrollBarDec(Control* tmpCtrl)
        : Decorator(tmpCtrl)
    {
    }

    virtual void draw() override
    {
        Decorator::draw();
        DrawHorScrollBar();
    }

private:
    void DrawHorScrollBar()
    {
        cout << "绘制垂直滚动条" << endl;
    }
};

int main(void)
{
    // (1) 首先绘制普通的列表控件
    Control* pListCtrl = new ListCtrl;

    // (2) 接着，借助普通的列表控件，可以通过边框装饰器绘制出一个 带边框的列表控件
    Decorator* pListCtrl_b = new BorderDec(pListCtrl);

    // (3) 然后，绘制出一个 带边框、垂直滚动条的列表控件
    Decorator* pListCtrl_b_v = new VerScrollBarDec(pListCtrl_b);
    pListCtrl_b_v->draw();

    cout << "----------" << endl;

    // (4) 最后，绘制出一个 水平滚动条的列表控件
    Decorator* pListCtrl_b_v_h = new HorScrollBarDec(pListCtrl_b_v);
    pListCtrl_b_v_h->draw();

    return 0;
}