/*
 * CPUBUSTEST
 **
 * This example code is in the public domain.
 */

// 
#include <pinda.h> 
#include "printf.h"
#include <SPI.h>

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}


//CPUBUSClass *Cpubus = new Cpubus_Direct ;
//Cpubus_Direct Cpubus("Tomcat");
Cpubus_Direct Cpubus;

//Cpubus_SPI Cpubus;
unsigned long time;
unsigned long time2;

ROM rom_u25; //U25 RAM
ROM rom_u26; //U26 ROM2
ROM rom_u27; //U27 ROM1

ROM rom_all; //FAKE ROM 0x0000 64K

MC6821 PIA1;

MC6821 PIAU10; 
MC6821 PIAU38; 
MC6821 PIAU41; 
MC6821 PIAU42; 
MC6821 PIAU51; 
MC6821 PIAU54; 


#define intledPin 11
#define fnledPin 12
#define sw1ledPin 10
#define sw2ledPin 13
#define sw3ledPin 11
#define sw4ledPin 12


#define sw1 41
#define sw2 40
#define sw3 39
#define sw4 38
#define sw5 7
#define sw6 6
#define sw7 5
#define sw8 4

void fnled(void) {
  digitalWrite(fnledPin, digitalRead(fnledPin) ^ 1);   // toggle LED pin 
}
void sw1led(void) {
  digitalWrite(sw1ledPin, digitalRead(sw1ledPin) ^ 1);   // toggle LED pin 
}
void sw2led(void) {
  digitalWrite(sw2ledPin, digitalRead(sw2ledPin) ^ 1);   // toggle LED pin 
}
void sw3led(void) {
  digitalWrite(sw3ledPin, digitalRead(sw3ledPin) ^ 1);   // toggle LED pin 
}
void sw4led(void) {
  digitalWrite(sw4ledPin, digitalRead(sw4ledPin) ^ 1);   // toggle LED pin 
}


void dotty(void){
 Serial.print("."); 
}
#define intledPin 11
void intled(void){
 digitalWrite(intledPin, digitalRead(intledPin) ^ 1);   // toggle LED pin
}


void setup()
{
  // initialize serial and wait for port to open:
  Serial.begin(115200);
  //while (!Serial) {
  //  ; // wait for serial port to connect. Needed for Leonardo only
  //}
  pinMode(intledPin, OUTPUT);
    printf_begin();
    Serial.println("CPUBUS init");
   Cpubus.init();
pindaStartTimer();

//demo leds - solenoids
pinMode(fnledPin, OUTPUT);
pinMode(intledPin, OUTPUT);
pinMode(sw1ledPin, OUTPUT);
pinMode(sw2ledPin, OUTPUT);

//demo leds-lamps
#define DEMOLEDSDDR DDRK 
#define DEMOLEDSPORT PORTK 

DEMOLEDSDDR=0xff;
DEMOLEDSPORT=0xAA;

//demo switches met pullup
pinMode( sw1, INPUT);
digitalWrite( sw1,HIGH);
pinMode( sw2, INPUT);
digitalWrite( sw2,HIGH);
pinMode( sw3, INPUT);
digitalWrite( sw3,HIGH);
pinMode( sw4, INPUT);
digitalWrite( sw4,HIGH);
pinMode( sw5, INPUT);
digitalWrite( sw5,HIGH);
pinMode( sw6, INPUT);
digitalWrite( sw6,HIGH);
pinMode( sw7, INPUT);
digitalWrite( sw7,HIGH);
pinMode( sw8, INPUT);
digitalWrite( sw8,HIGH);


/*pinMode( 13 ,OUTPUT );
digitalWrite( 13,HIGH);

pinMode( 12 ,OUTPUT );
digitalWrite( 12,LOW);
*/
//delay(5000);

//pindaAddInterrupt(dotty,20);
pindaAddInterrupt(fnled,20);
pindaAddInterrupt(intled,1);


//  PIA1.init( &Cpubus,96);
  PIAU54.init( &Cpubus,0x2400);
  PIAU54.write_ddra(255); // A uitgang  
  PIAU54.write_ddrb(255);  //B uitgang
  PIAU54.write_pdrb(0x00); 

  PIAU10.init( &Cpubus,0x2100);
  PIAU10.write_ddra(255); // A uitgang  
  PIAU10.write_ddrb(255);  //B uitgang
  PIAU10.write_pdra(0x00); 
  PIAU10.write_pdrb(0x00); 


  PIAU51.init( &Cpubus,0x2800);
  PIAU51.write_ddra(255); // A uitgang  
  PIAU51.write_ddrb(255);  //B uitgang
  PIAU51.write_pdra(0x00); 
  PIAU51.write_pdrb(0x00); 



    // dump the rom to screen
    rom_all.init(&Cpubus, 0x0000,65535);
    rom_u26.init(&Cpubus, 0x4000,0x4000);
    rom_u27.init(&Cpubus, 0x8000,0x8000);
 // Cpubus.read(0x20);
 // Cpubus.write(0x3000,128);
 
  // show 256 bytes
//  read256();
// rom_all.dump();
    Serial.println("\n[memCheck]");
    Serial.println(freeRam());




}
void read256() {
  printf("Read 256 bytes...");
  for ( int i=0;i<256;i++ ){
    if ( i%16 == 0 ) {
      printf("\n%04X: ",i);
    }
  uint8_t data = Cpubus.read( (0x2800-16)+ i );
  printf("%02X ",data);
 }
 printf("\n");
} //read256



void loop() {

 
pindaLoop();
  
// / *
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
// * /


  Serial.println( "-- PIA test --") ; 
  int val=0x55;
 
  PIAU10.write_pdrb( 0xA4 ); 
  for (uint16_t count=0;count<32768;count++){
  //  time = millis();
    val=0x55;
//delay(1);
    for (uint8_t i=0;i<8;i++){
//    PIAU51.write_pdra(0x04); 
      for (uint8_t r=0;r<8;r++){
        PIAU51.write_pdra(0x14); 
        if ( count > 5000 )   PIAU10.write_pdrb( 0 );

        PIAU54.write_pdrb( ( 1 << r ) );  // set output
   // if ( i%32 == 0 ) printf("\n");
 //   PIA1.write_pdra( 1 << i );  // set output
//val = ~(1 << i);
//val = 0x55;
        val=(count>>5) & 0xff;
//PORTK=PING;
        PORTK=val;
        PIAU54.write_pdra( val  );  // set output
   // printf("%02X ",PIAU51.read_pdra());
   //delay(1);
        PIAU51.write_pdra(0x00);
      }
    }
  
    if ( digitalRead(sw1) == 0 ) sw1led();
    if ( digitalRead(sw2) == 0 ) sw2led();
    
//    time2=millis();
//    Serial.print("mAinloop = ");
//    Serial.print(time2-time);
//    Serial.println("ms");

  }
Serial.println("");

     Serial.println("\n[memCheck]");
    Serial.println(freeRam());
 delay(5000);
// * /
}
