#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

// 도형 선택 구조체
struct Fig {
    unsigned int isBox : 1;
    unsigned int isWheel : 1;
    unsigned int isBono : 1;
    unsigned int isSpace : 1;
};
struct Fig fig = { 1,0,0,0 };//선언 및 초기화

//마우스 관련 구조체
struct Mouse {
    POINT startPoint;
    POINT endPoint;
    unsigned int isMouseLButtonPressed : 1;
    unsigned int isMouseInDrawBox : 1;
};
struct Mouse mouse = { {0},{0}, 0 , 0};//선언 및 초기화

//RGB색깔 변수
unsigned char R = 255;
unsigned char G = 0;
unsigned char B = 0;

int margin = 8;
int padding = 8;
int buttonWidth = 160;
int buttonHeight = 64;
int buttonMargin = 16;

int boxLeft;
int boxTop;
int boxRight;
int boxBottom;

int drawingLeft;
int drawingTop;
int drawingRight;
int drawingBottom;

void Draw(HWND hWnd, HDC hdc, WPARAM wParam) {
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 240, 200));
    SelectObject(hdc, hBrush);
    Rectangle(hdc, boxLeft, boxTop, boxRight, boxBottom);
    hBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hBrush);
    Rectangle(hdc, drawingLeft, drawingTop, drawingRight, drawingBottom);
    if (mouse.isMouseLButtonPressed) {
        hBrush = CreateSolidBrush(RGB(R, G, B)); // 빨간색 박스
        SelectObject(hdc, hBrush);
        //그리기
        if (fig.isBox) {
            Rectangle(hdc, mouse.startPoint.x, mouse.startPoint.y, mouse.endPoint.x, mouse.endPoint.y);
        }
        else if (fig.isWheel) {
            Ellipse(hdc, mouse.startPoint.x, mouse.startPoint.y, mouse.endPoint.x, mouse.endPoint.y);
        }
    }
    else if (fig.isBono) {
        hBrush = CreateSolidBrush(RGB(127, 200, 255));
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 100, 120, 300, 320);
        hBrush = CreateSolidBrush(RGB(255, 150, 255));
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 180, 220, 220, 280);
        hBrush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 150, 200, 200, 250);
        Ellipse(hdc, 200, 200, 250, 250);
        hBrush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc, hBrush);
        
        if (fig.isSpace) {
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
    }
    DeleteObject(hBrush);
}

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    switch (message) {
    case WM_KEYDOWN:
        if (32 == wParam){
            fig.isSpace = 1;
            InvalidateRect(hWnd, NULL, true);
        }
        break;
    case WM_LBUTTONDOWN:
        mouse.startPoint.x = LOWORD(lParam);
        mouse.startPoint.y = HIWORD(lParam);
        mouse.isMouseLButtonPressed = 1;
        break;
    case WM_MOUSEMOVE:
        if (drawingLeft <= LOWORD(lParam) &&
            drawingTop <= HIWORD(lParam) &&
            drawingRight >= LOWORD(lParam) &&
            drawingBottom >= HIWORD(lParam)) {
            SetCursor(LoadCursor(NULL, IDC_CROSS));
            mouse.isMouseInDrawBox = 1;
        }
        else {
            mouse.isMouseInDrawBox = 0;
        }
        if (mouse.isMouseLButtonPressed) {
            mouse.endPoint.x = LOWORD(lParam);
            mouse.endPoint.y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, true);
        }
        break;
    case WM_LBUTTONUP:
        mouse.endPoint.x = LOWORD(lParam);
        mouse.endPoint.y = HIWORD(lParam);
        mouse.isMouseLButtonPressed = 0;
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1:
            // 첫 번째 버튼 클릭
            fig.isBox = 1;
            fig.isWheel = 0;
            fig.isBono = 0;
            break;
        case 2:
            // 두 번째 버튼 클릭
            fig.isBox = 0;
            fig.isWheel = 1;
            fig.isBono = 0;
            break;
        case 3:
            // 세 번째 버튼 클릭
            fig.isBox = 0;
            fig.isWheel = 0;
            fig.isBono = 1;
            InvalidateRect(hWnd, NULL, true);
            break;
        }
        break;
    case WM_PAINT:
        PAINTSTRUCT ps;
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

    margin = 8;
    padding = 8;
    buttonWidth = 160;
    buttonHeight = 64;
    buttonMargin = 16;
    boxLeft = margin;
    boxTop = margin;
    boxRight = clientRect.right - margin;
    boxBottom = clientRect.bottom - margin;
    drawingLeft = boxLeft + padding;
    drawingTop = boxTop + padding + 80;
    drawingRight = boxRight - padding;
    drawingBottom = boxBottom - padding;

    hButton1 = CreateWindow(
        L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        16, 16, 147, 64, hWnd, (HMENU)1, hInstance, NULL);
    hButton2 = CreateWindow(
        L"BUTTON", L"Wheel", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        163, 16, 147, 64, hWnd, (HMENU)2, hInstance, NULL);
    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        313, 16, 147, 64, hWnd, (HMENU)3, hInstance, NULL);
    hButton4 = CreateWindow(
        L"BUTTON", L"Line", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        463, 16, 147, 64, hWnd, (HMENU)4, hInstance, NULL);
    hButton5 = CreateWindow(
        L"BUTTON", L"Line", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        613, 16, 147, 64, hWnd, (HMENU)5, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}