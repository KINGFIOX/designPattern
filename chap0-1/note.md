# chap0 - 1 - 类和对象

## 1 - 静态成员对象

### 类中的 类类型 静态成员变量

结论：类中的静态成员变量，及时没有被使用，娥辉被构造和析构

inline, C++17 中 引入 “inline 静态成员变量”

也就是不需要在类外单独额外的初始化了，只需要加入 inline 关键字即可。

也就是如下的结果

```cpp
/*
class B {
public:
    static A m_sa;
};
A B::m_sa;
*/

class B {
public:
    inline static A m_sa;
};
```

上面这段代码输出：

```sh
A::A()缺省构造函数执行了
A::A()析构函数执行了
```

说明了系统给这个 m_sa 静态成员变量分配了内存，并且进行了初始化。

如果这个 m_sa 不是类类型，而是简单类型，那么如果源码中没有用到这个静态成员变量，
编译器很可能部位这个 m_sa 分配内存

### 函数中的静态对象

如果该函数没有被调用过，那么这个静态对象就不会被构造。
即使这个函数被调用多次，该静态对象只会被构造一次

### 全局对象的构造顺序问题

全局对象、静态对象。

C++只会保证 单个编译单元中（比方说单个.cc 文件） 全局、静态对象的初始化顺序（从上到下依次）。

如果一个项目中有多个.cc 源文件，每个源文件都可能定义着一些不同的全局对象，
那么这些全局对象的构造顺序（初始化顺序）是无规律的

先构造的，调用了后被构造了成员对象会怎么样？

千万不要写出这样的代码：构造一个全局对象的时候，需要用到另一个全局对象，因为根本无法确定另一个全局对象是否被构造出来了

如果一定要这样用的话，可以变通一下。

但是如果是通过手动调用构造的话，遇到多线程会有问题（双重检查锁定），
当然也可以是：通过手动的方式，率先构造出来。

## 2 - 拷贝构造函数和拷贝赋值运算符

### 拷贝构造函数 和 拷贝赋值运算符的书写

### 对象自我赋值产生的问题

```cpp
A& operator=(const A& tmpobj) {
	delete m_cap;
	m_cap = new char [100]; // <--- 这里有问题
	memcpy(m_cap, tmpobj.m_cap, 100);
}
```

可以先添加`if`，简单粗暴，但是效率可能会有问题

```cpp
A& operator=(const A& tmpobj) {
	if (this == &tmpboj) {
		return *this;
	}
	delete m_cap;
	m_cap = new char [100];
	memcpy(m_cap, tmpobj.m_cap, 100);
}
```

还可以先拷贝，再删除（顺序）。
当然效率也不一定有提升

```cpp
A& operator=(const A& tmpobj) {
	char *ptmp = new char[100];
	memcpy(ptmp, tmpobj.m_cap, 100);
	delete m_cap;
	m_cap = ptmp;
}
```

### 继承关系下 构造函数 和 拷贝赋值运算符的书写

继承的话，要记得设置 虚析构。

自动执行父类的拷贝构造函数 和 拷贝赋值运算符，如果子类没有拷贝构造函数的话。
但是，如果程序员在子类中写了自己的拷贝构造函数 和 拷贝赋值运算，
那么对于父类中的拷贝构造函数和拷贝赋值运算符 的 调用，就变成了程序员自己的责任（编译器不会自动操作）

初始化列表中，调用父类拷贝构造函数

```cpp
B(const B& tmpobj) : A(tmpobj) { }
```

只能在初始化列表中，调用父类的拷贝构造函数

```cpp
B(const B& tmpobj) {
	A(tmpobj);  // <--- 这种代码具有二义性，比方说还可以解释成：临时对象，甚至是重定义错误（因为解释成了 B tmpobj = A(tmpobj);）
}
```

拷贝赋值运算符

```cpp
B& operator=(const B& tmpobj) {
	A::operator(tmpobj);
	return *this;
}
```

### 拷贝构造函数 和 拷贝赋值运算符 中重复代码的处理

