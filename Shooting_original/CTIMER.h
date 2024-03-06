#pragma once
#include "BasicAbility.h"

const double DEF_TIMER_INTERVAL{ 1 / 24.0 };

class CTIMER :
	public BasicAbility
{
	double TIMER_INIT_TIME_;
public:
	CTIMER() :TIMER_INIT_TIME_(DEF_TIMER_INTERVAL), CTimer_(TIMER_INIT_TIME_), isTimerRun_(true) {}
	CTIMER(double _initTime) :TIMER_INIT_TIME_(_initTime), CTimer_(TIMER_INIT_TIME_), isTimerRun_(true) {}
	double CTimer_;
	bool IsTimeOver();
	void ResetTimer();
	void StartTimer();
	void STopTimer();
	bool isTimerRun_;
	void Update() override;
};

