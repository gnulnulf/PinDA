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

#include <pinda.h> 
#include "printf.h"
#include <SPI.h>

Pinda pinda;
const bool slave=true;


// ----------------------------------------------------------------------------
// Initialize Hardware
// ----------------------------------------------------------------------------

// the base of the interface to existing pinball machines is the CPUBUS class

//CPUBUSClass *Cpubus = new Cpubus_Direct ;
//Cpubus_Direct Cpubus("Tomcat");
Cpubus_Direct Cpubus("Williams System 11A F14-Tomcat");
//Cpubus_SPI Cpubus;

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

SOLENOID_demo soldemo1 ( 10 ,  false , SOLENOID_CONT, 10 ,10 , "SOLDEMO1" );
SOLENOID_demo soldemo2 ( 11 ,  false , SOLENOID_PULSE, 5  ,10, "SOLDEMO2" );
SOLENOID_demo soldemo3 ( 12 ,  false , SOLENOID_PULSE, 50  ,10, "SOLDEMO3" );
SOLENOID_demo soldemo4 ( 13 ,  false , SOLENOID_PULSE, 250 ,10 , "SOLDEMO4" );

DISPLAY_WIL11A display1 ( &PIAU41, &PIAU51, &PIAU42);

SOLENOID & sol_test = soldemo4;

SOLENOID & sol_outlane = solenoid1;
SOLENOID & sol_enable = solenoid14;
SOLENOID & sol_beacon = solenoid16;

//solenoid16.setName("SOL16 Beacons");
//solenoid16.setType( SOLENOID_CONT );

//Flashers
//FLASHER_williams11a flasher1(1,"Flasher 1"); 

lamps_williams11a lamps1(&PIAU54,"sys11a lamps");
lamps_demo lampsdemo("demo lamps");

SWITCHES_demo switchesdemo;
SWITCHES_williams11a switches1(&PIAU38);


LAMP lamp1( &lamps1 , 0 , "LAMP1");
LAMP lamp2( &lamps1 , 1 , "LAMP2");

// ----------------------------------------------------------------------------
// End Initialize Hardware
// ----------------------------------------------------------------------------

// serial listener
PindaCom com;

uint8_t val=0;
uint8_t switchrow = 0;

unsigned long time;
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
    
  // start printf to make it usefull
  printf_begin();
  
  // Start the pinda Interrupt timer
  pinda.StartTimer();

//  PIAU51.outputA();
//  PIAU51.allOffA();
//  PIAU51.outputB();
//  PIAU51.allOffB();

//  PIAU54.outputA();
//  PIAU54.allOffA();
 // PIAU54.outputB();
  //PIAU54.allOffB();
  
 // PIAU10.outputA();
//  PIAU10.allOffA();
 // PIAU10.outputB();
 // PIAU10.allOffB();


//pindaAddInterrupt(dotty,20);
//pindaAddInterrupt(fnled,20);
//pindaAddInterrupt(intled,1);

// dump the rom to screen
// Cpubus.read(0x20);
// Cpubus.write(0x3000,128);
 
lampsdemo.on(0);
lampsdemo.on(51);
lampsdemo.on(16);
lampsdemo.on(48);
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
com.setLampBank( 1, &lampsdemo);
com.setSwitchBank( 0, &switches1);
com.setSwitchBank( 1, &switchesdemo);
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

com.setSolenoid( 26, &soldemo1);
com.setSolenoid( 27, &soldemo2);
com.setSolenoid( 28, &soldemo3);
com.setSolenoid( 29, &soldemo4);


pinda.AddInterrupt ( &com , 1);
com.enableInterrupt();


} // Setup ------------------------------------------------------------------------------



