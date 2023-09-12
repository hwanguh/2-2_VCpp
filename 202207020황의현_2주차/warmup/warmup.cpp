#include <iostream>
#include <conio.h>
using namespace std;

int main(){
    cout << "     202207020" << endl << "     황의현의" << endl << "     VC++" << endl;

    while (1) {
        cout << "command>";
        int input = _getch();
        cout << (char)input << endl;

        if ('q' == input) {
            cout << "qwer 화이팅" << endl;
        }
        else if ('w' == input) {
            cout << "과제 너무 좋다" << endl;
        }
        else if ('e' == input) {
            cout << "담주부턴 과제량 3배다" << endl;
        }
        else if ('r' == input) {
            cout << "행복합니다." << endl;
        }
        else if (27 == input) {
            return 0;
        }
        else {
            cout << "대응하는 문자열이 존재하지 않습니다 다시 입력하세요(q,w,e,r)(종료 : Esc키)" << endl;
        }
    }
}