#include "cTimer.h"
#include <Windows.h>

cTimer::cTimer()
{
	this->mElapsedTime = 0;
	this->mStartTime = 0;
	this->mStopTime = 0;

	LARGE_INTEGER tempTime;

	QueryPerformanceFrequency( &tempTime ); 

	this->mFrequency = static_cast<unsigned long long>( tempTime.QuadPart );
}

cTimer::~cTimer() {}

void cTimer::Start()
{
	LARGE_INTEGER tempTime;
	QueryPerformanceCounter( &tempTime );
	this->mStartTime = static_cast<unsigned long long>( tempTime.QuadPart );
}

void cTimer::Stop()
{
	LARGE_INTEGER tempTime;
	QueryPerformanceCounter( &tempTime );
	this->mStopTime = static_cast<unsigned long long>( tempTime.QuadPart );
}

void cTimer::Reset()
{
	this->mElapsedTime = 0;
	this->mStartTime = 0;
	this->mStopTime = 0;
}

float cTimer::Split()
{
	LARGE_INTEGER tempTime;
	QueryPerformanceCounter( &tempTime );
	this->mStopTime = static_cast<unsigned long long>( tempTime.QuadPart );

	this->mElapsedTime = this->mStopTime - this->mStartTime;
	float elapsedTimeSec = static_cast<float>( this->mElapsedTime ) / this->mFrequency;

	return elapsedTimeSec;
}

float cTimer::Restart()
{
	LARGE_INTEGER tempTime;
	QueryPerformanceCounter( &tempTime );
	this->mStopTime = static_cast<unsigned long long>( tempTime.QuadPart );

	this->mElapsedTime = this->mStopTime - this->mStartTime;
	float elapsedTimeSec = static_cast<float>( this->mElapsedTime ) / this->mFrequency;

	QueryPerformanceCounter( &tempTime );
	this->mStartTime = static_cast<unsigned long long>( tempTime.QuadPart );

	return elapsedTimeSec;
}

float cTimer::Elapsed()
{
	this->mElapsedTime = this->mStopTime - this->mStartTime;
	float elapsedTimeSec = static_cast<float>( this->mElapsedTime ) / this->mFrequency;

	return elapsedTimeSec;
}

unsigned long long cTimer::GetFrequency()
{
	return this->mFrequency;
}