#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>

#define CMMD_BUFER_SIZE 6

using namespace std;

int main(){
    int input = 0;
    char command[CMMD_BUFER_SIZE] = { 0, };

    cout << "     202207020" << endl << "     황의현의" << endl << "     VC++" << endl << "기술 커맨드 입력(방향키 a:손 s:발)" << endl;

    while (1) {
        if (_kbhit()) {
            for (int i = 1; i < CMMD_BUFER_SIZE; i++) {
                command[i - 1] = command[i];
            }

            input = _getch();
            if (-32 == input) {
                command[CMMD_BUFER_SIZE - 1] = input;
                for (int i = 1; i < CMMD_BUFER_SIZE; i++) {
                    command[i - 1] = command[i];
                }
                input = _getch();
            }
            if (27 == input) { // Esc 키를 누르면 프로그램 종료
                break; // 무한 루프 종료
            }

            command[CMMD_BUFER_SIZE-1] = input;
            
            this_thread::sleep_for(chrono::milliseconds(300));

            bool flag = 1;

            for (int i = 1; i < CMMD_BUFER_SIZE; i++) {
                if (i == 1 && command[i] != -32) {
                    flag = 0;
                    break;
                }
                else if (i == 2 && command[i] != 80) {
                    flag = 0;
                    break;
                }
                else if (i == 3 && command[i] != -32) {
                    flag = 0;
                    break;
                }
                else if (i == 4 && command[i] != 77) {
                    flag = 0;
                    break;
                }
                else if (i == 5 && command[i] != 'a') {
                    flag = 0;
                    break;
                }
            }

            if (flag) {
                cout << "하도~~~켄~~~ ==0" << endl;
            }

            flag = 1;

            for (int i = 0; i < CMMD_BUFER_SIZE; i++) {
                if (i == 1 && command[i] != 'a') {
                    flag = 0;
                    break;
                }
                else if (i == 1 && command[i] != 'a') {
                    flag = 0;
                    break;
                }
                else if (i == 2 && command[i] != -32) {
                    flag = 0;
                    break;
                }
                else if (i == 3 && command[i] != 77) {
                    flag = 0;
                    break;
                }
                else if (i == 4 && command[i] != 's') {
                    flag = 0;
                    break;
                }
                else if (i == 5 && command[i] != 'a') {
                    flag = 0;
                    break;
                }
            }

            if (flag) {
                cout << "일순천격!" << endl;
            }

            flag = 1;

            for (int i = 1; i < CMMD_BUFER_SIZE; i++) {
                if (i == 1 && command[i] != -32) {
                    flag = 0;
                    break;
                }
                else if (i == 2 && command[i] != 80) {
                    flag = 0;
                    break;
                }
                else if (i == 3 && command[i] != -32) {
                    flag = 0;
                    break;
                }
                else if (i == 4 && command[i] != 75) {
                    flag = 0;
                    break;
                }
                else if (i == 5 && command[i] != 's') {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                cout << "찹!쌀!떡!두~개~~~~~ㅇㅇ" << endl;
            }                   
        }
    }
    return 0;
}