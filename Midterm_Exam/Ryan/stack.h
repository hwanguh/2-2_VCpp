#pragma once



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
    void pop(POINT* startPointP, POINT* endPointP, Fig* figP);
    ~stack();
};
