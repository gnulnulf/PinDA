/**
 @file 

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

 @brief Example of combining a Williams F14-Tomcat with the demo on the arduino
 
*/ 

#ifdef RASPBERRY
#include <iostream>
#include "rpi/compatibility.h" 
#define MCP_SELECT 8
#define spio spi
#include "rpi/spi.h"
//#include <linux/spi/spidev.h>

#endif


#ifdef ARDUINO
#include "printf.h"
#include <SPI.h>
#define MCP_SELECT 53
#endif

#include "pinda.h" 


#ifdef ARDUINO
#include "printf.h"
#include <SPI.h>
#endif
Pinda pinda;
const bool slave=false;
/*

	loc_unknown, //!< location not known
	loc_playfield,	//!< part is on playfield
	loc_head,		//!< part is in head
	loc_body,		//!< part is in body (non playfield)
	loc_door,		//!< part is on coin door 
	loc_top			//!< part is located on top of the head

	colour_unknown,
	colour_white,
	colour_yellow,
	colour_orange,
	colour_red,
	colour_blue,
	colour_green,
	colour_purple
*/

const int tomcat_l[64][6]={
  {57, 200, 1, colour_red,		loc_playfield  },
  {61, 209, 1, colour_white,	loc_playfield  },
  {67, 200, 1, colour_blue,  	loc_playfield  },
  {58,  35, 1, colour_orange,  loc_playfield  },
  {57, 120, 1, colour_orange,  loc_playfield  },
  {61, 124, 1, colour_white,  	loc_playfield  },
  {65, 120, 1, colour_orange,  loc_playfield  },
  { 7,  66, 1, colour_white,  	loc_playfield  },
  {43,  54, 1, colour_white,  	loc_playfield  },
  {46,  60, 1, colour_white,  	loc_playfield  },
  {52,  58, 1, colour_white,  	loc_playfield  },
  {57,  62, 1, colour_white,  	loc_playfield  },
  {61,  58, 1, colour_white,  	loc_playfield  },
  {69,  60, 1, colour_white,  	loc_playfield  },
  {71,  54, 1, colour_red,  	loc_playfield  },
  {57,  48, 1, colour_blue,  	loc_playfield  },
  {67,  77, 1, colour_blue,  	loc_playfield  },
  {71,  87, 1, colour_blue,  	loc_playfield  },
  {76,  98, 1, colour_blue,  	loc_playfield  },
  {81, 109, 1, colour_blue,  	loc_playfield  },
  {85, 118, 1, colour_blue,  	loc_playfield  },
  {89, 128, 1, colour_blue,  	loc_playfield  },
  {94, 139, 1, colour_blue,  	loc_playfield  },
  {0, 81, 2, colour_red,  	loc_playfield  },
  {  		47,  77,  1,  colour_red,  loc_playfield  },
  {  44,  88,  1,  colour_red,  loc_playfield  },
  {  40,  98,  1,  colour_red,  loc_playfield  },
  {  37,  109,  1,  colour_red,  loc_playfield  },
  {  33,  121,  1,  colour_red,  loc_playfield  },
  {  29,  132,  1,  colour_red,  loc_playfield  },
  {  26,  143,  1,  colour_red,  loc_playfield  },
  {  27,  205,  1,  colour_orange,  loc_playfield  },
  { 24,  106,  1,  colour_red,  loc_playfield  },
  {24, 115,  1,  colour_red,  loc_playfield  },
  {23, 125,  1,  colour_red,  loc_playfield  },
  {93, 101,  1,  colour_blue,  loc_playfield  },
  {95, 111,  1,  colour_blue,  loc_playfield  },
  {97, 121,  1,  colour_blue,  loc_playfield  },
  {0,  87,  2,  colour_white,  loc_playfield  },
  {108,  177,  1,  colour_blue,  loc_playfield  },
  {46, 136,  1,  colour_white,  loc_playfield  },
  {43, 142,  1,  colour_white,  loc_playfield  },
  {40, 148,  1,  colour_white,  loc_playfield  },
  {76, 136,  1,  colour_white,  loc_playfield  },
  {79, 142,  1,  colour_white,  loc_playfield  },
  {82, 148,  1,  colour_white,  loc_playfield  },
  {104,  164,  1,  colour_white,  loc_playfield  },
  {98,  151,  1,  colour_orange,  loc_playfield  },
  { 48,  204,  1,  colour_red,  loc_playfield  },
  { 52,  210,  1,  colour_red,  loc_playfield  },
  { 55,  216,  1,  colour_red,  loc_playfield  },
  { 76,  204,  1,  colour_blue,  loc_playfield  },
  { 72,  210,  1,  colour_blue,  loc_playfield  },
  { 69,  216,  1,  colour_blue,  loc_playfield  },
  { 95,  197,  1,  colour_blue,  loc_playfield  },
  {  98,  210,  1,  colour_red,  loc_playfield  },
  {  16,  206,  1,  colour_red,  loc_playfield  },
  {  16,  195,  1,  colour_red,  loc_playfield  },
  {  16,  176,  1,  colour_red,  loc_playfield  },
  { 16,  222,  1,  colour_blue,  loc_playfield  },
  {  16,  201,  1,  colour_blue,  loc_playfield  },
  {  16,  181,  1,  colour_blue,  loc_playfield  },
  {  167,  1,  colour_white,  loc_playfield  },
  {  23,  153,  1,  colour_orange,  loc_playfield  }
};


