/**
 *
 * Tetwiis
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 
//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <gccore.h>
#include <ogc/lwp_watchdog.h>



#ifndef TIMER_HPP
#define TIMER_HPP
class Timer
{
	public:
		Timer();
		~Timer();
		
		double then;
		double timePassed();
		
	private:

};
#endif

