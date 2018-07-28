#include <Windows.h>

// ������ ���ν��� �Լ� : ������� ���� ���� �̺�Ʈ�� ó���ϴ� �Լ� (���� ó���Ѵ�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(0, "Hello World", "Hello", MB_OK);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(
	HINSTANCE hInstance,	// ���� ���� ���α׷��� ���� �ڵ�
	HINSTANCE hPrevInstance,	// �Ⱦ���
	PSTR pCmdLine,	// �����ϴµ� ���̴� ����� �Ǵ� �μ�
	int nCmdShow	// �������α׷� ǥ�� ���. �ּ�ȭ/�ִ�ȭ �ؼ� �����ٰų� �܎�
)
{
	// ������ ��Ÿ���� �����
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	// ������ ���ν��� �Լ� ���
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = "2DTileFrameWnd";			// �� ������ ��Ÿ���� �̸�

	// ���� ������ ��Ÿ�� ���
	if (FALSE == RegisterClass(&wc))
	{
		return 0;
	}

	// â �ڵ�(���̵�)�� ���� �߱��� ����
	HWND hWnd = CreateWindow(
		"2DTileFrameWnd",	// ����� ������ ��Ÿ�� �̸�. OS�� ��� �Ǿ�����.
		"2D Tile Frmae",
		WS_OVERLAPPEDWINDOW,	// ������ ��Ÿ��
		CW_USEDEFAULT, CW_USEDEFAULT,	// ������ġ :  x, y
		1024, 768,		// �ػ�. �ʺ�/����
		0,		// �θ� â�� �ڵ�. ��� ����
		0,		// �޴� �ڵ�. ��� ����
		hInstance,	// OS�� ������ ����. OS���� �����츦 ������ �� �ִ�.
		0
	);
	if (NULL == hWnd)
	{
		return 0;
	}

	// hWnd : �ϳ��� �����츦 ����Ű�� �ڵ�(���̵�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// �� �����찡 ������ �ʰ� �����ǵ��� ó��
	MSG msg;
	while (-1 != GetMessage(&msg, 0, 0, 0))	// �߻��� �޽����� ������
	{
		TranslateMessage(&msg);		// Ű���� ��ȯ ����
		DispatchMessage(&msg);	// �޽��� â�� ����� ��û�Ѵ�.
	}

	return 0;
}