#pragma once

// check 6
class GameTimer
{
private:
	// check 9-3
	float _secondsPerCount;

	// check 8-2
	float _deltaTime;
	float _prevTime;

public:
	GameTimer();
	~GameTimer();

	// check 7-1
	void Init();
	void Update();
	float GetDeltaTime();		// ���� �����Ӻ��� ���ݱ��� �帥 �ð��� ����
};