/* 
 * File:   spi.h
 * Author: Purinda Gunasekara <purinda@gmail.com>
 * 
 * Created on 24 June 2012, 11:00 AM
 *
 * changed by Arco van Geest <arco@appeltaart.mine.nu>
 */

#ifndef SPI_H
#define	SPI_H

#include <string>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <inttypes.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

using namespace std;

class SPI {
public:
	
	SPI();
	uint8_t transfernot(uint8_t tx_ );
	uint8_t transfer(uint8_t tx_[], uint8_t length );
	uint16_t transfer16(uint8_t tx_[] ,uint8_t length);

//	uint8_t read(uint8_t tx_[]);
//	uint16_t read(uint8_t tx_[]);
//	uint32_t read(uint8_t tx_[]);

	
	
	void transfer3(uint8_t cmd_,uint8_t reg_,uint8_t data_);
	virtual ~SPI();
	void init();	
	void begin();
	void setdevice( string devicefile );
	void setbits( uint8_t bits );
	void setspeed( uint32_t speed );
	void setClockDivider(uint8_t _cd) const { };
	void setBitOrder(uint8_t _bo) const { };
	void setDataMode(uint8_t _dm) const { };

private:

	// Default SPI device
	string device;
	// SPI Mode set 
	uint8_t mode;
	// word size
	uint8_t bits;
	// Set SPI speed
	uint32_t speed;
	int fd;

};

#endif	/* SPI_H */

