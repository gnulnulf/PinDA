/**
 @file 

 @see template.h for details
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

 @brief The code part of template
 
*/ 
//#include "lamps.h"

#include "switches.h"


#ifdef ARDUINO
#include "Arduino.h"
#define println(line) Serial.println(line)
#define print(line) Serial.print(line)
#else
#include "arduino_compat.h"
#endif

SWITCHES::SWITCHES(void) {
}

void SWITCHES::clear(void) {
	currentRow=0;
	for (uint8_t i=0;i<8;i++) {
		switchdata[i]=0;
		switchdatalast[i]=0;
		flankupdata[i]=0;
		flankdowndata[i]=0;
		changed=false;
	}
} //SWITCHES::switches

void SWITCHES::interrupt( void ) {
	currentRow++;
	if ( currentRow>7) currentRow=0;
} //SWITCHES::interrupt

void SWITCHES::serviceLoop(void){
	println("SwitchServiceLoop");
} //SWITCHES::serviceLoop

void SWITCHES::show(void){
	for (uint8_t i=0;i<8;i++) {
		printf("%02X ",switchdata[i]);
	}
	printf("\n");
} //SWITCHES::show

String SWITCHES::getString(void){
	String s;
	for (uint8_t i=0;i<8;i++) {
		#ifdef ARDUINO
		s+= String( switchdata[i], HEX )+" ";
		#endif
		#ifdef RASPBERRY  
		char buf[10];
		sprintf(buf,"%02X ", switchdata[i]);
		s+= buf;
		#endif
	}
	return s;
} //SWITCHES::getString

String SWITCHES::getFlank(void){
	String s,t;
	for (uint8_t i=0;i<8;i++) {
	#ifdef ARDUINO
		t="0"+String( flankupdata[i], HEX );
		s+= t.substring(t.length()-2);
		t="0"+String( flankdowndata[i], HEX );
		s+= t.substring(t.length()-2);
	#endif
	#ifdef RASPBERRY
		char buf[10];
		sprintf(buf,"%02X%02X", flankupdata[i],flankdowndata[i] );
		s+= buf;
	#endif 
		flankupdata[i]=0;
		flankdowndata[i]=0;
	}
	return s;
} //SWITCHES::getFlank

bool SWITCHES::hasFlank(void) {
	uint8_t c=0;
	for (uint8_t i=0;i<8;i++) {
		c |= flankupdata[i] | flankdowndata[i];
//		flankupdata[i]=0;
//		flankdowndata[i]=0;
	}
		return ( c )?true:false;
}

uint8_t SWITCHES::getRow(uint8_t row){
	return switchdata[ row & 0x7 ];
} //SWITCHES::getRow


bool SWITCHES::isOn( uint8_t number ){
	return ( switchdata[ number >>3 ] & ( 1<< (number & 0x7) ) );
} //SWITCHES::isOn

bool SWITCHES::flankup( uint8_t number) {
	if ( flankupdata[ number >>3 ] & ( 1<< (number & 0x7) ) ) {
		flankupdata[ number >>3 ] &= ~( 1<< (number & 0x7)) ;
		return true;
	}
	return false;
} // SWITCHES::flankup

bool SWITCHES::flankdown( uint8_t number) {
	if ( flankdowndata[ number >>3 ] & ( 1<< (number & 0x7) ) ) {
		flankdowndata[ number >>3 ] &= ~( 1<< (number & 0x7)) ;
		return true;
	}
	return false;
} // SWITCHES::flankdown

bool SWITCHES::isChanged( void ) {
	if ( changed == false ) return false;
	changed=false;
	return true;
}



SWITCHES_demo::SWITCHES_demo(String _name) {
	objName=_name;
	//demo switches with pullup
	clear();
	pinMode( sw1_pin, INPUT);
	digitalWrite( sw1_pin,HIGH);
	pinMode( sw2_pin, INPUT);
	digitalWrite( sw2_pin,HIGH);
	pinMode( sw3_pin, INPUT);
	digitalWrite( sw3_pin,HIGH);
	pinMode( sw4_pin, INPUT);
	digitalWrite( sw4_pin,HIGH);
	pinMode( sw5_pin, INPUT);
	digitalWrite( sw5_pin,HIGH);
	pinMode( sw6_pin, INPUT);
	digitalWrite( sw6_pin,HIGH);
	pinMode( sw7_pin, INPUT);
	digitalWrite( sw7_pin,HIGH);
	pinMode( sw8_pin, INPUT);
	digitalWrite( sw8_pin,HIGH);

		pinda.AddInterrupt ( this , 1);
} // switches_demo::init

/* a bit silly matrix subset
cols87654321
row1_______0
row2______1_
row3_____2__
row4____3___
row5___4____
row6__5_____
row7_6______
row87_______


*/
void SWITCHES_demo::interrupt(void) {
#ifdef ARDUINO
	//uint8_t number=currentRow * 9;
	uint8_t index[8] = { 
		sw1_pin,
		sw2_pin,
		sw3_pin,
		sw4_pin,
		sw5_pin,
		sw6_pin,
		sw7_pin,
		sw8_pin
	};
	switchdatalast[ currentRow ] = switchdata[ currentRow ] ;

	if ( digitalRead( index[currentRow]) == 0 ) {
		switchdata[ currentRow ] |= ( 1<< currentRow);
	} else {
		switchdata[ currentRow ] &= ~( 1<< currentRow);
	}
	if ( switchdatalast[ currentRow ] != switchdata[ currentRow ] )  changed=true;
	
	// XOR the data to get the changes and only for the flank direction
	flankupdata[ currentRow ] |= ( switchdatalast[ currentRow ] ^ switchdata[ currentRow ] ) & switchdata[ currentRow ] ;
	flankdowndata[ currentRow ] |= ( switchdatalast[ currentRow ] ^ switchdata[ currentRow ] ) & switchdatalast[ currentRow ] ;
	
	currentRow++;
	if ( currentRow>7) currentRow=0;
#endif
} // switches_demo::interrupt


SWITCHES_williams11a::SWITCHES_williams11a( MC6821 * piaptr, String _name ) {
	objName=_name;

	pia=piaptr;
	clear();
	pia->write_ddra(0); // A ingang  
	pia->write_ddrb(255);  //B uitgang
	pia->write_pdra(0x00); 
	pia->write_pdrb(0x00); 
		pinda.AddInterrupt ( this , 1);
}

void SWITCHES_williams11a::interrupt( void ) {

//	print("L");
//	print(row);
	switchdatalast[ currentRow ] = switchdata[ currentRow ] ;
	switchdata[ currentRow ] =  pia->read_pdra() ;
    pia->write_pdrb( ( 1 << currentRow ) );  // set row

	if ( switchdatalast[ currentRow ] != switchdata[ currentRow ] )  changed=true;

	// XOR the data to get the changes and only for the flank direction
	flankupdata[ currentRow ] |= ( switchdatalast[ currentRow ] ^ switchdata[ currentRow ] ) & switchdata[ currentRow ] ;
	flankdowndata[ currentRow ] |= ( switchdatalast[ currentRow ] ^ switchdata[ currentRow ] ) & switchdatalast[ currentRow ] ;
	
	currentRow++;
	if ( currentRow>7) currentRow=0;
}

  
  
  
  
  
  
  
  
 