就是我们会发现，这个 拷贝构造函数 和 拷贝赋值运算符，这两个函数长得很像。

## 3 - 类的 public 继承 (is-a 关系) 及 代码编写规则

子类继承父类的方式 有三种：public protected private 继承

public 代表的是一种 is-a (is a kind of) 的关系。is-a 表示 “是一个”：通过这个子类产生的对象 也一定是一个 父类对象

父类表现的是一种 更泛华的改变，而子类表现的是一种更加特化的概念。

比方说 rectangle --> square

public 继承关系的检验规则：

1. 能够在父类对象上做的行为也必然能在子类的对象上做，每个子类对象同时也都是一个父类对象。
   （里氏替换原则，liskov 替换）：任何 base 出现的地方，都应该可以无差别的使用子类替换

### 子类遮盖父类的普通成员函数

这就需要 virtual 了。父类有`virtual void eat`，子类有`void eat`。
子类遮蔽了父类的普通成员函数。

但是 public 继承 其实不应该 函数遮蔽。
因为这相当于是：子类否定了父类的成员函数，这相当于是否定了 public 的 is-a 关系。

### 父类的纯虚函数接口

纯虚函数让子类继承父类的成员接口。

纯虚函数意味着什么？

1. 纯虚函数所在的类变成了抽象类，抽象类不能用来生成该类对象
2. 任何从抽象类 human 继承的子类，都要定义该虚函数自己的实现方法。
   也就是说，只继承了一个成员函数的接口。

日后，如果需要在子类中实现具体的函数代码时，就可以在父类中定义一个纯虚函数

### 父类的虚函数接口

虚函数：让子类继承父类的程序函数接口和实现，子类还可以提供自己的新的实现

### 为 纯虚函数 指定实现体

比方说，我有了一个虚函数，但是我忘记了在子类中实现，那么程序就会有逻辑错误。
为了避免这种问题，可以使用纯虚函数。

纯虚函数也是可以有实现体的（类外指定）

```cpp
class Human{
public:
	virtual void avlf() = 0;
};

void Human::avlf() {
	cout << "大概75岁" << endl;
}
```

为什么 纯虚函数 还要有实现体呢？纯虚函数不是强制重写吗？

比方说，有众多子类，然后子类的 纯虚函数重写都是一致的。
那么我们就可以偷个懒

```cpp
class Human{
public:
	virtual void avlf() = 0;
};

void Human::avlf() {
	cout << "大概75岁" << endl;
}

class woman : public Human {
	virtual void avlf() {
		Human::avlf();  // 调用父类的纯虚函数
	}
};
```

为纯虚函数指定实现体:

1. 强制子类必须去实现该函数，以免产生一些重要的程序代码逻辑错误
2. 让一些确实不需要单独实现 avlf 接口的子类有机会直接调用父类的 avlf 成员函数

### 类的 public 继承 (is-a 关系) 综合范例

```cpp
class A { };
class B : public A { };
class C : public B { };

void myfunc(A tmpa)
{
    cout << "myfunc(A tmpa)执行了" << endl;
}

void myfunc(C tmpc)
{
    cout << "myfunc(C tmpc)执行了" << endl;
}

int main(void)
{
    B myobjB;
    myfunc(myobjB); // myfunc(A tmpa)执行了

    C myobjC;
    myfunc(myobjC); // myfunc(C tmpc)执行了
    return 0;
}
```

就近原则

```cpp
class A { };
class B : public A { };
class C : public B { };

void myfunc(A tmpa)
{
    cout << "myfunc(A tmpa)执行了" << endl;
}

void myfunc(B tmpB)
{
    cout << "myfunc(B tmpb)执行了" << endl;
}

int main(void)
{
    C myobjC;
    myfunc(myobjC); // myfunc(B tmpb)执行了
    return 0;
}
```

## 4 - 类与类之间的 组合关系 和 委托关系

组合关系：一个类的定义中 含有其他类类型的成员变量

### 组合关系

#### has-a 关系（也成为 is-part-of 关系）

