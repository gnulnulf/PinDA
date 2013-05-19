/*
  mc6821.h - interface to the 8bit 68xx memory bus

  (C) Copyright 2013 Arco van Geest <arco@appeltaart.mine.nu> All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef MC6821_h
#define MC6821_h

/*****************************************************************************
* Includes
******************************************************************************/
#include "CPUBUS.h"

 enum pia_io { 
	PIA_PA0=0,PIA_PA1,PIA_PA2,PIA_PA3,PIA_PA4,PIA_PA5,PIA_PA6,PIA_PA7,
	PIA_PB0=8,PIA_PB1,PIA_PB2,PIA_PB3,PIA_PB4,PIA_PB5,PIA_PB6,PIA_PB7,
	PIA_CA1=17,PIA_CA2=18,
	PIA_CB1=19,PIA_CB2=20
	};


class MC6821 {
  public:
	MC6821( void );
	MC6821(  CPUBUSClass *busptr ,int addr , String _name="UNNAMED");
    
	void outputA(void);
	void outputB(void);
	void allOnA(void);
	void allOnB(void);
	void allOffA(void);
	void allOffB(void);
	void inputA(void);
	void inputB(void);
	void outputCRA2(void);
	void outputCRB2(void);
	void inputCRA2(void);
	void inputCRB2(void);
	void onCRA2(void);
	void offCRA2(void);
	void onCRB2(void);
	void offCRB2(void);
	//get int
	//get CRA1/2  CRB1/2
	//0-7=A 8-15=B 16=CRA1 17=CRA2 18=CRB1 19=CRB2
	void on( uint8_t number);
	void off( uint8_t number);
	void toggle(uint8_t number);
	bool isOn( uint8_t pin) ;
	void output(uint8_t number);
	
	void init(  CPUBUSClass *busptr ,int addr );
	uint8_t read( const int & address );
	void write (const int & address, const uint8_t & data);
	void write_cra( const uint8_t & data );
	void write_crb( const uint8_t & data );
	void write_ddra(const uint8_t & data);
	void write_ddrb(const uint8_t & data);
	void write_pdra(const uint8_t & data);
	void write_pdrb(const uint8_t & data);
	uint8_t read_pdra();
	uint8_t read_pdrb();
	uint8_t read_cra();
	uint8_t read_crb();

	void select_ddra();
	void select_ddrb();
	void select_pdra();
	void select_pdrb();
	
	//  protected:
    CPUBUSClass * bus;
    int pia_addr;
	String name;
	int cra;
	int crb;
	int ddra;
	int ddrb;
	int pdra;
	int pdrb;
	uint8_t cra_sv;
	uint8_t crb_sv;

	uint8_t ddra_sv;
	uint8_t ddrb_sv;

	uint8_t pdra_sv;
	uint8_t pdrb_sv;
	
  
};



#endif /* MC6821_h */