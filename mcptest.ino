#ifdef RASPBERRY
#include <iostream>
#include "rpi/compatibility.h" 
#define MCP_SELECT 7
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

#include "mcp23s17.h"
//#include <Wire.h>
Pinda pinda;


//MCP23S17 mcp0( MCP_SELECT, 0);
//MCP23S17 mcp1( MCP_SELECT, 1);
//MCP23017 mcp0(0);

MCP23S17 mcpaddr( MCP_SELECT, 0);
MCP23S17 mcpdata( MCP_SELECT, 1);
//MCP23S17 mcpswitch( 53, 2);
MCP23S17 mcplamps( MCP_SELECT, 2);

Cpubus_SPI Cpubus(&mcpaddr, &mcpdata, "CPUBUS SPI");

//PIA initialisation
MC6821 PIAU10( &Cpubus , 0x2100 , "U10 SOLENOID/SOUND");
MC6821 PIAU38( &Cpubus , 0x3000 , "U38 SWITCH");
MC6821 PIAU41( &Cpubus , 0x2c00 , "U41 ALFADISPLAY" );
MC6821 PIAU42( &Cpubus , 0x3400 , "U42 DISPLAY/WIDGET" );
MC6821 PIAU51( &Cpubus , 0x2800 , "U51 DISPLAY" );
MC6821 PIAU54( &Cpubus , 0x2400 , "U54 LAMPS" );

// latched io
LATCH8 latch_u28(&Cpubus, 0x2200, "U28 SOLENOIDS");


//SPI * spiio;

uint16_t x=0;
void setup() {
//spiio = new SPI();
//spiio->setdevice("/dev/spidev0.0");

//spiio->setspeed(2000000);
 //       spiio->setbits(8);
//spiio->init();

    Serial.begin(115200);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("test1");
  //Serial.p("test2");
  Serial.print("test");

#ifdef ARDUINO
    
  // start printf to make it usefull
  printf_begin();
#endif //ARDUINO
  /*
  
  Wire.begin();                // wake up I2C bus
Wire.beginTransmission(0x20);// Connect to chip
Wire.write((byte)0x00);      // Select Bank B
Wire.write((byte)0x00);      // Set all of bank B to outputs
Wire.endTransmission();      // Close connection

Wire.beginTransmission(0x20);// Connect to chip
Wire.write((byte)0x01);      // Select Bank B
Wire.write((byte)0x00);      // Set all of bank B to outputs
Wire.endTransmission();      // Close connection
  
  
Wire.beginTransmission(0x20); // Connect to chip
Wire.write(0x12);             // Set Memory Pointer to Bank A
Wire.write(0x55);                 // Write the Byte
Wire.endTransmission();       // Close connection
  */
	mcpaddr.pinMode(0xffff);
	mcpdata.pinMode(false);
	mcpaddr.port(0x3333);
	mcpdata.port(0xffff);  
}



void loop(void) {
//digitalWrite( 8, LOW );
//spiio->transfer3(0x40,0,x);
//digitalWrite( 8, HIGH );

	//cout << "Loop 1" <<endl;
  x++;
  mcpaddr.port( x );
//  mcpaddr.portA( x );
//  mcpaddr.portB( ~x );
delay(1);  
}


#ifdef RASPBERRY
int main(void) {
setup();
while(1) {
	loop();
}

}
#endif
