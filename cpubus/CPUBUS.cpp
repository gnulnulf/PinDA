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
 * Constructors
 ******************************************************************************/

/******************************************************************************
 * User API
 ******************************************************************************/




CPUBUSClass::CPUBUSClass( void) {
	println("CPUBUS");
}

void CPUBUSClass::init(void ){
	println("CPUBUS init");
#if CPUBUS_TYPE == CPUBUS_SPI
	println("CPUBUS init SPI_ADDR");
	println("CPUBUS init SPI_DATA_CTRL");

#endif
}


uint8_t CPUBUSClass::read(int address)
{
#if CPUBUS_TYPE == CPUBUS_DIRECT
	println("E_HIGH");
	printf("A_LOW %02X\n\r",address&0xFF);
	printf("A_HIGH %02X\n\r",(address>>8)&0xFF);
	println("E_LOW");
	println("DATA");
	println("E_HIGH");
	println("RETURN DATA");

	println("");

	return 0;
#endif
#if CPUBUS_TYPE == CPUBUS_SPI
	println("SPI_CTL E_HIGH");
	printf("SPI_ADDR address %04X\n\r",address&0xFFFF);
	println("SPI_CTL E_LOW");
	println("SPI_DATA DATA");
	println("SPI_CTL E_HIGH");
	println("RETURN DATA");

	println("");

	return 0;
#endif
	//return eeprom_read_byte((unsigned char *) address);
}

void CPUBUSClass::write(int address, uint8_t value)
{
#if CPUBUS_TYPE == CPUBUS_DIRECT	
	println("E_HIGH");
	printf("A_LOW %02X\n\r",address&0xFF);
	printf("A_HIGH %02X\n\r",(address>>8)&0xFF);
	println("DATA OUTPUT");
	printf("DATA %02X\n\r",value);
	println("WR");
	println("E_LOW");
	println("WRITE_SLEEP x ns");
	println("E_HIGH");
	println("RD");
	println("DATA INPUT");
	println("");
#endif
#if CPUBUS_TYPE == CPUBUS_SPI	
	println("SPI_CTL E_HIGH");
	printf("SPI_ADDRESS address %04X\n\r",address&0xFFFF);
	printf("SPI_DATA %02X\n\r",value);
	println("SPI_CTL WR");
	println("SPI_CTL E_LOW");
	println("WRITE_SLEEP x ns");
	println("SPI_CTL E_HIGH");
	println("SPI_CTL RD");
	println("");
#endif


	//eeprom_write_byte((unsigned char *) address, value);
}




int main( void){
  CPUBUSClass Cpubus;
  Cpubus.init( );
  Cpubus.read(0x20);
  Cpubus.write(0x3000,128);
}





