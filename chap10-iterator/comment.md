# comment

## C++ 标准库中的 迭代器

在 C++中，迭代器模式通常遵循 STL（Standard Template Library）中定义的迭代器接口。
迭代器模式旨在提供一种方法来顺序访问集合对象中的元素，而无需暴露其底层表示（如列表、树或图结构）。

迭代器应该实现的最小接口取决于迭代器的类型。C++ STL 中有五种类型的迭代器，它们的接口复杂程度依次递增：

1. Input Iterator：用于从数据结构中读取数据。
2. Output Iterator：用于向数据结构中写入数据。
3. Forward Iterator：可以读写，并且可以多次向前迭代，但不支持向后迭代。
4. Bidirectional Iterator：扩展了前向迭代器，可以向前和向后迭代。
5. Random Access Iterator：提供了最丰富的功能，支持全双工迭代，可以进行算术运算（例如，加减整数）。

最简单的迭代器类型是 Input Iterator 和 Output Iterator，它们的最小接口通常包括：

- `operator*` (解引用操作符)：用于获取当前迭代器指向的元素的引用。
- `operator++` (前缀和后缀递增操作符)：用于将迭代器移动到下一个元素。
- `operator==` 和 `operator!=` (相等和不等比较操作符)：用于比较两个迭代器是否指向同一个元素。

在 C++中，一个最基本的输入迭代器可能看起来像这样：

```cpp
template <typename T>
class InputIterator {
public:
    typedef InputIterator self_type;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::input_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;

    InputIterator(pointer ptr) : ptr_(ptr) {}

    self_type operator++() { self_type i = *this; ptr_++; return i; }    // 前缀++
    self_type operator++(int junk) { ptr_++; return *this; }             // 后缀++
    reference operator*() { return *ptr_; }
    pointer operator->() { return ptr_; }
    bool operator==(const self_type& rhs) const { return ptr_ == rhs.ptr_; }
    bool operator!=(const self_type& rhs) const { return ptr_ != rhs.ptr_; }

private:
    pointer ptr_;
};
```

注意，这个迭代器示例是一个输入迭代器，它是最基本的迭代器形式。
对于其他类型的迭代器，如双向迭代器或随机访问迭代器，接口将更加复杂，包括如`operator--` (双向迭代器所需要的递减操作符)
或`operator+`, `operator-`, `operator[]` (随机访问迭代器特有的操作符)。
