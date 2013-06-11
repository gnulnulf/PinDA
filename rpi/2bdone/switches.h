/**
 @file

 @brief switch drivers and switch functions 

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

Switches are a core item on pinball machines.

@todo direct pia switches
  

*/ 
#ifndef SWITCHES_h
#define SWITCHES_h

#include "pinda.h"
#include "mc6821.h"
// will be needed for bally mpu35 switches
#include "lamps.h" 

//! base class for switches
class SWITCHES : public PindaObj{
	public:
		SWITCHES(void);
		//! Interrupt is used for timed actions from the pinda interrupt timer
		virtual void interrupt(void); 
		
		//! the serviceLoop is for maintenance tasks which are not time critical and should be in the main loop.
		virtual void serviceLoop(void);
		
		//! clear switch arrays and counters
		void clear(void);
		
		//! show the state in hex on the serial link.
		//! probably debugging uses only
		void show(void);
		String getString(void);
		String getFlank(void);	
		//! get all switches in a row
		//! @param row is the row from 0-7
		//! @returns a byte with 8 state bits
		uint8_t getRow( uint8_t row);
		
		//! get single switch
		//! obsolete?
		//! @param number is the switchnumber 0-63
		//! @returns a byte with the switch state
		uint8_t get(uint8_t number);

		//! get single switch
		//! @param number is the switchnumber 0-63
		//! @returns true/false for the switch state
		bool isOn( uint8_t number );
		
//		void rowSet( const uint8_t row, const uint8_t data);
//		void allSet( uint8_t row1,uint8_t row2,uint8_t row3,uint8_t row4,uint8_t row5,uint8_t row6,uint8_t row7,uint8_t row8);

		//! get the flank up flag
		//! this query will clear the flag and returns the state
		//! @param number is the switchnumber 0-63
		//! @returns true/false for the flank up flag
		bool flankup( uint8_t number);
		
		
		//! get the flank down flag
		//! this query will clear the flag and returns the state
		//! @param number is the switchnumber 0-63
		//! @returns true/false for the flank down flag
		bool flankdown( uint8_t number);
		
		
		//! get changed flag
		//! this query will clear the flag and returns the state
		//! @returns true/false for the change flag
		bool isChanged(void);
		bool hasFlank(void);
		
	protected:
		uint8_t switchdata[8]; 		//!< the standard lamp container
		uint8_t switchdatalast[8]; 	//!< the standard lamp container
		uint8_t currentRow;			//!< row inside interrupt
		uint8_t flankupdata[8]; 	//!< store flank up events
		uint8_t flankdowndata[8]; 	//!< store flank down events
		
		bool changed;				//!< is anything changed
}; //SWITCHES

/** 
demo driver for 8 switches on the arduino.

this driver uses arduino pins 4,5,6,7,38,39,41 and 41.
These are free when the CPUBUS_direct is used.
Because of the internal pullup is used only a switch to ground is needed.
Possibly you can add a small resistor like 330 Ohm for protection.

The switches are bit silly matrix subset to use all row collumn crossings.

	cols87654321
	row1_______0
	row2______1_
	row3_____2__
	row4____3___
	row5___4____
	row6__5_____
	row7_6______ 
	row87_______

This results in switches 0,9,18,27,36,45,54,63
*/
class  SWITCHES_demo : public SWITCHES {
	public:
		//! constructor
		SWITCHES_demo(String _name="SWITCHES DEMO");
		void interrupt(void);
	private:
		const static uint8_t sw1_pin = 41; 	//!< switch 0 pin
		const static uint8_t sw2_pin = 40; 	//!< switch 9 pin
		const static uint8_t sw3_pin = 39; 	//!< switch 18 pin
		const static uint8_t sw4_pin = 38; 	//!< switch 27 pin
		const static uint8_t sw5_pin = 7;	//!< switch 36 pin
		const static uint8_t sw6_pin = 6; 	//!< switch 45 pin
		const static uint8_t sw7_pin = 5;	//!< switch 54 pin
		const static uint8_t sw8_pin = 4;	//!< switch 63 pin
}; //switches_demo


/**
Switch Driver class for Williams System 11a

The Williams System 11 switches are multiplexed by one MC6821.
@todo opto lines should be detected
*/
class  SWITCHES_williams11a : public SWITCHES {
	public:
		//! constructor 
		//! the PIA needs to be defined and will be setup by the constructor.
		//! @param _pia is the reference to MC6821
		SWITCHES_williams11a( MC6821 * _pia,String _name="SWITCHES SYS11A");
		//! interrupt to poll the switches
		void interrupt();
	private:
		MC6821 * pia;	//!< pointer to MC6821 pia
}; // SWITCHES_williams11a

#endif //SWITCHES_h