
#include "compatibility.h"
/**********************************************************************/
/**
 * This function is added in order to simulate arduino delay() function
 * @param milisec
 */
//SerialFake Serial;

void digitalWrite(uint8_t a, uint8_t b) {
}
void pinMode(uint8_t a, bool b){}

void SerialFake::begin( uint32_t speed) {}
void SerialFake::print( String str) {}
void SerialFake::println( String str) {}
void SerialFake::printf( String str) {}

void __msleep(int milisec)
{
	struct timespec req = {0};
	req.tv_sec = 0;
	req.tv_nsec = milisec * 1000000L;
	nanosleep(&req, (struct timespec *)NULL);	
}

void __usleep(int milisec)
{
	struct timespec req = {0};
	req.tv_sec = 0;
	req.tv_nsec = milisec * 1000L;
	nanosleep(&req, (struct timespec *)NULL);	
}

/**
 * This function is added in order to simulate arduino millis() function
 */
void __start_timer()
{
	gettimeofday(&start, NULL);
}

long __millis()
{
	gettimeofday(&end, NULL);
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;	
	return mtime;
}
