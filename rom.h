/*
  rom.h - interface to the rom on the 68xx memory bus

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

#ifndef rom_h
#define rom_h

class ROM {
public:
	/** initialize ROM 
	*
	*/
	void init(  CPUBUSClass *busptr ,unsigned int addr, unsigned int size );

	/** read byte from ROM, using real CPUBUS address 
	* @param address real CPUBUS address
	* @returns byte from the ROM
	*/
	uint8_t read( unsigned int address );
	
	
	/** read byte n from start of ROM, start of rom=0 
	* @param offset from start of ROM
	* @returns byte from the ROM
	*/
	uint8_t read_offset( unsigned int offset );

	/** Dump content of ROM */
	void dump();

	// checksum
 
	CPUBUSClass * bus; //!< Used CPUBUS
	unsigned int rom_address; //!< start address of ROM
	unsigned int rom_size;		//!< size of ROM
};



#endif /* rom_h */