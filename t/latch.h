/**
 @file

 @brief latch io 

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

LATCH8 is just a latched output on the cpu bus
this can output 8 bits
it is used for solenoids in system11 systems
*/ 

#ifndef LATCH_h
#define LATCH_h
 
#include "pinda.h"

/**
* LATCH8 is just a latched output on the cpu bus
* this can output 8 bits
* it is used for solenoids in system11 systems
*/  
 class LATCH8 : public PindaObj {
	public:
		//! constructor
		LATCH8( 
			CPUBUSClass * _bus,		//!< reference to the CPUBUS 
			unsigned int address, 	//!< address of the latch chip
			String _name="LATCH8"	//!< name for diagnostics 
		);
		
		//! turn on bit
		//! @param bit number to set (0-7)
		void on( uint8_t bit);
		
		//! turn off bit
		//! @param bit number to reset (0-7)
		void off( uint8_t bit);
		
		//! toggle bit
		//! @param bit number to toggle (0-7)
		void toggle( uint8_t bit);

		//! write all bits at once
		//! @param data byte to set
		void all(uint8_t data);
		
		//! test if bit is set
		//! @param bit number to test (0-7)
		//! @returns true if bit is set
		bool isOn(uint8_t bit);
		
	private:
		uint8_t state;		//!< current state of latch data
		CPUBUSClass * bus;	//!< cpubus pointer
//		String name;
		unsigned int address;	//!< address on CPUBUS
}; 
  
  
#endif // LATCH_h
