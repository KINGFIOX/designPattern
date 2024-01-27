/**
 * @file s1.cxx 解释器模式 初步
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <map>

using namespace std;

/**
 * @brief 小表达式（节点）的父类
 *
 */
class Expression {
public:
    Expression(int num, char sign) /* 构造函数 */
        : m_dgb_num(num)
        , m_dgb_sign(sign)
    {
    }

public:
    /**
     * @brief 解析语法树中的当年节点
     *
     * @param var map 容器中的键值对，用于保存变量名以及对应的值
     * @return int
     */
    virtual int interpret(map<char, int> var) = 0;

public:
    int m_dgb_num; /* 创建该对象时的一个编号，用来记录本对象是 第几个创建的 */
    char m_dgb_sign; /* 标记本对象的类型，v: 变量（终结符），或者是 + -（非终结符） */
};

/**
 * @brief 终结符表达式
 *
 */
class VarExpression : public Expression {
public:
    VarExpression(const char& key, int num, char sign)
        : Expression(num, sign)
    {
        m_key = key;
    }

    int interpret(map<char, int> var) override
    {
        return var[m_key]; /* 变量的值在 map 中存着 */
    }

private:
    char m_key; /* 变量名，本范例中诸如 a, b, c, d 都是变量名 */
};

/**
 * @brief 运算符表达式（非终结符表达式）
 *
 */
class SymbolExpression : public Expression {
public:
    SymbolExpression(Expression* left, Expression* right, int num, char sign)
        : m_left(left)
        , m_right(right)
        , Expression(num, sign)
    {
    }

public:
    Expression* getLeft() { return m_left; }
    Expression* getRight() { return m_right; }

protected:
    /* 左右各有一个操作数 */
    Expression* m_left;
    Expression* m_right;
};

/**
 * @brief 加法表达式
 *
 */
class AddExpression : public SymbolExpression {
public:
    AddExpression(Expression* left, Expression* right, int num)
        : SymbolExpression(left, right, num, '+')
    {
    }

public:
    int interpret(map<char, int> var) override
    {
        int l_v = m_left->interpret(var); /* 递归调用 left 的 interpret */
        int r_v = m_right->interpret(var); /* 递归调用 right 的 interpret */
        return l_v + r_v;
    }
};

/**
 * @brief 加法表达式
 *
 */
class SubExpression : public SymbolExpression {
public:
    SubExpression(Expression* left, Expression* right, int num)
        : SymbolExpression(left, right, num, '-')
    {
    }

public:
    int interpret(map<char, int> var) override
    {
        int l_v = m_left->interpret(var); /* 递归调用 left 的 interpret */
        int r_v = m_right->interpret(var); /* 递归调用 right 的 interpret */
        return l_v - r_v;
    }
};