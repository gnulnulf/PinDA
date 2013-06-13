
// MCP23S17 SPI 16-bit IO expander
// http://ww1.microchip.com/downloads/en/DeviceDoc/21952b.pdf

// For the cmd, AAA is the 3-bit MCP23S17 device hardware address.
// Useful for letting up to 8 chips sharing same SPI Chip select
// #define MCP23S17_READ  B0100AAA1 
// #define MCP23S17_WRITE B0100AAA0 

// The default SPI Control Register - SPCR = B01010000;
// interrupt disabled,spi enabled,msb 1st,master,clk low when idle,
// sample on leading edge of clk,system clock/4 rate (fastest).
// Enable the digital pins 11-13 for SPI (the MOSI,MISO,SPICLK)
//#include <SPI.h>
#include "pinda.h"
#include "mcp23s17.h"
#ifdef ARDUINO
#include <Wire.h>
#endif

// Note: You may need to take _RESET_ on the MCP23S17 low
// for a few hundred ms and then take (and hold) it high
// again before you begin to communicate with the chip.

//---------- constructor ----------------------------------------------------

MCP23S17::MCP23S17(uint8_t slave_select_pin)
{
  spiio->begin();
  setup_ss(slave_select_pin);
  setup_device(0x00);
}

//#define    ADDR_ENABLE   (0b00001000)  // Configuration register for MCP23S17, the only thing we change is enabling hardware addressing

MCP23S17::MCP23S17(uint8_t slave_select_pin, uint8_t aaa_hw_addr)
{
  spiio->begin();
  // Set the aaa hardware address for this chip by tying the 
  // MCP23S17's pins (A0, A1, and A2) to either 5v or GND.
  setup_ss(slave_select_pin);

  spiio->setClockDivider(CLOCK_DIVIDER);   // Sets the SPI bus speed
#ifdef ARDUINO
  spiio->setBitOrder(MSBFIRST);            // Sets SPI bus bit order (this is the default, setting it for good form!)
#endif
  spiio->setDataMode(SPI_MODE0);           // Sets the SPI bus timing mode (this is the default, setting it for good form!)
  
  spiio->setClockDivider(0 );   // Sets the SPI bus speed
  
  ::digitalWrite(slave_select_pin, LOW);
  spiio->transfer(0b01000000);
  spiio->transfer(IOCON);
  spiio->transfer(0b00001000);
  ::digitalWrite(slave_select_pin, HIGH);

  ::digitalWrite(slave_select_pin, LOW);
  spiio->transfer(0b01001110);
  spiio->transfer(IOCON);
  spiio->transfer(0b00001000);
  ::digitalWrite(slave_select_pin, HIGH);
  
  
  
  // We enable HAEN on all connected devices before we can address them individually
  setup_device(0x07);
  write_addr(IOCON, read_addr(IOCON)|HAEN);

  setup_device(0x00);
  write_addr(IOCON, read_addr(IOCON)|HAEN);

  // Remember the hardware address for this chip
  setup_device(aaa_hw_addr);
}

//------------------ protected -----------------------------------------------
uint16_t MCP23X17::byte2uint16(uint8_t high_byte, uint8_t low_byte)
{
  return (uint16_t)high_byte<<8 | (uint16_t)low_byte;
}

uint8_t MCP23X17::uint16_high_byte(uint16_t uint16)
{
  return (uint8_t)(uint16>>8);
}

uint8_t MCP23X17::uint16_low_byte(uint16_t uint16)
{
  return (uint8_t)(uint16 & 0x00FF);
}

void MCP23S17::setup_ss(uint8_t slave_select_pin)
{
  // Set slave select (Chip Select) pin for SPI Bus, and start high (disabled)
  ::pinMode(slave_select_pin,OUTPUT);
  ::digitalWrite(slave_select_pin,HIGH);
  this->slave_select_pin = slave_select_pin;
}

void MCP23S17::setup_device(uint8_t aaa_hw_addr)
{
  this->aaa_hw_addr = aaa_hw_addr;
  this->read_cmd  = 0x40 | aaa_hw_addr<<1 | 1<<0; // MCP23S17_READ  = B0100AAA1 
  this->write_cmd = 0x40 | aaa_hw_addr<<1 | 0<<0; // MCP23S17_WRITE = B0100AAA0
  write_addr(IOCON, read_addr(IOCON)|SEQOP); // no need to enable SEQOP if BANK=0
}

uint16_t MCP23S17::read_addr(uint8_t addr)
{
  uint8_t low_byte;
  uint8_t high_byte;
  ::digitalWrite(slave_select_pin, LOW);
  spiio->transfer(read_cmd);
  spiio->transfer(addr);
  low_byte  = spiio->transfer(0x0/*dummy data for read*/);
  high_byte = spiio->transfer(0x0/*dummy data for read*/);
  ::digitalWrite(slave_select_pin, HIGH);
  return byte2uint16(high_byte,low_byte);
}

uint8_t MCP23S17::read_addr_byte(uint8_t addr)
{
  uint8_t low_byte;
  ::digitalWrite(slave_select_pin, LOW);
//	PORTB &= ~(1<<PB0);
  spiio->transfer(read_cmd);
  spiio->transfer(addr);
  low_byte  = spiio->transfer(0x0/*dummy data for read*/);
  ::digitalWrite(slave_select_pin, HIGH);
	//PORTB |= (1<<PB0);
  return low_byte;
}


