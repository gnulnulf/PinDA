/**
 @file

 @brief solenoid drivers and solenoid functions 

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

Solenoids are quite fragile. 
Turning on too many or turning on too long would hopefully burn switches.
Because of the nature of these coils the timers are in the drivers.
there are three timer states:
- delayed on timer
- maximum on timer
- minimum off timer 

*/ 

#ifndef SOLENOIDS_h
#define SOLENOIDS_h
 
#include "pinda.h"
#include "mc6821.h"

// --------------------------------------------------------
// Enumerations
// --------------------------------------------------------

//! a solenoid can enter several states.
enum sol_state {
	SOL_OFF=0,		//!< just off
	SOL_DELAY_ON=1,	//!< waiting to be turned on
//	SOL_TURN_ON=2,	
//	SOL_ON=3,
	SOL_ON_TIMER=4,	//!< on or waiting to let the max on timer end
//	SOL_TURN_OFF=5, 
	SOL_OFF_TIMER=6	//!< leaving the solenoid off for a minimal time
};


//! solenoids can be pulsed or continious. 	
enum solenoid_type { 
	SOLENOID_UNUSED, 	//!< placeholder for undefined solenoids 
	SOLENOID_PULSE,		//!< solenoid may only be pulsed
	SOLENOID_CONT 		//!< solenoid may be on long and has no on timer
}; 


//! solenoid base class
 class SOLENOID : public PindaObj {
	protected:
 		uint8_t timer;			//!< timer counter
 		bool active;			//!< is the soloid active high or low
		bool state;				//!< current state of the solenoid
		solenoid_type type;		//!< type of the solenoid (pulse/continious)
		uint8_t max_on;			//!< amount of Pinda interrupts the solenoid may be on
		uint8_t min_off;		//!< amount of Pinda interrupts the solenoid should be off

		//! the state the solenoid is in
		volatile sol_state current_state;
	public:
		//! constructor
		SOLENOID ( void );
		
		//! this realy turns on the solenoid
		virtual void real_on(void);
		
		//! this realy turns off the solenoid
		virtual void real_off(void);
		
		//! turn on solenoid or start delay timer
		virtual void on(uint16_t delay=0);
		
		//! start turn off sequence 
		virtual void off( void);
		
		//! toggle the solenoid from on to off or otherwise
		virtual void toggle(void);
		
		//! check if solenoid is activated
		//! @returns true if solenoid is on
		bool isOn(void);
		
		//! interrupt function which will be started by the Pinda interrupt timer
		virtual void interrupt(void);
 };

 
/** 
* uses direct attached solenoids to the arduino pin.
*/ 
class SOLENOID_demo : public SOLENOID {
	public:
		//! constructor
		SOLENOID_demo( 
			uint8_t _port,						//!< arduino port number
			bool _active=true,					//!< active state on=true
			solenoid_type _type=SOLENOID_PULSE,	//!< solenoid type, default to pulse
			uint8_t _max_on=10,					//!< solenoid may be on for this amount of pinda interrupts
			uint8_t _min_off=10,				//!< solenoid should be off for this amount of pinda interrupts
			String _name="SOLENOIDDEMO"			//!< name of the solenoid
		);
		
		//!< turn on solenoid, no other logic
		virtual void real_on(void);
		//!< turn off solenoid, no other logic
		virtual void real_off(void);
	private:
		uint8_t port;							//!< arduino port number
}; // SOLENOID_demo

 
/** 
* solenoid which uses one bit on the 8 bit latch IC on the cpubus
*/ 
class SOLENOID_latch : public SOLENOID {
	public:
		//! constructor
		SOLENOID_latch( 
			LATCH8 * _latch, 					//!< pointer to latch object
			uint8_t _bit,						//!< bit number on the latch ic (0-7)
			bool _active,						//!< active state on=true
			solenoid_type _type=SOLENOID_PULSE,	//!< solenoid type, default to pulse
			uint8_t _max_on=10,					//!< solenoid may be on for this amount of pinda interrupts
			uint8_t _min_off=10,				//!< solenoid should be off for this amount of pinda interrupts
			String _name="SOLENOIDLATCH"		//!< name of the solenoid
		);
		
		//!< turn on solenoid, no other logic
		virtual void real_on(void);
		//!< turn off solenoid, no other logic
		virtual void real_off(void);
	private:
		LATCH8 * latch;							//!< pointer to latch object
		uint8_t bitnr;							//!< bit number on the latch ic (0-7)
}; // SOLENOID_latch 

/** 
* solenoid which uses a io-bit on a MC6821 IC on the cpubus
*/ 
class SOLENOID_pia : public SOLENOID {
	public:
		//! constructor
		SOLENOID_pia( 
			MC6821 * _pia,							//!< pointer to mc6821 object
			pia_io _index,							//!< bit number on the pia ic (0-20)
			bool _active=true,						//!< active state on=true
			solenoid_type _type=SOLENOID_PULSE,		//!< solenoid type, default to pulse
			uint8_t _max_on=10,						//!< solenoid may be on for this amount of pinda interrupts
			uint8_t _min_off=10,					//!< solenoid should be off for this amount of pinda interrupts
			String _name="SOLENOIDPIA"				//!< name of the solenoid
		);
		//!< turn on solenoid, no other logic
		virtual void real_on(void);
		//!< turn off solenoid, no other logic
		virtual void real_off(void);
	private:
		MC6821 * pia;								//!< pointer to mc6821 object
		pia_io index;								//!< bit number on the pia ic (0-20)
}; // SOLENOID_pia


#endif //SOLENOIDS