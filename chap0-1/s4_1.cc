#include <string>

class Info {
private:
    std::string m_name;
    int m_gender;
    int m_age;
};

class Human {
public:
    Info m_info;
};
