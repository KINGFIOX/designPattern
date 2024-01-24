#include <iostream>

using namespace std;

enum EnumColor {
    Black,
    White
};

struct Position {
    int m_x;
    int m_y;

    Position(int tmpx, int tmpy)
        : m_x(tmpx)
        , m_y(tmpy)
    {
    }
};

/**
 * @brief 棋子类
 *
 */
class Piece {
public:
    Piece(EnumColor tmpcolor, Position tmppos)
        : m_color(tmpcolor)
        , m_pos(tmppos)
    {
    }

    void draw() // 绘制棋子
    {
        if (m_color == Black) {
            cout << "在位置: (" << m_pos.m_x << " , " << m_pos.m_y << ") 处绘制了一个黑色棋子!" << endl;
            /*  */
        } else {
            cout << "在位置: (" << m_pos.m_x << " , " << m_pos.m_y << ") 处绘制了一个白色棋子!" << endl;
            /*  */
        }
    }

private:
    EnumColor m_color;
    Position m_pos;
};

int main(void)
{
    Piece* p_piece1 = new Piece(Black, { 3, 3 });
    p_piece1->draw();
    Piece* p_piece2 = new Piece(White, { 5, 5 });
    p_piece2->draw();
    Piece* p_piece3 = new Piece(White, { 6, 6 });

    delete p_piece3;
    delete p_piece2;
    delete p_piece1;
    return 0;
}