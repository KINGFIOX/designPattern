#include <iostream>

using namespace std;

class PVC {
protected:
    PVC(const PVC&) { }
    PVC() { }
};

class SubPVC : public PVC {
};

int main(void)
{
    PVC* p = new SubPVC();
    delete p;
}