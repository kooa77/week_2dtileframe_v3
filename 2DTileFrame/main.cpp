#include <Windows.h>

// check 5
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

	HWND hWnd = CreateWindow(
		L"2DTileFrameWnd",		// ����� ������ ��Ÿ��. ��ϵ� ������ ��Ÿ�� �� �߿��� �̸��� ���� ������ �´�. ���� ����� ���� �ִ�.
		L"2D Tile Frame",		// â�� ����
		WS_OVERLAPPEDWINDOW,	// ������ ��Ÿ��. ĸ���� ���� ������, �޴��� ���� ������ ���
		CW_USEDEFAULT, CW_USEDEFAULT,	// x, y ��ǥ
		1024, 768,	// �ʺ�, ����
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

	// check 3 : fps ���� (60)
	float frameInterval = 1.0f / 60.0f;
	float frameTime = 0.0f;

	// check 4
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
			// check 2
			gameTimer.Update();
			float deltaTime = gameTimer.GetDeltaTime();		// ���� �����Ӻ��� ���ݱ��� �帥 �ð��� ����

			// check 1 : �����ӿ� �°� ������Ʈ
			frameTime += deltaTime;	// �ð��� �帥��.
			if (frameInterval <= frameTime)
			{
				frameTime = 0.0f;

				// todo : game update
				OutputDebugString(L"Update\n");
			}
		}
	}

	return 0;
}

