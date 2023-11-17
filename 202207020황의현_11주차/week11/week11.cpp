#include <iostream>

#include "stack.h"

using namespace std;

int main()
{
    stack s;
    s.push(5);
    s.push(6);
    s.push(7);

    cout << s.pop() << endl;
    cout << s.pop() << endl;
    cout << s.pop() << endl;
}