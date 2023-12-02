#pragma once

#include <windows.h>

#include "Fig.h"

class node
{
public:
    POINT startPoint;
    POINT endPoint;
    Fig fig;
    node* prev_node;
};

class stack
{
private:
    node* top;
public:
    stack();
    void push(POINT startPoint, POINT endPoint, Fig fig);
    bool pop(POINT* startPoint, POINT* endPoint, Fig* fig);
    ~stack();
};