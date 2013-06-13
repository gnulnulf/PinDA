/**
 @file
 @brief Framework for controlling pinball hardware
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

 @date       20130520 Initial version

 @details This framework controls pinball machine based on mc680x cpu's
This file is a placeholder to include all seperate classes into a game.
just use \#include pinda.h
*/

#ifndef PINDA_h
#define PINDA_h

#define ENABLE_SPI
//#define ENABLE_I2C


// --------------------------------------------------------
// Typedefs
// --------------------------------------------------------
//typedef int (*IntFunctionWithOneParameter) (int a);
//! void pointer definition
typedef void (*voidFunction) (void);
// --------------------------------------------------------
// Standard Includes
// --------------------------------------------------------
#include <inttypes.h>



#ifdef RASPBERRY
#include "rpi/compatibility.h"
#include "rpi/spi.h"
#include <string>
#define String std::string
#define CHARAT at
extern SPI* spiio;
#endif //RASPBERRY

#ifdef ARDUINO 
#define CHARAT charAt
#include <SPI.h>
//spiio = new SPI();
extern SPIClass* spiio;
//#include <Wire.h>
//#include <String>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Arduino.h"
//#define println(line) Serial.println(line)
//#define print(line) Serial.print(line)
#else
//#include "arduino_compat.h"
#endif



//! location of part
enum Location {
	loc_unknown, //!< location not known
	loc_playfield,	//!< part is on playfield
	loc_head,		//!< part is in head
	loc_body,		//!< part is in body (non playfield)
	loc_door,		//!< part is on coin door 
	loc_top			//!< part is located on top of the head
}; 

enum LampColour { 
	colour_unknown,
	colour_white,
	colour_yellow,
	colour_orange,
	colour_red,
	colour_blue,
	colour_green,
	colour_purple
};


struct Property {
	uint8_t index;
	String name;
	uint8_t x;
	uint8_t y;
	uint8_t count;
	LampColour col;
	Location loc;
};



//! Base class to unify all other classes
//!
//! This way it is possible to create pointers to different class types.
//! The pointers will be needed for interrupt and serviceloop jump tables.
//! Every IO Class object should be derived from this.
// it needs to be in from because other header files depend on this.
class PindaObj {
	public:
		//! get name of the object
		//! @returns string with Object name
		String getName(void);
		
		//! placeholder for interrupts
		virtual void interrupt(void);
		
		//! placeholder for untimed serviceLoop
		virtual void serviceLoop(void);
		
		virtual void on(uint16_t delay=0);
		//virtual void on(void);
		virtual void off(void);
		virtual void toggle(void);
		virtual bool isChanged(void);
		virtual String getString(void);
		virtual String getFlank(void);
		virtual bool hasFlank(void);
		
	//protected:
		String objName;	//!< Object name 
		String name;	//!< Object name 
}; //PindaObj
//typedef void (PindaObj::*PindaFunc)(void);  
//typedef void (*PindaObj::*PindaFuncPtr)(void);  


//typedef void (PindaObj::*PindaInterrupt)(void) ; //= &PindaObj::interrupt;
//typedef void (PindaObj::*PindaServiceLoop)(void) ; //= &PindaObj::serviceLoop;



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





/**
* PinDA framework
*
* PinDA is the base of the framework.
*
* @todo add interrupt to class
* @todo self register interrupt and serviceloops to jumptable
*/
class Pinda {
	public:
		//! constructor
		Pinda(void);
		
		//! get the status in a string
		String status(void);
		
		//! start the interrupt timer
		void StartTimer(void);

		//! this is the interrupt routine initiated by the pindaTimer
		//! the main interrupt starts the PindaObj and function interrupt from the interruptPointers 
		//! and interruptFNPointers arrays.
		void mainInterrupt(void);

		//! Pinda Main non-timed service loop
		//! this starts all attached functions @see pindaAddLoop 
		//! it should be placed in the arduino "loop" section
		void loop(void);

		//! Add function to the non timed service loop
		//! @param fun Function to add
		//! @returns slot used in the function store or -1 if no empty slot was found.
		int AddLoop ( voidFunction fun );

		//! add PindaObj to the interrupt service table
		int AddInterrupt ( 
			PindaObj * obj, 		//!< pointer to PinDA object
			unsigned int interval 	//!< interval in timerhits
		);

