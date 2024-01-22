#include <iostream>
using namespace std;

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
