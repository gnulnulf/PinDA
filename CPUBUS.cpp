/*
  CPUBUS.cpp - interface to the 8bit 68xx memory bus

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

/******************************************************************************
 * Includes
 ******************************************************************************/
#include <inttypes.h>
#include <stdio.h>


#include <SPI.h>
#include "Mcp23s17.h"

#ifdef ARDUINO
#include "Arduino.h"
#define println(line) Serial.println(line)
#define print(line) Serial.print(line)

#else
#include "arduino_compat.h"


#endif

#include "CPUBUS.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/


/******************************************************************************
 * Base class
 ******************************************************************************/
//	CPUBUSClass::CPUBUSClass();
//	 void CPUBUSClass::init(void);
//     uint8_t CPUBUSClass::read(int address);
//     void CPUBUSClass::write(int address, uint8_t data);
//	 void CPUBUSClass::e_low();
//	 void CPUBUSClass::e_high();
//	 void CPUBUSClass::set_read();
//	 void CPUBUSClass::set_write();

/******************************************************************************
 * CPUBUS_Direct
 ******************************************************************************/

Cpubus_Direct::Cpubus_Direct(void) {
	writes=0;
	reads=0;
	Cpubus_Direct::init();
}
/*
Cpubus_Direct::Cpubus_Direct( String _name ) {
	writes=0;
	reads=0;
	name=_name;
	Cpubus_Direct::init();
}
*/

void Cpubus_Direct::init(void) {
	//println("CPUBUS init DIRECT_ADDR_DIRECT");
	//println("CPUBUS init DIRECT_DATA_CTRL");
	CPUBUS_ADDRL_DDR =0xff;
	CPUBUS_ADDRH_DDR =0xff;	
	
	CPUBUS_DATA_DDR =0x0; 	//data IO
	CPUBUS_DATA_PORT=0xff; 	//pullup

	CPUBUS_CTL_DDR =0x0; 	// control IO
	CPUBUS_CTL_PORT=0xff; 	//pullup

	CPUBUS_ADDRL_PORT = 0x00;
	CPUBUS_ADDRH_PORT = 0x00;

	pinMode( CPUBUS_E_PIN ,OUTPUT );
	pinMode( CPUBUS_VMA_PIN ,OUTPUT );
	pinMode( CPUBUS_RW_PIN ,OUTPUT );

//	Cpubus_Direct::reset();

} //init

String Cpubus_Direct::getStatus(void) {
	String status="CPUBUS_DIRECT\n";
	status += "Name   :";
	status += name;
	status += "\n";
	status += "reads  : ";
	status += reads;
	status += "\n";
	status += "writes : ";
	status += writes;
	status += "\n";
	return status;
	
} //getStatus
void Cpubus_Direct::reset(void) {
	pinMode( CPUBUS_RESET_PIN ,OUTPUT );
	digitalWrite(CPUBUS_RESET_PIN, LOW);   // Pull reset low
	delay(500);                  
//	digitalWrite(CPUBUS_RESET_PIN, HIGH);  // no pullup needed
	pinMode( CPUBUS_RESET_PIN ,INPUT );

} //reset

uint8_t Cpubus_Direct::read(unsigned int address) {
	reads++; //debug read count
	CPUBUS_CTL_PORT &= ~( 1<< CPUBUS_E); 	//e_low
	CPUBUS_CTL_PORT |= ( 1<<CPUBUS_RW); 	//READ
	CPUBUS_ADDRL_PORT = address&0xFF;		//Address Low
	CPUBUS_ADDRH_PORT = ( address >> 8 )&0xFF ;	//Address High
	
	CPUBUS_CTL_PORT |= ( 1<< CPUBUS_VMA);		//VMA  high
			__asm__("nop\n\t"); 
	CPUBUS_CTL_PORT |= ( 1<< CPUBUS_E);		//E high
//	delay(1);
//	for (int del=0;del<100;del++) {
		__asm__("nop\n\t"); 			// (62.5ns on a 16MHz Arduino) 
//	}					// (62.5ns on a 16MHz Arduino) 
	uint8_t data= CPUBUS_DATA_PINS;			//get data from bus
	CPUBUS_CTL_PORT &= ~( ( 1<< CPUBUS_E ) | (1 << CPUBUS_VMA) );	//E and VMA  low 
	return data;
} //read

void Cpubus_Direct::write(unsigned int address, uint8_t value) {
	writes++; //debug write count
	CPUBUS_CTL_PORT &= ~( 1<< CPUBUS_E); 	//e_low
	CPUBUS_CTL_PORT &= ~( 1<< CPUBUS_RW);	//Write
	CPUBUS_ADDRL_PORT = address&0xFF;		//Address Low
	CPUBUS_ADDRH_PORT = (address>>8)&0xFF;	//Address High
	CPUBUS_CTL_PORT |= ( 1<< CPUBUS_VMA);		//VMA high
		__asm__("nop\n\t"); 			// (62.5ns on a 16MHz Arduino) 
	CPUBUS_DATA_DDR =0xff;
	CPUBUS_DATA_PORT= value & 0xff;
	CPUBUS_CTL_PORT |= ( 1<< CPUBUS_E)|( 1<< CPUBUS_VMA);		//E high
//	delay(1);
//	for (int del=0;del<10;del++) {
		__asm__("nop\n\t"); 			// (62.5ns on a 16MHz Arduino) 
//	}
	CPUBUS_CTL_PORT &= ~( ( 1<< CPUBUS_E ) | (1 << CPUBUS_VMA) );	//E and VMA  low 
//	__asm__("nop\n\t"); 					// (62.5ns on a 16MHz Arduino) 
	CPUBUS_DATA_DDR =0x00;					//D0-7 as input
	CPUBUS_DATA_PORT=0xff;					//Pullup
	CPUBUS_CTL_PORT |= ( 1<<CPUBUS_RW); 	//READ
} //write
	
	
	
	
/******************************************************************************
 * CPUBUS_SPI
 ******************************************************************************/
