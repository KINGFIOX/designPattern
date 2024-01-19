#include <iostream>

using namespace std;

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