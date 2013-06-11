/**
 @file
 @brief control lamps
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

 Driver for several types of lamp. 
 - direct to io pins
 - matrix connected to pia
 @todo rgb
 @todo matrix and direct 23s17

*/
#ifndef LAMPS_h
#define LAMPS_h

	

//include "pinda.h"
//! baseclass to control lamps
class lamps : public PindaObj {
	public:
		lamps(void);
		/**
		* Interrupt is used for timed actions from the pinda interrupt timer
		*/
		virtual void interrupt(void); 
		/*
		* the serviceLoop is for maintenance tasks which are not time critical and should be in the main loop.
		*/
		virtual void serviceLoop(void);
		/**
		* show the current state of the lamps as text
		*/
		void show(void);
		/**
		* turn lamp on
		*
		* @param number lamp index from 0 to 63
		*/
		void on(uint8_t number);
		void off(uint8_t number);
		void toggle(uint8_t number);
		
		void set(uint8_t number,uint8_t state);
		void rowSet( const uint8_t row, const uint8_t data);
		void allSet( uint8_t row1,uint8_t row2,uint8_t row3,uint8_t row4,uint8_t row5,uint8_t row6,uint8_t row7,uint8_t row8);
		void allOff( void);
		void allOn( void);
		void setProperties(  Property * _properties );
	//protected:
		uint8_t lampdata[8]; //!< the standard lamp container
		//Lamp properties[64];
		 Property * properties;
		uint8_t currentRow;
};

//typedef void (lamps::* interrupt_ptr)(void);


/** demo lamps connected to the arduino
The 8 lamps are connected to PORTK on the arduino
The silly matrix layout is to use all crossings

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
class  lamps_demo : public lamps {
	public:
		lamps_demo(String _name="DEMO LAMPS");
		void interrupt(void);
	private:
}; // lamps_demo


/**
Driver class for Williams System 11a

The Williams System 11 lamps are multiplexed by one MC6821.
When no system11a display is used no lamps will light.
Then a blanking interrupt is needed to enable output.
*/
class  lamps_williams11a : public lamps  {
	public:
//	method intfunc;
			lamps_williams11a( MC6821 * piaref, String _name="SYS11A LAMPS");
			//void init( MC6821 * piaref);
			void interrupt();
	
		MC6821 * pia;
	private:

		//uint_8 row;

}; //lamps_williams11a
//typedef void (lamps_williams11a::* interrupt_williams11a_ptr)(void);


class  lamps_spi_matrix : public lamps  {
	public:
			lamps_spi_matrix( MCP23S17 * mcp, String _name="SPI MATRIX LAMPS");
			void interrupt();
	
	private:
		MCP23S17 * mcp;
}; //lamps_spi_matrix





//! class to control a single lamp
//! usefullness unknown
class LAMP : PindaObj {
	public:
	LAMP( lamps * _lampptr , uint8_t index, String name="UNNAMED") ;
		
		void on(void);
		void off(void);
		void toggle(void);
		void setName( String _name);
//		String getName( void );
	
	private:
		lamps * lampptr;
		uint8_t index;
		String name;
}; //LAMP



#endif //LAMPS_h