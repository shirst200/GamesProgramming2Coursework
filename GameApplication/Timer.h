#pragma once

#include <windows.h>

class Timer
{
public:
        Timer();					//basic constructor
        ~Timer();					//basic deconstructor

        void start();				//start the timer
        void update();				//called every frame
        void reset();				//reset the timer
        float getElapsedTime();		//get the time that has currently elapsed
        float getTotalTime();		//get the total time
private:
        __int64 m_LastTime;			//the last time checked
        __int64 m_CurrentTime;		//the current time
        __int64 m_Frequency;		//the performance frequency
        float m_fElapsedTime;		//the elapsed time
        float m_fTotalTime;			//the total time
        bool m_bUseHighPrecision;	//the precision of time measurement
};