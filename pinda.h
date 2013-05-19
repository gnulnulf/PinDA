/*
  PinDA.h - wrapper for all Pinball direct access parts

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

/**
* @file
* @brief Framework for controlling pinball hardware
* @details This framework controls pinball machine based on mc680x cpu's
* @author Arco van Geest <arco@appeltaart.mine.nu>
* @copyright GNU Public License.
*

* This file is a placeholder to include all seperate classes into a game.
* just use \#include pinda.h
*/
#ifndef PINDA_h
#define PINDA_h
/******************************************************************************
* Sources
******************************************************************************/
/**
* @page Information sources
* - Microcomputer techniek - Stam technische boeken 1981 (dutch)
* - http://www.arduino.cc
* - http://www.pinwiki.com/wiki/index.php?title=Pinball_Part_Datasheets
* - http://www.pinballpcb.com/datasheets.html
* - http://appeltaart.mine.nu/wiki/index.php/PinDA (dutch)
*/

typedef int (*IntFunctionWithOneParameter) (int a);
typedef void (*voidFunction) (void);

/******************************************************************************
* Includes
******************************************************************************/
// Enable printf ( must have printf_begin() )
//#include "printf.h"

//interrupt stuff
#include <avr/io.h>
#include <avr/interrupt.h>
#include <String>
#include <vector>

class PindaObj {
	public:
		virtual void test(void);
	
};


//! Class to access the CPU(680n) BUS
#include "CPUBUS.h"

//! mc6821 access
#include "mc6821.h"

//!rom access 
#include "rom.h"

//!lamps 
#include "lamps.h"

//!switches
#include "switches.h"

//!solenoids
#include "solenoids.h"

//!protocol master-slave
#include "cpubuscom.h"

//!display
//#include "lcdchars.h"
#include "display.h"





class Pinda {
};


//Pinda pinda;

//pinda timer(s)
void pindaStartTimer(void);
void pindaInterrupt(void);
int pindaAddInterrupt ( voidFunction fun, unsigned int interval );
// service hooks
// interval



//service loop
/** Pinda Main non-timed service loop
* this starts all attached functions @see pindaAddLoop 
* it should be placed in the arduino "loop" section
*/
void pindaLoop(void);

/** Add function to the non timed service loop
* @param fun Function to add
* @returns slot used in the function store or -1 if no empty slot was found.
*/
int pindaAddLoop ( voidFunction fun );
// service hooks

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


 
*/



#endif /* PINDA_h */
