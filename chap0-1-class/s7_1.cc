class noncopyable {
protected:
    noncopyable() { }
    ~noncopyable() { }

private:
    noncopyable(const noncopyable&);
    noncopyable& operator=(const noncopyable&);
};

class A : public noncopyable {
};

int main(void)
{
    A aobj1;
    noncopyable* p = new A; // cannot cast 'A' to its private base class 'noncopyable'
    // delete p; // calling a protected destructor of class 'noncopyable'
    delete static_cast<A*>(p);
    // A aobj2 = aobj1; // n implicit copy constructor for 'A' first required here
}