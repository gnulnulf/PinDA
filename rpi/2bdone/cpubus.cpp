/**
 @file 

 @see cpubus.h for details
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

 @date 20130520 Initial documented version

 @brief interface to the 8bit 68xx memory bus

*/

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "pinda.h"
#include "cpubus.h"
#include <inttypes.h>
#include <stdio.h>

#ifdef ARDUINO
#include <SPI.h>
#endif 
#include "mcp23s17.h"

#ifdef ARDUINO
#include "Arduino.h"
#define println(line) Serial.println(line)
#define print(line) Serial.print(line)

#else
#include "arduino_compat.h"


#endif

#include "cpubus.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/


/******************************************************************************
 * Base class
 ******************************************************************************/
void CPUBUSClass::interrupt(void ){};
void CPUBUSClass::serviceLoop(void ){};
CPUBUSClass::CPUBUSClass(void){};
//	 void CPUBUSClass::init(void);
//uint8_t CPUBUSClass::read(int address);
//void CPUBUSClass::write(int address, uint8_t data);
//	 void CPUBUSClass::e_low();
//	 void CPUBUSClass::e_high();
//	 void CPUBUSClass::set_read();
//	 void CPUBUSClass::set_write();

void CPUBUSClass::reset(void ){};

uint8_t CPUBUSClass::read(const unsigned int address){ return 0;};

void CPUBUSClass::write(const unsigned int address, const uint8_t data){};


String CPUBUSClass::status(void) {
	String status="###CPUBUS STATUS###";
	status += "\nSystem type   : " + system;
	status += "\nName          : " + objName;
//`	status += "\nCPUBUS reads  : " + String( reads );
//`	status += "\nCPUBUS writes : " + String( writes );
	status += "\n"; 
	return status;
} //getStatus


#ifdef ARDUINO
/******************************************************************************
 * CPUBUS_Direct
 ******************************************************************************/

Cpubus_Direct::Cpubus_Direct(String _name) {
	writes=0;
	reads=0;
	objName=_name;
	system="Cpubus direct";
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

} //Cpubus_Direct::Cpubus_Direct

void Cpubus_Direct::reset(void) {
	pinMode( CPUBUS_RESET_PIN ,OUTPUT );
	digitalWrite(CPUBUS_RESET_PIN, LOW);   // Pull reset low
	delay(500);                  
//	digitalWrite(CPUBUS_RESET_PIN, HIGH);  // no pullup needed
	pinMode( CPUBUS_RESET_PIN ,INPUT );

} //reset

