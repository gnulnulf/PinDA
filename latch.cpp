/**
 @file 

 @see latch.h for details
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

 @brief control latched IO
 
*/ 
#include "pinda.h"
#include "latch.h"

LATCH8::LATCH8(
		CPUBUSClass * _bus,
		unsigned int _address,
		String _name
	) :
	state(0),
	bus(_bus),
	address(_address)
{
	name=_name;


}

void LATCH8::all(uint8_t data) {
	state = data;
	bus->write(address,state);
}

void LATCH8::on(uint8_t bit) {
	state |= (1<<bit);
	bus->write(address,state);
}

void LATCH8::off(uint8_t bit) {
	state &= ~(1<<bit);
	bus->write(address,state);
}

void LATCH8::toggle(uint8_t bit) {
	(state & (1<<bit) )?off( bit ):on( bit );
}

bool LATCH8::isOn(uint8_t bit) {
	return (state & (1<<bit) );
}