```cpp
class Info {
private:
    std::string m_name;
    int m_gender;
    int m_age;
};

class Human {
public:
    Info m_info;
};
```

human has a info，也可以认为 info is a part of human

#### is-implemented-in-terms-of 关系

“根据...实现出...”的意思。
比方说，我们的标准库有`std::multimap`容器，允许 key 重复，
我们现在想要 通过 multimap 实现 single-map。

如果是继承关系，也就是`class MyMap : public multimap { };`其实是不合适的，
因为这里并不是一个`is-a`的关系

我们可以：

```cpp
template <typename T, typename U>
class smap {
public:
    void insert(const T& key, const U& value)
    {
        if (container.find(key) != container.end()) {
            return;
        }
        container.insert(std::make_pair(key, value));
    }

private:
    std::multimap<T, U> container;
};
```

smap 与 multimap 容器之间的关系就是 is-implemented-in-terms-of 这种组合关系。
进一步说明就是：根据 multimap 容器实现出了 smap 容器，
实现方法也是在 smap 类中定义了一个 multimap 类型的成员变量 container

### 组合关系的 UML 图

实心菱形框：意味着如果创建了一个 human 类对象（整体对象），其中会包含 info 类对象（成员对象）。
这两个对象具有统一的生命周期，一旦整体对象不存在了，成员对象也将不存在

### 委托关系（聚合关系）delegation

空心菱形框：一个类中，包含指向另一个类的指针。整体对象，成员对象可以具有不一致的生命周期。

```cpp
class A {
public:
    void funca()
    {
        cout << "funca()被调用了" << endl;
    }
};

class B {
public:
    B(A* tmpa)
        : m_pa(tmpa)
    {
    }
    void funcb()
    {
        m_pa->funca();
    }

private:
    A* m_pa;
};

int main(void)
{
    A* pa = new A;
    B* pb = new B(pa);

    pb->funcb(); // funca()被调用了

    delete pa;
    delete pb;
}
```

### public 继承关系下的代码编写规则

1. 父类的普通成员函数，子类不应该去覆盖，如果需要覆盖，那么应该在父类中将该普通成员函数修改为虚函数
2. 子类的纯虚函数，定义了一个结构，子类等于继承了该接口，具体的实现代码需要子类自己去完成
3. 父类的普通虚函数（非纯虚函数）。不但定义了一个接口，还书写了实现代码，子类继承了该接口，
   子类可以书写自己的实现代码 来取代 父类的实现代码，也可以不书写自己的实现代码 而使用 父类的 缺省实现代码
4. 在可以使用非 public 继承时，就不要使用 public 继承。为什么单独说这条，因为有程序员在写代码时，只要涉及到继承，就使用 public 继承

## 5 - 类的 private 继承探讨

问题代码：

```cpp
class Human {
public:
    virtual ~Human() { }
};

class Man : private Human {
public:
};

int main(void)
{
    Man mymen;
    Human& myhuman1 = mymen; // 父类引用绑定子类对象
    Human* myhuman2 = new Man; // 父类指针指向子类对象
}
```

这段代码就报错了

```sh
s5_1.cc:16:23: error: cannot cast 'Man' to its private base class 'Human'
    Human& myhuman1 = mymen; // 父类引用绑定子类对象
                      ^
s5_1.cc:9:13: note: declared private here
class Man : private Human {
            ^~~~~~~~~~~~~
s5_1.cc:17:23: error: cannot cast 'Man' to its private base class 'Human'
    Human* myhuman2 = new Man; // 父类指针指向子类对象
                      ^
s5_1.cc:9:13: note: declared private here
class Man : private Human {
            ^~~~~~~~~~~~~
2 errors generated.
```

msvc 上报错是：从 `Man*` 到 `Muman*` 的转换存在，但无法访问。

### private 继承 ---> 组合关系

private 继承，是一种组合关系，更确切的说，是组合关系中的 is-implemented-in-terms-of 关系。

一般 **优先考虑使用组合关系**，只有在一些比较特殊的情况和必要的情况下，
比方说牵扯到一些 protected 成员、private 成员、虚函数等。才考虑到用 private 继承来表达 组合关系

