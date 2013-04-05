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
	void init(  CPUBUSClass *busptr ,int addr, int size );
	uint8_t read( int address );
	uint8_t read_offset( int address );
	void dump();

	CPUBUSClass * bus;
	int rom_address;
	int rom_size;
};



#endif /* rom_h */