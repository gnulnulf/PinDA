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



class MC6821 {
  public:
	void init(  CPUBUSClass *busptr ,int addr );
	uint8_t read( int address );
	void write (int address, uint8_t data);
	void write_cra( uint8_t data );
	void write_crb( uint8_t data );
	void write_ddra(uint8_t data);
	void write_ddrb(uint8_t data);
	void write_pdra(uint8_t data);
	void write_pdrb(uint8_t data);
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