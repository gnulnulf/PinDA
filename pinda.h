/*
  PinDA.h - wrapper for all Pinball direct access parts

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

/**
* @file
* @brief Framework for controlling pinball hardware
* @details This framework controls pinball machine based on mc680x cpu's
* @author Arco van Geest <arco@appeltaart.mine.nu>
* @copyright GNU Public License.
*

* This file is a placeholder to include all seperate classes into a game.
* just use #include pinda.h
*/
#ifndef PINDA_h
#define PINDA_h
/******************************************************************************
* Sources
******************************************************************************/
/**
* @page Information sources
* - Microcomputer techniek - Stam technische boeken 1981 (dutch)
* - http://www.arduino.cc
* - http://www.pinwiki.com/wiki/index.php?title=Pinball_Part_Datasheets
* - http://www.pinballpcb.com/datasheets.html
* - http://appeltaart.mine.nu/wiki/index.php/PinDA (dutch)
*/
/******************************************************************************
* Includes
******************************************************************************/
// Enable printf ( must have printf_begin() )
//#include "printf.h"

//! Class to access the CPU(680n) BUS
#include "CPUBUS.h"

//! mc6821 access
#include "mc6821.h"

//!rom access 
#include "rom.h"

#endif /* PINDA_h */