/*
PROGMEM Property tomcat_lamps[64]={
  {0,  "LITES LOCK ON", 57, 200, 1, colour_red,		loc_playfield  },
  {1,  "LITES RELEASE", 61, 209, 1, colour_white,	loc_playfield  },
  {2,  "HOT STREAK",    67, 200, 1, colour_blue,  	loc_playfield  },
  {3,  "FLY AGAIN",     58,  35, 1, colour_orange,  loc_playfield  },
  {4,  "RESCUE (LC)",   57, 120, 1, colour_orange,  loc_playfield  },
  {5,  "KILL (C)",      61, 124, 1, colour_white,  	loc_playfield  },
  {6,  "RESCUE (RC)",   65, 120, 1, colour_orange,  loc_playfield  },
  {7,  "RESCUE (L)",     7,  66, 1, colour_white,  	loc_playfield  },
  {8,  "ALPHA KILL",    43,  54, 1, colour_white,  	loc_playfield  },
  {9,  "BRAVO KILL",    46,  60, 1, colour_white,  	loc_playfield  },
  {10,  "CHARLIE KILL", 52,  58, 1, colour_white,  	loc_playfield  },
  {11,  "DELTA KILL",   57,  62, 1, colour_white,  	loc_playfield  },
  {12,  "ECHO KILL",    61,  58, 1, colour_white,  	loc_playfield  },
  {13,  "FOX KILL",     69,  60, 1, colour_white,  	loc_playfield  },
  {14,  "GOLF KILL",    71,  54, 1, colour_red,  	loc_playfield  },
  {15,  "FLIGHT INSURE",57,  48, 1, colour_blue,  	loc_playfield  },
  {16,  "1K",           67,  77, 1, colour_blue,  	loc_playfield  },
  {17,  "2K",           71,  87, 1, colour_blue,  	loc_playfield  },
  {18,  "4K",           76,  98, 1, colour_blue,  	loc_playfield  },
  {19,  "8K",           81, 109, 1, colour_blue,  	loc_playfield  },
  {20,  "16K",          85, 118, 1, colour_blue,  	loc_playfield  },
  {21,  "32K",          89, 128, 1, colour_blue,  	loc_playfield  },
  {22,  "64K",          94, 139, 1, colour_blue,  	loc_playfield  },
  {23,  "SPECIAL",      0, 81, 2, colour_red,  	loc_playfield  },
  {24,  "2X",  		47,  77,  1,  colour_red,  loc_playfield  },
  {25,  "3X",  44,  88,  1,  colour_red,  loc_playfield  },
  {26,  "4X",  40,  98,  1,  colour_red,  loc_playfield  },
  {27,  "5X",  37,  109,  1,  colour_red,  loc_playfield  },
  {28,  "6X",  33,  121,  1,  colour_red,  loc_playfield  },
  {29,  "7X",  29,  132,  1,  colour_red,  loc_playfield  },
  {30,  "8X",  26,  143,  1,  colour_red,  loc_playfield  },
  {31,  "BONUS X (LEFT)",  27,  205,  1,  colour_orange,  loc_playfield  },
  {32,  "T (LOWER L)",  24,  106,  1,  colour_red,  loc_playfield  },
  {33,  "O (LOWER L)", 24, 115,  1,  colour_red,  loc_playfield  },
  {34,  "M (LOWER L)", 23, 125,  1,  colour_red,  loc_playfield  },
  {35,  "T (LOWER R)", 93, 101,  1,  colour_blue,  loc_playfield  },
  {36,  "A (LOWER R)", 95, 111,  1,  colour_blue,  loc_playfield  },
  {37,  "C (LOWER R)", 97, 121,  1,  colour_blue,  loc_playfield  },
  {38,  "LITES KILL",  0,  87,  2,  colour_white,  loc_playfield  },
  {39,  "LANDING",     108,  177,  1,  colour_blue,  loc_playfield  },
  {40,  "3 TARGET",    46, 136,  1,  colour_white,  loc_playfield  },
  {41,  "2 TARGET",    43, 142,  1,  colour_white,  loc_playfield  },
  {42,  "1 TARGET",    40, 148,  1,  colour_white,  loc_playfield  },
  {43,  "4 TARGET",    76, 136,  1,  colour_white,  loc_playfield  },
  {44,  "5 TARGET",    79, 142,  1,  colour_white,  loc_playfield  },
  {45,  "6 TARGET",    82, 148,  1,  colour_white,  loc_playfield  },
  {46,  "RELEASE",     104,  164,  1,  colour_white,  loc_playfield  },
  {47,  "LOCK ON",     98,  151,  1,  colour_orange,  loc_playfield  },
  {48,  "T (UPPER L)", 48,  204,  1,  colour_red,  loc_playfield  },
  {49,  "O (UPPER L)", 52,  210,  1,  colour_red,  loc_playfield  },
  {50,  "M (UPPER L)", 55,  216,  1,  colour_red,  loc_playfield  },
  {51,  "T (UPPER R)", 76,  204,  1,  colour_blue,  loc_playfield  },
  {52,  "A (UPPER R)", 72,  210,  1,  colour_blue,  loc_playfield  },
  {53,  "C (UPPER R)", 69,  216,  1,  colour_blue,  loc_playfield  },
  {54,  "BONUX X (RIGHT)",  95,  197,  1,  colour_blue,  loc_playfield  },
  {55,  "2000 SPINNER",  98,  210,  1,  colour_red,  loc_playfield  },
  {56,  "RED LOCK TOP",  16,  206,  1,  colour_red,  loc_playfield  },
  {57,  "RED LOCK MID",  16,  195,  1,  colour_red,  loc_playfield  },
  {58,  "RED LOCK LOW",  16,  176,  1,  colour_red,  loc_playfield  },
  {59,  "BLUE LANDING TOP", 16,  222,  1,  colour_blue,  loc_playfield  },
  {60,  "BLUE LANDING MID",  16,  201,  1,  colour_blue,  loc_playfield  },
  {61,  "BLUE LANDING LOW",  16,  181,  1,  colour_blue,  loc_playfield  },
  {62,  "RIPOFF",  19,  167,  1,  colour_white,  loc_playfield  },
  {63,  "EXTRA BALL",  23,  153,  1,  colour_orange,  loc_playfield  }
}; // tomcat_lamps
*/
//Propery tomcat_lamps[64] ;

