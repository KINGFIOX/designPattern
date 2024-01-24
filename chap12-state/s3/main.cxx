/**
 * @file s3 状态模式
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

#include "monster.hxx"
#include "status.hxx"

using namespace std;

int main(void)
{
    Monster m(500);
    cout << "怪物出生，当前处于凶悍状态，500点🩸!" << endl;
    m.Attacked(100);
    m.Attacked(120);
    m.Attacked(220);
    m.Attacked(100);
}