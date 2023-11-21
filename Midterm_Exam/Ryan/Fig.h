#pragma once
class Fig {
private:
    unsigned int isBox : 1;
    unsigned int isWheel : 1;
    unsigned int isBono : 1;
    unsigned int isSpace : 1;
    unsigned int isRyan : 1;
public:
    Fig();
    unsigned int getBox() {
        return isBox;
    }
    unsigned int getWheel() {
        return isWheel;
    }
    unsigned int getBono() {
        return isBono;
    }
    unsigned int getSpace() {
        return isSpace;
    }
    unsigned int getRyan() {
        return isRyan;
    }
    void setBox();
    void setWheel();
    void setBono();
    void onSpace();
    void offSpace();
    void setRyan();
};