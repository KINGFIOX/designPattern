# comment

## 私有内部类

在 C++中，一个类可以包含另一个类的定义，这种包含的类称为内部类（嵌套类）。根据内部类的访问说明符（`public`、`protected`或`private`），它可以有不同的访问特性。

如果一个内部类被声明为私有（`private`），它具有以下特性：

1. **封装性**: 私有内部类对外界是隐藏的，仅对包含它的外部类可见。这意味着只有外部类的成员函数或友元函数可以创建和访问私有内部类的实例。

2. **特殊的访问权限**: 尽管内部类是私有的，它仍然可以访问外部类的所有成员，包括私有成员。这是因为内部类是其外部类的一个作用域内的成员。

3. **控制接口的复杂性**: 通过使用私有内部类，可以在不公开实现细节的情况下提供公共接口，这有助于降低类接口的复杂性。

4. **实现细节的隐藏**: 私有内部类通常用于实现一些仅供外部类使用的功能，无需暴露给外部类的使用者。这有助于保持外部类的 API 简洁和稳定。

5. **设计模式的实现**: 某些设计模式，如工厂模式和迭代器模式，可能会用到私有内部类，以便在不公开内部实现的情况下向客户端代码提供服务。

6. **减少名称冲突**: 由于私有内部类的作用域限制在外部类之内，因此它的名称不会与外部作用域的其他名称冲突。

下面是一个简单的示例，展示如何在 C++中定义和使用私有内部类：

```cpp
#include <iostream>

class Outer {
public:
    void outerFunction() {
        Inner in;
        in.innerFunction();
    }

private:
    class Inner {
    public:
        void innerFunction() {
            std::cout << "Inner function called." << std::endl;
        }
    };
};

int main() {
    Outer outer;
    outer.outerFunction(); // 正常工作，因为外部类可以访问私有内部类

    // 下面的代码将无法编译，因为Inner类是私有的
    // Outer::Inner innerObject;
    // innerObject.innerFunction();

    return 0;
}
```

在上述代码中，`Inner` 类是私有的，因此只能在 `Outer` 类的上下文中使用。尝试在 `Outer` 类的外部创建 `Inner` 类的实例会导致编译错误。