#define	MCP23S17 B01000000  // MCP23017 SPI Address (Not used in this sketch)
#define	MCPADDR B01000000  // MCP23017 SPI Address (Not used in this sketch)
#define	MCPDATA B01000010  // MCP23017 SPI Address (Not used in this sketch)
#define	IOCON	0x0A	    // MCP23017 Config Reg.
#define	IODIRA	0x00	    // MCP23017 address of I/O direction
#define	IODIRB	0x01	    // MCP23017 1=input
#define	IPOLA	0x02  	    // MCP23017 address of I/O Polarity
#define	IPOLB	0x03  	    // MCP23017 1= Inverted
#define	GPIOA	0x12	    // MCP23017 address of GP Value
#define	GPIOB	0x13	    // MCP23017 address of GP Value
#define	GPINTENA  0x04	    // MCP23017 IOC Enable
#define	GPINTENB  0x05	    // MCP23017 IOC Enable
#define	INTCONA	0x08	    // MCP23017 Interrupt Cont 
#define	INTCONB	0x09	    // MCP23017 1= compair to DEFVAL(A or B) 0= change
#define	DEFVALA	0x06	    // MCP23017 IOC Default value
#define	DEFVALB	0x07	    // MCP23017 if INTCONA set then INT. if diff. 
#define	GPPUA	0x0C	    // MCP23017 Weak Pull-Ups
#define	GPPUB	0x0D	    // MCP23017 1= Pulled HIgh via internal 100k
#define	OLATA	0x14
#define	OLATB	0x15
#define	INTFA	0x0E
#define	INTFB	0x0F
#define	INTCAPA 0x10
#define	INTCAPB	0x11
#define HAEN (0b00001000)

void Cpubus_SPI::init(void) {
	pinMode (CPUBUS_SPI_SS, OUTPUT);
	SPI.begin();
	  SPI.setClockDivider(SPI_CLOCK_DIV2); //16MHz / 2 = 8MHz
	//MCP_ADDR = new MCP23S17( CPUBUS_SPI_SS,0x0 );
	//MCP_DATA = new MCP23S17( CPUBUS_SPI_SS,0x1 );
  //IOCON設定(SEQOPのみDisable→0x20)
  writeData(IOCON,0x20|HAEN);
  writeData(IOCON+1,0x20|HAEN);

  //IODIRA,B設定(0で出力,1で入力)
  writeData(IODIRA,0x00);
  writeData(IODIRB,0x00);
	//MCP_DATA->pinMode(INPUT);
    //MCP_DATA->port( 0xffff );

	//MCP_ADDR->pinMode(OUTPUT);
	//MCP_ADDR->port( 0x0000 );
  writeData(GPIOB,0xff);
  writeData(GPIOA,0xaa);
  delay(300);
  writeData(GPIOB,0x00);
  writeData(GPIOA,0x55);
  delay(300);
  
	} //init

uint8_t Cpubus_SPI::read(unsigned int address) {
  //digitalWrite(CPUBUS_SPI_SS,LOW);
  	PORTB &= ~( 1<< PB0); 	//SS LOW

  SPI.transfer(MCPADDR);
  SPI.transfer(GPIOA);
  SPI.transfer(address&0xFF);
  
  SPI.transfer(MCPADDR);
  SPI.transfer(GPIOB|1);
  uint8_t data =SPI.transfer(0);
  	PORTB |= ( 1<< PB0);		//SS high
  //digitalWrite(CPUBUS_SPI_SS,HIGH);

  //delay(5);
	return 0;
} //read

void Cpubus_SPI::write(unsigned int address, uint8_t value) {
  //digitalWrite(CPUBUS_SPI_SS,LOW);
    	PORTB &= ~( 1<< PB0); 	//SS LOW
  SPI.transfer(MCPADDR);
  SPI.transfer(GPIOA);
  SPI.transfer(address&0xFF);
  
  SPI.transfer(MCPADDR);
  SPI.transfer(GPIOB);
  SPI.transfer((address>>8)&0xFF);
  //digitalWrite(CPUBUS_SPI_SS,HIGH);
    	PORTB |= ( 1<< PB0);		//SS high

 //delay(5);
} //write


// obsolete?
void Cpubus_SPI::writeData(uint8_t addr,uint8_t data)
{
  digitalWrite(CPUBUS_SPI_SS,LOW);
  SPI.transfer(MCP23S17);
  SPI.transfer(addr);
  SPI.transfer(data);
  digitalWrite(CPUBUS_SPI_SS,HIGH);
} //writeData








/*
CPUBUSClass::CPUBUSClass( void) {
	println("CPUBUS");
}
*/
/*

void Cpubus_SPI::init(void ){
	println("CPUBUS init SPI_ADDR");

	println("CPUBUS init SPI_DATA_CTRL");
}

*/





/*
int main( void){
  CPUBUSClass Cpubus;
  Cpubus.init( );
  Cpubus.read(0x20);
  Cpubus.write(0x3000,128);
}
*/




