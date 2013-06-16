/**
 @file 

 @see pindacom.h for details
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

 @brief protocol definition between raspberry and arduino-slave

*/ 



/******************************************************************************
 * Includes
 ******************************************************************************/
 #include "pinda.h"
 #include "pindacom.h"
 #ifdef RASPBERRY
 #include <iostream>
 #endif
/******************************************************************************
* Definitions
******************************************************************************/
PindaCom::PindaCom ( void ) {
	msgStart=false;
	msgReady=false;
	enable=false;
	message="";
	pinda.AddInterrupt ( this , 5);
}

void PindaCom::listen(void) {
	msgReady=false;
	msgStart=false;
	message="";
}

void PindaCom::enableInterrupt(void) {
		Serial.println("\nENABLE SERIAL INT");
		//pinda.AddInterrupt ( this , 1);
		enable=true;
}


String PindaCom::getMessage( void ) {
	return message;
}

bool PindaCom::isReady( void ) {
	return msgReady;
}

void PindaCom::interrupt(void) {
#ifdef ARDUINO
	if ( ( enable ) && (!msgReady) ) {
//	Serial.print(".");
	
	if ( Serial.available()   )  {
    char in = (char)Serial.read(); 
	Serial.print("*");
	if (  in == '{' ){
		msgReady=false;
		message="";
		msgStart=true;
	} else {
		if ( msgStart ) {
			if (in == '}') {
				msgReady = true;
			} else {
				message += in;
			}
		}
	}
  }
}
#endif
}//PindaCom::interrupt

void PindaCom::serialIn() {
#ifdef ARDUINO
  while (( Serial.available()  ) && (!msgReady) )  {
    char in = (char)Serial.read(); 
	if (  in == '{' ){
//		Serial.print("SER START");
		msgReady=false;
		message="";
		msgStart=true;
	} else {
		if ( msgStart ) {
			if (in == '}') {
				msgReady = true;
//				Serial.print("SER END");
			} else {
				message += in;
			}
		}
	}
  }
#endif
} //serialIn

void PindaCom::setLampBank( uint8_t index, PindaObj * obj) {
	if ( index < lampBanks ) {
		lampBank[ index ] = obj;
	}
}

void PindaCom::setSwitchBank( uint8_t index, PindaObj * obj) {
	if ( index < switchBanks ) {
		switchBank[ index ] = obj;
	}
}

void PindaCom::setSolenoid( uint8_t index, PindaObj * obj) {
	if ( index < solenoids ) {
		solenoid[ index ] = obj;
	}
}

String PindaCom::status( void ) {
	String (PindaObj::*PindaGetName)(void) = &PindaObj::getName;
	String s="\n### Serial map status ###";

	// dump lamp banks
	for ( uint8_t i=0; i<lampBanks ;i++) {
		if ( lampBank [ i ] ) {
#ifdef ARDUINO
			s+= "\nLAMPBANK " + String(i)+ ": " + ( lampBank[i]->*PindaGetName )();
#endif	
#ifdef RASPBERRY
		char buf[80];
		sprintf(buf,"\nLAMPBANK %02d : %s ", i, ( lampBank[i]->*PindaGetName )().c_str());
		s+= buf;
#endif

		}
	}
	// dump switch banks
	for ( uint8_t i=0; i<switchBanks ;i++) {
		if ( switchBank [ i ] ) {
#ifdef ARDUINO
			s+= "\nSWITCHBANK " + String(i)+ ": " + ( switchBank[i]->*PindaGetName )();
#endif	
#ifdef RASPBERRY
		char buf[80];
		sprintf(buf,"\nSWITCHBANK %02d : %s ", i, ( switchBank[i]->*PindaGetName )().c_str());
		s+= buf;
#endif
		}
	}
	// dump solenoids
	for ( uint8_t i=0; i<solenoids ;i++) {
		if ( solenoid [ i ] ) {
#ifdef ARDUINO
			s+= "\nSOLENOID " + String(i)+ ": " + ( solenoid[i]->*PindaGetName )();
#endif	
#ifdef RASPBERRY
		char buf[80];
		sprintf(buf,"\nSOLENOID %02d : %s ", i, ( solenoid[i]->*PindaGetName )().c_str());
		s+= buf;
#endif
		}
	}

	s+= "\n";
	return s;
}

//! @page protocol Master-slave protocol

void PindaCom::flank(void) {
	// dump switch banks
	for ( uint8_t i=0; i<switchBanks ;i++) {
		if ( switchBank [ i ] ) {
			String (PindaObj::*PindaGetFlank)(void) = &PindaObj::getFlank;
			bool (PindaObj::*PindaHasFlank)(void) = &PindaObj::hasFlank;
			if( ( switchBank[i]->*PindaHasFlank )() ) {
			#ifdef ARDUINO
				Serial.println("{S"+String( i,HEX )+( switchBank[i]->*PindaGetFlank )() +"}" );
			#endif
			#ifdef RASPBERRY
				cout << "{S" << i << ( switchBank[i]->*PindaGetFlank )() <<endl;
			#endif
			
			}			
		}
	}
}// PindaCom::flank


void PindaCom::parseMsg( void ) {
	String (PindaObj::*PindaGetName)(void) = &PindaObj::getName;

	char cmd=message.CHARAT(0);
#ifdef ARDUINO
	Serial.println("MSG: "+message );
	Serial.println("CMD: "+String(cmd) );
	Serial.println("LEN: "+String(message.length() ) );
#endif
	switch( cmd ) {

		// --------------------------------------------------------
		//! @subsection solenoids Solenoids
		//!
		//! { Q [index.2] [0|1|T] }
		//!
		//! example: {Q261} turn solenoid at index 26 on
		case 'Q':
			//! {Q[index.2][0|1|T]}
			if ( message.length() == 4 ) {
				void (PindaObj::*PindaOn)(uint16_t) = &PindaObj::on;
				void (PindaObj::*PindaOff)(void) = &PindaObj::off;
				void (PindaObj::*PindaToggle)(void) = &PindaObj::toggle;
			
				uint8_t index=( message.CHARAT(1)-'0')*10 +( message.CHARAT(2)-'0'); 
				if ( solenoid[ index ] ) {
					String a;
					switch ( message.CHARAT( 3) ){
						case '0':
							( solenoid[ index ]->*PindaOff )();
							a="OFF";
							break;
						case '1':
							( solenoid[ index ]->*PindaOn )(0);
							a="ON";
							break;
						case 'T':
							( solenoid[ index ]->*PindaToggle )();
							a="TOGGLE";
							break;
						default:
							a="FAILED";
					}
					Serial.println("SET SOLENOID "+a+" : " +( solenoid[ index ]->*PindaGetName )() ); 
				} else {
					Serial.println("SOLENOID NOT MAPPED");
				}
			} else {
				Serial.println("SOLENOID BADMSG");
			}
			break;
			// --------------------------------------------------------

			
			
		default:
			Serial.println("UNKNOWN COMMAND");
			break;
	
	}


}
 





 