uint8_t Cpubus_Direct::read(const unsigned int  address) {
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

void Cpubus_Direct::write(const unsigned int address, const uint8_t  value) {
	writes++; //debug write count
	CPUBUS_CTL_PORT &= ~( 1<< CPUBUS_E); 	//e_low
	CPUBUS_CTL_PORT &= ~( 1<< CPUBUS_RW);	//Write
	CPUBUS_ADDRL_PORT = address&0xFF;		//Address Low
	CPUBUS_ADDRH_PORT = (address>>8)&0xFF;	//Address High
	CPUBUS_CTL_PORT |= ( 1<< CPUBUS_VMA);		//VMA high
		__asm__("nop\n\t"); 			// (62.5ns on a 16MHz Arduino) 
	CPUBUS_DATA_DDR =0xff;
//	CPUBUS_DATA_PORT= value & 0xff;
	CPUBUS_DATA_PORT= value;
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

void Cpubus_Direct::writeref(const unsigned int & address, const uint8_t & value) {
	writes++; //debug write count
	CPUBUS_CTL_PORT &= ~( 1<< CPUBUS_E); 	//e_low
	CPUBUS_CTL_PORT &= ~( 1<< CPUBUS_RW);	//Write
	CPUBUS_ADDRL_PORT = address & 0xFF;		//Address Low
	CPUBUS_ADDRH_PORT = (address>>8)&0xFF;	//Address High
	CPUBUS_CTL_PORT |= ( 1<< CPUBUS_VMA);		//VMA high
		__asm__("nop\n\t"); 			// (62.5ns on a 16MHz Arduino) 
	CPUBUS_DATA_DDR =0xff;
	CPUBUS_DATA_PORT= value;
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
	
	
#endif //ARDUINO
	
	
/******************************************************************************
 * CPUBUS_SPI
 ******************************************************************************/

 Cpubus_SPI::Cpubus_SPI(	
MCP23S17 * _mcpaddr , MCP23S17 * _mcpdata , String _name 
) 
{
	writes=0;
	reads=0;
	objName=_name;
	system="Cpubus spi";
	sv_cpureg=0;
	
	mcpdata=_mcpdata;
	mcpaddr=_mcpaddr;
	
	mcpdata->pinMode(INPUT);
	mcpaddr->pinMode(OUTPUT);
	mcpdata->port( 0xffff); //pullup
	mcpaddr->port( 0x0000); //addr 0

	mcpdata->pinModeB( CPUBUS_E ,OUTPUT );
	mcpdata->pinModeB( CPUBUS_VMA ,OUTPUT );
	mcpdata->pinModeB( CPUBUS_RW ,OUTPUT );

} //init

uint8_t Cpubus_SPI::read(unsigned int address) {
	//return 0;
	reads++; //debug read count
	sv_cpureg &= ~( 1<< CPUBUS_E);
	sv_cpureg |= ( 1<< CPUBUS_RW);
	mcpdata->portB(sv_cpureg);
//	mcpdata->pinB( CPUBUS_E, false ); //E_LOW
//	mcpdata->pinB( CPUBUS_RW, true ); //READ
	mcpaddr->port( address ); //set address

	sv_cpureg |= ( 1<< CPUBUS_VMA);
		mcpdata->portB(sv_cpureg);

//	mcpdata->pinB( CPUBUS_VMA, true ); //VMA_HIGH
//			__asm__("nop\n\t"); 
	sv_cpureg |= ( 1<< CPUBUS_E);
	mcpdata->portB(sv_cpureg);
	//mcpdata->pinB( CPUBUS_E, true ); //E_HIGH

	uint8_t data= mcpdata->portA();			//get data from bus
	sv_cpureg &= ~(( 1<< CPUBUS_E)|(1<<CPUBUS_VMA));
	mcpdata->portB(sv_cpureg);
//	mcpdata->pinB( CPUBUS_E, false ); //E_LOW
//	mcpdata->pinB( CPUBUS_VMA, false ); //VMA_LOW
	return data;
} //read

void Cpubus_SPI::write(unsigned int address, uint8_t value) {
//return;
	writes++; //debug write count
		sv_cpureg &= ~(( 1<< CPUBUS_E)|(1<<CPUBUS_RW));
			mcpdata->portB(sv_cpureg);
	//mcpdata->pinB( CPUBUS_E, false ); //E_LOW
	//mcpdata->pinB( CPUBUS_RW, false ); //WRITE
	mcpaddr->port( address ); //set address
	sv_cpureg |= ( 1<< CPUBUS_VMA);
		mcpdata->portB(sv_cpureg);


//	mcpdata->pinB( CPUBUS_VMA, true ); //VMA_HIGH
//		__asm__("nop\n\t"); 			// (62.5ns on a 16MHz Arduino) 
	mcpdata->ddrA(0xFF);
	mcpdata->portA(value);

		sv_cpureg |= ( 1<< CPUBUS_E);
	mcpdata->portB(sv_cpureg);

//	mcpdata->pinB( CPUBUS_E, true ); //E_HIGH
//	__asm__("nop\n\t"); 			// (62.5ns on a 16MHz Arduino) 
//	mcpdata->pinB( CPUBUS_E, false ); //E_LOW
	sv_cpureg &= ~(( 1<< CPUBUS_E));
	mcpdata->portB(sv_cpureg);
	mcpdata->ddrA(0x00);
	
//	mcpdata->pinB( CPUBUS_RW, true ); //READ
//	mcpdata->pinB( CPUBUS_VMA, false ); //VMA_LOW

	sv_cpureg |= ( 1<< CPUBUS_RW);
	sv_cpureg &= ~(( 1<< CPUBUS_E)|(1<<CPUBUS_VMA));
	mcpdata->portB(sv_cpureg);
} //write


/*

OLD

uint8_t Cpubus_SPI::read(unsigned int address) {
	//return 0;
	reads++; //debug read count
	sv_cpureg &= ~( 1<< CPUBUS_E);
	sv_cpureg |= ( 1<< CPUBUS_RW);
	mcpdata->portB(sv_cpureg);
//	mcpdata->pinB( CPUBUS_E, false ); //E_LOW
//	mcpdata->pinB( CPUBUS_RW, true ); //READ
	mcpaddr->port( address ); //set address

	sv_cpureg |= ( 1<< CPUBUS_VMA);
		mcpdata->portB(sv_cpureg);

//	mcpdata->pinB( CPUBUS_VMA, true ); //VMA_HIGH
//			__asm__("nop\n\t"); 
	sv_cpureg |= ( 1<< CPUBUS_E);
	mcpdata->portB(sv_cpureg);
	//mcpdata->pinB( CPUBUS_E, true ); //E_HIGH

	uint8_t data= mcpdata->portA();			//get data from bus
	sv_cpureg &= ~(( 1<< CPUBUS_E)|(1<<CPUBUS_VMA));
	mcpdata->portB(sv_cpureg);
//	mcpdata->pinB( CPUBUS_E, false ); //E_LOW
//	mcpdata->pinB( CPUBUS_VMA, false ); //VMA_LOW
	return data;
} //read

void Cpubus_SPI::write(unsigned int address, uint8_t value) {
//return;
	writes++; //debug write count
	mcpdata->pinB( CPUBUS_E, false ); //E_LOW
	mcpdata->pinB( CPUBUS_RW, false ); //WRITE
	mcpaddr->port( address ); //set address
	mcpdata->pinB( CPUBUS_VMA, true ); //VMA_HIGH
		__asm__("nop\n\t"); 			// (62.5ns on a 16MHz Arduino) 
	mcpdata->ddrA(0xFF);
	mcpdata->portA(value);
	mcpdata->pinB( CPUBUS_E, true ); //E_HIGH
	__asm__("nop\n\t"); 			// (62.5ns on a 16MHz Arduino) 
	mcpdata->pinB( CPUBUS_E, false ); //E_LOW
	mcpdata->ddrA(0x00);
	mcpdata->pinB( CPUBUS_RW, true ); //READ
	mcpdata->pinB( CPUBUS_VMA, false ); //VMA_LOW
} //write



*/






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




