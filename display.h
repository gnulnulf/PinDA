#ifndef DISPLAY_h
#define DISPLAY_h

#include "pinda.h"
#include "mc6821.h"



class DISPLAYCLASS : public PindaObj {
	//protected:
		
	public:
		void test( void);
	//		DISPLAY ( void );
//		void interrupt( void);
 };

 
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