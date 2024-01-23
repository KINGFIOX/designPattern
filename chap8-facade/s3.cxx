/**
 * @file s3.cxx 外观模式
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

class Screen {
public:
    void On()
    {
        cout << "屏幕打开了!" << endl;
    }
    void Off()
    {
        cout << "屏幕关闭了!" << endl;
    }
};

class Light {
public:
    void On()
    {
        cout << "灯光打开了!" << endl;
    }
    void Off()
    {
        cout << "灯光关闭了!" << endl;
    }
};

class Speaker {
public:
    void On()
    {
        cout << "音响打开了!" << endl;
    }
    void Off()
    {
        cout << "音响关闭了!" << endl;
    }
};

class DVDPlayer {
public:
    void On()
    {
        cout << "DVD播放器打开了!" << endl;
    }
    void Off()
    {
        cout << "DVD播放器关闭了!" << endl;
    }
};

class PlayStation {
public:
    void On()
    {
        cout << "游戏机打开了!" << endl;
    }
    void Off()
    {
        cout << "游戏机关闭了!" << endl;
    }
};

/**
 * @brief 家庭影院外观类
 *
 */
class HomeThreaterFacade {
public:
    void WatchMovie()
    {
        scnObj.On();
        lgObj.Off();
        spkObj.On();
        dpObj.On();
        psObj.Off();
    }

    void PlayGame()
    {
        scnObj.On();
        lgObj.On();
        spkObj.On();
        dpObj.Off();
        psObj.On();
    }

private:
    Screen scnObj;
    Light lgObj;
    Speaker spkObj;
    DVDPlayer dpObj;
    PlayStation psObj;
};

int main(void)
{
    HomeThreaterFacade htf;
    cout << " ---------- 玩游戏 ---------- " << endl;
    htf.PlayGame();
}