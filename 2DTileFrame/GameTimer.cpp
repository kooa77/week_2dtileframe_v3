#include <Windows.h>
#include "GameTimer.h"

GameTimer::GameTimer()
{
	// check 9-1 : �ð��� ��� ���� ���̽� �۾�
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);		// �ʴ� �������� ����. PC �� ���ο��� �ð��� ����ϴ� ���
	_secondsPerCount = 1.0f / (double)countsPerSec;		// �� �������ô� �ɸ��� �ð�
}

GameTimer::~GameTimer()
{

}

// check 7-2
void GameTimer::Init()
{
	// check 9-2 : �ð��� ��� ���� ���̽� �۾�
	__int64 currentTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);	// 64��Ʈ ������ �̿��ؼ� �ð� ���� �����ش�. �ð��� ���� ������ ����. ���� �ð��� ��´�.

	// check 11-2
	_prevTime = currentTime;
	_deltaTime = 0.0;
}

void GameTimer::Update()
{
	// check 9-3 : �ð��� ��� ���� ���̽� �۾�
	__int64 currentTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);	// 64��Ʈ ������ �̿��ؼ� �ð� ���� �����ش�. �ð��� ���� ������ ����. ���� �ð��� ��´�.

	// check 10 - ��ŸŸ���� ���Ѵ�.
	_deltaTime = (currentTime - _prevTime) * _secondsPerCount;
	_prevTime = currentTime;

}

float GameTimer::GetDeltaTime()
{
	// check 8-1
	return _deltaTime;
}