#include <iostream>

using namespace std;

/**
 * @brief 厨师类
 *
 */
class Cook {
public:
    void cook_fish()
    {
        cout << "做一盘红烧鱼菜品" << endl;
    }

    void cook_meat()
    {
        cout << "做一盘锅包肉菜品" << endl;
    }
};

int main(void)
{
    Cook* pc = new Cook();
    pc->cook_fish();
    pc->cook_meat();

    delete pc;
    return 0;
}