void MCP23S17::write_addr(uint8_t addr, uint16_t data)
{
  ::digitalWrite(slave_select_pin, LOW);
  spiio->transfer(write_cmd);
  spiio->transfer(addr);
  spiio->transfer(uint16_low_byte(data));
  spiio->transfer(uint16_high_byte(data));
  ::digitalWrite(slave_select_pin, HIGH);
}

void MCP23S17::write_addr_byte(uint8_t addr, uint8_t data)
{
//	PORTB &= ~(1<<PB0);
  ::digitalWrite(slave_select_pin, LOW);
  spiio->transfer(write_cmd);
  spiio->transfer(addr);
  spiio->transfer(data);
  ::digitalWrite(slave_select_pin, HIGH);
//  	PORTB |= (1<<PB0);
}


//---------- public ----------------------------------------------------

void MCP23X17::pinMode(bool mode) {
  uint16_t input_pins;
  if(mode == INPUT)
    input_pins = 0xFFFF;
  else
    input_pins = 0x0000;

  write_addr(IODIR, input_pins);
}

void MCP23X17::portA(uint8_t value)
{
  write_addr_byte(GPIOA,value);
}

void MCP23X17::portB(uint8_t value)
{
  write_addr_byte(GPIOA,value);
}

uint8_t MCP23X17::portA(void)
{
  return read_addr_byte(GPIOA);
}

uint8_t MCP23X17::portB(void)
{
  return read_addr_byte(GPIOB);
}


void MCP23X17::port(uint16_t value)
{
  write_addr(GPIO,value);
}

uint16_t MCP23X17::port()
{
  return read_addr(GPIO);
}

void MCP23X17::ddrA(uint8_t val)
{
  write_addr_byte(IODIRA,val);
}

void MCP23X17::ddrB(uint8_t val)
{
 write_addr_byte(IODIRB,val);
}

void MCP23X17::pinMode(uint8_t pin, bool mode)
{
  if(mode == INPUT)
    write_addr(IODIR, read_addr(IODIR) | 1<<pin );
  else
    write_addr(IODIR, read_addr(IODIR) & ~(1<<pin) );
}


void MCP23X17::pinModeA(uint8_t pin, bool mode)
{
  if(mode)
    write_addr_byte(IODIRA, read_addr_byte(IODIRA) | 1<<pin );
  else
    write_addr_byte(IODIRA, read_addr_byte(IODIRA) & ~(1<<pin) );
}

void MCP23X17::pinA(uint8_t pin, bool mode)
{
  if(mode)
    write_addr_byte(GPIOA, read_addr_byte(GPIOA) | 1<<pin );
  else
    write_addr_byte(GPIOA, read_addr_byte(GPIOA) & ~(1<<pin) );
}

void MCP23X17::pinB(uint8_t pin, bool mode)
{
  if(mode)
    write_addr_byte(GPIOB, read_addr_byte(GPIOB) | 1<<pin );
  else
    write_addr_byte(GPIOB, read_addr_byte(GPIOB) & ~(1<<pin) );
}


void MCP23X17::pinModeB(uint8_t pin, bool mode)
{
  if(mode)
    write_addr_byte(IODIRB, read_addr_byte(IODIRB) | 1<<pin );
  else
    write_addr_byte(IODIRB, read_addr_byte(IODIRB) & ~(1<<pin) );
}




void MCP23X17::digitalWrite(uint8_t pin, bool value)
{
  if(value)
    write_addr(GPIO, read_addr(GPIO) | 1<<pin );  
  else
    write_addr(GPIO, read_addr(GPIO) & ~(1<<pin) );  
}

int MCP23X17::digitalRead(uint8_t pin)
{
  return (int)(read_addr(GPIO) & 1<<pin);
}



// ---------------------------------------------------------------
// MCP23017 I2C
// ---------------------------------------------------------------
#ifdef ENABLE_I2C
MCP23017::MCP23017( uint8_t aaa_hw_addr)
{
	Wire.begin();	//start I2c as master

  // Remember the hardware address for this chip
  this->aaa_hw_addr = aaa_hw_addr;
  this->mcp_addr  = 0x20 | aaa_hw_addr; // MCP23017  = B0100AAA1, but shifted in wire 
}

uint16_t MCP23017::read_addr(uint8_t addr)
{
	Wire.beginTransmission(mcp_addr); 
	Wire.write((uint8_t)addr);	
	Wire.endTransmission();
	
	Wire.requestFrom((uint8_t)mcp_addr ,(uint8_t) 2 );
	return ( Wire.read() ) | ( Wire.read() << 8);
}

uint8_t MCP23017::read_addr_byte(uint8_t addr)
{
	Wire.beginTransmission(mcp_addr); 
	Wire.write((uint8_t)addr);	
	Wire.endTransmission();
	
	Wire.requestFrom((uint8_t)mcp_addr ,(uint8_t) 1 );
	return Wire.read();
}


void MCP23017::write_addr(uint8_t addr, uint16_t data)
{
	Wire.beginTransmission(mcp_addr); 
	Wire.write((uint8_t)addr);	
	Wire.write((uint8_t)( data& 0xff));	
	Wire.write((uint8_t)( (data>>8)& 0xff));	
	Wire.endTransmission();
}

void MCP23017::write_addr_byte(uint8_t addr, uint8_t data)
{
	Wire.beginTransmission(mcp_addr); 
	Wire.write((uint8_t)addr);	
	Wire.write((uint8_t)( data & 0xff));	
	Wire.endTransmission();
}
#endif //ENABLE_i2C
