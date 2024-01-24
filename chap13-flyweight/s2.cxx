#include <iostream>
#include <map>
#include <utility>

using namespace std;

struct Position {
    int m_x;
    int m_y;

    Position(int tmpx, int tmpy)
        : m_x(tmpx)
        , m_y(tmpy)
    {
    }
};

enum EnumColor {
    Black,
    White
};

class Piece {
public:
    virtual ~Piece() { }

public:
    virtual void draw(Position tmppos) = 0;
};

class BlackPiece : public Piece {
public:
    virtual void draw(Position tmppos) override
    {
        cout << "在位置: (" << tmppos.m_x << " , " << tmppos.m_y << ") 处绘制了一个黑色棋子!" << endl;
    }
};

class WhitePiece : public Piece {
public:
    virtual void draw(Position tmppos) override
    {
        cout << "在位置: (" << tmppos.m_x << " , " << tmppos.m_y << ") 处绘制了一个白色棋子!" << endl;
    }
};

/**
 * @brief 创建棋子的 简单工厂
 *
 */
class PieceFactory {
public:
    virtual ~PieceFactory()
    {
        /* 释放内存 */
        for (auto v : m_FlyWeightMap) {
            delete v.second;
        }
        m_FlyWeightMap.clear();
    }

    /**
     * @brief Get the Fly Weight object 获取被共享的 棋子对象
     *
     * @param tmpcolor
     * @return Piece*
     */
    Piece* getFlyWeight(EnumColor tmpcolor) // FIXME 核心代码
    {
        auto iter = m_FlyWeightMap.find(tmpcolor);
        if (iter == m_FlyWeightMap.end()) {
            /* 没有该享元对象，那么就创建出来 */
            Piece* tmpfw = nullptr;
            if (tmpcolor == Black) {
                tmpfw = new BlackPiece();
            } else {
                tmpfw = new WhitePiece();
            }
            m_FlyWeightMap.insert(make_pair(tmpcolor, tmpfw));
            return tmpfw;
        } else {
            return iter->second;
        }
    }

private:
    std::map<EnumColor, Piece*> m_FlyWeightMap; // 用 map 容器保存所有的享元对象，一共就两个香享元对象（黑色棋子一个，白色棋子一个）
};

int main(void)
{
    PieceFactory* pFactory = new PieceFactory;

    Piece* p_piece1 = pFactory->getFlyWeight(Black);
    p_piece1->draw({ 3, 3 }); /* 小黑子落子到(3, 3) */

    Piece* p_piece2 = pFactory->getFlyWeight(White);
    p_piece2->draw({ 1, 1 });
}