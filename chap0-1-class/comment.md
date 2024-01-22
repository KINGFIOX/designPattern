# comment

## 不能被 拷贝赋值 拷贝构造 的类

不能被拷贝的类对象通常用于以下场景：

1. 管理资源的独占性

当一个类管理的资源（比如文件句柄、网络连接、数据库连接）是独占性的时候，你可能不希望有两个对象同时引用同一个资源。为了防止资源的不当共享，你可以禁止对象的拷贝，确保资源在一个时间点只被一个对象所拥有和管理。

2. 表示唯一的实体

如果类的实例代表了一个不可分割的唯一实体或操作（比如一个单例模式的实现），那么拷贝这个实例可能没有意义，也可能会导致逻辑错误。在这种情况下，拷贝操作被禁止可以确保实体的唯一性。

3. 避免意外的副本产生

在某些情况下，拷贝可能会导致性能问题或不必要的资源消耗，尤其是对于大型对象。禁止拷贝可以防止这些情况的发生，确保对象传递或赋值时，开发者必须明确使用引用或指针。

4. 移动语义和资源转移

在支持移动语义的编程语言中（如 C++11 及以后版本），对象可以被移动而不是被拷贝。这意味着一个对象的资源可以被转移给另一个对象，原对象在移动操作后不再有效。在这种情况下，禁止拷贝确保了资源的安全转移。

5. 安全和错误防范

在某些情况下，类的拷贝可能会引入安全隐患或逻辑错误。例如，当类包含指向动态分配内存的指针时，浅拷贝可能导致多个对象指向同一块内存，从而引发双重释放的问题。禁止拷贝可以预防这类问题。

如何禁止类的拷贝

在 C++中，可以通过将拷贝构造函数和拷贝赋值运算符声明为`delete`来实现：

```cpp
class NonCopyable {
public:
    NonCopyable(const NonCopyable&) = delete;            // 删除拷贝构造函数
    NonCopyable& operator=(const NonCopyable&) = delete; // 删除拷贝赋值运算符

    // 移动构造函数和移动赋值运算符可以是公开的，如果你希望类的实例可以被移动
    NonCopyable(NonCopyable&&) = default;
    NonCopyable& operator=(NonCopyable&&) = default;

    // 类的其他成员...
};
```

## 非虚函数重写问题

在 C++中，如果基类中的函数不是虚函数（即没有用 `virtual` 关键字声明），则在子类中重写（提供一个具有相同名称和参数的函数）并不会改变函数的静态绑定性质。
这意味着，哪个版本的函数被调用，将由对象的静态类型（编译时类型）决定，而不是对象的动态类型（运行时类型）。

让我们通过一些例子来说明这一点：

```cpp
class Base {
public:
    void NonVirtualFunction() {
        std::cout << "Base NonVirtualFunction called." << std::endl;
    }
};

class Derived : public Base {
public:
    void NonVirtualFunction() {
        std::cout << "Derived NonVirtualFunction called." << std::endl;
    }
};

int main() {
    Derived d;
    Base* bPtr = &d;
    bPtr->NonVirtualFunction(); // 将调用 Base 类的 NonVirtualFunction

    Derived* dPtr = &d;
    dPtr->NonVirtualFunction(); // 将调用 Derived 类的 NonVirtualFunction
}
```

在这个例子中，`NonVirtualFunction` 在 `Base` 类中不是虚函数。
即便 `Derived` 类提供了一个名为 `NonVirtualFunction` 的函数，这个函数也不会覆盖（override）基类的版本，因为它不是虚函数。

当通过基类的指针调用这个函数时（如 `bPtr->NonVirtualFunction();`），将始终调用基类提供的版本，不管这个指针实际上指向的是基类对象还是派生类对象。
这就是所谓的静态绑定，因为调用哪个函数是在编译时就决定的。

当通过派生类的指针或对象调用这个函数时（如 `dPtr->NonVirtualFunction();`），将调用派生类中的版本，因为编译器知道指针的类型是 `Derived`。

如果你想要在派生类中覆盖基类的函数，并且希望通过基类的指针或引用调用派生类的版本，你需要在基类中将这个函数声明为虚函数。
这样，当基类的指针或引用指向一个派生类对象时，将根据对象的动态类型来调用相应的函数版本，这就是动态绑定或多态。

## 不能被继承的类

在 C++98 中，没有直接的语言特性来阻止一个类被继承。在 C++11 及其之后的版本中，可以使用`final`关键字来阻止一个类被继承。
但在 C++98 中，你需要使用设计模式来实现这一点。

一种常见的模式是使用“私有构造函数”和“友元类”来创建一个不能被继承的类。
这通常涉及到创建一个辅助类，然后将主类的构造函数设为私有，以确保没有其他类可以继承它。

下面是一个例子：

```cpp
class Final; // 前向声明

class MakeFinal {
private:
    MakeFinal() {}  // 私有构造函数阻止创建实例
    friend class Final; // Final可以访问私有成员
};

class Final : virtual MakeFinal { // 继承MakeFinal
public:
    Final() {} // 构造函数
};

class Derived : public Final { // 尝试继承Final
    // 这里会因为MakeFinal的构造函数是私有的而编译失败
};
```

在这个模式中，`Final`类是你想要防止被继承的类。它通过虚继承`MakeFinal`类。
`MakeFinal`的构造函数是私有的，因此不能直接实例化。
同时，`Final`类是`MakeFinal`类的友元，因此`Final`可以访问`MakeFinal`的私有构造函数。
任何尝试从`Final`派生的类都将无法访问`MakeFinal`的构造函数，因此将导致编译错误。

这种模式利用了 C++的访问控制规则来阻止类的继承，但它有一些缺点，比如增加了复杂性，并且可能会导致不必要的虚继承开销。
在实际编码中，通常更喜欢简单地文档化类不应该被继承，而不是强制使用这种设计模式。随着 C++11 引入了`final`关键字，现代 C++代码可以更简洁地阻止类被继承。
