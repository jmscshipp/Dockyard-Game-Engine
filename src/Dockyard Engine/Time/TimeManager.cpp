#include "TimeManager.h"

TimeManager* TimeManager::instance = nullptr;

TimeManager::TimeManager()
	: currentTime(0.0f),
	previousTime(0.0f),
	frameTime(0.0f)
{
}

TimeManager::~TimeManager()
{

}

float TimeManager::PrivGetTime()
{
	return currentTime;
}

float TimeManager::PrivGetFrameTime()
{
	return frameTime;
}

void TimeManager::NonstaticProcessTime() // float systemTime parameter
{
	previousTime = currentTime;
	//currentTime = systemTime;
	currentTime = frzTime.ComputeGameTime(previousTime);
	frameTime = currentTime - previousTime;
}

void TimeManager::NonstaticDelete()
{
	delete instance;
	instance = nullptr;
}