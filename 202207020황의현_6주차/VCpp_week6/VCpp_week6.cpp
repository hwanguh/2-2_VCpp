//#define DEBUG
#ifdef UNICODE
#ifdef DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:WINDOWS")
#endif // DEBUG
#else
#ifdef DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:WINDOWS")
#endif // DEBUG
#endif

#include <windows.h>
#include <thread>
#include <chrono>

bool key[256] = { 0 };

RECT rect_user = { 5, 5, 30, 30 }; // 왼쪽 상단 좌표 (50, 50)에서 오른쪽 하단 좌표 (150, 150)까지의 사각형
RECT rect_target = { 100, 100, 300, 300 }; // 왼쪽 상단 좌표 (50, 50)에서 오른쪽 하단 좌표 (150, 150)까지의 사각형
// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = GetDC(hwnd);

	HBRUSH hBrush_user = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH hBrush_target = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH hBrush_eraser = CreateSolidBrush(RGB(255, 255, 255));
	const wchar_t* text = L"이게 왜 맞아";
	

	if (uMsg == WM_KEYDOWN){
		key[wParam] = 1;
		InvalidateRect(hwnd, NULL, TRUE);
	}
	else if (uMsg == WM_KEYUP) {
		key[wParam] = 0;
	}
	else if (uMsg == WM_PAINT){
		FillRect(hdc, &rect_user, hBrush_eraser);
		int offsetX = 0;
		int offsetY = 0;
		if (key[VK_LEFT] == key[VK_RIGHT]) {
			offsetX = 0;
		}
		else if (key[VK_LEFT]) {
			offsetX = -1;
		}
		else {
			offsetX = 1;
		}

		if (key[VK_UP] == key[VK_DOWN]) {
			offsetY = 0;
		}
		else if (key[VK_UP]) {
			offsetY = -1;
		}
		else {
			offsetY = 1;
		}
		rect_user.left += offsetX;
		rect_user.right += offsetX;
		rect_user.top += offsetY;
		rect_user.bottom += offsetY;

		FillRect(hdc, &rect_target, hBrush_target);

		if (rect_user.left > rect_target.left
			&& rect_user.top > rect_target.top
			&& rect_user.bottom < rect_target.bottom
			&& rect_user.right < rect_target.right) {
			TextOut(hdc, 155, 190, text, lstrlen(text));
		}

		FillRect(hdc, &rect_user, hBrush_user);
		
		std::this_thread::sleep_for(std::chrono::microseconds(2));
	}
	else if (uMsg == WM_CLOSE) {
		DestroyWindow(hwnd);
	}
	else if (uMsg == WM_DESTROY) {
		PostQuitMessage(0);
	}
	else{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	DeleteObject(hBrush_user);
	DeleteObject(hBrush_target);
	DeleteObject(hBrush_eraser);
	ReleaseDC(hwnd, hdc);

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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//예외
	}

	// Window viewport 영역 조정
	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("202207020황의현"),
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

	// 메시지 처리.
	while (msg.message != WM_QUIT)
	{
		if (GetMessage(&msg, NULL, 0, 0))
		{
			// 메시지 해석해줘.
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달해줘.
			DispatchMessage(&msg);
		}
		//if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		//{
		//	// 메시지 해석해줘.
		//	TranslateMessage(&msg);
		//	// 메시지를 처리해야할 곳에 전달해줘.
		//	DispatchMessage(&msg);
		//} // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
		//else{}
	}

	UnregisterClass(wc.lpszClassName, wc.hInstance);

	//종료 메시지 보내기
	return (int)msg.wParam;

}