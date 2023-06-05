#include "pch.h"
#include "Timer.h"

// 시간은 몇시몇분몇초가 아닌 어떤 시간을 기준으로 얼만큼 흘렀는지 상대 시간
void Timer::Init()
{
	// GetTickCount64() - 정밀도가 떨어진다는 단점
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount)); // 이전 프레임의 CPU 클럭
}

void Timer::Update()
{
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount)); // 현재 프레임의 CPU 클럭

	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	_frameCount++;
	_frameTime += _deltaTime;

	if (_frameTime > 1.f)
	{
		_fps = static_cast<uint32>(_frameCount / _frameTime);

		_frameTime = 0.f;
		_frameCount = 0;
	}
}