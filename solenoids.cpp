//solenoids.cpp
#include "pinda.h"
#include "mc6821.h"
#include "solenoids.h"

void SOLENOID::test(void){
	Serial.print ("SOLENOID-test");
}

SOLENOID::SOLENOID( void ){

}



void SOLENOID::off(void) {
//	_real_off();
}


void SOLENOID::serviceTimer( void ){
	if ( type == SOLENOID_PULSE ) {
		if ( timer > 0 ) {
	//Serial.print( "TIMER" );
	//Serial.println( this->timer );
			timer--;
			if ( timer==0 ) {
				off();
				//Serial.print( "TOFF" );
			}
		}
	}
}

void SOLENOID_demo::serviceTimer( void ){
	if ( type == SOLENOID_PULSE ) {
		if ( this->timer > 0 ) {
	//Serial.print( "TIMER" );
	//Serial.println( this->timer );
			this->timer--;
			if ( this->timer==0 ) {
				this->off();
			//	Serial.print( "TOFF" );
			}
		}
	}
}


void SOLENOID_latch::serviceTimer( void ){
	if ( type == SOLENOID_PULSE ) {
	if ( delay_timer > 0) {
		if (delay_timer == 1 ) {
			on();
		}
		delay_timer--;
	}
		if ( this->timer > 0 ) {
	//Serial.print( "TIMER" );
	//Serial.println( this->timer );
			this->timer--;
			if ( this->timer==0 ) {
				this->off();
			//	Serial.print( "TOFF" );
			}
		}
	}
}


SOLENOID_demo::SOLENOID_demo( 
uint8_t _port , bool _active, solenoid_type _type, uint8_t _max_on,
		uint8_t _min_off,
 String _name
):
		port(_port)
		//active(_active),
		//type(_type),
		//max_on(_max_on),
		//name(_name)
		//timer(0)
{
	min_off=_min_off;
	max_on=_max_on;
	name=_name;
	active=_active;
	timer=0;
	type=_type;
	pinMode(port, OUTPUT);
	off();
}

void SOLENOID_demo::on(void) {
	this->timer=this->max_on;
//timer=10;
	 digitalWrite(this->port, (active)?true:false );
}
void SOLENOID_demo::off(void) {
	timer=0;
	 digitalWrite(this->port, (active)?false:true );
}

void SOLENOID_demo::toggle( void ) {
	timer=max_on;
	 digitalWrite(this->port, digitalRead( this->port) ^1  );
} 

bool SOLENOID_demo::isOn( void ) {
	return digitalRead(this->port); 
} 



SOLENOID_latch::SOLENOID_latch( 
		LATCH8 * _latch ,
		uint8_t _bit,
		bool _active ,
		solenoid_type _type,
		uint8_t _max_on,
		uint8_t _min_off,
		String _name 
	) : latch(_latch), 
		bitnr(_bit)
{
	min_off=_min_off;
	max_on=_max_on;
	name=_name;
	active=_active;
	timer=0;
	type=_type;
	



}


void SOLENOID_latch::on( void ) {
	timer=max_on;
	( active ) ? latch->on( bitnr ) : latch->off( bitnr );
} 

void SOLENOID_latch::off( void ) {
	timer=0;
	( active ) ? latch->off( bitnr ) : latch->on( bitnr );
} 

void SOLENOID_latch::toggle( void ) {
	timer=max_on;
	latch->toggle( bitnr ); 
} 

bool SOLENOID_latch::isOn( void ) {
	return latch->isOn( bitnr ); 
} 
	
	


SOLENOID_pia::SOLENOID_pia( MC6821 * _pia, pia_io _index, bool _active,solenoid_type _type, uint8_t _max_on, uint8_t _min_off,String _name):
	pia(_pia),
	index(_index)
	
	{
	max_on=_max_on;
	min_off=_min_off;
	name=_name;
	active=_active;
	timer=0;
	delay_timer=0;
		type=_type;

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
}		



//0-7=A 8-15=B 16=CRA1 17=CRA2 18=CRB1 19=CRB2

void SOLENOID_pia::on( void ) {
	timer=max_on;
	delay_timer=0;
		( active ) ? pia->on( index ) : pia->off( index );
} 

void SOLENOID_pia::onDelay( uint16_t delay ) {
	timer=max_on;
	delay_timer=delay;
	if ( delay == 0 ) { 
		on();
	}
} 

void SOLENOID_pia::off( void ) {
	timer=0;
	off_timer=min_off;
	( active ) ? pia->off( index ) : pia->on( index );
} 

void SOLENOID_pia::toggle( void ) {
	timer=max_on;
	pia->toggle( index ); 
} 

bool SOLENOID_pia::isOn( void ) {
	return (active)?( pia->isOn( index ) ):~( pia->isOn( index ) ); 
} 
	
	
void SOLENOID_pia::serviceTimer( void ){
	if ( type == SOLENOID_PULSE ) {
	// wait for the timer to end before turning on
	if ( delay_timer > 0) {
		if (delay_timer == 1 ) {
			on();
		}
		delay_timer--;
	}


	if ( this->timer > 0 ) {
	//Serial.print( "TIMER" );
	//Serial.println( this->timer );
			this->timer--;
			if ( this->timer==0 ) {
				this->off();
			//	Serial.print( "TOFF" );
			}
		}
	}
}
	
