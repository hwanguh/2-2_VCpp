#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT startMovePoint = { 0 };
POINT endMovePoint = { 0 };
int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_LBUTTONDOWN){
		startPoint.x = LOWORD(lParam);
		startPoint.y = HIWORD(lParam);
		isMouseLButtonPressed = 1;
	}

	//강의에 안나왔지만 마우스가 움직일때의 이벤트를 뜻합니다.
	else if (uMsg == WM_MOUSEMOVE) {		// 마우스 이동 중
		if (isMouseLButtonPressed){
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);
		}
		else if (isMouseRButtonPressed) {
			endMovePoint.x = LOWORD(lParam);
			endMovePoint.y = HIWORD(lParam);

			int offsetX = endMovePoint.x - startMovePoint.x;
			int offsetY = endMovePoint.y - startMovePoint.y;

			startPoint.x += offsetX;
			endPoint.x += offsetX;
			startPoint.y += offsetY;
			endPoint.y += offsetY;

			InvalidateRect(hwnd, NULL, TRUE);
			UpdateWindow(hwnd);

			startMovePoint = endMovePoint;
		}
	}
	else if (uMsg == WM_LBUTTONUP) {
		endPoint.x = LOWORD(lParam);
		endPoint.y = HIWORD(lParam);

		// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
		InvalidateRect(hwnd, NULL, TRUE);

		isMouseLButtonPressed = 0;
	}
	else if (uMsg == WM_RBUTTONDOWN
			&& ((startPoint.x > LOWORD(lParam) && endPoint.x < LOWORD(lParam)
			&& startPoint.y > HIWORD(lParam) && endPoint.y < HIWORD(lParam))
			|| (startPoint.x < LOWORD(lParam) && endPoint.x > LOWORD(lParam)
				&& startPoint.y < HIWORD(lParam) && endPoint.y > HIWORD(lParam)))
		) {
		startMovePoint.x = LOWORD(lParam);
		startMovePoint.y = HIWORD(lParam);
		isMouseRButtonPressed = 1;
	}
	else if (uMsg == WM_RBUTTONUP) {

		isMouseRButtonPressed = 0;
	}
	else if (uMsg == WM_PAINT) {
		HDC hdc = GetDC(hwnd);
		
		if (isMouseLButtonPressed || isMouseRButtonPressed)
		{
			HDC hdc = GetDC(hwnd);
			RECT rect;
			HBRUSH hBrush = (HBRUSH)COLOR_WINDOW;
			GetClientRect(hwnd, &rect);
			FillRect(hdc, &rect, hBrush);
			MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
			rect = { startPoint.x+1, startPoint.y + 1, endPoint.x - 1, endPoint.y - 1 };
			hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
			Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
			FillRect(hdc, &rect, hBrush);
		}
		ReleaseDC(hwnd, hdc);
	}
	else if (uMsg == WM_DESTROY) {
		PostQuitMessage(0);
	}
	else{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return S_OK;
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	/* 윈도우 클래스 선언.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// 모두 0으로 초기화.

	// 윈도우 클래스 값 설정
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//예외
	}

	// Window viewport 영역 조정
	RECT rect = { 150, 100, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("컴소 Application"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	// 오류 검사.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// 창 보이기.
	ShowWindow(hwnd, SW_SHOW); // 창 띄우고
	UpdateWindow(hwnd); // 업데이트해야 보임. 한 쌍으로 쓴다고 보면 됨.



	// 메시지 처리 루프.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// 메시지 처리.
		if (GetMessage(&msg, hwnd, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
		{

			// 메시지 해석해줘.
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달해줘.
			DispatchMessage(&msg);

		}
		/*else
		{

		}*/
	}

	//종료 메시지 보내기
	return (int)msg.wParam;

}