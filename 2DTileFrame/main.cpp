#include <Windows.h>
#include <d3dx9.h>
#include "GameTimer.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(0, L"Hello World", L"Hello", MB_OK);
		return 0;
	case WM_KEYDOWN:
		if (VK_ESCAPE == wParam)
		{
			DestroyWindow(hWnd);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);		// 기본 처리 프로시저
}


// HINSTANCE hInstance : 현재 응용프로그램의 인스턴스 핸들. 응용프로그램을 위한 식별 수단으로 쓰인다.
//	핸들 : 운영체제가부여하는 아이디. 무언가를 식별하거나 가리키기 위해 쓰인다. 특히 객체를 참조하기 위해 쓰인다.
//		윈도우는 핸들을 이용해서, 자원을 관리한다. (응용프로그램 포함)
// HINSTANCE hPrevInstance : 쓰이지 않음.
// PSTR pCmdLine : 프로그램을 실행하는 데 쓰인 명령줄 인수 문자열
// int nCmdShow : 응용프로그램 표시 방식. 크게 보일 것인가, 작게 보일 것인가?
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	int width = 1024;
	int height = 768;
	bool isWindow = true;

	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;	// 창의 스타일 지정. 수평/수직 크기가 변하면 창을 다시 갱신
	wc.lpfnWndProc = WndProc;	// 프로시저 함수. 윈도우 운영체제가 보내는 이벤트를 처리하기 위한 함수
	wc.cbClsExtra = 0;	// 사용 안함
	wc.cbWndExtra = 0;	// 사용 안함
	wc.hInstance = hInstance;	// 응용 프로그램 인스턴스 핸들 연결
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);	// 아이콘을 생성하고, 아이콘 핸들을 세팅해 둔다.
	wc.hCursor = LoadCursor(0, IDC_ARROW);		// 커서를 생성하고, 커서 핸들을 세팅해 둔다.
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 클라이언트 영역의 배경 색을 세팅한다.
	wc.lpszMenuName = 0;	// 창의 메뉴. 현재 없다.
	wc.lpszClassName = L"2DTileFrameWnd";		// 윈도우 스타일의 이름. 이 이름을 이용해서, 다른 창에서 가져다 사용할 수 있다.
	if (!RegisterClass(&wc))
	{
		return 0;
	}

	// 풀스크린 모드일 때는, 윈도우에 부가적인 요소를 제거한다.
	DWORD style;
	if (isWindow)
	{
		style = WS_OVERLAPPEDWINDOW;
	}
	else
	{
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}

	HWND hWnd = CreateWindow(
		L"2DTileFrameWnd",		// 사용할 윈도우 스타일. 등록된 윈도우 스타일 들 중에서 이름을 통해 가지고 온다. 직접 등록할 수도 있다.
		L"2D Tile Frame",		// 창의 제목
		style,	// 윈도우 스타일. 캡션이 있을 것인지, 메뉴가 있을 것인지 등등
		CW_USEDEFAULT, CW_USEDEFAULT,	// x, y 좌표
		width, height,	// 너비, 높이
		0,		// 부모 창의 핸들을 세팅한다. 현재 최상위 창이므로 0을 세팅한다.
		0,		// 메뉴 핸들. 사용하지 않음
		hInstance,	// 윈도우 운영체제가 부여한 인스턴스 핸들을 세팅한다. 현재 창과 연결. 운영체제가 관리할 수 있다.
		0	// 추가적인 생성 플래그. 사용 안함.
	);
	if (NULL == hWnd)
	{
		return 0;
	}


	// hWnd : 하나의 윈도우를 관리하기 위한 핸들(OS는 이 핸들로 해당 윈도우를 기억한다.)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 실제 게임 영역 확보
	if (true == isWindow)
	{
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		MoveWindow(hWnd, 0, 0,
			width + (width - clientRect.right),
			height + (height - clientRect.bottom),
			TRUE);
	}

	// DirectX

	// 누군가가(DirectX)한테 하드웨어 직접 접근할 수 있는
	// 먼가(Device)를 생성해서 달라고 요청
	LPDIRECT3D9 direct3d;	// 그래픽을 담당하는 DirectX
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == direct3d)
	{
		return 0;
	}

	D3DFORMAT format;
	if (isWindow)
	{
		format = D3DFMT_UNKNOWN;	// 윈도우 설정에 맡긴다.
	}
	else
	{
		format = D3DFMT_X8R8G8B8;	// 전용 색상 포맷을  사용.
	}

	// Device를 생성하기 전에,
	// Device를 통해서 화면에 어떻게 보여질지를 결정
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = format;
	d3dpp.BackBufferCount = 1;	// 더블 버퍼링 갯수
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = isWindow;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// 디바이스를 생성
	LPDIRECT3DDEVICE9 dxDevice;
	HRESULT hr = direct3d->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&dxDevice);
	if (FAILED(hr))
	{
		return 0;
	}

	// Sprite COM 인터페이스 생성
	ID3DXSprite* spriteDX;
	hr = D3DXCreateSprite(dxDevice, &spriteDX);
	if (FAILED(hr))
	{
		return 0;
	}

	// 이미지 로드
	IDirect3DTexture9* textureDX;
	RECT textureRect;
	D3DCOLOR textureColor;
	{
		// 로드 할 파일명
		LPCWSTR fileName = L"../Resources/Images/character_sprite.png";

		// 파일로 부터 이미지의 너비와 높이를 얻는다
		D3DXIMAGE_INFO texInfo;
		hr = D3DXGetImageInfoFromFile(fileName, &texInfo);
		if (FAILED(hr))
		{
			return 0;
		}

		// 이미지데이타 로드
		hr = D3DXCreateTextureFromFileEx(dxDevice,
			fileName,
			texInfo.Width, texInfo.Height,
			1,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_ARGB(255, 255, 255, 255),
			&texInfo,
			NULL,
			&textureDX);
		if (FAILED(hr))
		{
			return 0;
		}
		
		// 출력할 영역 지정
		textureRect.left = 0;
		textureRect.right = textureRect.left + texInfo.Width;
		textureRect.top = 0;
		textureRect.bottom = textureRect.top + texInfo.Height;

		textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	float frameInterval = 1.0f / 60.0f;
	float frameTime = 0.0f;

	GameTimer gameTimer;
	gameTimer.Init();

	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		// PeekMessage : 메시지가 없으면, 윈도우가 아닌 응용 프로그램에 제어권을 반환한다.
		//	PM_REMOVE : 메시지큐에서 사용한 메시지 제거
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);		// 키보드 변환 수행. 키 코드를 문자 메시지로 변환
			DispatchMessage(&msg);		// 메시지를 창으로 배분
		}
		else
		{
			gameTimer.Update();
			float deltaTime = gameTimer.GetDeltaTime();		// 지난 프레임부터 지금까지 흐른 시간의 차이

			frameTime += deltaTime;	// 시간이 흐른다.
			if (frameInterval <= frameTime)
			{
				frameTime = 0.0f;

				dxDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 128, 0), 0.0f, 0);	// 매 프레임마다 화면의 색을 채운다.
				{
					dxDevice->BeginScene();
					{
						// Scene 작업 : 게임 화면과 관련된 모든 작업 공간
						spriteDX->Begin(D3DXSPRITE_ALPHABLEND);
						{
							// 2D 이미지 출력 공간. Texture(텍스쳐)
							spriteDX->Draw(
								textureDX,		// 그릴 텍스쳐 정보가 들어있는 인터페이스
								&textureRect,	// 원본 이미지에서 그릴 부분
								NULL,
								NULL,
								textureColor	// 스프라이트의 색상과 알파채널
							);
						}
						spriteDX->End();
					}
					dxDevice->EndScene();
				}
				dxDevice->Present(NULL, NULL, NULL, NULL);	// 채운 색을 모니터를 통해 보여준다.
			}
		}
	}

	if (dxDevice)
	{
		dxDevice->Release();
		dxDevice = NULL;
	}

	if (direct3d)
	{
		direct3d->Release();
		direct3d = NULL;
	}

	return 0;
}

