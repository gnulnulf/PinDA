/*
  pinda.cpp - interface to the 8bit 68xx memory bus

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

#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef ARDUINO
#include "Arduino.h"
#define println(line) Serial.println(line)
#define print(line) Serial.print(line)

#else
#include "arduino_compat.h"


#endif

#include "pinda.h"


void PindaObj::test(void){
	//Serial.print("PindaObj");
	print( "PindaObj-test" );
}

const int maxInterrupts=32;
const int maxLoop=32;

voidFunction interruptFunctions[ maxInterrupts ];
unsigned int interruptInterval[maxInterrupts];

voidFunction loopFunctions[maxLoop];

//pinda timer(s)
void pindaStartTimer(void){
  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

 // OCR1A = 31250;            // compare match register 16MHz/256/2Hz
  OCR1A = 62;  	// 16Mhz/256=62500 -> every ms..
 //OCR1A = 31;	
  //  OCR1A = 6200;  	// 16Mhz/256=62500 -> every 100ms..
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();    
}

//void pindaInterrupt(void){
ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
	static unsigned int interruptCounter;
	interruptCounter++;
	for(int i = 0; i < maxInterrupts; ++i) {
		if ( interruptFunctions[ i ] ) {
			if ( interruptCounter % interruptInterval[i] == 0 ) {
				interruptFunctions[ i ]();
			}
		}
    }
} //ISR pindaInterrupt

int pindaAddLoop ( voidFunction fun ){
	for(int i = 0; i < maxLoop; ++i) {
		if ( loopFunctions[i] == NULL ) {
			loopFunctions[i]=fun;
			return i;
		}
	}
	println("{ERROR:Out of loopslots}");
	return -1;
}

int pindaAddInterrupt ( voidFunction fun, unsigned int interval ){
	for(int i = 0; i < maxInterrupts; ++i) {
		if ( interruptFunctions[i] == NULL ) {
			interruptFunctions[i]=fun;
			interruptInterval[i]=interval;
			return i;
		}
	}
	println("{ERROR:Out of interruptslots}");
	return -1;
}

/** Pinda Main non-timed service loop
* this starts all attached functions @see pindaAddLoop 
* it should be placed in the arduino "loop" section
*/
void pindaLoop(void){
  for(int i = 0; i < maxLoop; ++i)    {
		if ( loopFunctions[ i ] ) {
				loopFunctions[ i ]();
		}
    }
}



LATCH8::LATCH8(
		CPUBUSClass * _bus,
		unsigned int _address,
		String _name
	) :
	state(0),
	bus(_bus),
	address(_address),
	name(_name)
{


}

void LATCH8::all(uint8_t data) {
	state = data;
	bus->write(address,state);
}

void LATCH8::on(uint8_t bit) {
	state |= (1<<bit);
	bus->write(address,state);
}

void LATCH8::off(uint8_t bit) {
	state &= ~(1<<bit);
	bus->write(address,state);
}

void LATCH8::toggle(uint8_t bit) {
	(state & (1<<bit) )?off( bit ):on( bit );
}

bool LATCH8::isOn(uint8_t bit) {
	return (state & (1<<bit) );
}



