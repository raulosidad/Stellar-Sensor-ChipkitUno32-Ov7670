/*
 * SpiRAM.h - Library for driving a 23k1024 SPI attached SRAM chip
 */

#ifndef SpiRAM_h
#define SpiRAM_h
 
#include <SPI.h>

// SRAM opcodes
#define WREN  6
#define WRDI  4
#define RDSR  5
#define WRSR  1
#define READ  3
#define WRITE 2

// SRAM Hold line override
#define HOLD 1

// SRAM modes
#define BYTE_MODE   (0x00 | HOLD)
#define PAGE_MODE   (0x80 | HOLD)
#define STREAM_MODE (0x40 | HOLD)

// Clock Divider for 20 MHz
#define CLOCK_DIVIDER_20_MHZ 1

// Image OV7670 Camera
#define IMAGE_RAM_RESERVED 77000   // MAX  VGA=307200 pixels
                                   // MAX QVGA= 76800 pixels
class SpiRAM
{
  public:
    SpiRAM(byte ssPin);
    uint8_t read_byte(uint32_t address);
    uint8_t write_byte(uint32_t address, uint8_t data_byte);
    void read_page(uint32_t address, uint8_t *buffer);
    void write_page(uint32_t address, uint8_t *buffer);
    void read_stream(uint32_t address, uint8_t *buffer, int length);
    void write_stream(uint32_t address, uint8_t *buffer, int length);
    
    //Camera
    void write_camera_line(int Image, int Line, uint8_t *buffer);
    void read_camera_line(int Image, int Line, uint8_t *buffer);
    void write_camera_pixel(int Image, int Line, int Column, uint8_t Pixel_value);
    uint8_t read_camera_pixel(int Image, int Line, int Column);
    void Set_Image_Columns(int ImgColumns);
    
  private:
    int Image_Columns;
    char _current_mode;
    byte _ssPin;
    void enable();
    void disable();
    void _set_mode(char mode); 
};

extern SpiRAM SpiRam;

#endif 
