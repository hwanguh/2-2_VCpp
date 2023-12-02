#include "Fig.h"

Fig::Fig() {
    isBox = 1;
    isWheel = 0;
    isBono = 0;
    isRyan = 0;
}
void Fig::setBox() {
    isBox = 1;
    isWheel = 0;
    isBono = 0;
    isRyan = 0;
}
void Fig::setWheel() {
    isBox = 0;
    isWheel = 1;
    isBono = 0;
    isRyan = 0;
}
void Fig::setBono() {
    isBox = 0;
    isWheel = 0;
    isBono = 1;
    isRyan = 0;
}
void Fig::onSpace() {
    isSpace = 1;
}
void Fig::offSpace() {
    isSpace = 0;
}
void Fig::setRyan() {
    isBox = 0;
    isWheel = 0;
    isBono = 0;
    isRyan = 1;
}