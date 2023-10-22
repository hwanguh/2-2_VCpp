#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#include <windows.h>

// 도형 선택 변수
bool isBox = 1;
bool isWheel = 0;
bool isLine = 0;

//마우스 관련 변수
POINT startPoint = { 0 };
POINT endPoint = { 0 };
bool isMouseLButtonPressed = 0;

//RGB색깔 변수
unsigned char R = 255;
unsigned char G = 0;
unsigned char B = 0;

void Draw(HWND hWnd, HDC hdc) {
    if (isMouseLButtonPressed) {
        HBRUSH hBrush = CreateSolidBrush(RGB(R, G, B)); // 빨간색 박스
        SelectObject(hdc, hBrush);
        //그리기
        if (isBox){
            Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);            
        }
        else if(isWheel){
            Ellipse(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }
        else if(isLine){
            MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
            LineTo(hdc, endPoint.x, endPoint.y);
        }
        DeleteObject(hBrush);
    }
}

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_LBUTTONDOWN) {
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        isMouseLButtonPressed = 1;
    }
    else if (message == WM_MOUSEMOVE) {
        if (isMouseLButtonPressed) {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, true);
        }
    }
    else if (message == WM_LBUTTONUP) {
        endPoint.x = LOWORD(lParam);
        endPoint.y = HIWORD(lParam);
        isMouseLButtonPressed = 0;
    }
    else if (message == WM_COMMAND) {
       if (LOWORD(wParam) == 1) {
            // 첫 번째 버튼 클릭
            isBox = 1;
            isWheel = 0;
            isLine = 0;
       }
        else if (LOWORD(wParam) == 2) {
            // 두 번째 버튼 클릭
            isBox = 0;
            isWheel = 1;
            isLine = 0;
        }
        else if (LOWORD(wParam) == 3) {
            // 세 번째 버튼 클릭
            isBox = 0;
            isWheel = 0;
            isLine = 1;
        }
        else if (LOWORD(wParam) == 4) {
            R = 255;
            G = 0;
            B = 0;
        }
        else if (LOWORD(wParam) == 5) {
            R = 0;
            G = 255;
            B = 0;
        }
        else if (LOWORD(wParam) == 6) {
            R = 0;
            G = 0;
            B = 255;
        }
        
    }
    else if (message == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        Draw(hWnd, hdc);
        EndPaint(hWnd, &ps);
    }
    else if (message == WM_DESTROY) {
        PostQuitMessage(0);
    }
    else{
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



// 프로그램 진입점
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

    HWND hWnd;
    HWND hButton1, hButton2, hButton3;
    HWND hCButton1, hCButton2, hCButton3;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"ButtonWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    hWnd = CreateWindow(
        L"ButtonWindowClass", L"Win32 Button Example", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    hButton1 = CreateWindow(
        L"BUTTON", L"Add Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 20, 200, 60, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Add Wheel", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 200, 200, 60, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Add Line", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 400, 200, 60, hWnd, (HMENU)3, hInstance, NULL);

    hCButton1 = CreateWindow(
        L"BUTTON", L"RED", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        820, 20, 200, 60, hWnd, (HMENU)4, hInstance, NULL);

    hCButton2 = CreateWindow(
        L"BUTTON", L"GREEN", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        820, 200, 200, 60, hWnd, (HMENU)5, hInstance, NULL);

    hCButton3 = CreateWindow(
        L"BUTTON", L"BLUE", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        820, 400, 200, 60, hWnd, (HMENU)6, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}