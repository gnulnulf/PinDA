/**
 @file 

 @brief protocol definition between raspberry and arduino-slave
 
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

protocol definition between raspberry and arduino-slave
*/
#ifndef CPUBUSCOM_h
#define CPUBUSCOM_h

/**
* protocol

start {
end }
lowercase get
uppercase set
message cannot contain {}

game
====
enable solenoids
disable solenoids
SOLENOID ON
{Q[index][0|1|T]}
Q solenoid

 
F set flashers


L set lamps
L set animation
start animation
stop animation

s get switches
S
E set event



diagnostics
===========
dR read byte
DR read reply byte
dW write byte
DW write reply byte

{dRESET} reset
{DRESETOK} reset handshake
{DACK}
{DERROR:STRING}

{dSTATE} get state
{DSTATE:STRING} send state

{dMEMORYMAP}
{DMEMORYMAP:STRING} get memorymap
dLAMPS get lamps



*
*
*/

// --------------------------------------------------------
// Includes
// --------------------------------------------------------
#include "pinda.h"
#ifdef RASPBERRY
#include "rpi/compatibility.h" 
#endif
//------------------------------------------------------------------------
// Definitions
//------------------------------------------------------------------------

class PindaCom : public PindaObj {
	public:
		//! constructor
		PindaCom( void );
		//! try to read one message from serial 
		void serialIn( void);	
		//! read message
		String getMessage(void);
		//! enable next message
		void listen( void );
		//! is message ready?
		bool isReady(void);
		
		//! parse the message
		void parseMsg(void);
		
		//! set lampbank on index to lamp object
		void setLampBank( uint8_t index, PindaObj * obj );
		
		//! set switchbank on index to lamp object
		void setSwitchBank( uint8_t index, PindaObj * obj );
		
		//! set solenoidbank on index to lamp object
		void setSolenoid( uint8_t index, PindaObj * obj );
		
		//! dump status
		String status(void);
		
		void interrupt(void);
		void enableInterrupt(void);
		
		void flank(void);
		
	private:
		String message;		//!< buffer for message
		bool msgStart;		//!< msg start { is found
		volatile bool msgReady;		//!< message is complete
		volatile bool enable;
		
		const static uint8_t lampBanks=4; 		//!< maximum amount of lamp banks
 		PindaObj * lampBank[ lampBanks ]; 		//!< array of lamp pointers
		
		const static uint8_t switchBanks=4;		//!< maximum amount of switch banks
		PindaObj * switchBank[ switchBanks ];	//!< array of lamp pointers
		
		const static uint8_t solenoids=32;		//!< maximum amount of solenoid objects
		PindaObj * solenoid[ solenoids ];		//!< array of solenoid pointers
}; //PindaCom



#endif /* CPUBUSCOM_h */



 
