/**
 @file

 @brief interface to the MCP23S17 SPI 16-bit IO expander

 @version 1.0
 @author others
 @author Arco van Geest <arco@appeltaart.mine.nu>
 
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

 @date       20130520 Initial documented version

the datasheet can be found at // http://ww1.microchip.com/downloads/en/DeviceDoc/21952b.pdf
based on https://github.com/thejpster/Mcp23s17


*/
#ifndef MCP23X17_h
#define MCP23X17_h

#ifdef RASPBERRY

#endif
#ifdef ARDUINO
#include "Arduino.h"
#include <SPI.h>
#include <Wire.h>
#endif
/**
* This is the base class for the 23X17 family
*
* The 23017 is I2C
* The 23S17 is SPI
*
* After the definition of the object all the commands are the same for both protocols.
*/
class MCP23X17 
{
public:
	// 16 bit commands
    void pinMode(bool mode);
    void pinMode(uint8_t pin, bool mode);
    void port(uint16_t value);
    uint16_t port();

	// Work on individual pins 0-15
    void digitalWrite(uint8_t pin, bool value);
    int  digitalRead(uint8_t pin);

	
	// 8 bit port A commands
	void pinModeA( uint8_t pin, bool state );	
	void pinA( uint8_t pin, bool state );
	uint8_t portA();
    void portA(uint8_t value);
	void ddrA(uint8_t val);

	// 8 bit port B commands
	void pinB( uint8_t pin, bool state );
	uint8_t portB();
    void portB(uint8_t value);
	void ddrB(uint8_t val);
	void pinModeB( uint8_t pin, bool state );



    const static uint8_t GPIO_A0 = 0;
    const static uint8_t GPIO_A1 = 1;
    const static uint8_t GPIO_A2 = 2;
    const static uint8_t GPIO_A3 = 3;
    const static uint8_t GPIO_A4 = 4;
    const static uint8_t GPIO_A5 = 5;
    const static uint8_t GPIO_A6 = 6;
    const static uint8_t GPIO_A7 = 7;
    const static uint8_t GPIO_B0 = 8;
    const static uint8_t GPIO_B1 = 9;
    const static uint8_t GPIO_B2 = 10;
    const static uint8_t GPIO_B3 = 11;
    const static uint8_t GPIO_B4 = 12;
    const static uint8_t GPIO_B5 = 13;
    const static uint8_t GPIO_B6 = 14;
    const static uint8_t GPIO_B7 = 15;
protected:
 // bank=0
const static uint8_t IODIRA=0x00;
const static uint8_t IODIRB=0x01;
const static uint8_t IODIR=IODIRA;
const static uint8_t IPOLA=0x02;
const static uint8_t IPOLB=0x03;
const static uint8_t GPINTENA=0x04;
const static uint8_t GPINTENB=0x05;
const static uint8_t DEFVALA=0x06;
const static uint8_t DEFVALB=0x07;
const static uint8_t INTCONA=0x08;
const static uint8_t INTCONB=0x09;
const static uint8_t IOCONA=0x0a;
const static uint8_t IOCON  = IOCONA; 
const static uint8_t IOCONB=0x0b;
const static uint8_t GPPUA=0x0c;
const static uint8_t GPPUB=0x0d;
const static uint8_t INTFA=0x0e;
const static uint8_t INTFB=0x0f;
const static uint8_t INTCAPA=0x10;
const static uint8_t INTCAPB=0x11;
const static uint8_t GPIOA=0x12;
const static uint8_t GPIOB=0x13;
const static uint8_t OLATA=0x14;
const static uint8_t OLATB=0x15;
const static uint8_t GPPU   = GPPUA;
const static uint8_t GPIO   = GPIOA;

//END bank=0

// for bank=1 addresses
const static uint8_t B1IODIRA=0x00;
const static uint8_t B1IPOLA=0x01;
const static uint8_t B1GPINTENA=0x02;
const static uint8_t B1DEFVALA=0x03;
const static uint8_t B1INTCONA=0x04;
const static uint8_t B1IOCONA=0x05;
const static uint8_t B1GPPUA=0x06;
const static uint8_t B1INTFA=0x07;
const static uint8_t B1INTCAPA=0x08;
const static uint8_t B1GPIOA=0x09;
const static uint8_t B1OLATA=0x0a;
const static uint8_t B1IOCON  = IOCONA; 
const static uint8_t B1IODIR=IODIRA;

const static uint8_t B1IODIRB=0x10;
const static uint8_t B1IPOLB=0x11;
const static uint8_t B1GPINTENB=0x12;
const static uint8_t B1DEFVALB=0x13;
const static uint8_t B1INTCONB=0x14;
const static uint8_t B1IOCONB=0x15;
const static uint8_t B1GPPUB=0x16;
const static uint8_t B1INTFB=0x17;
const static uint8_t B1INTCAPB=0x18;
const static uint8_t B1GPIOB=0x19;
const static uint8_t B1OLATB=0x1a;
 // END bank=1
const static uint8_t READ=0x00;
const static uint8_t WRITE=0x01;

//BANK MIRROR SEQOP DISSLW HAEN ODR INTPOL —
const static uint8_t BANK  	= 0b10000000;
const static uint8_t MIRROR = 0b01000000;
const static uint8_t SEQOP  = 0b00100000;
const static uint8_t DISSLW = 0b00010000;
const static uint8_t HAEN  	= 0b00001000;
const static uint8_t ODR  	= 0b00000100;
const static uint8_t INTPOL = 0b00000010;
//const static uint8_t UNUSED = 0b00000001;

