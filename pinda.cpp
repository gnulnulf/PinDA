/**
 @file 

 @see pinda.h for details
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

 @brief Base of the PinDA framework
 
*/ 
#include "pinda.h"


#ifdef ARDUINO
#define println(line) Serial.println(line)
#define print(line) Serial.print(line)
#endif


const int maxInterrupts=32;
const int maxLoop=32;

// constructor
Pinda::Pinda(void) {
	interruptCounter=0;
	interruptTop=0;
	interruptFNTop=0;
	//interruptptr = &PindaObj::interrupt;
	//serviceloopptr = &PindaObj::serviceLoop;
//	void (PindaObj::*PindaInterrupt)(void) = &PindaObj::interrupt;
//	void (PindaObj::*PindaServiceLoop)(void) = &PindaObj::serviceLoop;
}


String PindaObj::getName(void){
	return objName;
}

void PindaObj::interrupt(void){
}

void PindaObj::serviceLoop(void){
}

voidFunction interruptFunctions[ maxInterrupts ];
unsigned int interruptInterval[maxInterrupts];

voidFunction loopFunctions[maxLoop];

//pinda timer(s)
void Pinda::StartTimer(void){
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

// timer compare interrupt service routine
ISR(TIMER1_COMPA_vect)          
{
	pinda.mainInterrupt();
} //ISR pindaInterrupt
/*
//= &<PindaObj>solenoid22::getName();
void (PindaObj::*PindaInterrupt)(void) = &PindaObj::interrupt;
void (PindaObj::*PindaServiceLoop)(void) = &PindaObj::serviceLoop;
String  (PindaObj::*getnameptr)(void) = &PindaObj::getName;
PindaFunc pf  = &PindaObj::interrupt;

SOLENOID & t= solenoid22;
PindaObj & s= solenoid22;
PindaObj * u = &solenoid22;

Serial.println("pointer...");
Serial.println( (t.*getnameptr)()     );
Serial.println( (s.*getnameptr)()     );
Serial.println( (u->*getnameptr)()     );
Serial.println( t.getName()     );
Serial.println("pointer...");

*/

void Pinda::mainInterrupt(void){
	static unsigned int interruptCounter;
	interruptCounter++;
	void (PindaObj::*PindaInterrupt)(void) = &PindaObj::interrupt;

	if ( interruptTop) {
		for(int i = 0; i < interruptTop; ++i) {
			if ( interruptPointers[ i ] ) {
				if ( interruptCounter % intteruptInterval[i] == 0 ) {
					(interruptPointers[ i ]->*PindaInterrupt)();
				}
			}
		}
	}
	if ( interruptFNTop ) {
		for(int i = 0; i < interruptFNTop; ++i) {
			if ( interruptFunctions[ i ] ) {
				if ( interruptCounter % intteruptFNInterval[i] == 0 ) {
					interruptFunctions[ i ]();
				}
			}
		}
	}
	
} //Pinda::mainInterrupt

int Pinda::AddLoop ( voidFunction fun ){
	for(int i = 0; i < maxServiceFunctions; ++i) {
		if ( serviceFunctions[i] == NULL ) {
			serviceFunctions[i]=fun;
			return i;
		}
	}
	println("{ERROR:Out of loopslots}");
	return -1;
}

int Pinda::AddInterrupt ( voidFunction fun, unsigned int interval ){
	for(int i = 0; i < maxFNInterrupts; ++i) {
		if ( interruptFunctions[i] == NULL ) {
			interruptFunctions[i]=fun;
			intteruptFNInterval[i]=interval;
			if ( i > interruptFNTop) interruptFNTop=i;
			return i;
		}
	}
	println("{ERROR:Out of interruptslots}");
	return -1;
}

int Pinda::AddInterrupt ( PindaObj * obj, unsigned int interval ){
	for(int i = 0; i < maxInterrupts; ++i) {
		if ( interruptPointers[i] == NULL ) {
			interruptPointers[i]=obj;
			intteruptInterval[i]=interval;
			if ( i > interruptTop) interruptTop=i;
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
void Pinda::loop(void){
	void (PindaObj::*PindaServiceLoop)(void) = &PindaObj::serviceLoop;

	for(int i = 0; i < maxInterrupts; ++i)    {
		if ( servicePointers[ i ] ) {
		(servicePointers[ i ]->*PindaServiceLoop)();
		}
	}

  for(int i = 0; i < maxServiceFunctions; ++i)    {
		if ( serviceFunctions[ i ] ) {
				serviceFunctions[ i ]();
		}
    }
}



int Pinda::freeRam ( void) {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
} //Pinda::freeRam

String Pinda::status(void) {
	String s;
		s+= "\n### PinDA status ###";
		s+= "\nMemory Free        : " + String( freeRam() );
		s+= "\nPindaInterrupts    : " + String( interruptTop );
		s+= "\nFunctionInterrupts : " + String( interruptFNTop );

		unsigned int count;
		count=0;
		for(int i = 0; i < maxInterrupts; ++i)    {
			if ( servicePointers[ i ] ) count++;
		}
		s+= "\nPindaLoop          : " + String( count );
		count=0;
		for(int i = 0; i < maxServiceFunctions; ++i)    {
			if ( serviceFunctions[ i ] ) count++;
		}
		s+= "\nFunctionLoop       : " + String( count );
		s+= "\n\n";
		return s;
} // Pinda::status








// pinda.cpp


