# chap0 - 2 - 引用计数基础理论与实践

## 1 - shared_ptr 实现及 string 存储简单说明

### shared_ptr 智能指针实现简单说明

共享所有权来管理指向对象的生命周期

```cpp
int main(void)
{
    shared_ptr<int> myp(new int(5));
    int icount = myp.use_count();
    cout << "icount = " << icount << endl;
    {
        cout << "----------" << endl;
        shared_ptr<int> myp2(myp);
        icount = myp2.use_count();
        cout << "icount = " << icount << endl;
        cout << "----------" << endl;
    }
    icount = myp.use_count();
    cout << "icount = " << icount << endl;
}
```

输出：

```sh
icount = 1
----------
icount = 2
----------
icount = 1
```

### string 类型字符串存储方式的简单说明

string 的实现方式：比较经典的有：eager-copy（贪婪的、粗暴的拷贝）方式、copy-on-write（写时复制）方式、small-string-optimization（短字符串优化）方式

#### eager-copy

比方说有下面这段代码：

```cpp
int main(void)
{
    string str1 = "i love china";
    string str2 = str1;
    printf("str1所存储的字符串的地址=%p\n", str1.c_str());
    printf("str2所存储的字符串的地址=%p\n", str2.c_str());
}
```

输出：

```sh
str1所存储的字符串的地址=0x16da0ede8
str2所存储的字符串的地址=0x16da0edd0
```

我们会发现，这两个字符串的地址是不一样的，这应该是 eager-copy 数据存储方式。

缺点就是：浪费内存。优点就是：代码简单

#### copy-on-write（写时复制）

这个与：引用技术特别像。只不过分离的时间不一样。

优点是：节省内存、拷贝的速度快。

而且这个 fork() 父进程 与 子进程 的内存空间是不一样的，
但是执行效率很高：就是 copy-on-write

## 2- 通过 copy-on-write 方式实现 mystring 类

### 骨架 与 计数设计

创建一个新结构， stringvalue：计数器，指向字符串的指针。

stringValue 对象的意义：把 “要保存的字符串” 以及 “对这个字符串的引用计数” 统一保存在一个 stringValue 对象中。

```cpp
struct _stringValue {
	size_t refcount; // 引用技术
	char* point; // 指向实际字符串
	_stringValue(const char* tmpstr) : refcount(1)
	{
		point = new char[strlen(tmpstr) + 1];
		strcpy(point, tmpstr);
	}
	~_stringValue()
	{
		delete[] point;
	}
};
```

### 构造函数

```cpp
MyString(const char* tmpstr = "")
	: pvalue(new _stringValue(tmpstr)) /* 构造函数 */
{
}
```

### 拷贝构造函数

```cpp
MyString(const MyString& tmpstr) : pvalue(tmpstr.pvalue) /* 拷贝构造 */
{
	// MyString kxstr3 = kxstr1 会调用 MyString 类的拷贝构造函数
	// 让 kxstr3 的 pvalue 指向 kxstr1 的 pvalue
	++pvalue->refcount;
}
```

### 析构函数

```cpp
~MyString()
{
	--pvalue->refcount;
	if (pvalue->refcount == 0) {
		delete pvalue;
	}
}
```

### 拷贝赋值运算符

```cpp
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
```

### 外部加锁、内部加锁、写时复制

外部加锁：调用者负责加锁，由调用者决定跨线程使用共享对象时加锁

内部加锁：对象将所有对自己的访问串行化，通过为每个成员函数加锁的方法来实现，这样就不用外部加锁了（内部加锁并不常见）

### 通过指针修改 mystring 所指字符串的内容 copy-on-write

实现出 某些接口的多线程版本（内部加锁） 的动机和必要性是值得深思的（就是不太赞同）。
一般应该使用外部接口。内部加锁一般只适合操作很独立、内部很完整的接口

```cpp
const char& operator[](int idx) const
{
	return this->pvalue->point[idx];
}
char& operator[](int idx)
{
	if (this->pvalue->refcount > 1) {
		/* diverge */
		--this->pvalue->refcount;
		this->pvalue = new _stringValue(pvalue->point);
	}
	return this->pvalue->point[idx];
}
```

然而，事实上，编译器是没法判断：

```cpp
cout << kxstr1[0] << endl; // ---> 非 const
kxstr1[0] = 'U'; // ---> 非 const
// TODO
```

编译器会非常简单粗暴的使用限制最小的，也就是非 const 的

## 3 - copy-on-write

甚至有下面这段代码

```cpp
kxstr4 = "i love china!";
char* p0 = &kxstr4[0];
MyString kxstr5 = kxstr4;
*p0 = 'T';
```

我们想的是：这里我们只会修改 kxstr4，但是不能修改 kxstr5。

几个方案：

1. 不解决，但是文档中说明
2. 解决

### \_stringValue 中增加 是否能够被共享的标记

```cpp
struct _stringValue {
	size_t refcount; // + 引用技术 +
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
```

拷贝构造函数的变化

```cpp
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
```

也就是说，一旦有`operator[]`以后，就不允许共享了
