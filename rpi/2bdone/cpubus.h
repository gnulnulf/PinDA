/**
 @file 

 @brief interface to the 8bit 68xx memory bus
 
 @version 1.0
 @author Arco van Geest <arco@appeltaart.mine.nu>
 @copyright 2013 Arco van Geest <arco@appeltaart.mine.nu> All right reserved.

	This file is part of PinDA.

	PinDA is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	PinDA is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with PinDA.  If not, see <http://www.gnu.org/licenses/>.

 @date       20130520 Initial version

several methods to access the 680x memory bus.

This is no emulator, just a way to access the periperials on the memory bus.

*/
#ifndef CPUBUS_h
#define CPUBUS_h


// --------------------------------------------------------
// Includes
// --------------------------------------------------------
#include <inttypes.h>
#include <string.h>
#include "pinda.h"

#ifdef ARDUINO
#error "Ardiuno "
#include <SPI.h>
#endif

#ifdef RASPBERRY
#include "spi.h"
#endif
#include "mcp23s17.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#if defined(ARDUINO)
#include "WProgram.h"
#endif
#endif

// --------------------------------------------------------
// Definitions
// --------------------------------------------------------

//! SPI slave select for CPUBUS_spi
#define CPUBUS_SPI_SS 53



/**
* placeholder class for accessing the 8bit 68xx memory bus
*/
class CPUBUSClass  : public PindaObj {
  public:
	CPUBUSClass();
	//! initialize bus
	//virtual void init(void);
	
	//! placeholder for interrupts
	void interrupt(void);
		
	//! placeholder for untimed serviceLoop
	void serviceLoop(void);
	
	
	//! read byte from bus
    virtual uint8_t read(const unsigned int address);
	
	//! write byte to bus
    virtual void write(const unsigned int address, const uint8_t data);

	//! toggle reset port on 68xx bus low
	virtual void reset(void);
	// status
	// getname
	// interrupt
	//String objName;
	String status(void);
	protected:
		unsigned long reads;		//!< amount of cpubus reads (diag)
		unsigned long writes;		//!< amount of cpubus writes
//	String name;	
		String system;				//!< name of system (diag)
};

/**
* CPUBUS using direct IO on arduino mega
*/
#ifdef ARDUINO
class Cpubus_Direct : public CPUBUSClass {
	//"private" defines
	// I do not know how to static const define the PORTS.
	
	//! arduino port for data pins
	#define CPUBUS_DATA_PORT PORTL
	//! arduino pins for data pins
	#define CPUBUS_DATA_PINS PINL
	//! arduino datadirection for data pins
	#define CPUBUS_DATA_DDR  DDRL

	//! arduino port for lower address pins
	#define CPUBUS_ADDRL_PORT PORTA
	//! arduino pins for lower address pins
	#define CPUBUS_ADDRL_PINS PINA
	//! arduino datadirection for lower address pins
	#define CPUBUS_ADDRL_DDR  DDRA

	//! arduino port for higher address pins
	#define CPUBUS_ADDRH_PORT PORTC
	//! arduino pins for higher address pins
	#define CPUBUS_ADDRH_PINS PINC
	//! arduino datadirection for higher address pins
	#define CPUBUS_ADDRH_DDR  DDRC

	//! arduino port for cpu control pins
	#define CPUBUS_CTL_PORT PORTF
	//! arduino pins for cpu control pins
	#define CPUBUS_CTL_PINS PINF
	//! arduino datadirection for cpu control pins
	#define CPUBUS_CTL_DDR  DDRF

  private:


	// hardware pins on arduino CPUBUS
	static const uint8_t CPUBUS_RW=0; //! RW bit on arduino port
	static const uint8_t CPUBUS_E=1;	//! E bit on arduino port
	static const uint8_t CPUBUS_VMA=2;
	static const uint8_t CPUBUS_RESET=3;
	static const uint8_t CPUBUS_HALT=4;
	static const uint8_t CPUBUS_MR=5;
	static const uint8_t CPUBUS_IRQ=6;
	static const uint8_t CPUBUS_NMI=7;

	static const uint8_t CPUBUS_RW_PIN=A0; //! RW PIN on arduino port
	static const uint8_t CPUBUS_E_PIN=A1;	//! E PIN on arduino port
	static const uint8_t CPUBUS_VMA_PIN=A2;
	static const uint8_t CPUBUS_RESET_PIN=A3;
	static const uint8_t CPUBUS_HALT_PIN=A4;
	static const uint8_t CPUBUS_MR_PIN=A5;
	static const uint8_t CPUBUS_IRQ_PIN=A6;
	static const uint8_t CPUBUS_NMI_PIN=A7;

  public:
	Cpubus_Direct(String _name="CPUBUSDIRECT");

	//void init(void);
	void reset(void);
	uint8_t read(const unsigned int  address);
    void write(const unsigned int address, const uint8_t data);
    void writeref(const unsigned int & address, const uint8_t & dataref);
	//void setName( String name );
	//String getName( void);
	
	
	
};
//extern Cpubus_Direct Cpubus;
#endif


/**
* CPUBUS using spi MCP23S17 io extenders
*/
class Cpubus_SPI : public CPUBUSClass {
  public:
	Cpubus_SPI(MCP23S17 * _mcpa , MCP23S17 * _mcpd ,  String _name="CPUBUS SPI");

	//void init(void);
	uint8_t read(unsigned int address);
    void write(unsigned int address, uint8_t data);
  private:
//	SPI * spi;
	static const uint8_t CPUBUS_RW=0; //! RW bit on arduino port
	static const uint8_t CPUBUS_E=1;	//! E bit on arduino port
	static const uint8_t CPUBUS_VMA=2;
	static const uint8_t CPUBUS_RESET=3;
	static const uint8_t CPUBUS_HALT=4;
	static const uint8_t CPUBUS_MR=5;
	static const uint8_t CPUBUS_IRQ=6;
	static const uint8_t CPUBUS_NMI=7;

    MCP23S17 * mcpaddr; 
	MCP23S17 * mcpdata;
	uint8_t sv_cpureg;
	
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
