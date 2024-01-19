#include <iostream>
using namespace std;

class Timer {
    Timer(int inttimes); // 间隔多少毫秒，调用一次callback
    virtual void CallBack();
    //  .. 定时器的编写
};

class MsgQueue : private Timer {
    // ... 入消息队列，出消息队列
private:
    virtual void CallBack(); // 子类重写父类的CallBack函数，到时间后会被调用的虚函数（神奇）
};