/*= {
//index,name,x,y,count,col,loc
{0,  "LITES LOCK ON",  0,  0,  1,  colour_white,  loc_unknown  }
  
  
};
*/
// ----------------------------------------------------------------------------
// Initialize Hardware
// ----------------------------------------------------------------------------

// the base of the interface to existing pinball machines is the CPUBUS class

//CPUBUSClass *Cpubus = new Cpubus_Direct ;
//Cpubus_Direct Cpubus("Tomcat");
#ifdef ARDUINO
Cpubus_Direct Cpubus("Williams System 11A F14-Tomcat");
#endif

//MCP23S17 mcp0( 53, 0);
//MCP23S17 mcp1( 53, 1);

#ifdef RASPBERRY
MCP23S17 mcpaddr( MCP_SELECT, 0);
MCP23S17 mcpdata( MCP_SELECT, 1);
//MCP23S17 mcpswitch( MCP_SELECT, 2);

Cpubus_SPI Cpubus(&mcpaddr, &mcpdata, "CPUBUS SPI");
#endif


MCP23S17 mcplamps( MCP_SELECT, 2);


// ram
ROM ram_u25(&Cpubus, 0x00,0x800 , "U25 RAM");

// roms
ROM rom_u26(&Cpubus, 0x4000,0x4000, "U26 ROM");
ROM rom_u27(&Cpubus, 0x8000,0x8000, "U27 ROM");

