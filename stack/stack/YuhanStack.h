#pragma once

#include <iostream>

using namespace std;

template<typename T>
class YuhanStack {
private:
    T* top;
    unsigned long count;
public:
    YuhanStack();
    void push(T input);
    T pop();
};

