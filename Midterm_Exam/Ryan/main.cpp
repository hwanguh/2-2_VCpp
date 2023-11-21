#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include "yuhanCG.h"
#include "Fig.h"
#include "Mouse.h"

Fig fig;
Mouse mouse;

//RGB색깔 변수
unsigned char R = 255;
unsigned char G = 0;
unsigned char B = 0;

//영역 관련 변수
const unsigned char margin = 8;
const unsigned char padding = 8;

const unsigned char buttonMargin = 16;
const unsigned char buttonHeight = 64;
unsigned char buttonWidth;

const unsigned char boxLeft = margin;
const unsigned char boxTop = margin;
short boxRight;
short boxBottom;

const unsigned char drawingLeft = boxLeft + padding;
const unsigned char drawingTop = boxTop + padding + 80;
short drawingRight;
short drawingBottom;

RECT drawingRect;

void Draw(HWND hWnd, HDC hdc, WPARAM wParam) {
    HBRUSH hBrush = CreateSolidBrush(RGB(R, G, B));
    HBRUSH hBrushBack = CreateSolidBrush(RGB(255, 240, 200));
    HBRUSH hBrushDraw = CreateSolidBrush(RGB(255, 255, 255));
    yuhanCG CG;
    SelectObject(hdc, hBrushBack);
    Rectangle(hdc, boxLeft, boxTop, boxRight, boxBottom);
    SelectObject(hdc, hBrushDraw);
    Rectangle(hdc, drawingLeft, drawingTop, drawingRight, drawingBottom);
    
    if (mouse.getIsMouseLButtonPressed() || mouse.getIsMouseRButtonPressed()) {
        SelectObject(hdc, hBrush);
        POINT startPoint = mouse.getStartPoint();
        POINT endPoint = mouse.getEndPoint();
        //그리기
        if (fig.getBox()) {
            Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }
        else if (fig.getWheel()) {
            Ellipse(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }
        else if (fig.getRyan()) {
            CG.DrawRyan(hWnd, hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }
    }
    else if (fig.getBono()) {
        CG.DrawBonobono(hWnd, hdc, fig.getSpace());
    }
    DeleteObject(hBrush);
    DeleteObject(hBrushBack);
    DeleteObject(hBrushDraw);
}

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_KEYDOWN:
        if (32 == wParam && fig.getBono()) {
            fig.onSpace();
            InvalidateRect(hWnd, &drawingRect, true);
        }
        break;
    case WM_KEYUP:
        fig.offSpace();
        InvalidateRect(hWnd, &drawingRect, true);
        break;
    case WM_LBUTTONDOWN:
        mouse.setStartPoint(LOWORD(lParam), HIWORD(lParam));
        mouse.onIsMouseLButtonPressed();
        break;
    case WM_MOUSEMOVE:
        if (drawingLeft <= LOWORD(lParam) &&
            drawingTop <= HIWORD(lParam) &&
            drawingRight >= LOWORD(lParam) &&
            drawingBottom >= HIWORD(lParam)) {
            SetCursor(LoadCursor(NULL, IDC_CROSS));
            if (mouse.getIsMouseLButtonPressed()) {
                mouse.setEndPoint(LOWORD(lParam), HIWORD(lParam));
                InvalidateRect(hWnd, &drawingRect, true);
            }
            else if (mouse.getIsMouseRButtonPressed()) {
                mouse.setEndMovePoint(LOWORD(lParam), HIWORD(lParam));
                if (fig.getBox()) {
                    mouse.moveBox();
                }
                else if (fig.getWheel()) {
                    mouse.moveWheel();
                }
                InvalidateRect(hWnd, &drawingRect, true);
                mouse.swapMovePoint();
            }
        }
        break;
    case WM_LBUTTONUP:
        mouse.setEndPoint(LOWORD(lParam), HIWORD(lParam));
        mouse.offIsMouseLButtonPressed();
        break;
    case WM_RBUTTONDOWN:
        if (mouse.isInFig(LOWORD(lParam), HIWORD(lParam))) {
            mouse.setStartMovePoint(LOWORD(lParam), HIWORD(lParam));
            mouse.onIsMouseRButtonPressed();
        }
        break;
    case WM_RBUTTONUP:
        mouse.setEndMovePoint(LOWORD(lParam), HIWORD(lParam));
        mouse.offIsMouseRButtonPressed();
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1:
            // 첫 번째 버튼 클릭
            fig.setBox();
            break;
        case 2:
            // 두 번째 버튼 클릭
            fig.setWheel();
            break;
        case 3:
            // 세 번째 버튼 클릭
            fig.setBono();
            break;
        case 4:
            // 네 번째 버튼 클릭
            fig.setRyan();
            break;
        }
        SetFocus(hWnd); //키보드 포커스 없애기
        InvalidateRect(hWnd, &drawingRect, true); //그림 영역 무효화
        break;
    case WM_PAINT:
        PAINTSTRUCT ps;
        HDC hdc;
        hdc = BeginPaint(hWnd, &ps);
        Draw(hWnd, hdc, wParam);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



// 프로그램 진입점
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    HWND hWnd;
    HWND hButton1, hButton2, hButton3, hButton4, hButton5;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 240, 200)));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"ButtonWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    hWnd = CreateWindow(
        L"ButtonWindowClass", L"202207020", WS_OVERLAPPEDWINDOW,
        0, 0, 800, 480, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);

    boxRight = (short)(clientRect.right - margin);
    boxBottom = (short)(clientRect.bottom - margin);

    buttonWidth = (boxRight - margin - buttonMargin * 2) / 5;

    drawingRight = boxRight - padding;
    drawingBottom = boxBottom - padding;

    drawingRect = { drawingLeft ,drawingTop ,drawingRight ,drawingBottom };

    hButton1 = CreateWindow(
        L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        buttonMargin + margin, buttonMargin + margin, buttonWidth, buttonHeight, hWnd, (HMENU)1, hInstance, NULL);
    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        buttonMargin + margin + buttonWidth, buttonMargin + margin, buttonWidth, buttonHeight, hWnd, (HMENU)2, hInstance, NULL);
    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        buttonMargin + margin + buttonWidth * 2, buttonMargin + margin, buttonWidth, buttonHeight, hWnd, (HMENU)3, hInstance, NULL);
    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        buttonMargin + margin + buttonWidth * 3, buttonMargin + margin, buttonWidth, buttonHeight, hWnd, (HMENU)4, hInstance, NULL);
    hButton5 = CreateWindow(
        L"BUTTON", L"button5", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        buttonMargin + margin + buttonWidth * 4, buttonMargin + margin, buttonWidth, buttonHeight, hWnd, (HMENU)5, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}