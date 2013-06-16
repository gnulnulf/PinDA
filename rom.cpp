/**
 @file 

 @see rom.h for details
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

 @date       20130520 Initial documented version

 @brief interface to the rom on the 68xx memory bus
 
*/ 

/*****************************************************************************
* Includes
******************************************************************************/
#include "pinda.h"
#include "cpubus.h"
#include "rom.h"
//#include "printf.h"

/*****************************************************************************
* Defines
******************************************************************************/
	uint8_t read( unsigned int address );
	uint8_t read_offset( unsigned int address );
	void dump();
	
	
/******************************************************************************
 * Base class
 ******************************************************************************/
ROM::ROM(  CPUBUSClass *busptr ,unsigned int addr, unsigned int size, String _name="ROM" ) {
	rom_address=addr; 
	rom_size=size;
	bus=busptr;
	objName=_name;
} //ROM::ROM

/*
RAM::RAM(  CPUBUSClass *busptr ,unsigned int addr, unsigned int size, String _name="RAM" ) 
	{
	rom_address=addr; 
	rom_size=size;
	bus=busptr;
	name=_name;
} //RAM::RAM
*/


uint8_t ROM::read( unsigned int address ) {
	return bus->read( address );
} // read

uint8_t ROM::read_offset( unsigned int offset ) {
	if ( offset >= rom_size ) return 0;
	return bus->read( rom_address + offset );
} // read

void ROM::dump(void) {
	printf("\nDUMP rom at %04X size %d bytes\n", rom_address,rom_size );
	Serial.println ( "# ROM Name: " + objName);
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


void ROM::ihex16(void){
	printf("\n#DUMP rom at %04X size %d bytes\n", rom_address,rom_size );
	Serial.println ( "# ROM Name: " + objName);
	for ( unsigned int lstart=0; lstart< rom_size;lstart+=16) {
		uint16_t checksum=0;
		// ;CCAAAATT 16 bytes, data=00
		printf(":10%04X00",lstart);
		checksum += (lstart>>8) &0xff;
		checksum += lstart &0xff;
		//16x DD
		for(unsigned int i=0;i<16;i++) {
			uint8_t val = bus->read( rom_address+ lstart + i );
			printf("%02X",val);
			checksum += val;
		}
		checksum = (0x100 - checksum);
		//Checksum LF
		printf("%02X\n",checksum);
	}
	printf(":00000001FF\n"); //end
} //ROM::ihex16

void ROM::ihex32(void){
	printf("\n#DUMP rom at %04X size %d bytes\n", rom_address,rom_size );
	Serial.println ( "# ROM Name: " + objName);
	for ( unsigned int lstart=0; lstart< rom_size;lstart+=32) {
		uint16_t checksum=0;
		// ;CCAAAATT 32 bytes, data=00
		printf(":20%04X00",lstart);
		checksum += (lstart>>8) &0xff;
		checksum += lstart &0xff;
		//16x DD
		for(unsigned int i=0;i<32;i++) {
			uint8_t val = bus->read( rom_address+ lstart + i );
			printf("%02X",val);
			checksum += val;
		}
		checksum = (0x100 - checksum);
		//Checksum LF
		printf("%02X\n",checksum);
	}
	printf(":00000001FF\n"); //end
} //ROM::ihex32

void ROM::checksums(void){
	printf("\n# Checksums for rom at %04X size %d bytes\n", rom_address,rom_size );
	Serial.println ( "# ROM Name: " + objName);
	uint16_t checksum8 = 0;
	uint16_t checksum16 = 0;
	for ( unsigned int lstart=0; lstart< rom_size;lstart+=2) {
		uint8_t val1 = bus->read( rom_address+ lstart  );
		uint8_t val2 = bus->read( rom_address+ lstart  +1);
		checksum16 += (val1<<8) + val2;
		checksum8 += val1 + val2;
	}
	printf("Checksum8 %04X - Checksum16 %04X\n",checksum8,checksum16);
} //ROM::checksums





/*
void read256() {
  printf("Read 256 bytes...");
  for ( int i=0;i<256;i++ ){
    if ( i%16 == 0 ) {
      printf("\n%04X: ",i);
    }
  uint8_t data = Cpubus.read( (0x2800-16)+ i );
  printf("%02X ",data);
 }
 printf("\n");
} //read256
*/
