/**
 @file 

 @see display.h for details
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

 @brief control displays
 
*/ 
#include "display.h"
#include "lcdchars.h"

void DISPLAYCLASS::test(void){
	Serial.print ("DISPLAYtest");
}

 DISPLAY_WIL11A::DISPLAY_WIL11A ( MC6821 * _piaalfa, MC6821 * _pia7seg, MC6821 * _piawidget ) {
	piaalfa = _piaalfa;
	pia7seg = _pia7seg;
	piawidget = _piawidget;
//	stext1="";
	//stext1a="";
	index=0;
	blink=false;
	blinktime=100;
	blinkcounter=0;
	
	for (int i=0;i<16;i++){
		stext1[i]=' ';
		stext1a[i]=' ';
	}
	
	pia7seg->write_ddra(255); // A output  
	pia7seg->write_ddrb(255);  //B uitgang
	pia7seg->write_pdra(0x00); 
	pia7seg->write_pdrb(0x00);
	//cra2/crb2
	
	piaalfa->write_ddra(255); // A output  
	piaalfa->write_ddrb(255);  //B uitgang
	piaalfa->write_pdra(0x00); 
	piaalfa->write_pdrb(0x00);
	
	//piawidget->write_ddra(255); // A output  
	//piawidget->write_pdra(0x00); 
	pinda.AddInterrupt ( this , 1);
	
 }
 
 void DISPLAY_WIL11A::interrupt ( void ) {
	//Serial.print( index );

	pia7seg->write_pdrb(0x00 ); 
	piaalfa->write_pdra(0x00); 
	piaalfa->write_pdrb(0x00); 
	
	uint8_t state=pia7seg->read_pdra();
	pia7seg->write_pdra( ( state & 0xf0) | index );
	
	// set alphanumeric data
	uint8_t c = stext1[ index ];
	uint16_t val= lcd14Char( c )  ;
	if ( ( stext1[ index ] >= '0' )  & ( stext1[ index ] <= '9') ) {
		switch(index) {
			case 1 :
			case 4 :
			case 9 :
			case 12 :
				val |= 0x8080;
			default:
				;;
		}
	}
	piaalfa->write_pdra(val >> 8); 
	piaalfa->write_pdrb(val & 0x00ff); 

	// set 7seg data
	uint8_t val7= lcd7Char( stext2[ index ] )  ;
	pia7seg->write_pdrb( val7 ); 
	//pia7seg->write_pdrb(0xff ); 
	

 	index++;
	if ( index>16) index=0;
 }

void DISPLAY_WIL11A::setScore1( String _txt) {
	_txt += "                ";
	for (int i=0;i<8;i++){
		stext1[i+1]=_txt.charAt( i );
	}
} 

void DISPLAY_WIL11A::setScore2( String _txt) {
	_txt += "                ";
	for (int i=0;i<8;i++){
		stext1[i+9]=_txt.charAt( i );
	}
} 

void DISPLAY_WIL11A::setScore3( String _txt) {
	_txt += "                ";
	for (int i=0;i<8;i++){
		stext2[i+1]=_txt.charAt( i );
	}
} 

void DISPLAY_WIL11A::setScore4( String _txt) {
	_txt += "                ";
	for (int i=0;i<8;i++){
		stext2[i+9]=_txt.charAt( i );
	}
} 

 
 
void DISPLAY_WIL11A::text1( String _text1) {
	_text1 += "                ";
	for (int i=0;i<16;i++){
		stext1[i]=_text1.charAt( i );
	}
} 

void DISPLAY_WIL11A::text2( String _text2) {
	_text2 += "                ";
	for (int i=0;i<16;i++){
		stext2[i]=_text2.charAt( i );
	}
} 

