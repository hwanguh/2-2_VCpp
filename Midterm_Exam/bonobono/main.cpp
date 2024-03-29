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
    POINT startMovePoint;
    POINT endMovePoint;
    unsigned int isMouseLButtonPressed : 1;
    unsigned int isMouseRButtonPressed : 1;
    int offsetX;
    int offsetY;
};
struct Mouse mouse = { {0},{0}, {0} , {0}, 0, 0, 0, 0 };//선언 및 초기화

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

//그림 관련 변수
RECT drawingRect;
HBRUSH hBrushBack = CreateSolidBrush(RGB(255, 240, 200));
HBRUSH hBrushDraw = CreateSolidBrush(RGB(255, 255, 255));
HBRUSH hBrush;
HDC hdc;
PAINTSTRUCT ps;

void Draw(HWND hWnd, HDC hdc, WPARAM wParam) {
    hBrush = CreateSolidBrush(RGB(R, G, B));
    if (mouse.isMouseLButtonPressed || mouse.isMouseRButtonPressed) {
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
    }
    DeleteObject(hBrush);
}

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_KEYDOWN:
        if (32 == wParam && fig.isBono) {
            fig.isSpace = 1;
            InvalidateRect(hWnd, &drawingRect, true);
        }
        break;
    case WM_KEYUP:
        fig.isSpace = 0;
        InvalidateRect(hWnd, &drawingRect, true);
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
            if (mouse.isMouseLButtonPressed) {
                mouse.endPoint.x = LOWORD(lParam);
                mouse.endPoint.y = HIWORD(lParam);
                InvalidateRect(hWnd, &drawingRect, true);
            }
            else if (mouse.isMouseRButtonPressed) {
                mouse.endMovePoint.x = LOWORD(lParam);
                mouse.endMovePoint.y = HIWORD(lParam);
                mouse.offsetX = mouse.endMovePoint.x - mouse.startMovePoint.x;
                mouse.offsetY = mouse.endMovePoint.y - mouse.startMovePoint.y;
                if (fig.isBox) {
                    mouse.startPoint.x += mouse.offsetX;
                    mouse.endPoint.x += mouse.offsetX;
                    mouse.startPoint.y += mouse.offsetY;
                    mouse.endPoint.y += mouse.offsetY;
                }
                else if (fig.isWheel) {
                    mouse.endPoint.x += mouse.offsetX;
                    mouse.endPoint.y += mouse.offsetX;
                }
                InvalidateRect(hWnd, &drawingRect, true);
                mouse.startMovePoint = mouse.endMovePoint;
            }
        }
        break;
    case WM_LBUTTONUP:
        mouse.endPoint.x = LOWORD(lParam);
        mouse.endPoint.y = HIWORD(lParam);
        mouse.isMouseLButtonPressed = 0;
        break;
    case WM_RBUTTONDOWN:
        if (((mouse.startPoint.x >= LOWORD(lParam) && mouse.endPoint.x <= LOWORD(lParam))
            || (mouse.startPoint.x <= LOWORD(lParam) && mouse.endPoint.x >= LOWORD(lParam)))
            && (((mouse.startPoint.y >= HIWORD(lParam) && mouse.endPoint.y <= HIWORD(lParam))
                || (mouse.startPoint.y <= HIWORD(lParam) && mouse.endPoint.y >= HIWORD(lParam))))) {
            mouse.startMovePoint.x = LOWORD(lParam);
            mouse.startMovePoint.y = HIWORD(lParam);
            mouse.isMouseRButtonPressed = 1;
        }
        break;
    case WM_RBUTTONUP:
        mouse.endMovePoint.x = LOWORD(lParam);
        mouse.endMovePoint.y = HIWORD(lParam);
        mouse.isMouseRButtonPressed = 0;
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
            break;
        }
        SetFocus(hWnd); //키보드 포커스 없애기
        InvalidateRect(hWnd, &drawingRect, true); //그림 영역 무효화
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        SelectObject(hdc, hBrushBack);
        Rectangle(hdc, boxLeft, boxTop, boxRight, boxBottom);
        SelectObject(hdc, hBrushDraw);
        Rectangle(hdc, drawingLeft, drawingTop, drawingRight, drawingBottom);

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
        L"BUTTON", L"button4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
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