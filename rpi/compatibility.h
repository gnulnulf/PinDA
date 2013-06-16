/* 
 * File:   compatiblity.h
 * Author: purinda
 *
 * Created on 24 June 2012, 3:08 PM
 */

#ifndef COMPATIBLITY_H
#define	COMPATIBLITY_H

#include <string>
#ifdef	__cplusplus
//extern "C" {
#endif
	
#include <stddef.h>
#include <time.h>
#include <sys/time.h>
#include <inttypes.h>

#include <string>
#include <iostream>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <inttypes.h>
#include <linux/types.h>
#include "gpio.h"

void digitalWrite(uint8_t a,uint8_t b);
void pinMode(uint8_t a, bool b);

#define pgm_read_word(p) (*(p))
#define pgm_read_byte(p) (*(p))
#define pgm_read_word(p) (*(p)) 
#define PSTR(x) (x)
#define printf_P printf
#define strlen_P strlen
#define PROGMEM
#define pgm_read_word(p) (*(p))
#define PRIPSTR "%s"



#define INPUT 1
#define OUTPUT 1
#define realdigitalWrite(pin, value) GPIO::write(pin, value)
#define realpinMode(pin, value) GPIO::open(pin, value)
#define SPI_CLOCK_DIV4 0x00
#define SPI_CLOCK_DIV16 0x01
#define SPI_CLOCK_DIV64 0x02
#define SPI_CLOCK_DIV128 0x03
#define SPI_CLOCK_DIV2 0x04
#define SPI_CLOCK_DIV8 0x05
#define SPI_CLOCK_DIV32 0x06
//#define SPI_CLOCK_DIV64 0x07

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define LOW 0
#define HIGH 1
#define MSBFIRST


#define String std::string

void printf_begin(void);

// added attribute unused to avoid compiler warnings
static struct timeval start __attribute__ ((unused)) ,end __attribute__ ((unused));

static long __attribute__ ((unused)) mtime;
static long __attribute__ ((unused)) seconds;
static long __attribute__ ((unused)) useconds;

#define delay(milisec) __msleep(milisec)
#define delayMicroseconds(usec) __usleep(usec)

void __msleep(int milisec);
void __usleep(int milisec);
void __start_timer();
long __millis();
long millis();


class SerialFake {
	public:
		void begin(uint32_t speed);
		void p(std::string s);
		void print(std::string s);
		void printf(std::string s);
		void println(std::string s);
		//bool SerialFake(void);
		operator bool(void);
		


};
extern SerialFake Serial;


#ifdef	__cplusplus
//}
#endif

#endif	/* COMPATIBLITY_H */

