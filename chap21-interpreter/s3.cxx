/**
 * @file s3.cxx 机器人例子，解释器模式
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstddef>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/**
 * @brief 表达式父类
 *
 */
class Expression {
public:
    virtual ~Expression() { }

public:
    virtual string interpret() = 0;
};

/**
 * @brief 运动方向表达式（终结符表达式）
 *
 */
class DirectionExpression : public Expression {
public:
    DirectionExpression(const string& direction)
    {
        m_direction = direction;
    }

    string interpret() override
    {
        if (m_direction == "up") {
            return "向上";
        } else if (m_direction == "right") {
            return "向右";
        } else if (m_direction == "left") {
            return "向左";
        } else if (m_direction == "down") {
            return "向下";
        } else {
            return "运动方向错误";
        }
    }

private:
    string m_direction;
};

/**
 * @brief 运动方式 表达式（终结符表达式）
 *
 */
class ActionExpression : public Expression {
public:
    ActionExpression(const string& action)
    {
        m_action = action;
    }

    string interpret() override
    {
        if (m_action == "walk") {
            return "行走";
        } else if (m_action == "run") {
            return "奔跑";
        } else {
            return "运动方式错误";
        }
    }

private:
    string m_action;
};

/**
 * @brief 运动方式 表达式（终结符表达式）
 *
 */
class DistanceExpression : public Expression {
public:
    DistanceExpression(const string& distance)
    {
        m_distance = distance;
    }

    string interpret() override
    {
        return m_distance + "米";
    }

private:
    string m_distance;
};

/**
 * @brief 句子，非终结表达式
 *
 */
class SentenceExpression : public Expression {
public:
    SentenceExpression(Expression* direction, Expression* action, Expression* distance)
        : m_direction(direction)
        , m_action(action)
        , m_distance(distance)
    {
    }

public:
    Expression* getDirection()
    {
        return m_direction;
    }

    Expression* getAction()
    {
        return m_action;
    }

    Expression* getDistance()
    {
        return m_distance;
    }

    string interpret() override
    {
        return m_direction->interpret() + m_action->interpret() + m_distance->interpret();
    }

private:
    Expression* m_direction;
    Expression* m_action;
    Expression* m_distance;
};

/**
 * @brief 和表达式
 *
 */
class AndExpression : public Expression {
public:
    AndExpression(Expression* left, Expression* right)
        : m_left(left)
        , m_right(right)
    {
    }

    Expression* getLeft()
    {
        return m_left;
    }

    Expression* getRight()
    {
        return m_right;
    }

    string interpret() override
    {
        return m_left->interpret() + "再" + m_right->interpret();
    }

private:
    Expression* m_left;
    Expression* m_right;
};

/* ---------- 上面，语法树相关的类已经准备完毕了 ---------- */

/**
 * @brief 机器人命令，用空格分割
 *
 * @param strExp
 * @return Expression*
 */
Expression* analyse(string strExp)
{
    stack<Expression*> expStack;

    Expression* direction = nullptr;
    Expression* action = nullptr;
    Expression* distance = nullptr;

    Expression* left = nullptr;
    Expression* right = nullptr;
    vector<string> resultVec;

    /* 拷贝到 c 风格的字符串中 */
    char* strc = new char[strlen(strExp.c_str()) + 1];
    strcpy(strc, strExp.c_str());

    char* tmpStr = strtok(strc, " ");
    while (tmpStr != nullptr) {
        resultVec.push_back(string(tmpStr));
        tmpStr = strtok(NULL, " ");
    }
    delete[] strc;

    for (auto iter = resultVec.begin(); iter != resultVec.end(); ++iter) {
        if ((*iter) == "and") {
            left = expStack.top(); /* 返回做操作数 */
            ++iter; /* 跳过 and  */
            direction = new DirectionExpression(*iter);
            ++iter;
            action = new ActionExpression(*iter);
            ++iter;
            distance = new DistanceExpression(*iter);
            right = new SentenceExpression(direction, action, distance);
            expStack.push(new AndExpression(left, right));
        } else {
            direction = new DirectionExpression(*iter);
            ++iter;
            action = new ActionExpression(*iter);
            ++iter;
            distance = new DistanceExpression(*iter);
            expStack.push(new SentenceExpression(direction, action, distance));
        }
    }
    return expStack.top();
}

void release(Expression* expr)
{
    SentenceExpression* pSe = dynamic_cast<SentenceExpression*>(expr);
    if (pSe) {
        release(pSe->getDirection());
        release(pSe->getAction());
        release(pSe->getDistance());
    } else {
        AndExpression* pAe = dynamic_cast<AndExpression*>(expr);
        if (pAe) {
            release(pAe->getLeft());
            release(pAe->getRight());
        }
    }
    delete expr;
}

/* ---------- 下面，可以使用分析 ---------- */

int main(void)
{
    string strExpr = "left walk 15 and down run 20";
    Expression* expr = analyse(strExpr);
    cout << expr->interpret() << endl;

    release(expr);
    return 0;
}