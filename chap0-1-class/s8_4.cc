#include <iostream>

using namespace std;

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