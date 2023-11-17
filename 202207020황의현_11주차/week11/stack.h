#pragma once

#include "node.h"

class stack
{
private:
    node* top;
public:
    stack();
    void push(int input);
    int pop();
    ~stack();
};

