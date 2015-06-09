/*
 * SpiRAM.cpp - Library for driving a 23k1024 SPI attached SRAM chip
 */ 

#include <SPI.h>
#include <SpiRAM.h>

// ******************************************************************************************
// Constructor
// ******************************************************************************************
SpiRAM::SpiRAM(byte ssPin)
{
  SPI.begin();
  // Ensure the RAM chip is disabled in the first instance
  disable();

  // Set the spi mode using the requested clock speed
  SPI.setClockDivider(CLOCK_DIVIDER_20_MHZ);
  _ssPin = ssPin;
  
  // Set the RAM operarion mode flag according to the chip default
  _current_mode = BYTE_MODE;
}

// ******************************************************************************************
// Enable and disable helper functions
// ******************************************************************************************
void SpiRAM::enable()
{
  digitalWrite(_ssPin, LOW);
}

void SpiRAM::disable()
{
  digitalWrite(_ssPin, HIGH);
}

// ******************************************************************************************
// Byte transfer functions
// ******************************************************************************************
uint8_t SpiRAM::read_byte(uint32_t address)
{
  uint8_t read_byte;

  // Set byte mode
  _set_mode(BYTE_MODE);
  
  // Write address, read data
  enable();
  SPI.transfer(READ);
  SPI.transfer((uint8_t)(address >> 16));
  SPI.transfer((uint8_t)(address >> 8));
  SPI.transfer((uint8_t)address);
  read_byte = SPI.transfer(0xFF);
  
  disable();
  
  return read_byte;
}

uint8_t SpiRAM::write_byte(uint32_t address, uint8_t data_byte)
{
  // Set byte mode
  _set_mode(BYTE_MODE);
  
  // Write address, read data
  enable();
  SPI.transfer(WRITE);
  SPI.transfer((uint8_t)(address >> 16));
  SPI.transfer((uint8_t)(address >> 8));
  SPI.transfer((uint8_t)address);
  SPI.transfer(data_byte);
  disable();

  return data_byte;
}

// ******************************************************************************************
// Page transfer functions. Bound to current page. Passing the boundary 
//  will wrap to the beginning
// ******************************************************************************************
void SpiRAM::read_page(uint32_t address, uint8_t *buffer)
{
  int i;

  // Set byte mode
  _set_mode(PAGE_MODE);
  
  // Write address, read data
  enable();
  SPI.transfer(READ);
  SPI.transfer((uint8_t)(address >> 16));
  SPI.transfer((uint8_t)(address >> 8));
  SPI.transfer((uint8_t)address);
  for (i = 0; i < 32; i++) 
  {
    buffer[i] = SPI.transfer(0xFF);
  }    
  disable();
}

void SpiRAM::write_page(uint32_t address, uint8_t *buffer)
{
  int i;

  // Set byte mode
  _set_mode(PAGE_MODE);
  
  // Write address, read data
  enable();
  SPI.transfer(WRITE);
  SPI.transfer((uint8_t)(address >> 16));
  SPI.transfer((uint8_t)(address >> 8));
  SPI.transfer((uint8_t)address);
  for (i = 0; i < 32; i++) 
  {
    SPI.transfer(buffer[i]);
  }    
  disable();
}

// ******************************************************************************************
// Stream transfer functions. Ignores page boundaries.
// ******************************************************************************************
void SpiRAM::read_stream(uint32_t address, uint8_t *buffer, int length)
{
  int i;

  // Set byte mode
  _set_mode(STREAM_MODE);
  
  // Write address, read data
  enable();
  SPI.transfer(READ);
  SPI.transfer((uint8_t)(address >> 16));
  SPI.transfer((uint8_t)(address >> 8));
  SPI.transfer((uint8_t)address);
  for (i = 0; i < length; i++)
  {
    buffer[i] = SPI.transfer(0xFF);
  }    
  disable();
}

void SpiRAM::write_stream(uint32_t address, uint8_t *buffer, int length)
{
  int i;

  // Set byte mode
  _set_mode(STREAM_MODE);
  
  // Write address, read data
  enable();
  SPI.transfer(WRITE);
  SPI.transfer((uint8_t)(address >> 16));
  SPI.transfer((uint8_t)(address >> 8));
  SPI.transfer((uint8_t)address);
  for (i = 0; i < length; i++)
  {
    SPI.transfer(buffer[i]);
  }    
  disable();
}

// ******************************************************************************************
// Mode handling
// ******************************************************************************************
void SpiRAM::_set_mode(char mode)
{
  if (mode != _current_mode)
  {
    enable();
    SPI.transfer(WRSR);
    SPI.transfer(mode);
    disable();
    _current_mode = mode;
  }
}

// ******************************************************************************************
// CAMERA OV7670  Image Control
// ******************************************************************************************
void SpiRAM::Set_Image_Columns(int ImgColumns)
{
  this->Image_Columns = ImgColumns;  
}

// ******************************************************************************************
// CAMERA OV7670  Image Control
// Image from 1 to 3
// ******************************************************************************************
void SpiRAM::write_camera_line(int Image, int Line, uint8_t *buffer)
{
  uint32_t address;
  
  // Calculate address
  address = ((Image -1) * IMAGE_RAM_RESERVED) + ((Line - 1) * Image_Columns);
  // Write data
  this->write_stream(address, buffer, Image_Columns);  
}

// ******************************************************************************************
// CAMERA OV7670 Image Control
// Image from 1 to 3
// ******************************************************************************************
void SpiRAM::read_camera_line(int Image, int Line, uint8_t *buffer)
{
  uint32_t address;
  
  // Calculate address
  address = ((Image -1) * IMAGE_RAM_RESERVED) + ((Line - 1) * Image_Columns);
  // read data
  this->read_stream(address, buffer, Image_Columns); 
}

// ******************************************************************************************
// CAMERA OV7670 640x480 Image Control
// Image from 1 to 3
// ******************************************************************************************
void SpiRAM::write_camera_pixel(int Image, int Line, int Column, uint8_t Pixel_value)
{
  uint32_t address;
  
  // Calculate address
  address = (((Image -1) * IMAGE_RAM_RESERVED) + ((Line - 1) * Image_Columns)) + (Column - 1);
  // Write data
  this->write_byte(address, Pixel_value);
}

// ******************************************************************************************
// CAMERA OV7670 640x480 Image Control
// Image from 1 to 3
// ******************************************************************************************
uint8_t SpiRAM::read_camera_pixel(int Image, int Line, int Column)
{
  uint32_t address;
  uint8_t value;
  // Calculate address
  address = (((Image -1) * IMAGE_RAM_RESERVED) + ((Line - 1) * Image_Columns)) + (Column - 1);
  
  // Read data
   value = this->read_byte(address);

  return value;
  
}