    uint8_t reset_pin;
    uint8_t aaa_hw_addr;


	
	virtual uint16_t read_addr(uint8_t addr);
    virtual uint8_t read_addr_byte(uint8_t addr);
    virtual void write_addr(uint8_t addr, uint16_t data);
	virtual	void write_addr_byte(uint8_t addr, uint8_t data);

	uint16_t byte2uint16(uint8_t high_byte, uint8_t low_byte);
	uint8_t uint16_high_byte(uint16_t uint16);
	uint8_t uint16_low_byte(uint16_t uint16);

};


#ifdef ENABLE_SPI
/**
*  MCP23S17 SPI 16 bit IO expander
*
*  ArduinoMega <-> MCP
*  MISO pin 50 = DIP14
*  MOSI pin 51 = DIP13
*  SCK pin 52 = DIP12
* ( /CS pin 53 = DIP11 ) hardcoded atm
* /RESET = DIP18
*/
class MCP23S17 : public MCP23X17
{
  public:
    //! constructor for single expander
    MCP23S17(
		uint8_t slave_select=53	//!< arduino pin for the slave select
	);
    //! constructor for an expander on a shared bus
	//! up to 8 expanders can be shared
    MCP23S17(
		uint8_t slave_select, 	//!< arduino pin for the slave select
		uint8_t aaa_hw_addr		//!< share index (0-7)
	);

	#define    CLOCK_DIVIDER (SPI_CLOCK_DIV2)           // SPI bus speed to be 1/2 of the processor clock speed - 8MHz on most Arduinos

  protected:
	uint8_t read_cmd; //!< store read address
    uint8_t write_cmd;	//!< store write address

    uint8_t slave_select_pin;		//!< store CS pin
	
	/** 
	* setup spi CS pin
	* @param slave_select_pin arduino pin number
	*/
    void setup_ss(uint8_t slave_select_pin);
	/** 
	* setup mcp address
	* @param aaa_hw_addr MCP number ( 0-7 )
	*/
    void setup_device(uint8_t aaa_hw_addr);

    uint16_t read_addr(uint8_t addr);
    uint8_t read_addr_byte(uint8_t addr);
    void write_addr(uint8_t addr, uint16_t data);
	void write_addr_byte(uint8_t addr, uint8_t data);
};
#endif //EnABLE_SPI

#ifdef ENABLE_I2C
/**
* MCP23017 I2C 16 port IO expander class
*
* ArduinoMega <-> MCP
* SDA pin 20   = DIP13
* SDL pin 21   = DIP12
* /RESET       = DIP18
*
* Don't forget to pullup the SDA/SDL lines
*/
class MCP23017 : public MCP23X17 {
  public:
    //! constructor for an expander on a shared bus
	//! up to 8 expanders can be shared
    MCP23017(
		uint8_t aaa_hw_addr		//!< share index (0-7)
	);
  protected:
	uint8_t mcp_addr; //!< store the i2c address
	
    uint16_t read_addr(uint8_t addr);
    uint8_t read_addr_byte(uint8_t addr);
    void write_addr(uint8_t addr, uint16_t data);
	void write_addr_byte(uint8_t addr, uint8_t data);
};


#endif //ENABLE_I2C

#endif // MCP23X17_h



