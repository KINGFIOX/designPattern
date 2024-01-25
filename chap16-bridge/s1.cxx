#include <iostream>

using namespace std;

class Image {
public:
    /**
     * @brief 根据 pData(缓冲区) 中的内容以及 iDataLen 所指示的缓冲区长度，将这些数据显示出来
     *
     * @param pfilename
     */
    void draw(const char* pfilename)
    {
        int iLen = 0;
        char* pdata = parsefile(pfilename, iLen);
        if (iLen > 0) {
            cout << "显示 pData 所指向的缓冲区中图像数据" << endl;
            delete[] pdata;
        }
    }

    virtual ~Image() { }

private:
    virtual char* parsefile(const char* pfilename, int& iLen) = 0;
};

class Image_png : public Image {
private:
    /**
     * @brief 读取 png 文件内容并进行解析，最终整理成统一的二进制数据格式返回
     *
     * @param pfilename
     * @param iLen
     * @return char*
     */
    char* parsefile(const char* pfilename, int& iLen) override
    {
        // 以下是模拟代码，模拟从图像文件中读取到的数据，最终转换成了 100 个字节的数据格式（实现约定好的格式规范）
        cout << "开始分析 png 文件中的数据并将分析结果放到 pData 中" << endl;
        iLen = 100;
        char* presult = new char[iLen];
        // ...
        return presult;
    }
};

class Image_jpg : public Image {
private:
    /**
     * @brief 读取 jpg 文件内容并进行解析，最终整理成统一的二进制数据格式返回
     *
     * @param pfilename
     * @param iLen
     * @return char*
     */
    char* parsefile(const char* pfilename, int& iLen) override
    {
        // 以下是模拟代码，模拟从图像文件中读取到的数据，最终转换成了 100 个字节的数据格式（实现约定好的格式规范）
        cout << "开始分析 jpg 文件中的数据并将分析结果放到 pData 中";
        iLen = 100;
        char* presult = new char[iLen];
        // ...
        return presult;
    }
};

int main(void)
{
    Image_png pImg;
    pImg.draw("./fuck.png");
}