#include <Windows.h>
#include <d3dx9.h>
#include "GameTimer.h"
#include "Sprite.h"

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

	return DefWindowProc(hWnd, msg, wParam, lParam);		// �⺻ ó�� ���ν���
}


// HINSTANCE hInstance : ���� �������α׷��� �ν��Ͻ� �ڵ�. �������α׷��� ���� �ĺ� �������� ���δ�.
//	�ڵ� : �ü�����ο��ϴ� ���̵�. ���𰡸� �ĺ��ϰų� ����Ű�� ���� ���δ�. Ư�� ��ü�� �����ϱ� ���� ���δ�.
//		������� �ڵ��� �̿��ؼ�, �ڿ��� �����Ѵ�. (�������α׷� ����)
// HINSTANCE hPrevInstance : ������ ����.
// PSTR pCmdLine : ���α׷��� �����ϴ� �� ���� ����� �μ� ���ڿ�
// int nCmdShow : �������α׷� ǥ�� ���. ũ�� ���� ���ΰ�, �۰� ���� ���ΰ�?
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	int width = 1024;
	int height = 768;
	bool isWindow = true;

	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;	// â�� ��Ÿ�� ����. ����/���� ũ�Ⱑ ���ϸ� â�� �ٽ� ����
	wc.lpfnWndProc = WndProc;	// ���ν��� �Լ�. ������ �ü���� ������ �̺�Ʈ�� ó���ϱ� ���� �Լ�
	wc.cbClsExtra = 0;	// ��� ����
	wc.cbWndExtra = 0;	// ��� ����
	wc.hInstance = hInstance;	// ���� ���α׷� �ν��Ͻ� �ڵ� ����
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);	// �������� �����ϰ�, ������ �ڵ��� ������ �д�.
	wc.hCursor = LoadCursor(0, IDC_ARROW);		// Ŀ���� �����ϰ�, Ŀ�� �ڵ��� ������ �д�.
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// Ŭ���̾�Ʈ ������ ��� ���� �����Ѵ�.
	wc.lpszMenuName = 0;	// â�� �޴�. ���� ����.
	wc.lpszClassName = L"2DTileFrameWnd";		// ������ ��Ÿ���� �̸�. �� �̸��� �̿��ؼ�, �ٸ� â���� ������ ����� �� �ִ�.
	if (!RegisterClass(&wc))
	{
		return 0;
	}

	// Ǯ��ũ�� ����� ����, �����쿡 �ΰ����� ��Ҹ� �����Ѵ�.
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
		L"2DTileFrameWnd",		// ����� ������ ��Ÿ��. ��ϵ� ������ ��Ÿ�� �� �߿��� �̸��� ���� ������ �´�. ���� ����� ���� �ִ�.
		L"2D Tile Frame",		// â�� ����
		style,	// ������ ��Ÿ��. ĸ���� ���� ������, �޴��� ���� ������ ���
		CW_USEDEFAULT, CW_USEDEFAULT,	// x, y ��ǥ
		width, height,	// �ʺ�, ����
		0,		// �θ� â�� �ڵ��� �����Ѵ�. ���� �ֻ��� â�̹Ƿ� 0�� �����Ѵ�.
		0,		// �޴� �ڵ�. ������� ����
		hInstance,	// ������ �ü���� �ο��� �ν��Ͻ� �ڵ��� �����Ѵ�. ���� â�� ����. �ü���� ������ �� �ִ�.
		0	// �߰����� ���� �÷���. ��� ����.
	);
	if (NULL == hWnd)
	{
		return 0;
	}


	// hWnd : �ϳ��� �����츦 �����ϱ� ���� �ڵ�(OS�� �� �ڵ�� �ش� �����츦 ����Ѵ�.)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���� ���� ���� Ȯ��
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

	// ��������(DirectX)���� �ϵ���� ���� ������ �� �ִ�
	// �հ�(Device)�� �����ؼ� �޶�� ��û
	LPDIRECT3D9 direct3d;	// �׷����� ����ϴ� DirectX
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == direct3d)
	{
		return 0;
	}

	D3DFORMAT format;
	if (isWindow)
	{
		format = D3DFMT_UNKNOWN;	// ������ ������ �ñ��.
	}
	else
	{
		format = D3DFMT_X8R8G8B8;	// ���� ���� ������  ���.
	}

	// Device�� �����ϱ� ����,
	// Device�� ���ؼ� ȭ�鿡 ��� ���������� ����
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = format;
	d3dpp.BackBufferCount = 1;	// ���� ���۸� ����
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = isWindow;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// ����̽��� ����
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

	// Sprite COM �������̽� ����
	ID3DXSprite* spriteDX;
	hr = D3DXCreateSprite(dxDevice, &spriteDX);
	if (FAILED(hr))
	{
		return 0;
	}

	// �̹��� �ε�
	IDirect3DTexture9* textureDX;
	RECT textureRect;
	D3DCOLOR textureColor;
	LPCWSTR fileName = L"../Resources/Images/character_sprite.png";

	// ��������Ʈ��  ����
	Sprite* testSprite = new Sprite();
	testSprite->Init(fileName, dxDevice, spriteDX);

	float frameInterval = 1.0f / 60.0f;
	float frameTime = 0.0f;

	GameTimer gameTimer;
	gameTimer.Init();

	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		// PeekMessage : �޽����� ������, �����찡 �ƴ� ���� ���α׷��� ������� ��ȯ�Ѵ�.
		//	PM_REMOVE : �޽���ť���� ����� �޽��� ����
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);		// Ű���� ��ȯ ����. Ű �ڵ带 ���� �޽����� ��ȯ
			DispatchMessage(&msg);		// �޽����� â���� ���
		}
		else
		{
			gameTimer.Update();
			float deltaTime = gameTimer.GetDeltaTime();		// ���� �����Ӻ��� ���ݱ��� �帥 �ð��� ����

			testSprite->Update(deltaTime);

			frameTime += deltaTime;	// �ð��� �帥��.
			if (frameInterval <= frameTime)
			{
				frameTime = 0.0f;

				dxDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 128, 0), 0.0f, 0);	// �� �����Ӹ��� ȭ���� ���� ä���.
				{
					dxDevice->BeginScene();
					{
						// Scene �۾� : ���� ȭ��� ���õ� ��� �۾� ����
						spriteDX->Begin(D3DXSPRITE_ALPHABLEND);
						{
							testSprite->Render();
						}
						spriteDX->End();
					}

					// DeviceLost ó��
					// Device ���� Ȯ�� (�� ������Ʈ ����)
					hr = dxDevice->TestCooperativeLevel();
					if (FAILED(hr))// Device ���¿� ������ ������,
					{
						// �� ������ ������ ���� �ٸ��� ó��
						if (D3DERR_DEVICELOST == hr)
						{
							// ���� �츮�� �ƹ� �͵� �� �� ���� ����
							Sleep(100);	// ����
						}
						else if(D3DERR_DEVICENOTRESET == hr)
						{
							// ������ ����������, ������ ������ ������ ����.
							// ���ݺ��� ������ ���� �Ͻÿ�.

							// ����̽��� �� �� ����̽��� ���ػ����� ��� ���ҽ��� ����
							// 1. ������ ������� �͵��� ��� ����
							testSprite->Release();

							// 2. ���� ���� (����)
							direct3d = Direct3DCreate9(D3D_SDK_VERSION);
							if (NULL != direct3d)
							{
								// ����̽� ����
								HRESULT hr = direct3d->CreateDevice(
									D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
									hWnd,
									D3DCREATE_HARDWARE_VERTEXPROCESSING,
									&d3dpp,
									&dxDevice);
								if (SUCCEEDED(hr))
								{
									// ��������Ʈ �������̽� ����
									hr = D3DXCreateSprite(dxDevice, &spriteDX);
									if (SUCCEEDED(hr))
									{
										testSprite->Reset();
									}
								}
							}
						}
					}

					dxDevice->EndScene();
				}
				dxDevice->Present(NULL, NULL, NULL, NULL);	// ä�� ���� ����͸� ���� �����ش�.
			}
		}
	}

	// �ؽ��� ������ ��������Ʈ�� �ı��� ��
	if (NULL != testSprite)
	{
		delete testSprite;
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

