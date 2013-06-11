/**
 @file 

 @see lamps.h for details
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

 @brief Control lamps
 
*/ 
#include "pinda.h"
#include "cpubus.h"
#include "lamps.h"

#include "mc6821.h"

#ifdef ARDUINO
#include "Arduino.h"
#define println(line) Serial.println(line)
#define print(line) Serial.print(line)

#else
#include "arduino_compat.h"


#endif



void lamps::setProperties(  Property * _properties ){
		properties=_properties;
}
		


LAMP::LAMP( lamps * _lampptr , uint8_t _index, String _name) : 
		lampptr(_lampptr),
		name(_name),
		index(_index) {
}

void LAMP::on( void){
	lampptr->on( index );
}

void LAMP::off( void){
	lampptr->off( index );
}

void LAMP::toggle( void){
	lampptr->toggle( index );
}


 lamps::lamps(void) {
	for (uint8_t i=0;i<8;i++) {
		lampdata[i]=0;
	}
} //lamps::lamps

void lamps::interrupt( void ) {
	static uint8_t row=0;
	print("L");
	//print(row);
	row++;
	if ( row>7) row=0;
} //lamps::interrupt

void lamps::serviceLoop(void){
	println("ServiceLoop");
} //lamps::serviceLoop

void lamps::show(void){
	for (uint8_t i=0;i<8;i++) {
		printf("%02X ",lampdata[i]);
	}
	println("");
} //lamps::show

void lamps::on(uint8_t number) {
	lampdata[ (number>>3) & 0x7 ] |= (1<< (number &0x7)); 
} //lamps::on

void lamps::off(uint8_t number) {
	lampdata[ (number>>3) & 0x7 ] &= ~(1<< (number &0x7)); 
} //lamps::off

void lamps::toggle(uint8_t number) {
	lampdata[ (number>>3) & 0x7 ] ^= (1<< (number &0x7)); 
} //lamps::toggle


void lamps::set(uint8_t number,uint8_t state) {
	if ( state ) {
		lampdata[ (number>>3) & 0x7 ] |= (1<< (number &0x7)); 
	} else {
		lampdata[ (number>>3) & 0x7 ] &= ~(1<< (number &0x7)); 
	}
} //lamps::set

void lamps::allSet(uint8_t row1,uint8_t row2,uint8_t row3,uint8_t row4,uint8_t row5,uint8_t row6,uint8_t row7,uint8_t row8) {
	lampdata[0]=row1;
	lampdata[1]=row2;
	lampdata[2]=row3;
	lampdata[3]=row4;
	lampdata[4]=row5;
	lampdata[5]=row6;
	lampdata[6]=row7;
} //lamps::allSet

void lamps::allOff(void) {
	lampdata[0]=0;
	lampdata[1]=0;
	lampdata[2]=0;
	lampdata[3]=0;
	lampdata[4]=0;
	lampdata[5]=0;
	lampdata[6]=0;
} //lamps::allOff

void lamps::allOn(void) {
	lampdata[0]=0xff;
	lampdata[1]=0xff;
	lampdata[2]=0xff;
	lampdata[3]=0xff;
	lampdata[4]=0xff;
	lampdata[5]=0xff;
	lampdata[6]=0xff;
} //lamps::allOn


void lamps::rowSet( const uint8_t row, const uint8_t  data) {
	lampdata[ row & 0x7 ] = data;
}




#ifdef ARDUINO
lamps_demo::lamps_demo(String _name) {
	objName=_name;
	DDRK = 0xff;
	// low is on...
	PORTK = 0xff;
	PORTK=0x55;
	pinda.AddInterrupt ( this , 2);
} // lamps_demo::init

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
void lamps_demo::interrupt(void) {
	static uint8_t row=0;
	if ( lampdata[ row ] & ( 1<< row) ) {
		PORTK = ~(1<<row);
	} else {
		PORTK = 0xff;
	}
	row++;
	if ( row>7) row=0;
} // lamps_demo::interrupt
#endif //lamps_demo



lamps_williams11a::lamps_williams11a( MC6821 * piaptr ,String _name) {
	objName=_name;
	pia=piaptr;
	
	pia->write_ddra(255); // A uitgang  
	pia->write_ddrb(255);  //B uitgang
	pia->write_pdra(0xff); 
	pia->write_pdrb(0x00); 

	pia->write_pdrb(0x01); 
	pia->write_pdra(0x55); 
	
	

//	typedef void (lamps::* interrupt_ptr)(void);
   // FuncDelegate f_delegate;
	//f_delegate = MakeDelegate(this, &lamps_williams11a::interrupt);
	//delegate d = MakeDelegate(this, &lamps_williams11a::interrupt);


//	interrupt_williams11a_ptr p= &lamps_williams11a::interrupt;
//	pindaAddInterrupt( this->*p ,5);

//void (lamps_williams11a:: *f)();
//f=((lamps_williams11a *)interrupt_williams11a_ptr)->interrupt;

	pinda.AddInterrupt ( this , 1);
}

/*
http://www.codeproject.com/Articles/7150/Member-Function-Pointers-and-the-Fastest-Possible
class SomeClass;

typedef void (SomeClass::* SomeClassFunction)(void);

void Invoke(SomeClass *pClass, SomeClassFunction funcptr) {
  (pClass->*funcptr)(); };

*/
void lamps_williams11a::interrupt( void ) {
	static uint8_t row=0;

    pia->write_pdra( 0xff  );  // clear lamps
    pia->write_pdrb( ( 1 << row ) );  // set row
    pia->write_pdra( ~ lampdata[ row ]  );  // set inverted output

	row++;
	if ( row>7) row=0;
}

lamps_spi_matrix::lamps_spi_matrix( MCP23S17 * _mcp ,String _name) {
	objName=_name;
	mcp=_mcp;
	mcp->port(0x0000);
	mcp->pinMode(true);
//	mcp->ddrB(0xff);
	mcp->port(0x0000);
	
	//	mcp->pinMode( true );
		pinda.AddInterrupt ( this , 1);
}




void lamps_spi_matrix::interrupt( void ) {
	static uint8_t row=0;
	//mcp->portA(row);
    //mcp->portB( 0xff  );  // clear lamps
    //mcp->portA( ( 1 << row ) );  // set row
    //mcp->portB( ~ lampdata[ row ]  );  // set inverted output
	mcp->port(0x0000);
	mcp->port(  ( ( 1 << row ) << 8 ) |   ~ lampdata[ row ] ); 
//	mcp->portA( lampdata[0]);
//	mcp->portB( lampdata[1]);
	
	
	
	row++;
	if ( row>7) row=0;
}
