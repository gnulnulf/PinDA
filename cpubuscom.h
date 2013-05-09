/*
  CPUBUSCOM.h - protocol definition between raspberry and arduino-slave

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

#ifndef CPUBUSCOM_h
#define CPUBUSCOM_h

/**
* protocol

start {
end }
lowercase get
uppercase set
message cannot contain {}

game
====
enable solenoids
disable solenoids

F set flashers


L set lamps
L set animation
start animation
stop animation

s get switches
S
E set event



diagnostics
===========
dR read byte
DR read reply byte
dW write byte
DW write reply byte

{dRESET} reset
{DRESETOK} reset handshake
{DACK}
{DERROR:STRING}

{dSTATE} get state
{DSTATE:STRING} send state

{dMEMORYMAP}
{DMEMORYMAP:STRING} get memorymap
dLAMPS get lamps



*
*


/******************************************************************************
 * Includes
 ******************************************************************************/
 
/******************************************************************************
* Definitions
******************************************************************************/




#endif /* CPUBUSCOM_h */



 