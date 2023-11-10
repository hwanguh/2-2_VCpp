#include "yuhanCG.h"

void yuhanCG::DrawBonobono(HWND hWnd, HDC hdc, int blink) {
    HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255));

    SelectObject(hdc, hBrush);
    Ellipse(hdc, 100, 120, 300, 320);
    DeleteObject(hBrush);

    hBrush = CreateSolidBrush(RGB(255, 150, 255));
    SelectObject(hdc, hBrush);
    Ellipse(hdc, 180, 220, 220, 280);
    DeleteObject(hBrush);

    hBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hBrush);
    Ellipse(hdc, 150, 200, 200, 250);
    Ellipse(hdc, 200, 200, 250, 250);
    DeleteObject(hBrush);

    hBrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hBrush);

    if (blink) {
        MoveToEx(hdc, 110, 190, NULL);
        LineTo(hdc, 130, 200);
        MoveToEx(hdc, 130, 200, NULL);
        LineTo(hdc, 110, 210);
        MoveToEx(hdc, 280, 190, NULL);
        LineTo(hdc, 260, 200);
        MoveToEx(hdc, 260, 200, NULL);
        LineTo(hdc, 280, 210);
    }
    else {
        Ellipse(hdc, 120, 195, 130, 205);
        Ellipse(hdc, 270, 195, 280, 205);
    }
    Ellipse(hdc, 185, 200, 215, 230);
    MoveToEx(hdc, 170, 220, NULL);
    LineTo(hdc, 140, 210);
    MoveToEx(hdc, 170, 230, NULL);
    LineTo(hdc, 140, 250);
    MoveToEx(hdc, 230, 220, NULL);
    LineTo(hdc, 270, 210);
    MoveToEx(hdc, 230, 230, NULL);
    LineTo(hdc, 270, 250);

    DeleteObject(hBrush);
}

void yuhanCG::DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {
    int x = right - left;
    int y = bottom - top;
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hBrush);
    Ellipse(hdc, left, top, left + 2 * x / 5, top + 2 * y / 5);
    Ellipse(hdc, right - 2 * x / 5, top, right, top + 2 * y / 5);
    Ellipse(hdc, left, top, right, bottom);
    DeleteObject(hBrush);

    hBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hBrush);
    Ellipse(hdc, left + 4 * x / 10, top + y / 2, left + x / 2, top + 6 * y / 10);
    Ellipse(hdc, left + x / 2, top + y / 2, left + 6 * x / 10, top + 6 * y / 10);
    DeleteObject(hBrush);

    hBrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hBrush);
    Ellipse(hdc, left + 5 * x / 20, top + 7 * y / 20, left + 6 * x / 20, top + 8 * y / 20);
    Ellipse(hdc, right - 6 * x / 20, top + 7 * y / 20, right - 5 * x / 20, top + 8 * y / 20);
    MoveToEx(hdc, left + x / 5, top + y / 4, NULL);
    LineTo(hdc, left + 2 * x / 5, top + y / 4);
    MoveToEx(hdc, left + x / 5, top + y / 4 - y / 100, NULL);
    LineTo(hdc, left + 2 * x / 5, top + y / 4 - y / 100);
    MoveToEx(hdc, left + x / 5, top + y / 4 + y / 100, NULL);
    LineTo(hdc, left + 2 * x / 5, top + y / 4 + y / 100);

    MoveToEx(hdc, left + 3 * x / 5, top + y / 4, NULL);
    LineTo(hdc, left + 4 * x / 5, top + y / 4);
    MoveToEx(hdc, left + 3 * x / 5, top + y / 4 - y / 100, NULL);
    LineTo(hdc, left + 4 * x / 5, top + y / 4 - y / 100);
    MoveToEx(hdc, left + 3 * x / 5, top + y / 4 + y / 100, NULL);
    LineTo(hdc, left + 4 * x / 5, top + y / 4 + y / 100);

    DeleteObject(hBrush);
}