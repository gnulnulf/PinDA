/**
 @file
 @brief interface display systems connected to PinDA
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

 @date       20130521 Initial documented version

Driver for displays connected to a PinDA system
at the moment only the williams system 11a display is implemented
maybe a driver to a simple lcd would be nice.
probably dmd can be done when using the original hardware.

*/
#ifndef DISPLAY_h
#define DISPLAY_h

#include "pinda.h"
#include "mc6821.h"


//! base class for displays
class DISPLAYCLASS : public PindaObj {
	//protected:
		
	public:
		//void test( void);
	//		DISPLAY ( void );
//		void interrupt( void);
 };

 //! display driver for Williams System 11A displays
 class DISPLAY_WIL11A : public DISPLAYCLASS {
	public:
		DISPLAY_WIL11A( MC6821 * _piaalfa, MC6821 * _pia7seg, MC6821 * _piawidgets );
		void interrupt(void);
		void text1( String _text1 );
		void text1a( String _text1 );
		void text2( String _text2 );
		void text2a( String _text2 );
		void setScore1( String _txt );
		void setScore2( String _txt );
		void setScore3( String _txt );
		void setScore4( String _txt );
		void enableBlink(void);
		void disable( void);
		void blinkTime( uint8_t _blink );
	private:
		MC6821 * piaalfa;
		MC6821 * pia7seg;
		MC6821 * piawidget;
		char stext1[16]; // upper displays
		char stext1a[16]; // upper displays blinked
		char stext2[16]; // lower displays
		char stext2a[16]; // lower displays blinked

		uint32_t score3;
		uint32_t score4;
		bool blink;
		uint8_t blinkcounter;
		uint8_t blinktime;
		uint8_t index;
 };


#endif //DISPLAY_h
