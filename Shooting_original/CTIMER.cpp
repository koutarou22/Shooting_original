#include "stdafx.h"
#include "CTIMER.h"


bool CTIMER::IsTimeOver()
{
	return(CTimer_ < 0);
}

void CTIMER::ResetTimer()
{
	CTimer_ = TIMER_INIT_TIME_;
	StartTimer();
}

void CTIMER::StartTimer()
{
	isTimerRun_ = true;
}

void CTIMER::STopTimer()
{
	isTimerRun_ = false;
}

void CTIMER::Update()
{
	if (isTimerRun_)
		CTimer_ = CTimer_ - Scene::DeltaTime();
}