		//! add function to the interrupt service table
		int AddInterrupt ( 
			voidFunction fun, 		//!< voidpointer to the interrupt function
			unsigned int interval 	//!< interval in timerhits
		);
		
		//! get the amount of free ram (estimate)
		//! @returns amount of free ram 
		int freeRam(void);

	protected:
//		void (PindaObj::*PindaInterrupt)(void) ;	// = &PindaObj::interrupt;
//		void (PindaObj::*PindaServiceLoop)(void); 	// = &PindaObj::serviceLoop;
		const static int maxInterrupts=100;			//!< amount of Pinda interrupt slots
		const static int maxFNInterrupts=32;		//!< amount of function interrupt slots
		const static int maxPindaService=100;		//!< amount of Pinda service slots
		const static int maxServiceFunctions=32;	//!< amount of function service slots
		unsigned int interruptCounter;				//!< internal interrupt counter
		uint8_t interruptTop;						//!< highest used Pinda interrupt slot
		uint8_t interruptFNTop;						//!< highest used function interrupt slot

		//! array of PinDA object which has interrupt functions that need to run during the PinDA interrupt
		PindaObj * interruptPointers[100];			
		uint8_t	intteruptInterval[100];				//!< array of intervals for the PindaObj interrupts 

		//! array of PinDA object which has interrupt functions that need to run during the PinDA interrupt
		voidFunction interruptFunctions[32];
		uint8_t	intteruptFNInterval[32];			//!< array of intervals for the interrupt functions

		PindaObj * servicePointers[100];			//!< array of objects which have an untimed loop function
		voidFunction serviceFunctions[32];			//!< array of functionpointerswhich need to be executed within the untimed loop
}; //Pinda
//! external definition of pinda.
extern Pinda pinda;

// --------------------------------------------------------
// Framework Includes
// --------------------------------------------------------

// Class to access the CPU(680n) BUS
//#include "cpubus.h"

// mc6821 access
//#include "mc6821.h"
#include "mcp23s17.h"

//#include "latch.h"

//rom access 
//#include "rom.h"

//lamps 
//#include "lamps.h"

//switches
//#include "switches.h"

//solenoids
//#include "solenoids.h"

//protocol master-slave
//#include "pindacom.h"

//display
//#include "lcdchars.h"
//#include "display.h"

// --------------------------------------------------------
// Framework Documentation
// --------------------------------------------------------

/**
@mainpage
@section Introduction
PinDA (Pinball Direct Access) is a framework to access pinball machines based on 68xx CPU's

it's no game emulator. The original roms are not used.

The framework will be used to access:
- lamps
- solenoids
- switches
- roms (for diagnose only)
- ram (for diagnose only)
- (optional) sound
- (optional) display

Due to speed concerns on the arduino, the arduino is only used to interface with the IO.
The rest of the controls are done on a seperate platform like raspberry pi or PC.

The latest version of the framework should be at https://github.com/gnulnulf/PinDA

@section Targets
As this is a framework several targets are planned or optional.
- Access the pinball through the original hardware (using directIO/SPI/I2C)
- control your own hardware


@section Uses
- create own games
- diagnose machines
 
@section Warning
Wrong usage will break things!
Turning Original inputs into outputs will create shorts, hopefully only harm fuses.
Leaving coils and flashers on too long will burn or melt them with potential risk of fire!

Don't use this if you cannot repair your own pinball, or cannot afford a pinball engineer.

We are in no way responsible for any damage like breaking or burning.

@section used sources
@ref sources

 
*/

// --------------------------------------------------------
// Sources
// --------------------------------------------------------
/**
@page sources Information sources
@section books Books
 - Microcomputer techniek - Stam technische boeken 1981 (dutch)
 - Aan de slag met C++ 5e druk - Gertjan Laan (dutch)
@section links Links
 - http://www.arduino.cc
 - http://www.pinwiki.com/wiki/index.php?title=Pinball_Part_Datasheets
 - http://www.pinwiki.com/wiki/index.php?title=Williams_System_9_-_11
 - http://www.pinballpcb.com/datasheets.html
 - http://appeltaart.mine.nu/wiki/index.php/PinDA (dutch)
@section other Other
- http://stackoverflow.com/questions/8819580/callback-function-pointers-c-with-without-classes
 
 */


#endif /* PINDA_h */
