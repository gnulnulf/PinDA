/*
  rom.cpp - interface to the rom on the 68xx memory bus

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

/*****************************************************************************
* Includes
******************************************************************************/
#include "CPUBUS.h"
#include "rom.h"
//#include "printf.h"
#include "pinda.h"
/*****************************************************************************
* Defines
******************************************************************************/
	uint8_t read( unsigned int address );
	uint8_t read_offset( unsigned int address );
	void dump();
	
	
/******************************************************************************
 * Base class
 ******************************************************************************/

void ROM::init(  CPUBUSClass *busptr ,unsigned int addr, unsigned int size ) {
	rom_address = addr; 
	rom_size = size;
	bus = busptr;
} //init

uint8_t ROM::read( unsigned int address ) {
	return bus->read( address );
} // read

uint8_t ROM::read_offset( unsigned int offset ) {
	if ( offset >= rom_size ) return 0;
	return bus->read( rom_address + offset );
} // read

void ROM::dump(void) {
	printf("\nDUMP rom at %04X size %d bytes\n", rom_address,rom_size );
	for(unsigned int i=0;i<rom_size;i++) {
		if ( i%32 == 0 ) { 
			printf("\n%04X: ",rom_address+i);
		} else { 
			if ( i%8 == 0 ) printf(" "); //extra seperator
		}
		printf("%02X ",bus->read( rom_address + i ));
	}
	printf("\n");
}


