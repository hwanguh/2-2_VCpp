﻿#include <iostream>
#include <conio.h>

using namespace std;

int main(){
    cout << "     202207020" << endl << "     황의현의" << endl << "     VC++" << endl;
    while (1) {
        int sum = 0;
        int input = 0;
        int command = 0;

        cout << "command>";
        do {
            input = _getch();
            if(33 <= input && 126 >= input){
                cout << (char)input;
                if (0 == sum) {
                    command = input;
                }
                sum++;
            }
            if (8 == input && 0 != sum) {
                cout << "\b \b";
                sum--;
            }
        }while(27 != input && 13 != input);

        cout << endl;

        if (27 == input) {
            return 0;
        }

        if (1==sum && ('q' == command || 'w' == command || 'e' == command || 'r' == command)) {
            if ('q' == command) {
                cout << "qwer 화이팅" << endl;
            }
            else if ('w' == command) {
                cout << "과제 너무 좋다" << endl;
            }
            else if ('e' == command) {
                cout << "담주부턴 과제량 3배다" << endl;
            }
            else if ('r' == command) {
                cout << "행복합니다." << endl;
            }
        }
        else {
            cout << "대응하는 문자열이 존재하지 않습니다 다시 입력하세요(q,w,e,r)(종료 : Esc키)" << endl;
        }
    }
}