#pragma once

class node
{
public:
    int data;
    node* prev_node;
};

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