//PIA initialisation
MC6821 PIAU10( &Cpubus , 0x2100 , "U10 SOLENOID/SOUND"); 
MC6821 PIAU38( &Cpubus , 0x3000 , "U38 SWITCH"); 
MC6821 PIAU41( &Cpubus , 0x2c00 , "U41 ALFADISPLAY" ); 
MC6821 PIAU42( &Cpubus , 0x3400 , "U42 DISPLAY/WIDGET" ); 
MC6821 PIAU51( &Cpubus , 0x2800 , "U51 DISPLAY" ); 
MC6821 PIAU54( &Cpubus , 0x2400 , "U54 LAMPS" ); 

// latched io
LATCH8 latch_u28(&Cpubus, 0x2200, "U28 SOLENOIDS");
 
// Solenoids
SOLENOID_latch solenoid1  ( &latch_u28 , 0       , true , SOLENOID_PULSE, 10 ,10  , "SOL1 OUTHOLE KICKER" );
SOLENOID_latch solenoid2  ( &latch_u28 , 1       , true , SOLENOID_PULSE, 10  ,10 , "SOL2 SHOOTERLANE" );
SOLENOID_latch solenoid3  ( &latch_u28 , 2       , true , SOLENOID_PULSE, 10 ,10  , "SOL3 BALL POPPER" );
SOLENOID_latch solenoid4  ( &latch_u28 , 3       , true , SOLENOID_PULSE, 10 ,10  , "SOL4 UNUSED" );
SOLENOID_latch solenoid5  ( &latch_u28 , 4       , true , SOLENOID_PULSE, 10  ,10 , "SOL5 C RIGHT EJECT" );
SOLENOID_latch solenoid6  ( &latch_u28 , 5       , true , SOLENOID_PULSE, 10  ,10 , "SOL6 KNOCKER" );
SOLENOID_latch solenoid7  ( &latch_u28 , 6       , true , SOLENOID_PULSE, 10  ,10 , "SOL7 RIGHT EJECT" );
SOLENOID_latch solenoid8  ( &latch_u28 , 7       , true , SOLENOID_PULSE, 10  ,10 , "SOL8 UNUSED" );

SOLENOID_pia   solenoid9  ( &PIAU10 , PIA_PB0 , true , SOLENOID_PULSE, 10  ,10 , "SOL9 FLASHER 9" );
SOLENOID_pia   solenoid10 ( &PIAU10 , PIA_PB1 , true , SOLENOID_PULSE, 10  ,10 , "SOL10 C LEFT EJECT" );
SOLENOID_pia   solenoid11 ( &PIAU10 , PIA_PB2 , true , SOLENOID_CONT, 10   ,10, "SOL11 GI RELAY" );
SOLENOID_pia   solenoid12 ( &PIAU10 , PIA_PB3 , true , SOLENOID_PULSE, 10   ,10, "SOL12 L O D KICKBACK" );
SOLENOID_pia   solenoid13 ( &PIAU10 , PIA_PB4 , true , SOLENOID_PULSE, 10   ,10, "SOL13 RESCUE KICKBACK" );
SOLENOID_pia   solenoid14 ( &PIAU10 , PIA_PB5 , true , SOLENOID_CONT, 10  ,10 , "SOL14 AC relay" );
SOLENOID_pia   solenoid15 ( &PIAU10 , PIA_PB6 , true , SOLENOID_PULSE, 10  ,10 , "SOL15 FLASHER 10" );
SOLENOID_pia   solenoid16 ( &PIAU10 , PIA_PB7 , true , SOLENOID_CONT , 255  ,10, "SOL16 Beacons" );

SOLENOID_pia   solenoid17 ( &PIAU38 , PIA_CA2 , false , SOLENOID_PULSE , 10 ,10 , "SOL17 UP DIV" );
SOLENOID_pia   solenoid18 ( &PIAU41 , PIA_CA2 , false , SOLENOID_PULSE , 10  ,10, "SOL18 UP DIV" );
SOLENOID_pia   solenoid19 ( &PIAU41 , PIA_CB2 , false , SOLENOID_PULSE , 10 ,10 , "SOL19 UP DIV" );
SOLENOID_pia   solenoid20 ( &PIAU38 , PIA_CB2 , false , SOLENOID_PULSE , 10 ,10 , "SOL20 UP DIV" );
SOLENOID_pia   solenoid21 ( &PIAU54 , PIA_CB2 , false , SOLENOID_PULSE , 200 ,10 , "SOL21 UP DIV" );
SOLENOID_pia   solenoid22 ( &PIAU54 , PIA_CA2 , false , SOLENOID_PULSE , 200 ,10, "SOL22 LOW DIV" );

