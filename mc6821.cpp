/**
 @file 

 @see mc6821.h for details
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

 @brief Interface to the 6821/6820 PIA

*/ 

/*****************************************************************************
* Includes
******************************************************************************/
# include "pinda.h"
# include "cpubus.h"
# include "mc6821.h"

/*****************************************************************************
* Defines
******************************************************************************/
#define CA1_CTL0 	0
#define CA1_CTL1 	1
#define DDRA_XS 	2
#define CA2_CTL0 	3
#define CA2_CTL1 	4
#define CA2_CTL2 	5
#define IRQA2 		6
#define IRQA1 		7

#define CB1_CTL0 	0
#define CB1_CTL1 	1
#define DDRB_XS 	2
#define CB2_CTL0 	3
#define CB2_CTL1 	4
#define CB2_CTL2 	5
#define IRQB2 		6
#define IRQB1 		7

/******************************************************************************
 * Base class
 ******************************************************************************/
MC6821::MC6821(  CPUBUSClass *busptr ,int addr , String _name) {
	objName=_name;
	pia_addr = addr; 
	cra=addr+1;
	crb=addr+3;
	ddra=addr;
	ddrb=addr+2;
	pdra=ddra;
	pdrb=ddrb;
	bus = busptr;

	write_cra(0); 	//clear cra
	write_crb(0); 	//clear crb
	write_ddra(0);	//inputs
	write_ddrb(0); 	//inputs
	
   
} //MC6821::MC6821
  
void MC6821::outputA( void) {
	ddra_sv=255;
	write_ddra(ddra_sv); 
} //MC6821::outputA

void MC6821::outputB( void) {
	ddrb_sv=255;
	write_ddrb(255); 
} //MC6821::outputB

void MC6821::inputA( void) {
  write_ddra(0); 
} //MC6821::inputA

void MC6821::inputB( void) {
  write_ddrb(0); 
}

void MC6821::allOnA( void) {
  write_pdra(255); 
} //MC6821::allOnA

void MC6821::allOnB( void) {
  write_pdrb(255); 
} // MC6821::allOnB

void MC6821::allOffA( void) {
  write_pdra(0); 
}  // MC6821::allOffA

void MC6821::allOffB( void) {
  write_pdrb(0); 
} // MC6821::allOffB

void MC6821::on ( uint8_t pin ) {
	if ( pin < 8) {
		pdra_sv |= (1<<pin);
		write_pdra( pdra_sv);
	} else {
		if ( pin < 16 ) {
			pdrb_sv |= 1<<(pin-8);
			write_pdrb( pdrb_sv);
		}
	}
	if ( pin == 18 ) {
		cra_sv |= (1<<3);
		write_cra( cra_sv);
	}
	if ( pin == 20 ) {
		crb_sv |= (1<<3);
		write_crb( crb_sv);
	}
	
} //MC6821::on

void MC6821::off ( uint8_t pin ) {
	if ( pin < 8) {
		pdra_sv &= ~(1<<pin);
		write_pdra( pdra_sv);
	} else {
		if ( pin < 16 ) {
			pdrb_sv &= ~(1<<(pin-8));
			write_pdrb( pdrb_sv);
		}
	}
	if ( pin == 18 ) {
		cra_sv &= ~(1<<3);
		write_cra( cra_sv);
	}
	if ( pin == 20 ) {
		crb_sv &= ~(1<<3);
		write_crb( crb_sv);
	}
} //MC6821::off 



// turn pin into output
void MC6821::output ( uint8_t pin ) {
	if ( pin < 8) {
		ddra_sv |= (1<<pin);
		write_ddra( pdra_sv);
	} else {
		if ( pin < 16 ) {
			ddrb_sv |= (1<<(pin-8));
			write_ddrb( pdrb_sv);
		}
	}
	if ( pin == 18 ) {
		cra_sv |= (1<<4)|(1<<5);
		write_cra( cra_sv);
	}
	if ( pin == 20 ) {
		crb_sv |= (1<<4)|(1<<5);
		write_crb( crb_sv);
	}
} //MC6821::output

// turn pin into input
void MC6821::input ( uint8_t pin ) {
	if ( pin < 8) {
		ddra_sv &= ~(1<<pin);
		write_ddra( pdra_sv);
	} else {
		if ( pin < 16 ) {
			ddrb_sv &= ~(1<<(pin-8));
			write_ddrb( pdrb_sv);
		}
	}
	if ( pin == 18 ) {
		cra_sv &= ~((1<<4)|(1<<5));
		write_cra( cra_sv);
	}
	if ( pin == 20 ) {
		crb_sv &= ~((1<<4)|(1<<5));
		write_crb( crb_sv);
	}
} //  MC6821::input




