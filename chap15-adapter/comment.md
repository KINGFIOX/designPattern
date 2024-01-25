# chap15

## std::bind

`std::bind` 是 C++ 标准库中的一个功能强大的实用工具，它位于 `<functional>` 头文件中。
`std::bind` 生成一个新的可调用对象，基本上可以将任何可调用对象（如函数指针、成员函数指针和函数对象）与其参数一起“绑定”。
这意味着你可以预先设定一些参数的值，创建一个新的函数，当调用这个新函数时，已经被绑定的参数会自动传递给原始的可调用对象。

下面是 `std::bind` 的用法示例：

```cpp
#include <iostream>
#include <functional>

void print(int a, int b, int c)
{
    std::cout << a << " " << b << " " << c << std::endl;
}

int main()
{
    // 使用 std::bind 绑定参数
    auto bindFunc1 = std::bind(print, 1, 2, 3); // 绑定所有参数
    bindFunc1(); // 输出：1 2 3

    // 使用 placeholders::_1 来表示未绑定的参数，该参数将在函数调用时提供
    auto bindFunc2 = std::bind(print, std::placeholders::_1, 4, 5); // 只绑定部分参数
    bindFunc2(2); // 输出：2 4 5

    // 使用 placeholders 来重新排列参数顺序
    auto bindFunc3 = std::bind(print, std::placeholders::_2, std::placeholders::_1, 6);
    bindFunc3(7, 3); // 输出：3 7 6

    // 绑定成员函数和成员变量
    struct Foo {
        void print_sum(int n) { std::cout << n + x << '\n'; }
        int x;
    };
    Foo foo = {10};
    auto bindFunc4 = std::bind(&Foo::print_sum, &foo, std::placeholders::_1);
    bindFunc4(5); // 输出：15

    auto bindFunc5 = std::bind(&Foo::x, &foo);
    std::cout << bindFunc5() << '\n'; // 输出：10

    return 0;
}
```

在上面的代码示例中，`std::placeholders::_1`、`std::placeholders::_2` 等是用来指定哪些参数是在调用绑定后的函数时提供的。这些占位符对应于绑定函数的参数。

需要注意的是，从 C++11 开始，通常推荐使用 lambda 表达式作为 `std::bind` 的现代替代品，因为 lambda 通常提供更简洁的语法和更好的性能。
以下是上面使用 `std::bind` 的示例，改用 lambda 表达式的方式：

```cpp
auto lambdaFunc1 = [] { print(1, 2, 3); };
lambdaFunc1();

auto lambdaFunc2 = [](int a) { print(a, 4, 5); };
lambdaFunc2(2);

auto lambdaFunc3 = [](int a, int b) { print(b, a, 6); };
lambdaFunc3(7, 3);

Foo foo = {10};
auto lambdaFunc4 = [&foo](int n) { foo.print_sum(n); };
lambdaFunc4(5);

auto lambdaFunc5 = [&foo] { return foo.x; };
std::cout << lambdaFunc5() << '\n';
```

如你所见，lambda 表达式更加直观，并且与 `std::bind` 相比，它们通常更易于理解和维护。
