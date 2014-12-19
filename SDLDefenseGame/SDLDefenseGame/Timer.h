#ifndef	__TIMER_H__
#define __TIMER_H__

#include <Windows.h>

class Timer
{
private:
	bool m_bIsDisabled;

	unsigned int m_uiStartMs;
	unsigned int m_uiWaitMs;

public:
	Timer( unsigned int _uiWaitMs )
	{
		m_uiStartMs = timeGetTime();
		m_uiWaitMs = _uiWaitMs;

		m_bIsDisabled = false;
	}
	
	~Timer()
	{
	}

	void Disable()
	{
		m_bIsDisabled = true;
	}

	bool IsDisabled()
	{
		return m_bIsDisabled;
	}

	bool Check()
	{
		if( m_bIsDisabled )
			return false;

		if( m_uiStartMs + m_uiWaitMs <= timeGetTime() )
		{
			m_bIsDisabled = true;
			return true;
		}
		else
			return false;
	}

	void Renew()
	{
		m_uiStartMs = timeGetTime();
		m_bIsDisabled = false;
	}

	int GetRemainTime()
	{
		return (m_uiWaitMs+m_uiStartMs)-timeGetTime();
	}
};

#endif