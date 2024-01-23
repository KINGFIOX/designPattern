#include <ios>
#include <iostream>

using namespace std;

class graphic {
    // ---------- 单例模式相关 begin ----------
private:
    graphic() {};
    graphic(const graphic& tmpobj) { }
    graphic& operator=(const graphic& tmpobj) { }
    ~graphic() { }

public:
    static graphic& getInstance()
    {
        static graphic instance;
        return instance;
    }
    // ---------- 单例模式相关 end ----------

public:
    void display(bool enable) /* 全屏显示 */
    {
        cout << "图形 --> 是否全屏显示: " << enable << endl;
    }

    void effect(bool enable) /* 是否开启特效 */
    {
        cout << "图形 --> 是否开启特效: " << enable << endl;
    }

    void resolution(int index) /* 分辨率 */
    {
        cout << "图形 --> 分辨率设置选项: " << index << endl;
    }

    void antialiasing(bool enable) /* 是否开启抗锯齿 */
    {
        cout << "图形 --> 是否开启抗锯齿: " << enable << endl;
    }

    // 其他接口略
};

class sound {
    // ---------- 单例模式相关 begin ----------
private:
    sound() {};
    sound(const graphic& tmpobj) { }
    sound& operator=(const graphic& tmpobj) { }
    ~sound() { }

public:
    static sound& getInstance()
    {
        static sound instance;
        return instance;
    }
    // ---------- 单例模式相关 end ----------

public:
    void bgsound(bool enable) /* 开启背景声音 */
    {
        cout << "声音 --> 开启背景声音: " << enable << endl;
    }

    void envirsound(bool enable) /* 是否开启环境音效 */
    {
        cout << "声音 --> 是否开启环境音效: " << enable << endl;
    }

    void expsound(bool enable) /* 是否开启表情声音 */
    {
        cout << "声音 --> 是否开启表情声音: " << enable << endl;
    }

    void setvolume(int level) /* 声音大小设置 */
    {
        cout << "声音 --> 音量大小设置: " << level << endl;
    }

    // 其他接口略
};

class chatvoice {
    // ---------- 单例模式相关 begin ----------
private:
    chatvoice() {};
    chatvoice(const graphic& tmpobj) { }
    chatvoice& operator=(const graphic& tmpobj) { }
    ~chatvoice() { }

public:
    static chatvoice& getInstance()
    {
        static chatvoice instance;
        return instance;
    }
    // ---------- 单例模式相关 end ----------

public:
    void micvolume(int level) /* 麦克风音量大小 */
    {
        cout << "语音聊天 --> 麦克风音量大小: " << level << endl;
    }

    void micsens(int level) /* 麦克风灵敏度设置 */
    {
        cout << "语音聊天 --> 麦克风灵敏度设置: " << level << endl;
    }

    void chatvolume(int level) /* 聊天音量大小 */
    {
        cout << "语音聊天 --> 聊天音量大小: " << level << endl;
    }

    // 其他接口略
};

class conffacade {
    // ---------- 单例模式相关 begin ----------
private:
    conffacade() {};
    conffacade(const graphic& tmpobj) { }
    conffacade& operator=(const graphic& tmpobj) { }
    ~conffacade() { }
    // ---------- 单例模式相关 end ----------

public:
    static conffacade& getInstance()
    {
        static conffacade instance;
        return instance;
    }

public:
    void LowConfComputer()
    {
        graphic& g_gp = graphic::getInstance();
        g_gp.display(true);
        g_gp.effect(false);
        g_gp.resolution(2);
        g_gp.antialiasing(false);

        sound& g_snd = sound::getInstance();
        g_snd.bgsound(false);
        g_snd.envirsound(false);
        g_snd.expsound(false);
        g_snd.setvolume(15);

        chatvoice& g_cv = chatvoice::getInstance();
        g_cv.chatvolume(20);
        g_cv.micsens(50);
        g_cv.chatvolume(60);
    }

    /**
     * @brief 高配电脑，能达到最好效果项，全部开启
     *
     */
    void HighConfComputer()
    {
        graphic& g_gp = graphic::getInstance();
        g_gp.display(false);
        g_gp.effect(true);
        g_gp.resolution(0);
        g_gp.antialiasing(true);

        sound& g_snd = sound::getInstance();
        g_snd.bgsound(false);
        g_snd.envirsound(false);
        g_snd.expsound(false);
        g_snd.setvolume(15);

        chatvoice& g_cv = chatvoice::getInstance();
        g_cv.chatvolume(20);
        g_cv.micsens(50);
        g_cv.chatvolume(60);
    }
};

int main(void)
{
    conffacade& g_cffde = conffacade::getInstance();
    cout << " ---------- 低配电脑 ---------- " << endl;
    g_cffde.LowConfComputer();

    cout << " ---------- 高配电脑 ---------- " << endl;
    g_cffde.HighConfComputer();
}
