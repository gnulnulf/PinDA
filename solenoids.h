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



 class SOLENOID : public PindaObj {
	protected:
 		uint8_t timer;
 	
		bool active;
		bool state;
		String name;
		solenoid_type type;
		uint8_t max_on;
		uint8_t min_off;

		uint16_t delay_timer;
		uint8_t off_timer;
		
		volatile sol_state current_state;
	public:
		SOLENOID ( void );
		virtual void real_on(void);
		virtual void real_off(void);
		void on(uint16_t delay=0);
		void off( void);
		void toggle(void);
		bool isOn(void);
		void serviceTimer(void);
		virtual void interrupt(void);
 };

 
/** 
* uses direct attached solenoids to the arduino pin.
*/ 
class SOLENOID_demo : public SOLENOID {
	public:
		SOLENOID_demo( 
			uint8_t _port,
			bool _active=true,
			solenoid_type _type=SOLENOID_PULSE,
			uint8_t _max_on=10,
			uint8_t _min_off=10,
			String _name="SOLENOIDDEMO"
		);
		virtual void real_on(void);
		virtual void real_off(void);
	private:
		uint8_t port;
};

 
 
class SOLENOID_latch : public SOLENOID {
	public:
		SOLENOID_latch( 
			LATCH8 * _latch, 
			uint8_t _bit,
			bool _active,
			solenoid_type _type=SOLENOID_UNUSED,
			uint8_t _max_on=10,
			uint8_t _min_off=10,
			String _name="SOLENOIDLATCH"
		);
		virtual void real_on(void);
		virtual void real_off(void);

	private:
		LATCH8 * latch;
		uint8_t bitnr;
};

class SOLENOID_pia : public SOLENOID {
	public:
		SOLENOID_pia( 
			MC6821 * _pia,
			pia_io _index,
			bool _active=true,
			solenoid_type _type=SOLENOID_UNUSED,
			uint8_t _max_on=10,
			uint8_t _min_off=10,
			String _name="SOLENOIDPIA"
		);
		void real_on(void);
		void real_off(void);

	private:
		MC6821 * pia;
		pia_io index;
}; 


#endif //SOLENOIDS