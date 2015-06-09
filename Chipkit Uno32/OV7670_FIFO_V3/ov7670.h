#include "ov7670reg.h"

#define OV7670_REGMAX (201)
#define OV7670_ADDDR  (int) 0x21

class ov7670
{
public:  
    ov7670(TwoWire& s);
    void init();
    void PrintRegister(void); 
    void setSerial(HardwareSerial *s); 
    void Reset(void);
    void InitForFIFOWriteReset(void);
    void InitSetColorbar(void);
    void InitDefaultReg(void); 
    void InitRGB444(void);
    void InitRGB555(void);
    void InitRGB565(void);
    void InitYUV(void);
    void InitBayerRGB(void);
    void InitVGA(void); 
    void InitFIFO_2bytes_color_nealy_limit_size(void); 
    void InitVGA_3_4(void); 
    void InitQVGA(void); 
    void InitQQVGA(void); 
  
  private:
    uint8_t initialized;
    HardwareSerial *serial;
    TwoWire& I2C;
    void sccb_read(uint8_t address, uint8_t *data);
    void sccb_write(uint8_t address, uint8_t data);
};