比方说，我们要写一个消息队列类 msgQueue，我们已经有了一个 Timer 类，可能是第三方开发的

```cpp
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
```

### 不能被拷贝的类对象

形而上学一些，因为不是 is-a 关系，因此不能 里氏替换，
因为是组合关系，而且甚至是 private 成员，因此就不能拷贝构造

```cpp
class A {};
class B : private A {};

void func(A tmp);

B bobj;
A aobj = bobj;  // --x--
func(bobj);  // --x--
```

## 6 - 不能被 拷贝构造 和 拷贝赋值 的类对象

### C++11 = delete

```cpp
class A {
public:
    A() = default;
    A(const A& tmp) = delete;
    A& operator=(const A&) = delete;
};

int main(void)
{
    A aobj1;
    A aobj2(aobj1); // call to deleted constructor of 'A'
    A aobj3;
    aobj3 = aobj2; // overload resolution selected deleted operator '='
    return 0;
}
```

### private 拷贝构造 和 拷贝赋值 ---> 但是友元、成员函数依然可以调用

```cpp
class A {
public:
    A() = default;
    A(const A& tmp) = default;

private:
    A& operator=(const A&) = default;
};

int main(void)
{
    A aobj1;
    A aobj2(aobj1);
    A aobj3;
    aobj3 = aobj2; // 'operator=' is a private member of 'A'
    return 0;
}
```

### 只保留声明，不实现

这个时候，编译器会报连接错误：一个无法解析的外部符号(msvc)

```cpp
ld: Undefined symbols:
  A::A(A const&), referenced from:
      A::func(A const&) in s6_3-7f138f.o
  A::operator=(A const&), referenced from:
      A::func(A const&) in s6_3-7f138f.o
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

### 借助一个 class noncopyable 实现 （这算是一种设计模式）

```cpp
class noncopyable {
protected:
    noncopyable() { }
    ~noncopyable() { }

private:
    noncopyable(const noncopyable&);
    noncopyable& operator=(const noncopyable&);
};

class A : private noncopyable {
};
```

1. A 中不重写 拷贝构造函数、拷贝赋值函数。
   如果发生了 A 的拷贝构造、拷贝赋值，根据继承关系，子类会调用父类的 拷贝构造函数、拷贝赋值函数，
   然而，在 A 中并不能调用 父类的私有成员函数

2. A 中重写了 拷贝构造函数、拷贝赋值函数。
   如果调用了 A 的拷贝构造、拷贝赋值，那么也会自动调用父类的 拷贝构造、拷贝赋值，
   然后在 A 中并不能调用 父类的私有成员函数

为什么使用 private 继承？
根据意思，应该是 is-implemented-in-terms-of(组合关系)，根据...实现...的关系

## 7 - 虚析构函数的内存泄露问题深谈

如果一个类不做父类，是不应该给该类增加一个 虚析构函数的。

不要随便 public 继承一个自己不熟悉的类，万一别人写的代码没有 虚析构 呢？
可能会导致内存泄露。

作为第三方库开发商，如果我们不想让别人继承我开发的类，我可以厚道一些，加一个`final`

### 回顾 private 继承

1. 如果子类 public 继承父类，那么父类指针可以指向子类对象
2. 如果子类 private 或者 protected 继承父类，那么父类指针不可以指向子类的对象。
3. 如果让父类指针指向子类对象，那么就需要用到 public 继承，这个时候父类就需要提供 虚析构函数

### 类中存在 虚析构函数 的情形：

1. 一般如果父类中有其他虚函数，意味着会按照多态的方式使用该父类，
   也就是一般会存在父类指针指向子类的对象的情形，
   那么此时，父类中应该有一个 public 修饰虚析构函数
2. 如果代码中并不出现父类指针指向子类对象 的多态情形，那么父类中不需要有虚析构函数。
   同时，在文档中应该明确告知开发者不应该 public 继承该类，而应该尽量用 private 继承

### noncopyable 的 public 继承

如果是 private 继承，当父类指针指向子类对象的时候，会出现报错：

```cpp
noncopyable* p = new A; // cannot cast 'A' to its private base class 'noncopyable'
```

但是，如果我将：private 继承，改为 public 继承，那么依然是可以 cast，不过这个时候，因为没有虚析构，
这个会有内存泄露的风险，并且，因为我的 noncopyable 的析构函数是不能被执行的，因为我是用了 protected 权限。
这就很有趣了，因为我这个可以创建对象，但是没有不能析构。

```cpp
delete p; // calling a protected destructor of class 'noncopyable'
```

这是一种常见的写法：如果我没有虚析构函数，那么父类的 析构函数 要设置为 private 或者 protected，
为了防止：不小心调用父类析构导致的内存泄露问题

当然，我是可以使用 `class A` 的析构函数啦

```cpp
delete static_cast<A*>(p);
```

## 8 - 类设计中的一些技巧

### 优先考虑为成员变量提供访问接口

返回左值引用，可以在真正使用变量之前，
做一些访问次数统计，或者是额外动作，那么就很方便。

```cpp
class A {

private:
    int m_a;
    long cnt;

public:
    A()
        : m_a(0)
        , cnt(0) {};
    int& getA()
    {
        this->cnt++;
        return this->m_a;
    }
    long getCNT()
    {
        return this->cnt;
    };
};

