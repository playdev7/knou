#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // 콜백 프로시저 선언
LRESULT CALLBACK ChildWndProc02(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // 콜백 프로시저 선언

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"HelloAPI";
LPCTSTR ChildClassName  = L"ChildWin"; // 클래스 이름 선언
LPCTSTR ChildClassName02  = L"ChildWin02"; // 클래스 이름 선언

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpszCmdParam,
					 int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH); // 윈도우 색상  //CreateSolidBrush(r,g,b)
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);    
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);     //메인윈도우 클래스 등록

	/* 첫번째 차일드 클래스 */
	WndClass.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH); // 차일드 윈도우 색상
	WndClass.lpfnWndProc =ChildWndProc;      //차일드 윈도우 콜백함수이름 (윈도우프로시저이름)
	WndClass.lpszClassName =ChildClassName; //차일드 윈도우 클래스이름
	RegisterClass(&WndClass); 

	/* 두번째 차일드 클래스 */
	WndClass.hbrBackground=(HBRUSH)GetStockObject(GRAY_BRUSH); // 차일드 윈도우 색상
	WndClass.lpfnWndProc =ChildWndProc02;      //차일드 윈도우 프로시저
	WndClass.lpszClassName =ChildClassName02; //차일드 윈도우 클래스이름
	RegisterClass(&WndClass); 

	hWnd=CreateWindow(lpszClass,			//윈도우클래스 이름
					L"윈도우 프로그래밍",			    //윈도우타이틀
					WS_OVERLAPPEDWINDOW | WS_VISIBLE,   //윈도우스타일
					200, 200,							//윈도우가 보일때 X Y좌표
					600, 600,							//윈도우의 폭과 높이				
					(HWND)NULL,							//부모윈도우 핸들
					(HMENU)NULL,						//윈도우가 가지는 메뉴핸들
					hInstance,							//인스턴스핸들
					NULL);								//여분의 데이터

 	   ShowWindow(hWnd,nCmdShow);
	
	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
						 WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"메인윈도우 생성";
	switch(iMessage) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				TextOut(hdc,100, 100, text, lstrlen(text));
				EndPaint(hWnd,&ps);
				return 0;
			}
		case WM_CREATE:
		{
			HWND hChildWnd = CreateWindow(  // 차일드 윈도우 생성
				ChildClassName,     		// 차일드 윈도우 클래스 이름 
				L"차일드 윈도우",            	// 윈도우 타이틀 
				WS_OVERLAPPEDWINDOW | WS_CHILD,  // 윈도우  스타일 
				20,       		// 윈도우 보일 때 x 좌표 
				150,       		// 윈도우 보일 때 y 좌표 
				260,       		// 윈도우 폭
				200,       		// 윈도우 높이
				hWnd,         		// 부모 윈도우
				(HMENU) 1000,        	// 차일드 윈도우ID 
				g_hInst,           		// 인스턴스 핸들 
				(LPVOID) NULL);      	// 여분의 데이터

			if (!hChildWnd) 	return -1; // 차일드윈도우 핸들이 false일경우를 check. -1을 retrun시켜 error message.

			ShowWindow(hChildWnd, SW_SHOW);

			hChildWnd = CreateWindow(  // 차일드 윈도우 생성
				ChildClassName02,     		// 차일드 윈도우 클래스 이름 
				L"차일드 윈도우",            	// 윈도우 타이틀 
				WS_OVERLAPPEDWINDOW | WS_CHILD,  // 윈도우  스타일 
				310,       		// 윈도우 보일 때 x 좌표 
				150,       		// 윈도우 보일 때 y 좌표 
				260,       		// 윈도우 폭
				200,       		// 윈도우 높이
				hWnd,         		// 부모 윈도우
				(HMENU) 1000,        	// 차일드 윈도우ID 
				g_hInst,           		// 인스턴스 핸들 
				(LPVOID) NULL);      	// 여분의 데이터

			if (!hChildWnd) 	return -1; // 차일드윈도우 핸들이 false일경우를 check. -1을 retrun시켜 error message.

			ShowWindow(hChildWnd, SW_SHOW);

			return 0;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // 차일드 윈도우 프로시저 콜백함수 선언.
{
	LPCTSTR text = L"차일드 윈도우생성";
	switch(message)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd,&ps);
			TextOut(hdc,10, 10, text, lstrlen(text));
			EndPaint(hWnd,&ps);
			return 0;
		}

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK ChildWndProc02(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // 차일드 프로시저2 콜백함수 선언.
{
	LPCTSTR text = L"두번째 차일드 윈도우생성";
	switch(message)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd,&ps);
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(255, 255, 255));
			TextOut(hdc,10, 10, text, lstrlen(text));
			TextOut(hdc,10, 35, text, lstrlen(text));
			EndPaint(hWnd,&ps);
			return 0;
		}

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}