#ifdef ARDUINO
SOLENOID_demo soldemo1 ( 10 ,  false , SOLENOID_CONT, 10 ,10 , "SOLDEMO1" );
SOLENOID_demo soldemo2 ( 11 ,  false , SOLENOID_PULSE, 5  ,10, "SOLDEMO2" );
SOLENOID_demo soldemo3 ( 12 ,  false , SOLENOID_PULSE, 50  ,10, "SOLDEMO3" );
SOLENOID_demo soldemo4 ( 13 ,  false , SOLENOID_PULSE, 250 ,10 , "SOLDEMO4" );
#endif

DISPLAY_WIL11A display1 ( &PIAU41, &PIAU51, &PIAU42);

#ifdef ARDUINO
SOLENOID & sol_test = soldemo4;
#endif 

SOLENOID & sol_outlane = solenoid1;
SOLENOID & sol_enable = solenoid14;
SOLENOID & sol_beacon = solenoid16;

//solenoid16.setName("SOL16 Beacons");
//solenoid16.setType( SOLENOID_CONT );

//Flashers
//FLASHER_williams11a flasher1(1,"Flasher 1"); 

lamps_williams11a lamps1(&PIAU54,"sys11a lamps");
#ifdef ARDUINO
lamps_demo lampsdemo("demo lamps");
#endif
lamps_spi_matrix lamps2(&mcplamps, "spi lamps");


#ifdef ARDUINO
SWITCHES_demo switchesdemo;
#endif
SWITCHES_williams11a switches1(&PIAU38);


//LAMP lamp1( &lamps1 , 0 , "LAMP1");
//LAMP lamp2( &lamps1 , 1 , "LAMP2");

// ----------------------------------------------------------------------------
// End Initialize Hardware
// ----------------------------------------------------------------------------

// serial listener
PindaCom com;

uint8_t val=0;
uint8_t switchrow = 0;

unsigned long time1;
unsigned long time2;
unsigned long lamptime;



void dotty(void){
 Serial.print("."); 
}

// if no wSYS11A display is used, the blanking signal needs to be generated.
void blanking_int(void) {
  PIAU51.toggle( 3 ); //blanking
}

