#pragma once

#include <windows.h>

class Mouse {
private:
    POINT startPoint;
    POINT endPoint;
    POINT startMovePoint;
    POINT endMovePoint;
    unsigned int isMouseLButtonPressed : 1;
    unsigned int isMouseRButtonPressed : 1;
    int offsetX;
    int offsetY;
public:
    Mouse() {
        startPoint = {0};
        endPoint = { 0 };
        startMovePoint = { 0 };
        endMovePoint = { 0 };
        isMouseLButtonPressed = 0;
        isMouseRButtonPressed = 0;
        offsetX = 0;
        offsetY = 0;
    }
    void setStartPoint(long x, long y) {
        startPoint.x = x;
        startPoint.y = y;
    }
    void setEndPoint(long x, long y) {
        endPoint.x = x;
        endPoint.y = y;
    }
    void setStartMovePoint(long x, long y) {
        startMovePoint.x = x;
        startMovePoint.y = y;
    }
    void setEndMovePoint(long x, long y) {
        endMovePoint.x = x;
        endMovePoint.y = y;
        offsetX = endMovePoint.x - startMovePoint.x;
        offsetY = endMovePoint.y - startMovePoint.y;
    }
    void moveBox() {
        startPoint.x += offsetX;
        endPoint.x += offsetX;
        startPoint.y += offsetY;
        endPoint.y += offsetY;
    }
    void moveWheel() {
        endPoint.x += offsetX;
        endPoint.y += offsetX;
    }
    void swapMovePoint() {
        startMovePoint = endMovePoint;
    }
    unsigned int isInFig(long x, long y) {
        return(unsigned int)(((startPoint.x >= x) & (endPoint.x <= x))
            | ((startPoint.x <= x) & (endPoint.x >= x)))
            & ((((startPoint.y >= y) & (endPoint.y <= y))
                | ((startPoint.y <= y) & (endPoint.y >= y))));
    }
    void onIsMouseLButtonPressed() {
        isMouseLButtonPressed = 1;
    }
    void offIsMouseLButtonPressed() {
        isMouseLButtonPressed = 0;
    }
    void onIsMouseRButtonPressed() {
        isMouseRButtonPressed = 1;
    }
    void offIsMouseRButtonPressed() {
        isMouseRButtonPressed = 0;
    }
    POINT getStartPoint() {
        return startPoint;
    }
    POINT getEndPoint() {
        return endPoint;
    }
    POINT getStartMovePoint() {
        return startMovePoint;
    }
    POINT getEndMovePoint() {
        return endMovePoint;
    }
    unsigned int getIsMouseLButtonPressed() {
        return isMouseLButtonPressed;
    }
    unsigned int getIsMouseRButtonPressed() {
        return isMouseRButtonPressed;
    }
};