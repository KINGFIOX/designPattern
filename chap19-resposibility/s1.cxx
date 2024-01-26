#include <iostream>

using namespace std;

/**
 * @brief 薪水处理类
 *
 */
class SalaryHandler {
public:
    /**
     * @brief
     *
     * @param sname 员工名字
     * @param salfigure 加薪多少
     */
    void raiseRequest(const string& sname, int salfigure)
    {
        if (salfigure <= 1000) {
            depManagerSP(sname, salfigure);
        } else if (salfigure <= 5000) {
            CTOSP(sname, salfigure);
        } else {
            genManagerSP(sname, salfigure);
        }
    }

private:
    void depManagerSP(const string& sname, int salfigure)
    {
        cout << sname << "的加薪要求为: " << salfigure << "元，部门经理审批通过!" << endl;
    }

    void CTOSP(const string& sname, int salfigure)
    {
        cout << sname << "的加薪要求为: " << salfigure << "元，技术总监审批通过!" << endl;
    }

    void genManagerSP(const string& sname, int salfigure)
    {
        cout << sname << "的加薪要求为: " << salfigure << "元，总经理审批通过!" << endl;
    }
};

int main(void)
{
    SalaryHandler sh;
    sh.raiseRequest("张三", 15000);
    sh.raiseRequest("李四", 3500);
    sh.raiseRequest("王五", 800);
}