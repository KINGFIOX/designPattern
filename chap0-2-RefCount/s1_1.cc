#include <iostream>
#include <memory>

using namespace std;

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
