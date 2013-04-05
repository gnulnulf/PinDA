/*
 * CPUBUSTEST
 **
 * This example code is in the public domain.
 */

// 
#include <pinda.h> 
#include "printf.h"
#include <SPI.h>

//CPUBUSClass *Cpubus = new Cpubus_Direct ;
Cpubus_Direct Cpubus;
//Cpubus_SPI Cpubus;
unsigned long time;
unsigned long time2;

MC6821 PIA1; 
ROM rom_u23;

void setup()
{
  // initialize serial and wait for port to open:
  Serial.begin(115200);
  //while (!Serial) {
  //  ; // wait for serial port to connect. Needed for Leonardo only
  //}
    printf_begin();
    Serial.println("CPUBUS init");
    Cpubus.init( );

  PIA1.init( &Cpubus,96);
  PIA1.write_ddra(0); // A ingang  
  PIA1.write_ddrb(255);  //B uitgang
  PIA1.write_pdrb(0x00); 

    // dump the rom to screen
    rom_u23.init(&Cpubus, 0x8000,1024);
 // Cpubus.read(0x20);
 // Cpubus.write(0x3000,128);
 
  // show 256 bytes
  read256();
  rom_u23.dump();

}
void read256() {
  printf("Read 256 bytes...");
  for ( int i=0;i<256;i++ ){
    if ( i%16 == 0 ) {
      printf("\n%04X: ",i);
    }
  uint8_t data = Cpubus.read( i );
  printf("%02X ",data);
 }
 printf("\n");
} //read256

void loop()
{
Serial.println( "-- Speed test --") ; 
time = millis();
for ( uint16_t x=0;x<50000;x++) {
  uint8_t data = Cpubus.read( x );
   //delay(1);
}
time2=millis();
Serial.print("READ Duration (50000x) = ");
Serial.print(time2-time);
Serial.println("ms");

time = millis();
for ( uint16_t x=0;x<50000;x++) {
  Cpubus.write( 98, 0x55 );
   //delay(1);
}
time2=millis();
Serial.print("PIA WRITE Duration (50000x) = ");
Serial.print(time2-time);
Serial.println("ms");



Serial.println( "-- PIA test --") ; 
 
for (uint8_t i=0;i<255;i++){
    if ( i%32 == 0 ) printf("\n");
    PIA1.write_pdrb(i);  // set output
    printf("%02X ",PIA1.read_pdra());
    delay(20);
}
Serial.println("");

 
 delay(5000);
// * /
}