/*---------------------------------------------------------------------------------------
*  Loop
*-------------------------------------------------------------------------------------*/ 
void loop() {
    pinda.loop();

    // loop 0-255 on the lamps
    time=millis();
    if ( time > lamptime ) {
      val++;
      for (uint8_t r=0;r<8;r++){
          lamps1.rowSet( r ,val );
          lampsdemo.rowSet( r ,val );
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
    
    
//  } else {
    
   // PIAU10.write_crb( 1<<5 | 1<<4   ); //enable solenoids U10-CB2
 //  PIAU51.toggle(4);


    
    
    
  display1.setScore1( String(switchrow) );
  display1.setScore2( String( switches1.getRow( switchrow ) ,BIN) );

    
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

*/
display1.setScore4("M "+ String( pinda.freeRam() ) );
  
delay(10);
  }
  //delay(200);

}


void bla() {





// PIAU10.write_pdrb( 1<<5   );
 //PIAU10.write_pdrb( 1<<7   );
 PIAU10.write_crb( 1<<5 | 1<<4   ); //enable solenoids
//  PIAU10.write_crb( (1<<5) | (1<<4) | (1<<3) ); //disable solenoids
 
 
 
 
/*
Cpubus.write(0x2200,0xA8);
delay(100);
Cpubus.write(0x2200,0x00);
PIAU10.write_pdrb( 0 );


PIAU10.write_pdrb( 1<<5 | 1<<7   );
for (uint8_t i=0;i<8;i++) {
      for (uint8_t r=0;r<8;r++){
Cpubus.write(0x2200,(1 << r));
delay(100);
Cpubus.write(0x2200,0x00);
delay(100);
}
//switches1.show();
}

PIAU10.write_pdrb( 1<<7   );
for (uint8_t i=0;i<2;i++) {
      for (uint8_t r=0;r<8;r++){
Cpubus.write(0x2200,(1 << r));
delay(100);
Cpubus.write(0x2200,0x00);
delay(1000);
}
//switches1.show();
}

 */
 soldemo1.on();
 soldemo2.on();
 soldemo3.off();
 delay(1000);
 soldemo1.off();
 soldemo2.off();
 soldemo3.off();
 soldemo4.off();
 
for (uint8_t i=0;i<8;i++) {
 soldemo1.toggle();
 soldemo2.on();
 soldemo3.on();
 soldemo4.on();
delay(1000);
} 
 
 
 
 /*
 PIAU54.write_crb( (1<<5) | (1<<3) );
 PIAU10.write_pdrb( 1<<5   );
 delay(2000);
 PIAU10.write_pdrb( 0 );
 PIAU54.write_crb( 1<<5   );
 PIAU54.write_crb( 0   );
 
 
 */

 // noInterrupts();           // disable all interrupts
// / *


/*
Serial.println( "-- Speed test --") ; 
time = millis();
for ( uint16_t x=0;x<50000;x++) {
  uint8_t data = Cpubus.read( x );
   //delay(1);
}
time2=millis();
Serial.print("CPUBUS READ Duration (50000x) = ");
Serial.print(time2-time);
Serial.println("ms");

time = millis();
for ( uint16_t x=0;x<50000;x++) {
  Cpubus.write( 0xf000, 0x55 );
   //delay(1);
}
time2=millis();
Serial.print("CPUBUS WRITE Duration (50000x) = ");
Serial.print(time2-time);
Serial.println("ms");

time = millis();
for ( uint16_t x=0;x<50000;x++) {
  Cpubus.writeref( 0xf000, 0x55 );
   //delay(1);
}
time2=millis();
Serial.print("CPUBUS WRITE REF Duration (50000x) = ");
Serial.print(time2-time);
Serial.println("ms");



time = millis();
for ( uint16_t x=0;x<10000;x++) {
  PIAU10.write_pdrb( 0xA4 ); 
//  Cpubus.writeref( 0xf000, 0x55 );
   //delay(1);
}
time2=millis();
Serial.print("PIA WRITE Duration (10000x) = ");
Serial.print(time2-time);
Serial.println("ms");


time = millis();
for ( uint16_t x=0;x<10000;x++) {
  lamps1.rowSet(0,0xff) ;
//  Cpubus.writeref( 0xf000, 0x55 );
   //delay(1);
}
time2=millis();
Serial.print("LAMP rowSET  Duration (10000x) = ");
Serial.print(time2-time);
Serial.println("ms");
*/
//delay(10000);
  Serial.println( "-- PIA test --") ; 
  int val=0x55;
 
//  PIAU10.write_pdrb( 0xA4 ); 
PIAU10.write_crb( (1<<5) );
//| (1<<3)
for (uint8_t i=0;i<64;i++) {
  lamps1.allOff();
   delay(200 - i*3);    
  lamps1.allOn();
   delay(200 - i*3);    
switches1.show();
}

  lamps1.allOn();
   delay(400);    
  lamps1.allOff();

//switches1.show();

for (uint8_t i=0;i<64;i++) {
  lamps1.allOff();
  lamps1.on( i );
   delay(100);    
}

for (uint8_t i=0;i<255;i++) {
      for (uint8_t r=0;r<8;r++){
        lamps1.rowSet( r ,i );
      }
   delay(200);    
//switches1.show();
}


for (uint8_t i=0;i<64;i++) {
  lamps1.allOff();
  lamps1.on( i );
   delay(100);    
switches1.show();
}
  

/*
  for (uint16_t count=0;count<32768;count++){
    val=0x55;
//switches1.show();
    for (uint8_t i=0;i<8;i++){
  //    PIAU51.write_pdra(0x04); 
      for (uint8_t r=0;r<8;r++){
    //    PIAU51.write_pdra(0x14);  //blanking
      //  if ( count > 5000 )   PIAU10.write_pdrb( 0 );
        //PIAU54.write_pdra( 0xff  );  // set output
        //PIAU54.write_pdrb( ( 1 << r ) );  // set output
   // if ( i%32 == 0 ) printf("\n");
 //   PIA1.write_pdra( 1 << i );  // set output
//val = ~(1 << i);
//val = 0x55;
        val=(count>>5) & 0xff;
        lamps1.rowSet( r ,val );
    //    lamps1.interrupt( );

        lamps1.rowSet( r ,~0x55 );
        
        lamps1.show( );
//PORTK=PING;
//        PORTK=val;
      //  PIAU54.write_pdra( val  );  // set output
   // printf("%02X ",PIAU51.read_pdra());
   delay(100);
//   delay();
    //    PIAU51.write_pdra(0x00); //blanking
      }
    }
  
//    if ( digitalRead(sw1) == 0 ) sw1led();
//    if ( digitalRead(sw2) == 0 ) sw2led();
    
//    time2=millis();
//    Serial.print("mAinloop = ");
//    Serial.print(time2-time);
//    Serial.println("ms");

  }
  */
Serial.println("");

     Serial.println("\n[memCheck]");
    Serial.println(pinda.freeRam());
 delay(5000);
// * /
}

