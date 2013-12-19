#include "Timer.h"

Timer::Timer()						//basic constructor
{
        m_LastTime=0;				//the last time checked
        m_CurrentTime=0;			//the current time 
        m_bUseHighPrecision=false;	//are we taking time measurements with a high degree of accuracy?
        m_fElapsedTime=0.0f;		//the elapsed time
        m_fTotalTime=0.0f;			//the total time
}

Timer::~Timer()						//basic deconstructor
{

}

void Timer::start()					//start the timer
{
        if (QueryPerformanceCounter((LARGE_INTEGER*)&m_LastTime))			//use a higher degree of accuracy if running at high performance
        {
                m_bUseHighPrecision=true;
                QueryPerformanceFrequency((LARGE_INTEGER*)&m_Frequency);
        }
        else
        {
                //use get time
        }
}

void Timer::reset()					//reset the timer
{
        m_fElapsedTime=0.0f;		//by setting elapsed and total time to 0
        m_fTotalTime=0.0f;
}

void Timer::update()
{
        if (m_bUseHighPrecision)		//if we're using the high accuracy, increment the timer based on the frequency of updating
        {
                QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentTime);
                m_fElapsedTime=(float)((m_CurrentTime-m_LastTime))*1.0f/(float)m_Frequency;
                m_LastTime=m_CurrentTime;
                m_fTotalTime+=m_fElapsedTime;
        }
        else
        {

        }
}

float Timer::getElapsedTime()		//return the total time elapsed
{
        return m_fElapsedTime;
}

float Timer::getTotalTime()			//return the total time
{
        return m_fTotalTime;
}