/*---------------------------------------------------------------------------------------
*  Setup
*-------------------------------------------------------------------------------------*/ 
void setup()
{
  // initialize serial and wait for port to open:
  //Serial.begin(115200);
  Serial.begin(19200);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("\n");
    
#ifdef ARDUINO
	// start printf to make it usefull
  printf_begin();
#endif
 
  // Start the pinda Interrupt timer
  pinda.StartTimer();

  PIAU51.outputA();
  PIAU51.allOffA();
  PIAU51.outputB();
  PIAU51.allOffB();

  PIAU54.outputA();
  PIAU54.allOffA();
  PIAU54.outputB();
  PIAU54.allOffB();
  
  PIAU10.outputA();
  PIAU10.allOffA();
  PIAU10.outputB();
  PIAU10.allOffB();


//pindaAddInterrupt(dotty,20);
//pindaAddInterrupt(fnled,20);
//pindaAddInterrupt(intled,1);

// dump the rom to screen
// Cpubus.read(0x20);
// Cpubus.write(0x3000,128);

#ifdef ARDUINO 
lampsdemo.on(0);
lampsdemo.on(51);
lampsdemo.on(16);
lampsdemo.on(48);
#endif
//lampsdemo.show();

//pinda.AddInterrupt(blanking_int,5);

display1.text1(" ARDUINO PINDA");
display1.text2(" ARDUINO PINDA");
//display1.text2(" ABCDEFG HIJKLMN");
//display1.text1(" ABCDEFG 0123456");
//display1.text2(" OPQRSTU VWXYZ79");
//display1.text1(" 01234567 8912345");
//display1.text1(" 2345678 9!\"#$%");
//display1.text1(" :;><=?@ ");

//PIAU51.output(4);

lamptime=millis();

solenoid17.off();
solenoid18.off();
solenoid19.off();
solenoid20.off();
solenoid21.off();
solenoid22.off();

Serial.print(pinda.status() );


// map functions to the serial slave handler
com.setLampBank( 0, &lamps1);
#ifdef ARDUINO
com.setLampBank( 1, &lampsdemo);
#endif
com.setSwitchBank( 0, &switches1);
#ifdef ARDUINO

com.setSwitchBank( 1, &switchesdemo);
#endif
com.setSolenoid( 0, &solenoid1);
com.setSolenoid( 1, &solenoid2);
com.setSolenoid( 2, &solenoid3);
com.setSolenoid( 3, &solenoid4);
com.setSolenoid( 4, &solenoid5);
com.setSolenoid( 5, &solenoid6);
com.setSolenoid( 6, &solenoid7);
com.setSolenoid( 7, &solenoid8);
com.setSolenoid( 8, &solenoid9);
com.setSolenoid( 9, &solenoid10);
com.setSolenoid( 10, &solenoid11);
com.setSolenoid( 11, &solenoid12);
com.setSolenoid( 12, &solenoid13);
com.setSolenoid( 13, &solenoid14);
com.setSolenoid( 14, &solenoid15);
com.setSolenoid( 15, &solenoid16);
com.setSolenoid( 16, &solenoid17);
com.setSolenoid( 17, &solenoid18);
com.setSolenoid( 18, &solenoid19);
com.setSolenoid( 19, &solenoid20);
com.setSolenoid( 20, &solenoid21);
com.setSolenoid( 21, &solenoid22);

#ifdef ARDUINO

com.setSolenoid( 26, &soldemo1);
com.setSolenoid( 27, &soldemo2);
com.setSolenoid( 28, &soldemo3);
com.setSolenoid( 29, &soldemo4);
#endif
/*
mcplamps.ddrA(0xff);
mcplamps.ddrB(0xff);
mcplamps.port(0x3333);


  mcp0.pinMode(true);
  mcplamps.pinMode(true);
//  mcp1.pinMode(false);
  mcp0.port(0x5555);
 // mcp1.port(0xffff);  
*/
pinda.AddInterrupt ( &com , 1);
com.enableInterrupt();

//lamps1.setProperties( & tomcat_lamps[0] );
//ram_u25.ihex32();
//rom_u26.checksums();

  Serial.print(pinda.status() );
  Serial.print(Cpubus.status() );
  Serial.print(com.status() );
  
  
    PIAU10.write_crb( 1<<5 | 1<<4   ); //enable solenoids U10-CB2
  
  
} // Setup ------------------------------------------------------------------------------



