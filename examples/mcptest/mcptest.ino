#include "pinda.h" 
#include "printf.h"
#include <SPI.h>
#include <mc23s17.h>
#include <Wire.h>
Pinda pinda;

MCP23S17 mcp2( 53, 0);
MCP23S17 mcp1( 53, 1);
MCP23017 mcp0(0);

uint8_t a=0;
void setup() {
    Serial.begin(115200);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("\n");
    
  // start printf to make it usefull
  printf_begin();
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
 mcp0.pinMode(true);
  mcp1.pinMode(false);
 mcp0.port(0x3333);
  mcp1.port(0xffff);  
 // mcp0.
}



void loop(void) {
  a++;
  mcp0.portA( a );
delay(200);  
}