void MC6821::toggle ( uint8_t pin ) {
	if ( pin < 8) {
		pdra_sv ^= (1<<pin);
		write_pdra( pdra_sv);
	} else {
		if ( pin < 16 ) {
			pdrb_sv ^= (1<<(pin-8));
			write_pdrb( pdrb_sv);
		}
	}
	if ( pin == 18 ) {
		cra_sv ^= ~(1<<3);
		write_cra( cra_sv );
	}
	if ( pin == 20 ) {
		crb_sv ^= ~(1<<3);
		write_crb( crb_sv );
	}
} //MC6821::toggle 

bool MC6821::isOn( uint8_t pin) {
	if (pin<8) {
		// when defined as output, see cache 
		if (ddra_sv & (1<<pin) ) {
			return ( pdra_sv & (1<pin) )?true:false;
		} else {
			return ( read_pdra() & (1<pin) )?true:false;
			
		}
	} else {
		if (pin<16) {
			// when defined as output, see cache 
			if (( ddrb_sv ) & (1<<(pin-8)) ) {
				return ( pdrb_sv & (1<<(pin-8) ))?true:false;
			} else {
				return ( read_pdrb() & (1<<(pin-8)) )?true:false;
			}
		}
	}
	if (pin==17) {
			return ( read_cra() & (1<<6) )?true:false;
	}
	if (pin==18) {
			return ( read_cra() & (1<<7) )?true:false;
	}
	if (pin==19) {
			return ( read_crb() & (1<<6) )?true:false;
	}
	if (pin==20) {
			return ( read_crb() & (1<<7) )?true:false;
	}
	return false;
} //MC6821::isOn





void MC6821::write_cra( const uint8_t & data ) {
	cra_sv=data;
	bus->write( cra ,data);
} //write_cra

void MC6821::write_crb( const uint8_t & data ) {
	crb_sv=data;
	bus->write( crb ,data);
}

void MC6821::write_ddra( const uint8_t & data){
	cra_sv &= ~(1<<DDRA_XS);
	bus->write( cra ,cra_sv);
	ddra_sv=data;
	bus->write( ddra ,ddra_sv);
}
void MC6821::write_ddrb( const uint8_t & data){
	crb_sv &= ~(1<<DDRB_XS);
	bus->write( crb ,crb_sv);
	ddrb_sv=data;
	bus->write( ddrb ,ddrb_sv);

}
void MC6821::write_pdra( const uint8_t & data){
	cra_sv |= (1<<DDRA_XS);
	bus->write( cra ,cra_sv);
	pdra_sv=data;
	bus->write( pdra ,pdra_sv);
}
void MC6821::write_pdrb( const uint8_t & data){
	crb_sv |= (1<<DDRB_XS);
	bus->write( crb ,crb_sv);
	pdrb_sv=data;
	bus->write( pdrb ,pdrb_sv);
}

uint8_t  MC6821::read_pdra(){
	cra_sv |= (1<<DDRA_XS);
	bus->write( cra ,cra_sv);
	pdra_sv=bus->read( pdra );
	return pdra_sv;
}

uint8_t  MC6821::read_pdrb(){
	crb_sv |= (1<<DDRB_XS);
	bus->write( crb ,crb_sv);
	pdrb_sv=bus->read( pdrb);
	return pdrb_sv;
}

uint8_t  MC6821::read_cra(){
	return bus->read( cra );
}

uint8_t  MC6821::read_crb(){
	return bus->read( crb );
}

void MC6821::select_ddra(){
	cra_sv &= ~(1<<DDRA_XS);
	bus->write( cra ,cra_sv);
}
void MC6821::select_ddrb(){
	crb_sv &= ~(1<<DDRB_XS);
	bus->write( crb ,crb_sv);
}
void MC6821::select_pdra(){
	cra_sv |= (1<<DDRA_XS);
	bus->write( cra ,cra_sv);
}

void MC6821::select_pdrb(){
	crb_sv |= (1<<DDRB_XS);
	bus->write( crb ,crb_sv);
}  


/*
uint8_t MC6821::read( const int & address ){
	return 0;
}

void MC6821::write ( const int & address,  const uint8_t & data){

}
*/