/*---------------------------------------------------------------------------------------
*  Loop
*-------------------------------------------------------------------------------------*/ 
void loop() {
  //	pinda.mainInterrupt();
    pinda.loop();

    // loop 0-255 on the lamps
    time1=millis();
    if ( time1 > lamptime ) {
      val++;
      for (uint8_t r=0;r<8;r++){
          lamps1.rowSet( r ,val );
          lamps2.rowSet( r ,~val );
		  #ifdef ARDUINO
          lampsdemo.rowSet( r ,val );
		  #endif
      }
      lamptime+=1000;
    }
    
  // parse a message when ready
  if (com.isReady() ) {
    com.parseMsg();
    com.listen();    // enable next message
  } 
  
  
  // 
  if (slave) {
     // send flank changes to serial
    com.flank();
    
    
  } else {
    
   // PIAU10.write_crb( 1<<5 | 1<<4   ); //enable solenoids U10-CB2
 //  PIAU51.toggle(4);


    
    
    
//  display1.setScore1( String(switchrow) );
 // display1.setScore2( String( switches1.getRow( switchrow ) ,BIN) );

#ifdef ARDUINO
    
if ( switchesdemo.flankup( 0 )) { 
  Serial.println( "SWICTCH1");
  soldemo1.toggle(); 
}

if ( switchesdemo.flankup( 9 )) { 
  Serial.println( "SWICTCH2");
  soldemo2.on(); 
}

if ( switchesdemo.flankup( 18 )) { 
  Serial.println( "SWICTCH3");
  soldemo3.on(); 
}
    
if ( switchesdemo.flankup( 27 )) { 
  Serial.println( "SWICTCH4");
  soldemo4.on(); 
}

if ( switchesdemo.flankdown( 27 )) { 
  Serial.println( "SWICTCH4OFF");
}

if ( switchesdemo.flankup( 36 )) { 
  Serial.println( "SWICTCH5");
  Serial.print(pinda.status() );
  Serial.print(Cpubus.status() );
  Serial.print(com.status() );
  
  sol_test.toggle(); 
}
  
  #endif
  
   
   /*
   
   
    

    
   if ( digitalRead(sw5) == 0 ) {
      if (sw5state==false) {
      display1.text2( " DEMOSW5 ");
       delay(22);
  solenoid21.off();
  solenoid22.off();
      solenoid14.on();
      sw5state=true;      
      }
    }

    if ( digitalRead(sw6) == 0 ) {
      if (sw6state==false) {
    display1.setScore3( "DEMOSW6");
   
      display1.setScore2( "SOL9");
      solenoid9.on();
      delay(1000);

      display1.setScore2( "SOL10");
      solenoid10.on();
      delay(1000);
 
      display1.setScore2( "SOL11");
      solenoid11.on();
      delay(1000);
 
      display1.setScore2( "SOL12");
      solenoid12.on();
      delay(1000);
 
      display1.setScore2( "SOL13");
      solenoid13.on();
      delay(1000);
 
      display1.setScore2( "SOL15");
      solenoid15.on();
      delay(1000);
 
 
      
      display1.setScore2( "DONE");

      sw6state=true;      
      }
    }

    if ( digitalRead(sw7) == 0 ) {
      if (sw7state==false) {
      display1.text2( " DEMOSW7 ");
       delay(22);
      display1.text1( " SOL17 ");
      solenoid17.on();
      delay(1000);
      display1.text1( " SOL18 ");
      solenoid18.on();
      delay(1000);
      display1.text1( " SOL19 ");
      solenoid19.on();
      delay(1000);
      display1.text1( " SOL20 ");
      solenoid20.on();
      delay(1000);
      display1.text1( " SOL21 ");
      solenoid21.on();
      delay(1000);
      display1.text1( " SOL22 ");
      solenoid22.on();
      
      display1.text1( " DONE ");


      sw7state=true;      
      }
    }
    
    if ( digitalRead(sw8) == 0 ) {
      if (sw8state==false) {
      display1.setScore3( "DEMO S8 ");
       delay(22);
      display1.setScore2( "SOLENOID1");
      solenoid1.on();
      delay(1000);
      display1.text1( " SOLENOID2 ");
      solenoid2.on();
      delay(1000);
      display1.text1( " SOLENOID3 ");
      solenoid3.on();
      delay(1000);
      display1.text1( " SOLENOID4 ");
      solenoid4.on();
      delay(1000);
      display1.text1( " SOLENOID5 ");
      solenoid5.on();
      delay(1000);
      display1.text1( " SOLENOID6 ");
      solenoid6.on();
      delay(1000);
      display1.text1( " SOLENOID7 ");
      solenoid7.on();
      delay(1000);
      display1.text1( " SOLENOID8 ");
      solenoid8.on();
      delay(1000);
      
      display1.text1( " DONE ");

      sw8state=true;      
      }
    }
*/

/*
if ( switches1.isOn( 8+2 ) ) {
  if (sw_3==false) {
     //do on stuff
     solenoid16.toggle();   
    
    sw_3=true ;
  }
} else {
    sw_3 = false;
}
   */ 

if ( switches1.flankup( 1*8+2)) { delay(100);solenoid2.on(); }

if ( switches1.flankup( 2*8+1)) { delay(100);solenoid1.on(); }

// left eject
if ( switches1.flankup( 3*8+5)) { solenoid10.on(100); }

// right eject
if ( switches1.flankup( 3*8+4)) { delay(500);
solenoid7.on();
delay(100);
solenoid21.on();
}

// center right eject 
if ( switches1.flankup( 3*8+6)) { delay(100);solenoid5.on(); }

// kickup 
if ( switches1.flankup( 3*8+7)) { delay(100);solenoid3.on(); }

// kickback 
if ( switches1.flankup( 7*8+6)) { solenoid12.on(); }

// rescue 
if ( switches1.flankup( 4)) { solenoid13.on(); }

if ( switches1.flankup( 4*8+1)) {
  switchrow++;
  if ( switchrow > 7) switchrow=0;

}

		char buf[10];
		sprintf(buf,"M%04X ", pinda.freeRam() );
		display1.setScore4( buf);
		
//display1.setScore4("M "+ String( pinda.freeRam() ) );
  
delay(10);
  }
  //delay(200);

}


#ifdef RASPBERRY
int main(void) {
setup();
while(1) {
	loop();
}

}
#endif
