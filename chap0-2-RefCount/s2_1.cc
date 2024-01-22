#include <cstring>
#include <string>
class MyString {
public:
    MyString(const char* tmpstr = "")
        : pvalue(new _stringValue(tmpstr)) /* 构造函数 */
    {
    }
    MyString(const MyString& tmpstr)
    // : pvalue(tmpstr.pvalue) /* 拷贝构造 */
    {
        if (tmpstr.pvalue->shareable) { /* 允许被共享 */
            this->pvalue = tmpstr.pvalue;
            ++pvalue->refcount;
        } else {
            this->pvalue = new _stringValue(tmpstr.pvalue->point);
        }
    }
    MyString& operator=(const MyString& tmpstr) /* 拷贝赋值运算符 */
    {
        if (this == &tmpstr) {
            return *this;
        }

        --this->pvalue->refcount;
        if (this->pvalue->refcount == 0) {
            delete pvalue;
        }
        this->pvalue = tmpstr.pvalue;
        ++this->pvalue->refcount;
        return *this;
    }
    /*
         const char& operator[](int idx) const
            {
                    return this->pvalue->point[idx];
            }
     */
    char& operator[](int idx)
    {
        if (this->pvalue->refcount > 1) {
            /* diverge */
            --this->pvalue->refcount;
            this->pvalue = new _stringValue(pvalue->point);
        }
        this->pvalue->shareable = false;
        return this->pvalue->point[idx];
    }
    ~MyString()
    {
        --this->pvalue->refcount;
        if (this->pvalue->refcount == 0) {
            delete pvalue;
        }
    }

private:
    struct _stringValue {
        size_t refcount; // 引用技术
        char* point; // 指向实际字符串
        bool shareable; /* 是否能够被共享 */
        _stringValue(const char* tmpstr)
            : refcount(1)
            , shareable(true) /* 当调用 operaotr[] 的时候，sharedable=false */
        {
            point = new char[strlen(tmpstr) + 1];
            strcpy(point, tmpstr);
        }
        ~_stringValue()
        {
            delete[] point;
        }
    };

private:
    _stringValue* pvalue;
};

int main(void)
{
}