int main(void)
{
    A aobj1;
    aobj1.getA() = 5;
    cout << aobj1.getA() << endl;
    cout << aobj1.getCNT() << endl;
}
```

总结：可以使用 private 来修饰成员变量，
然后提供一个 public 修饰的成员函数作为外界访问该变量的接口

### 如何避免将父类的虚函数暴露给子类

```cpp
class A {
public:
    void myfunc() /* 非虚拟接口 */
    {
        /* myfunc函数是myvirfunc函数的一行通道性质的代码，走虚函数表 */
        myvirfunc();
    }
    virtual ~A() { }

private:
    virtual void myvirfunc()
    {
        cout << "A::myvirfunc()执行了!" << endl;
    }
};

class B : public A {
private:
    virtual void myvirfunc()
    {
        cout << "B::myvirfunc()执行了!" << endl;
    }
};

int main(void)
{
    A* paobj = new B();
    paobj->myfunc(); // B::myvirfunc()执行了!
    delete paobj;
}
```

当然，这种通道性质的代码，并不适用于 虚析构函数。

总结：如果能讲虚函数设置为私有，则优先考虑将其设置为私有函数

### 不要在 类的构造函数 与 析构函数中 调用虚函数

- 首先：不能在父类的构造函数中，调用子类的 虚函数，因为这个时候，子类还没有构造出来，还是一个未成熟的对象。
- 其次：如果在父类的析构函数中，对象的子类部分实际上已经销毁了

比如下面代码

```cpp
class ANew {
public:
    ANew()
    {
        f1();
    }
    virtual ~ANew()
    {
        f2();
    }

    virtual void f1()
    {
        cout << "虚函数ANew::f1()执行了" << endl;
    }
    virtual void f2()
    {
        cout << "虚函数ANew::f2()执行了" << endl;
    }

    // 定义普通成员函数，调用虚函数
    void AClassFunc()
    {
        f1();
    }
};

class BNew : public ANew {
public:
    BNew()
    {
        f1();
    }
    virtual ~BNew()
    {
        f2();
    }

    virtual void f1()
    {
        cout << "虚函数BNew::f1()执行了" << endl;
    }
    virtual void f2()
    {
        cout << "虚函数BNew::f2()执行了" << endl;
    }

    // 定义普通成员函数，调用虚函数
    void BClassFunc()
    {
        f1();
    }
};

