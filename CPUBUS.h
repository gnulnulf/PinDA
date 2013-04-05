/*
  CPUBUS.h - interface to the 8bit 68xx memory bus

  (C) Copyright 2013 Arco van Geest <arco@appeltaart.mine.nu> All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef CPUBUS_h
#define CPUBUS_h


/*****************************************************************************
* Includes
******************************************************************************/
#include <inttypes.h>

#include <SPI.h>
#include "Mcp23s17.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/******************************************************************************
* Definitions
******************************************************************************/
#define CPUBUS_DIRECT 0
#define CPUBUS_SPI 1
#define CPUBUS_I2C 2

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

#define CPUBUS_RW 0
#define CPUBUS_E 1
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




class CPUBUSClass
{
  public:
	//CPUBUSClass();
	virtual void init(void);
    virtual uint8_t read(int address);
    virtual void write(int address, uint8_t data);
};

//extern CPUBUSClass Cpubus;

class Cpubus_Direct : public CPUBUSClass {
  public:
	void init(void);
	uint8_t read(int address);
    void write(int address, uint8_t data);
};
//extern Cpubus_Direct Cpubus;


class Cpubus_SPI : public CPUBUSClass {
  public:
	void init(void);
	uint8_t read(int address);
    void write(int address, uint8_t data);
  private:
//	SPI * spi;
    MCP23S17 * MCP_ADDR; 
	MCP23S17 * MCP_DATA;
	
	void writeData(uint8_t addr,uint8_t data);
};


class Cpubus_I2C : CPUBUSClass {

};

//extern Cpubus_SPI Cpubus;
//extern Cpubus_I2C Cpubus;



#endif /* CPUBUS_h */
