//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This file is for defining the link class for I2C communications.  
//
// Note, the PixyI2C class takes an optional argument, which is the I2C address 
// of the Pixy you want to talk to.  The default address is 0x54 (used when no 
// argument is used.)  So, for example, if you wished to talk to Pixy at I2C 
// address 0x55, declare like this:
//
// PixyI2C pixy(0x55);
//

#ifndef _PIXYI2C_H
#define _PIXYI2C_H

#include "TPixy.h"
#include "i2c_t3.h"

#define PIXY_I2C_TIMOUT 500
#define PIXY_I2C_DEFAULT_ADDR 0x54

class LinkI2C
{
public:
  void init()
  {
    // scrap this
    // Wire.begin();
  }
  void setArg(uint16_t arg)
  {
    if (arg==PIXY_DEFAULT_ARGVAL)
      addr = PIXY_I2C_DEFAULT_ADDR;
  	else
  	  addr = arg;
  }
  uint16_t getWord()
  {
    uint16_t w;
  	uint8_t c;
  	Wire.requestFrom((int)addr, 2, I2C_STOP, PIXY_I2C_TIMOUT);
    c = Wire.read();
    w = Wire.read();
    w <<= 8;
    w |= c; 
    return w;
  }
  uint8_t getByte()
  {
  	if (Wire.requestFrom((int)addr, 1, I2C_STOP, PIXY_I2C_TIMOUT) == 0){ return 0; }
  	return Wire.read();
  }

  int8_t send(uint8_t *data, uint8_t len)
  {
    Wire.beginTransmission(addr);
    Wire.write(data, len);
  	Wire.endTransmission(I2C_STOP, PIXY_I2C_TIMOUT);
  	return len;
  }
	
private:
  uint8_t addr;
};

typedef TPixy<LinkI2C> PixyI2C;

#endif
