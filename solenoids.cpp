/**
 @file 

 @see solenoids.h for details
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

 @brief Control solenoids
 
*/ 
//solenoids.cpp
#include "pinda.h"
#include "mc6821.h"
#include "solenoids.h"


SOLENOID::SOLENOID( void ){}

void SOLENOID::on(uint16_t _delay) {
	timer=_delay;
	current_state=SOL_DELAY_ON;
}

void SOLENOID::off(void) {
	real_off();
	timer=min_off;
	current_state=SOL_OFF_TIMER;
}

void SOLENOID::toggle(void) {
	(state)?off():on();
}


void SOLENOID::real_on(void){};
void SOLENOID::real_off(void){};


void SOLENOID::interrupt(void){
	serviceTimer();
}


void SOLENOID::serviceTimer( void ){
	//Serial.print( current_state );  
	switch ( current_state ) {
		// just off
		case SOL_OFF: 
			break;
			
		// timer before solenoid is activated
		case SOL_DELAY_ON:
			//Serial.print( " D");
			//Serial.print( timer );
			if ( timer > 0 ) {
				timer--;
			} else { 
				//Serial.print( " ON");
				current_state = SOL_ON_TIMER;
				timer=max_on;
				state=true;
				real_on();
			}
			break;
			
		// for pulse type the timer will turn off the solenoid
		case SOL_ON_TIMER:
			state=true;
			//Serial.print( " O");
			//Serial.print( timer );
			if ( type == SOLENOID_PULSE ) {

					if ( timer > 0 ) {
					timer--;
				} else {
					current_state = SOL_OFF_TIMER;
					timer = min_off;
					real_off();
					state=false;
				}
			}
			break;
			
		// 	the solenoid needs to be off for the duration of the timer
		case SOL_OFF_TIMER:
			state=false;
				if ( timer > 0 ) {
					//Serial.print( " T");
					//Serial.print( timer );
					
					timer--;
				} else {
					current_state = SOL_OFF;
				}
				break;;
		default:
				break;;
	} //switch
}

// ------------------------------------------------------
// demo
// ------------------------------------------------------
SOLENOID_demo::SOLENOID_demo( 
uint8_t _port , bool _active, solenoid_type _type, uint8_t _max_on,
		uint8_t _min_off,
 String _name
) {
	port=_port;
	min_off=_min_off;
	max_on=_max_on;
	objName=_name;
	active=_active;
	timer=0;
	type=_type;
	pinMode(port, OUTPUT);
	off();
	pinda.AddInterrupt ( this , 5);
}

void SOLENOID_demo::real_on(void) {
	timer=max_on;
	current_state=SOL_ON_TIMER;
	 digitalWrite(this->port, (active)?true:false );
}



void SOLENOID_demo::real_off(void) {
	 digitalWrite(this->port, (active)?false:true );
}

// ------------------------------------------------------
// LATCH
// ------------------------------------------------------
SOLENOID_latch::SOLENOID_latch( 
		LATCH8 * _latch ,
		uint8_t _bit,
		bool _active ,
		solenoid_type _type,
		uint8_t _max_on,
		uint8_t _min_off,
		String _name 
	) {
	latch=_latch;
	bitnr=_bit;
	min_off=_min_off;
	max_on=_max_on;
	objName=_name;
	active=_active;
	timer=0;
	type=_type;
		pinda.AddInterrupt ( this , 5);

}

void SOLENOID_latch::real_on( void ) {
	( active ) ? latch->on( bitnr ) : latch->off( bitnr );
} 

void SOLENOID_latch::real_off( void ) {
	( active ) ? latch->off( bitnr ) : latch->on( bitnr );
} 

// ------------------------------------------------------
// PIA
// ------------------------------------------------------
//0-7=A 8-15=B 16=CRA1 17=CRA2 18=CRB1 19=CRB2
SOLENOID_pia::SOLENOID_pia( 
		MC6821 * _pia,
		pia_io _index, 
		bool _active,
		solenoid_type _type, 
		uint8_t _max_on, 
		uint8_t _min_off,
		String _name
	)
	{
	pia=_pia;
	index=_index;
	max_on=_max_on;
	min_off=_min_off;
	objName=_name;
	active=_active;
	timer=0;
	delay_timer=0;
	type=_type;
	if ( index <17 ){
		pia->output(index);
	}
	
	if ( index == 18 ) {
		pia->on(18);
		pia->output(18);
	}

	if ( index == 20 ) {
		pia->on(20);
		pia->output(20);
	}

	//set pin as output
//set off state
	pinda.AddInterrupt ( this , 5);

}		

void SOLENOID_pia::real_on( void ) {
		( active ) ? pia->on( index ) : pia->off( index );
} 

void SOLENOID_pia::real_off( void ) {
	( active ) ? pia->off( index ) : pia->on( index );
} 

// solenoids.cpp