#include "YuhanStack.h"

template<typename T>
YuhanStack<T>::YuhanStack() {
    count = 0;
    top = new T();
}

template<typename T>
void YuhanStack<T>::push(T input) {
    top++;
    *top = input;
    count++;
}

template<typename T>
T YuhanStack<T>::pop() {
    if (0 < count) {
        T result = *top;
        top--;
        count--;
        return result;
    }
    return 0;
}

template class YuhanStack<int>;