int main(void)
{
    ANew* pbnew = new BNew();

    cout << "----------"
         << "begin"
         << "----------" << endl;
    pbnew->f1();
    pbnew->f2();
    pbnew->AClassFunc();
    cout << "----------"
         << "end"
         << "----------" << endl;

    delete pbnew;
}
```

输出：

```sh
虚函数ANew::f1()执行了
虚函数BNew::f1()执行了
----------begin----------
虚函数BNew::f1()执行了
虚函数BNew::f2()执行了
虚函数BNew::f1()执行了
----------end----------
虚函数BNew::f2()执行了
虚函数ANew::f2()执行了
```

设想有父子关系的两个类：

1. 如果在父类的构造函数中调用了一个 子类的虚函数是无法做到的，
   因为执行到父类的构造函数时，对象的子类部分还没有被构造出来（未成熟的对象）
2. 如果在父类的析构函数中调用了一个 子类的虚函数是无法做到的，
   因为执行到父类的析构函数时，对象的子类部分已经被销毁了

总结：不要在类的构造函数和析构函数中调用虚函数，在构造函数和析构函数中，
虚函数可能会失去虚函数的作用 而被当做普通函数看待

### 析构函数的 虚 与 非虚 谈

父类析构函数不一定非要是 虚函数。但是当父类指针指向子类对象的时候（这种多态形式的代码存在时），
父类需要写一个 public 修饰的虚析构，这样就可以通过父类的接口来多态的销毁子类对象，
否则就可能会造成内存泄露

```cpp
class ANew {
protected:
    ~ANew() { }
};

class BNew : public ANew {
};

int main(void)
{
    ANew aobj; // variable of type 'ANew' has protected destructor
    ANew* paobj = new ANew();
    delete paobj; // calling a protected destructor of class 'ANew'

    ANew* pbobj = new BNew();
    delete pbobj; // calling a protected destructor of class 'ANew'
}
```

仅仅用 protected 修饰一下析构函数就达到了几个效果：

1. 无法创建父类对象
2. 只能 new，但是没有 delete ---> 无法让父类指针指向子类对象

```cpp
BNew *pb = new BNew(); // ✅
BNew bobj; // ✅
```

a）如果一个 父类的析构函数 不是 虚函数，并且不利用这个父类创建对象，也不会用到父类类型的指针，
则应该考虑将该父类的析构函数 使用 protected 而非 public 来修饰，以防止写出错误的代码（增加代码编写的安全性），防止误用。
名言警句：一个类型要做到 “易于使用”，不容易错误的使用

b）父类的析构函数不是虚函数，本身就暗示着不会通过父类的接口来多态的销毁子类对象，也暗示着不会用到父类类型的指针

### 抽象类的模拟

抽象类不能创建对象，主要是用来定义接口规范，或者是定义纯虚函数，来管理子类：派生出子类，要求子类实现这些接口规范。
抽象类中：要求至少有一个纯虚函数。抽象类的特征：不能用来生成对象（作为父类不能用来生成对象）

1. 将模拟的抽象类的 构造函数 和 拷贝构造函数 都使用 protected 来修饰

为什么是 protect 呢？为了能够让子类访问到。
如果 子类没法访问，自然子类都是无法创建的，因为子类在构造的时候，
需要调用父类的构造函数？除非友元

```cpp
class PVC {
protected:
    PVC(const PVC&) { }
    PVC() { }
};
```

2. 将模拟的抽象类的析构函数 设置为 纯虚函数，并在类外为该纯虚函数定义实现体。
   类外实现类的纯虚析构（绝大部分纯虚函数没有实现体，但是纯虚函数是一个特例，为了释放资源等，所以一般要有实现体）

因为析构函数，即使是虚析构，那么实际上，编译器在析构子类的时候，也会调用父类的析构函数，也就是父类需要析构函数。
如果不实现函数体是怎么样？

```cpp
class PVC {
public:
    PVC(const PVC&) { }
    PVC() { }
    virtual ~PVC() = 0;
};

class SubPVC : public PVC {
};

int main(void)
{
    PVC* p = new SubPVC();
    delete p;
}
```

这个时候，编译器会报一个链接的错误

```sh
ld: Undefined symbols:
  PVC::~PVC(), referenced from:
      SubPVC::~SubPVC() in s8_6-c9dfdd.o
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

