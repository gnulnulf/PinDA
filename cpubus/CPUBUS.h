/*
  CPUBUS.h - interface to the 8bit 68xx memory bus

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

#ifndef CPUBUS_h
#define CPUBUS_h


/*****************************************************************************
* Includes
******************************************************************************/
#include <inttypes.h>
/******************************************************************************
* Definitions
******************************************************************************/
#define CPUBUS_DIRECT 0
#define CPUBUS_SPI 1

//#define CPUBUS_TYPE CPUBUS_DIRECT

#define CPUBUS_TYPE CPUBUS_SPI


class CPUBUSClass
{

/******************************************************************************
 * Constructors
 ******************************************************************************/
  public:
	CPUBUSClass();
	void init(void);
	
  
    uint8_t read(int);
    void write(int, uint8_t);
};

extern CPUBUSClass Cpubus;




#endif /* CPUBUS_h */
