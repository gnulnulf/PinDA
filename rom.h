/**
 @file

 @brief interface to the rom/ram on the 68xx memory bus

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

Access ram and rom on the cpu bus.
This is not needed in games but could be usefull for diagnostics
*/ 
#ifndef rom_h
#define rom_h

class ROM : public PindaObj {
public:
	/** initialize ROM 
	*
	*/
	ROM(CPUBUSClass *busptr ,unsigned int addr, unsigned int size ,String name );
	//void init(  CPUBUSClass *busptr ,unsigned int addr, unsigned int size );

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
	//String name;
};
/*
class RAM: public ROM {
	public:
		RAM(CPUBUSClass *busptr ,unsigned int addr, unsigned int size ,String name );

}; //RAM
*/
#endif /* rom_h */