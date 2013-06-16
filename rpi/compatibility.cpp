
#include "compatibility.h"

/**********************************************************************/
/**
 * This function is added in order to simulate arduino delay() function
 * @param milisec
*/
SerialFake Serial;

void digitalWrite(uint8_t pin, uint8_t value) {
 GPIO::write(pin, value);

}
void pinMode(uint8_t pin, bool direction){
GPIO::open(pin, direction);
}

void SerialFake::begin( uint32_t speed) {std::cout << "Serial SPEED : "<<speed << std::endl;}
void SerialFake::p( std::string s) {std::cout<< "PRINT" << s;}
void SerialFake::print( std::string s) {std::cout <<"P"<< s;}
void SerialFake::println( std::string s) {std::cout << "PRINTLN : " << (std::string)s << std::endl;}
void SerialFake::printf( String s) {}
 SerialFake::operator bool() {return 1==1;}

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

long millis()
{
	gettimeofday(&end, NULL);
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;	
	return mtime;
}

