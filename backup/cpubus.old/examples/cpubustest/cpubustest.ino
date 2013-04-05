/*
 * CPUBUSTEST
 **
 * This example code is in the public domain.
 */

#include <CPUBUS.h>


void setup()
{
  // initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  CPUBUSClass Cpubus;
  Cpubus.init( );
  Serial.println("now cpu bus things");
  
}

void loop()
{
 
  delay(500);
}
