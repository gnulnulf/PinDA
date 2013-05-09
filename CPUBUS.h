/*
  CPUBUS.h - interface to the 8bit 68xx memory bus
*/

/**
* @file
* @author Arco van Geest <arco@appeltaart.mine.nu>
* @brief interface to the 8bit 68xx memory bus
* @copyright 2013 Arco van Geest <arco@appeltaart.mine.nu> All right reserved.
* @version 1.0
* 
* @section LICENSE
*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
* several methods to access the 680x memory bus.
* This is no emulator, just a way to access the periperials on the memory bus.
*/
#ifndef CPUBUS_h
#define CPUBUS_h


/* ****************************************************************************
* Includes
******************************************************************************/
#include <inttypes.h>
#include <string.h>

#include <SPI.h>
#include "Mcp23s17.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
//#if defined(ARDUINO)
#include "WProgram.h"
//#endif
#endif

/* *****************************************************************************
* Definitions
******************************************************************************/
// #define CPUBUS_DIRECT 0
// #define CPUBUS_SPI 1
// #define CPUBUS_I2C 2


#define CPUBUS_DATA_PORT PORTL
#define CPUBUS_DATA_PINS PINL
#define CPUBUS_DATA_DDR  DDRL

#define CPUBUS_ADDRL_PORT PORTA
#define CPUBUS_ADDRL_PINS PINA
#define CPUBUS_ADDRL_DDR  DDRA

#define CPUBUS_ADDRH_PORT PORTC
#define CPUBUS_ADDRH_PINS PINC
#define CPUBUS_ADDRH_DDR  DDRC

#define CPUBUS_CTL_PORT PORTF
#define CPUBUS_CTL_PINS PINF
#define CPUBUS_CTL_DDR  DDRF

const int CPUBUS_RW=0; //! RW bit on arduino port
const int CPUBUS_E=1;	//! E bit on arduino port
#define CPUBUS_VMA 2
#define CPUBUS_RESET 3
#define CPUBUS_HALT 4
#define CPUBUS_MR 5
#define CPUBUS_IRQ 6
#define CPUBUS_NMI 7

#define CPUBUS_RW_PIN A0
#define CPUBUS_E_PIN A1
#define CPUBUS_VMA_PIN A2
#define CPUBUS_RESET_PIN A3
#define CPUBUS_HALT_PIN A4
#define CPUBUS_MR_PIN A5
#define CPUBUS_IRQ_PIN A6
#define CPUBUS_NMI_PIN A7

#define CPUBUS_SPI_SS 53



/**
* placeholder class for accessing the 8bit 68xx memory bus
*/
class CPUBUSClass
{
  public:
	//CPUBUSClass();
	//! initialize bus
	virtual void init(void);
	
	//! read byte from bus
    virtual uint8_t read(unsigned int address);
	
	//! write byte to bus
    virtual void write(unsigned int address, uint8_t data);

	//! toggle reset port on 68xx bus low
	void reset(void);
	// status
	// getname
	// interrupt
};

/**
* CPUBUS using direct IO on arduino mega
*/
class Cpubus_Direct : public CPUBUSClass {
  private:
	unsigned long reads;
	unsigned long writes;
	String name;
	String system;
	
  public:
	Cpubus_Direct(void);
	//Cpubus_Direct(String _name);

	void init(void);
	void reset(void);
	uint8_t read(unsigned int address);
    void write(unsigned int address, uint8_t data);
	//void setName( String name );
	//String getName( void);
	String getStatus(void);
	
	
};
//extern Cpubus_Direct Cpubus;


/**
* CPUBUS using spi MCP23S17 io extenders
*/
class Cpubus_SPI : public CPUBUSClass {
  public:
	void init(void);
	uint8_t read(unsigned int address);
    void write(unsigned int address, uint8_t data);
  private:
//	SPI * spi;
    MCP23S17 * MCP_ADDR; 
	MCP23S17 * MCP_DATA;
	
	void writeData(uint8_t addr,uint8_t data);
};


/**
* CPUBUS using I2C MCP23017 io extenders
*/
class Cpubus_I2C : CPUBUSClass {

};

//extern Cpubus_SPI Cpubus;
//extern Cpubus_I2C Cpubus;



#endif /* CPUBUS_h */