但是如果我实现了函数体就是没问题的

```cpp
class PVC {
public:
    PVC(const PVC&) { }
    PVC() { }
    virtual ~PVC() = 0;
};

PVC::~PVC()
{
}

class SubPVC : public PVC {
};

int main(void)
{
    PVC* p = new SubPVC();
    delete p;
}
```

3. 将父类的析构函数用 protected 修饰

子类在销毁的时候，可以访问到父类的析构函数。
但是没法创建父类的对象。因为没办法析构。

### 尽量避免隐式类型转换

这个我大概了解，如果是单个参数，会隐式类型 implicit 转换

```cpp
class A {
public:
	A(int i) : m_i(i) { /* 这个就是类型转化构造函数了 */
		cout << i << endl;
	}

public:
	int m_i;
};
```

可以在 类型转换构造函数前面加上 explicit，拒绝类型转换构造函数。

### 强制类对象不可以 或 只可以在堆上分配内存

#### 强制类对象 不可以 在堆上分配内存

将`operator new`与`operaotr delete`用 private 修饰。
但是这样其实还是可以 构造对象数组的。当然可以 private `operator new[]`和`operator delete[]`

#### 强制类对象 只可以 在堆上分配内存

不能在栈上 创建对象，也就是`A aobj;`这种代码不能被允许。
那么只需要将`class A`的析构函数用 private 修饰。

但是问题是：delete 的时候就会有问题了，因为 delete 也需要用到 析构函数。
那么我可以在类中定义一个`destroy = delete this`的函数。

```cpp
class A {
public:
    int m_i;

public:
    A(int i)
        : m_i(i)
    {
    }
    void destroy()
    {
        delete this;
    }

private:
    ~A() { }
};

int main(void)
{
    // A a(1); // Variable of type 'A' has private destructor
    A* p = new A(0);
    // delete p; // Calling a private destructor of class 'A'
    p->destroy();
}
```

## 9 - 命名空间使用的一些注意事项

大部分标准库的部件，都位于 std 这个命令空间中。

1. 通过 using 声明命名空间的代码，不要放在.h 头文件中
   很容易造成：命名空间被污染的问题

## 10 - 类定义的相互依赖 与 类的前向声明

```cpp
class A1 {
public:
	A2* m_pa2; /* 不认识A2，需要A2声明 */
};

class A2 {
public:
	A1* m_pa1;
};
```

这个`class A1`与`class A2`是相互依赖的。
这里是直接依赖，还有一种是间接依赖，就是`A --> B --> C`，然后`C --> B --> A`。

直接的相互依赖和间接的相互依赖，这种都是应该避免的。
应该要引入一个新类`class CNew`，然后让 A, B 都依赖这个 CNew。

如果我把这两个类定义，放到两个头文件之中，那问题更大了 ---> 不能通过头文件相互包含解决，
因为有头文件的保护机制，所以我们需要 前向声明。

```cpp
class A2;  // 前向声明

class A1 {
public:
	A2* m_pa2; /* 不认识A2，需要A2声明 */
};
```

```cpp
class A1;  // 前向声明

class A2 {
public:
	A1* m_pa1;
};
```

但是有时候，前向声明并不一定好使。有时候是要类的完整定义的。

1. 在类 A1 的定义中，加入 A2 类型的对象

```cpp
class A2;  // 前向声明

class A1 {
public:
	A2* m_pa2;
	A2 maobj2; /* 错误，因为编译器不知道 A2 的内存大小 */
};
```

2. 在 A1 定义中，需要知道 A2 的大小

```cpp
class A2;  // 前向声明

class A1 {
public:
	void func() {
		int s = sizeof(A2); /* 使用了未定义类型A2 */
	}
};
```

3. 在 class A1 中，需要调用 class A2 的成员函数

```cpp
class A2;  // 前向声明

class A1 {
public:
	void func() {
		m_pa2->a2func();  /* 使用了未定义的类型A2 */
	}

	A2* m_pa2; /* 不认识A2，需要A2声明 */
};
```

### 解决互相依赖问题的 正解
