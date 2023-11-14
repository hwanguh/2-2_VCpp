#include <iostream>

#include "YuhanStack.h"

using namespace std;

int main()
{
    YuhanStack<int> s;

    s.push(8);
    s.push(2);
    s.push(1);
    
    cout << s.pop();
    cout << s.pop();
    cout << s.pop();
}
