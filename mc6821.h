/**
 @file

 @brief interface to the mc6821 IO on the 8bit 68xx memory bus

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

The MC6821 IO chip is used in a lot of pinball machines.
The chip has a strange register access mechanism.


*/ 
#ifndef MC6821_h
#define MC6821_h

// --------------------------------------------------------
// Includes
// --------------------------------------------------------
#include "CPUBUS.h"

//! usable ports on the mc6821.
//! The ports and special IO ports are concattenated.
enum pia_io { 
	PIA_PA0=0,PIA_PA1,PIA_PA2,PIA_PA3,PIA_PA4,PIA_PA5,PIA_PA6,PIA_PA7,
	PIA_PB0=8,PIA_PB1,PIA_PB2,PIA_PB3,PIA_PB4,PIA_PB5,PIA_PB6,PIA_PB7,
	PIA_CA1=17,PIA_CA2=18,
	PIA_CB1=19,PIA_CB2=20
	};
//get int

//! class to control the MC6821 IO chip
//! todo CRA/CRB interrupt implementation. store int-flag on read as flag?
class MC6821 : public PindaObj{
  public:
	//! constructor
	MC6821(  
		CPUBUSClass *busptr,			//!< pointer to the CPUBUS object
		int addr , 						//!< address on the CPUBUS
		String _name="MC6821 UNNAMED"	//!< name of the MC6821
	);
    
	void outputA(void);
	void outputB(void);
	void allOnA(void);
	void allOnB(void);
	void allOffA(void);
	void allOffB(void);
	void inputA(void);
	void inputB(void);

//	void outputCRA2(void);
//	void outputCRB2(void);
//	void inputCRA2(void);
//	void inputCRB2(void);
//	void onCRA2(void);
//	void offCRA2(void);
//	void onCRB2(void);
//	void offCRB2(void);


	//! turn pin on the mc6821 off
	//! @param number of pin on the mc6821 see enum @ref pia_io
	void on( uint8_t number);

	//! turn pin off the mc6821 off
	//! @param number of pin on the mc6821 see enum @ref pia_io
	void off( uint8_t number);
	
	//! toggle pin on the mc6821
	//! @param number of pin on the mc6821 see enum @ref pia_io
	void toggle(uint8_t number);
	
	//! get the pin state on the mc6821
	//! @param number of pin on the mc6821 see enum @ref pia_io
	//! @returns pin state
	bool isOn( uint8_t pin) ;

	//! turn pin into input
	//! @param number of pin on the mc6821 see enum @ref pia_io
	void input(uint8_t number);

	//! turn pin into output
	//! @param number of pin on the mc6821 see enum @ref pia_io
	void output(uint8_t number);
	

	
	//void init(  CPUBUSClass *busptr ,int addr );
//	uint8_t read( const int & address );
//	void write (const int & address, const uint8_t & data);

	//! write byte to the crb
	//! @param data 8bit data for the control register crb
	void write_cra( const uint8_t & data );
	//! write byte to the crb
	//! @param data 8bit data for the control register crb
	void write_crb( const uint8_t & data );

	//! write byte to the ddrb
	//! @param data 8bit data for the data direction register ddrb
	void write_ddra(const uint8_t & data);

	//! write byte to the ddrb
	//! @param data 8bit data for the data direction register ddrb
	void write_ddrb(const uint8_t & data);

	//! write byte to the pdra
	//! @param data 8bit data for the io port pdra
	void write_pdra(const uint8_t & data);
	
	//! write byte to the pdrb
	//! @param data 8bit data for the io port pdrb
	void write_pdrb(const uint8_t & data);

	//! read the pdra register
	//! @returns the pdra contents as a byte
	uint8_t read_pdra();

	//! read the pdrb register
	//! @returns the pdrb contents as a byte
	uint8_t read_pdrb();

	//! read the cra register
	//! @returns the cra contents as a byte
	uint8_t read_cra();
	
	//! read the crb register
	//! @returns the crb contents as a byte
	uint8_t read_crb();

	//! set the ddra active
	void select_ddra();
	//! set the ddrb active
	void select_ddrb();
	//! set the pdra active
	void select_pdra();
	//! set the pdrb active
	void select_pdrb();
	
protected:
    CPUBUSClass * bus;		//!< pointer to the cpubus object
    int pia_addr;			//!< address of the mc6821 on the cpubus
//	String name;
	int cra;				//!< address of the CRA
	int crb;				//!< address of the CRB
	int ddra;				//!< address of the DDRA
	int ddrb;				//!< address of the DDRB
	int pdra;				//!< address of the PDRA
	int pdrb;				//!< address of the PDRB
	uint8_t cra_sv;			//!< cache for the CRA register
	uint8_t crb_sv;			//!< cache for the CRB register

	uint8_t ddra_sv;		//!< cache for the DDRA register
	uint8_t ddrb_sv;		//!< cache for the DDRB register

	uint8_t pdra_sv;		//!< cache for the PDRA register
	uint8_t pdrb_sv;		//!< cache for the PDRB register
	
  
};



#endif /* MC6821_h */