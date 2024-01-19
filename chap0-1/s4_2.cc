#include <iostream>
#include <map>
#include <utility>
using namespace std;

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

int main(void)
{
    std::multimap<int, int> tmpmpc;
    tmpmpc.insert(std::make_pair(1, 1));
    tmpmpc.insert(std::make_pair(2, 3));
    tmpmpc.insert(std::make_pair(1, 2));
    cout << "tmpmpc.size() = " << tmpmpc.size() << endl;
}