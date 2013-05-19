 
#include "pinda.h"
#include "lamps.h"

#include "switches.h"
#include "mc6821.h"

#ifdef ARDUINO
#include "Arduino.h"
#define println(line) Serial.println(line)
#define print(line) Serial.print(line)

#else
#include "arduino_compat.h"


#endif


switches::switches(void) {
	for (uint8_t i=0;i<8;i++) {
		switchdata[i]=0;
		switchdatalast[i]=0;
	}
} //switches::switches

void switches::interrupt( void ) {
	static uint8_t row=0;
	print("S");
	print(row);
	row++;
	if ( row>7) row=0;
} //switch::interrupt

void switches::serviceLoop(void){
	println("SwitchServiceLoop");
} //switches::serviceLoop

void switches::show(void){
	for (uint8_t i=0;i<8;i++) {
		printf("%02X ",switchdata[i]);
	}
	println();
} //switches::show

uint8_t switches::getRow(uint8_t row){
	return switchdata[ row & 0x7 ];
}


bool switches::isOn( uint8_t number ){
	return ( switchdata[ number >>3 ] & ( 1<< (number & 0x7) ) );

}

bool switches::flankup( uint8_t number) {
	if ( flankupdata[ number >>3 ] & ( 1<< (number & 0x7) ) ) {
		flankupdata[ number >>3 ] &= ~( 1<< (number & 0x7)) ;
		return true;
	}
	return false;
}

bool switches::flankdown( uint8_t number) {
	if ( flankdowndata[ number >>3 ] & ( 1<< (number & 0x7) ) ) {
		flankdowndata[ number >>3 ] &= ~( 1<< (number & 0x7)) ;
		return true;
	}
	return false;
}



void switches_demo::init(void) {
	println("switches_demo_init");
//demo switches met pullup
pinMode( SW1, INPUT);
digitalWrite( SW1,HIGH);
pinMode( SW2, INPUT);
digitalWrite( SW2,HIGH);
pinMode( SW3, INPUT);
digitalWrite( SW3,HIGH);
pinMode( SW4, INPUT);
digitalWrite( SW4,HIGH);
pinMode( SW5, INPUT);
digitalWrite( SW5,HIGH);
pinMode( SW6, INPUT);
digitalWrite( SW6,HIGH);
pinMode( SW7, INPUT);
digitalWrite( SW7,HIGH);
pinMode( SW8, INPUT);
digitalWrite( SW8,HIGH);
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
void switches_demo::interrupt(void) {
	static uint8_t row=0;
	uint8_t number=row * 9;
	uint8_t index[8] = { SW1,SW2,SW3,SW4,SW5,SW6,SW7,SW8};
	switchdatalast[ row ] = switchdata[ row ] ;

	if ( digitalRead( index[row]) == 0 ) {
		switchdata[ row ] |= ( 1<< row);
	} else {
		switchdata[ row ] &= ~( 1<< row);
	}

	// XOR the data to get the changes and only for the flank direction
	flankupdata[ row ] |= ( switchdatalast[ row ] ^ switchdata[ row ] ) & switchdata[ row ] ;
	flankdowndata[ row ] |= ( switchdatalast[ row ] ^ switchdata[ row ] ) & switchdatalast[ row ] ;
	

	
	row++;
	if ( row>7) row=0;
} // switches_demo::interrupt


void switches_williams11a::init( MC6821 * piaptr ) {
	println("switches_williams11a_init ");
	pia=piaptr;
	
	pia->write_ddra(0); // A ingang  
	pia->write_ddrb(255);  //B uitgang
	pia->write_pdra(0x00); 
	pia->write_pdrb(0x00); 

//	pia->write_pdrb(0x01); 
//	pia->write_pdra(0x55); 
}

void switches_williams11a::interrupt( void ) {
	static uint8_t row=0;
//	print("L");
//	print(row);
	switchdatalast[ row ] = switchdata[ row ] ;
	switchdata[ row ] =  pia->read_pdra() ;
    pia->write_pdrb( ( 1 << row ) );  // set row

	// XOR the data to get the changes and only for the flank direction
	flankupdata[ row ] |= ( switchdatalast[ row ] ^ switchdata[ row ] ) & switchdata[ row ] ;
	flankdowndata[ row ] |= ( switchdatalast[ row ] ^ switchdata[ row ] ) & switchdatalast[ row ] ;
	
	

	row++;
	if ( row>7) row=0;
}

  
  
  
  
  
  
  
  
 


