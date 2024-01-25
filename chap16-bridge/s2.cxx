/**
 * @file s2.cxx 桥接模式
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

using namespace std;

class ImageOS {
public:
    virtual void draw(char* pData, int iLen) = 0;
    virtual ~ImageOS() { } /* 做父类时析构函数应该为虚函数 */
};

class ImageOS_Windows : public ImageOS {
public:
    void draw(char* pData, int iLen) override
    {
        cout << "在 windows 操作系统下显示 pData 所指向的缓冲区中的图像数据。" << endl;
        /* 具体处理代码 略 */
    }
};

class ImageOS_Linux : public ImageOS {
public:
    void draw(char* pData, int iLen) override
    {
        cout << "在 linux 操作系统下显示 pData 所指向的缓冲区中的图像数据。" << endl;
        /* 具体处理代码 略 */
    }
};

class ImageOS_Mac : public ImageOS {
public:
    void draw(char* pData, int iLen) override
    {
        cout << "在 mac 操作系统下显示 pData 所指向的缓冲区中的图像数据。" << endl;
        /* 具体处理代码 略 */
    }
};

// ----------   ----------

class ImageFormat {
public:
    ImageFormat(ImageOS* pimgOS)
        : m_pImgOS(pimgOS)
    {
    }

    virtual void parsefile(const char* pfilename) = 0; /* 根据文件名分析文件内容 */
    virtual ~ImageFormat() { } /* 做父类时析构函数应该为虚函数 */

protected:
    ImageOS* m_pImgOS; /* 委托 */

protected:
};

class Image_png : public ImageFormat {
public:
    Image_png(ImageOS* pimgOS) /* 继承构造 */
        : ImageFormat(pimgOS)
    {
    }

    void parsefile(const char* pfilename) override
    {
        cout << "开始分析 png 文件中的数据并将分析结果放到 pData 中" << endl;
        int iLen = 100;
        char* presult = new char[iLen];
        m_pImgOS->draw(presult, iLen);
        // ...

        // 释放资源
        delete[] presult;
    }
};

class Image_jpg : public ImageFormat {
public:
    Image_jpg(ImageOS* pimgOS) /* 继承构造 */
        : ImageFormat(pimgOS)
    {
    }

    void parsefile(const char* pfilename) override
    {
        cout << "开始分析 png 文件中的数据并将分析结果放到 pData 中" << endl;
        int iLen = 100;
        char* presult = new char[iLen];
        m_pImgOS->draw(presult, iLen);
        // ...

        // 释放资源
        delete[] presult;
    }
};

class Image_bmp : public ImageFormat {
public:
    Image_bmp(ImageOS* pimgOS) /* 继承构造 */
        : ImageFormat(pimgOS)
    {
    }

    void parsefile(const char* pfilename) override
    {
        cout << "开始分析 png 文件中的数据并将分析结果放到 pData 中" << endl;
        int iLen = 100;
        char* presult = new char[iLen];
        m_pImgOS->draw(presult, iLen);
        // ...

        // 释放资源
        delete[] presult;
    }
};

int main(void)
{
    /* 通过在主流程中 装配 */
    ImageOS* pImgOS_Windows = new ImageOS_Windows();
    ImageFormat* pImg_Png = new Image_png(pImgOS_Windows);
    pImg_Png->parsefile("fuck.png");

    delete pImg_Png;
    delete pImgOS_Windows;
}