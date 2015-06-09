#include "ov7670.h"

#define OV7670_REGMAX (201)

// Constructor
ov7670::ov7670(TwoWire& s): I2C(s)
{
  initialized = false;
  serial = 0;
 }

void ov7670::init() 
{
  if (!initialized) 
  {
    initialized = true;
  }
}

 // print register
void ov7670::PrintRegister(void) {   
    char dataString[2] = {0};

    serial->print("AD\t +0\t +1\t +2\t +3\t +4\t +5\t +6\t +7\t +8\t +9\t +A\t +B\t +C\t +D\t +E\t +F");
    for (int i=0;i<OV7670_REGMAX;i++)
    {
        uint8_t data;
        sccb_read(i, &data); // READ REG
        if ((i & 0x0F) == 0) 
        {
            serial->print("\r\n");       
            sprintf(dataString, "%.2X", i);   
            serial->print(dataString);
            serial->print("\t");
        }
        sprintf(dataString, "%.2X",data);
        serial->print(dataString);
        serial->print("\t");
    }
    serial->print("AD_END\r\n");
}

void ov7670::setSerial(HardwareSerial *s) {
	serial = s;
}

void ov7670::Reset(void) {    
    sccb_write(REG_COM7,COM7_RESET); // RESET CAMERA
}

void ov7670::InitForFIFOWriteReset(void) {
    sccb_write(REG_COM10, COM10_VS_NEG);
}

void ov7670::InitSetColorbar(void)  {
    uint8_t reg_com7;
    sccb_read(REG_COM7, &reg_com7);
    // color bar
    sccb_write(REG_COM17, reg_com7|COM17_CBAR);
}

void ov7670::InitDefaultReg(void) {
    // Gamma curve values
    sccb_write(0x7a, 0x20);
    sccb_write(0x7b, 0x10);
    sccb_write(0x7c, 0x1e);
    sccb_write(0x7d, 0x35);
    sccb_write(0x7e, 0x5a);
    sccb_write(0x7f, 0x69);
    sccb_write(0x80, 0x76);
    sccb_write(0x81, 0x80);
    sccb_write(0x82, 0x88);
    sccb_write(0x83, 0x8f);
    sccb_write(0x84, 0x96);
    sccb_write(0x85, 0xa3);
    sccb_write(0x86, 0xaf);
    sccb_write(0x87, 0xc4);
    sccb_write(0x88, 0xd7);
    sccb_write(0x89, 0xe8);
    
    // AGC and AEC parameters.  Note we start by disabling those features,
    //then turn them only after tweaking the values.
    sccb_write(REG_COM8, COM8_FASTAEC | COM8_AECSTEP | COM8_BFILT);
    sccb_write(REG_GAIN, 0);
    sccb_write(REG_AECH, 0);
    sccb_write(REG_COM4, 0x40);
    // magic reserved bit
    sccb_write(REG_COM9, 0x18);
    // 4x gain + magic rsvd bit
    sccb_write(REG_BD50MAX, 0x05);
    sccb_write(REG_BD60MAX, 0x07);
    sccb_write(REG_AEW, 0x95);
    sccb_write(REG_AEB, 0x33);
    sccb_write(REG_VPT, 0xe3);
    sccb_write(REG_HAECC1, 0x78);
    sccb_write(REG_HAECC2, 0x68);
    sccb_write(0xa1, 0x03);
    // magic
    sccb_write(REG_HAECC3, 0xd8);
    sccb_write(REG_HAECC4, 0xd8);
    sccb_write(REG_HAECC5, 0xf0);
    sccb_write(REG_HAECC6, 0x90);
    sccb_write(REG_HAECC7, 0x94);
    sccb_write(REG_COM8, COM8_FASTAEC|COM8_AECSTEP|COM8_BFILT|COM8_AGC|COM8_AEC);
    
    // Almost all of these are magic "reserved" values.
    sccb_write(REG_COM5, 0x61);
    sccb_write(REG_COM6, 0x4b);
    sccb_write(0x16, 0x02);
    sccb_write(REG_MVFP, 0x07);
    sccb_write(0x21, 0x02);
    sccb_write(0x22, 0x91);
    sccb_write(0x29, 0x07);
    sccb_write(0x33, 0x0b);
    sccb_write(0x35, 0x0b);
    sccb_write(0x37, 0x1d);
    sccb_write(0x38, 0x71);
    sccb_write(0x39, 0x2a);
    sccb_write(REG_COM12, 0x78);
    sccb_write(0x4d, 0x40);
    sccb_write(0x4e, 0x20);
    sccb_write(REG_GFIX, 0);
    sccb_write(0x6b, 0x0a);
    sccb_write(0x74, 0x10);
    sccb_write(0x8d, 0x4f);
    sccb_write(0x8e, 0);
    sccb_write(0x8f, 0);
    sccb_write(0x90, 0);
    sccb_write(0x91, 0);
    sccb_write(0x96, 0);
    sccb_write(0x9a, 0);
    sccb_write(0xb0, 0x84);
    sccb_write(0xb1, 0x0c);
    sccb_write(0xb2, 0x0e);
    sccb_write(0xb3, 0x82);
    sccb_write(0xb8, 0x0a);
    
    // More reserved magic, some of which tweaks white balance
    sccb_write(0x43, 0x0a);
    sccb_write(0x44, 0xf0);
    sccb_write(0x45, 0x34);
    sccb_write(0x46, 0x58);
    sccb_write(0x47, 0x28);
    sccb_write(0x48, 0x3a);
    sccb_write(0x59, 0x88);
    sccb_write(0x5a, 0x88);
    sccb_write(0x5b, 0x44);
    sccb_write(0x5c, 0x67);
    sccb_write(0x5d, 0x49);
    sccb_write(0x5e, 0x0e);
    sccb_write(0x6c, 0x0a);
    sccb_write(0x6d, 0x55);
    sccb_write(0x6e, 0x11);
    sccb_write(0x6f, 0x9f);
    // "9e for advance AWB"
    sccb_write(0x6a, 0x40);
    sccb_write(REG_BLUE, 0x40);
    sccb_write(REG_RED, 0x60);
    sccb_write(REG_COM8, COM8_FASTAEC|COM8_AECSTEP|COM8_BFILT|COM8_AGC|COM8_AEC|COM8_AWB);
    
    // Matrix coefficients
    sccb_write(0x4f, 0x80);
    sccb_write(0x50, 0x80);
    sccb_write(0x51, 0);
    sccb_write(0x52, 0x22);
    sccb_write(0x53, 0x5e);
    sccb_write(0x54, 0x80);
    sccb_write(0x58, 0x9e);
    
    sccb_write(REG_COM16, COM16_AWBGAIN);
    sccb_write(REG_EDGE, 0);
    sccb_write(0x75, 0x05);
    sccb_write(0x76, 0xe1);
    sccb_write(0x4c, 0);
    sccb_write(0x77, 0x01);
    sccb_write(0x4b, 0x09);
    sccb_write(0xc9, 0x60);
    sccb_write(REG_COM16, 0x38);
    sccb_write(0x56, 0x40);
    
    sccb_write(0x34, 0x11);
    sccb_write(REG_COM11, COM11_EXP|COM11_HZAUTO_ON);
    sccb_write(0xa4, 0x88);
    sccb_write(0x96, 0);
    sccb_write(0x97, 0x30);
    sccb_write(0x98, 0x20);
    sccb_write(0x99, 0x30);
    sccb_write(0x9a, 0x84);
    sccb_write(0x9b, 0x29);
    sccb_write(0x9c, 0x03);
    sccb_write(0x9d, 0x4c);
    sccb_write(0x9e, 0x3f);
    sccb_write(0x78, 0x04);
    
    // Extra-weird stuff.  Some sort of multiplexor register
    sccb_write(0x79, 0x01);
    sccb_write(0xc8, 0xf0);
    sccb_write(0x79, 0x0f);
    sccb_write(0xc8, 0x00);
    sccb_write(0x79, 0x10);
    sccb_write(0xc8, 0x7e);
    sccb_write(0x79, 0x0a);
    sccb_write(0xc8, 0x80);
    sccb_write(0x79, 0x0b);
    sccb_write(0xc8, 0x01);
    sccb_write(0x79, 0x0c);
    sccb_write(0xc8, 0x0f);
    sccb_write(0x79, 0x0d);
    sccb_write(0xc8, 0x20);
    sccb_write(0x79, 0x09);
    sccb_write(0xc8, 0x80);
    sccb_write(0x79, 0x02);
    sccb_write(0xc8, 0xc0);
    sccb_write(0x79, 0x03);
    sccb_write(0xc8, 0x40);
    sccb_write(0x79, 0x05);
    sccb_write(0xc8, 0x30);
    sccb_write(0x79, 0x26);
}

void ov7670::InitRGB444(void){
    uint8_t reg_com7;
    sccb_read(REG_COM7, &reg_com7);

    sccb_write(REG_COM7, reg_com7|COM7_RGB);
    sccb_write(REG_RGB444, RGB444_ENABLE|RGB444_XBGR);
    sccb_write(REG_COM15, COM15_R01FE|COM15_RGB444);

    sccb_write(REG_COM1, 0x40);                          // Magic reserved bit
    sccb_write(REG_COM9, 0x38);                          // 16x gain ceiling; 0x8 is reserved bit
    sccb_write(0x4f, 0xb3);                              // "matrix coefficient 1"
    sccb_write(0x50, 0xb3);                              // "matrix coefficient 2"
    sccb_write(0x51, 0x00);                              // vb
    sccb_write(0x52, 0x3d);                              // "matrix coefficient 4"
    sccb_write(0x53, 0xa7);                              // "matrix coefficient 5"
    sccb_write(0x54, 0xe4);                              // "matrix coefficient 6"
    sccb_write(REG_COM13, COM13_GAMMA|COM13_UVSAT|0x2);  // Magic rsvd bit

    sccb_write(REG_TSLB, 0x04);
}

void ov7670::InitRGB555(void){
    uint8_t reg_com7;
    sccb_read(REG_COM7, &reg_com7);

    sccb_write(REG_COM7, reg_com7|COM7_RGB);
    sccb_write(REG_RGB444, RGB444_DISABLE);
    sccb_write(REG_COM15, COM15_RGB555|COM15_R00FF);

    sccb_write(REG_TSLB, 0x04);

    sccb_write(REG_COM1, 0x00);
    sccb_write(REG_COM9, 0x38);      // 16x gain ceiling; 0x8 is reserved bit
    sccb_write(0x4f, 0xb3);          // "matrix coefficient 1"
    sccb_write(0x50, 0xb3);          // "matrix coefficient 2"
    sccb_write(0x51, 0x00);          // vb
    sccb_write(0x52, 0x3d);          // "matrix coefficient 4"
    sccb_write(0x53, 0xa7);          // "matrix coefficient 5"
    sccb_write(0x54, 0xe4);          // "matrix coefficient 6"
    sccb_write(REG_COM13, COM13_GAMMA|COM13_UVSAT);
}

void ov7670::InitRGB565(void){
    uint8_t reg_com7;
    sccb_read(REG_COM7, &reg_com7);

    sccb_write(REG_COM7, reg_com7|COM7_RGB);
    sccb_write(REG_RGB444, RGB444_DISABLE);
    sccb_write(REG_COM15, COM15_R00FF|COM15_RGB565);

    sccb_write(REG_TSLB, 0x04);

    sccb_write(REG_COM1, 0x00);
    sccb_write(REG_COM9, 0x38);      // 16x gain ceiling; 0x8 is reserved bit
    sccb_write(0x4f, 0xb3);          // "matrix coefficient 1"
    sccb_write(0x50, 0xb3);          // "matrix coefficient 2"
    sccb_write(0x51, 0x00);          // vb
    sccb_write(0x52, 0x3d);          // "matrix coefficient 4"
    sccb_write(0x53, 0xa7);          // "matrix coefficient 5"
    sccb_write(0x54, 0xe4);          // "matrix coefficient 6"
    sccb_write(REG_COM13, COM13_GAMMA|COM13_UVSAT);
}

void ov7670::InitYUV(void){
    uint8_t reg_com7;
    sccb_read(REG_COM7, &reg_com7);

    sccb_write(REG_COM7, reg_com7|COM7_YUV);
    sccb_write(REG_RGB444, RGB444_DISABLE);
    sccb_write(REG_COM15, COM15_R00FF);

    sccb_write(REG_TSLB, 0x04);
//       sccb_write(REG_TSLB, 0x14);
//       sccb_write(REG_MANU, 0x00);
//       sccb_write(REG_MANV, 0x00);
    
    sccb_write(REG_COM1, 0x00);
    sccb_write(REG_COM9, 0x18);     // 4x gain ceiling; 0x8 is reserved bit
    sccb_write(0x4f, 0x80);         // "matrix coefficient 1"
    sccb_write(0x50, 0x80);         // "matrix coefficient 2"
    sccb_write(0x51, 0x00);         // vb
    sccb_write(0x52, 0x22);         // "matrix coefficient 4"
    sccb_write(0x53, 0x5e);         // "matrix coefficient 5"
    sccb_write(0x54, 0x80);         // "matrix coefficient 6"
    sccb_write(REG_COM13, COM13_GAMMA|COM13_UVSAT|COM13_UVSWAP);
}

void ov7670::InitBayerRGB(void){
    uint8_t reg_com7;
    sccb_read(REG_COM7, &reg_com7);

    // odd line BGBG... even line GRGR...
    sccb_write(REG_COM7, reg_com7|COM7_BAYER);
    // odd line GBGB... even line RGRG...
    //sccb_write(REG_COM7, reg_com7|COM7_PBAYER);

    sccb_write(REG_RGB444, RGB444_DISABLE);
    sccb_write(REG_COM15, COM15_R00FF);

    sccb_write(REG_COM13, 0x08); /* No gamma, magic rsvd bit */
    sccb_write(REG_COM16, 0x3d); /* Edge enhancement, denoise */
    sccb_write(REG_REG76, 0xe1); /* Pix correction, magic rsvd */

    sccb_write(REG_TSLB, 0x04);
}

void ov7670::InitVGA(void) {
    // VGA
    uint8_t reg_com7;
    sccb_read(REG_COM7, &reg_com7);

    sccb_write(REG_COM7,reg_com7|COM7_VGA);

    sccb_write(REG_HSTART,HSTART_VGA);
    sccb_write(REG_HSTOP,HSTOP_VGA);
    sccb_write(REG_HREF,HREF_VGA);
    sccb_write(REG_VSTART,VSTART_VGA);
    sccb_write(REG_VSTOP,VSTOP_VGA);
    sccb_write(REG_VREF,VREF_VGA);
    sccb_write(REG_COM3, COM3_VGA);
    sccb_write(REG_COM14, COM14_VGA);
    sccb_write(REG_SCALING_XSC, SCALING_XSC_VGA);
    sccb_write(REG_SCALING_YSC, SCALING_YSC_VGA);
    sccb_write(REG_SCALING_DCWCTR, SCALING_DCWCTR_VGA);
    sccb_write(REG_SCALING_PCLK_DIV, SCALING_PCLK_DIV_VGA);
    sccb_write(REG_SCALING_PCLK_DELAY, SCALING_PCLK_DELAY_VGA);
}

void ov7670::InitFIFO_2bytes_color_nealy_limit_size(void) {
    // nealy FIFO limit 544x360
    uint8_t reg_com7;
    sccb_read(REG_COM7, &reg_com7);

    sccb_write(REG_COM7,reg_com7|COM7_VGA);

    sccb_write(REG_HSTART,HSTART_VGA);
    sccb_write(REG_HSTOP,HSTOP_VGA);
    sccb_write(REG_HREF,HREF_VGA);
    sccb_write(REG_VSTART,VSTART_VGA);
    sccb_write(REG_VSTOP,VSTOP_VGA);
    sccb_write(REG_VREF,VREF_VGA);
    sccb_write(REG_COM3, COM3_VGA);
    sccb_write(REG_COM14, COM14_VGA);
    sccb_write(REG_SCALING_XSC, SCALING_XSC_VGA);
    sccb_write(REG_SCALING_YSC, SCALING_YSC_VGA);
    sccb_write(REG_SCALING_DCWCTR, SCALING_DCWCTR_VGA);
    sccb_write(REG_SCALING_PCLK_DIV, SCALING_PCLK_DIV_VGA);
    sccb_write(REG_SCALING_PCLK_DELAY, SCALING_PCLK_DELAY_VGA);

    sccb_write(REG_HSTART, 0x17);
    sccb_write(REG_HSTOP, 0x5b);
    sccb_write(REG_VSTART, 0x12);
    sccb_write(REG_VSTOP, 0x6c);
}

void ov7670::InitVGA_3_4(void) {
    // VGA 3/4 -> 480x360
    uint8_t reg_com7;
    sccb_read(REG_COM7, &reg_com7);

    sccb_write(REG_COM7,reg_com7|COM7_VGA);

    sccb_write(REG_HSTART,HSTART_VGA);
    sccb_write(REG_HSTOP,HSTOP_VGA);
    sccb_write(REG_HREF,HREF_VGA);
    sccb_write(REG_VSTART,VSTART_VGA);
    sccb_write(REG_VSTOP,VSTOP_VGA);
    sccb_write(REG_VREF,VREF_VGA);
    sccb_write(REG_COM3, COM3_VGA);
    sccb_write(REG_COM14, COM14_VGA);
    sccb_write(REG_SCALING_XSC, SCALING_XSC_VGA);
    sccb_write(REG_SCALING_YSC, SCALING_YSC_VGA);
    sccb_write(REG_SCALING_DCWCTR, SCALING_DCWCTR_VGA);
    sccb_write(REG_SCALING_PCLK_DIV, SCALING_PCLK_DIV_VGA);
    sccb_write(REG_SCALING_PCLK_DELAY, SCALING_PCLK_DELAY_VGA);

    sccb_write(REG_HSTART, 0x1b);
    sccb_write(REG_HSTOP, 0x57);
    sccb_write(REG_VSTART, 0x12);
    sccb_write(REG_VSTOP, 0x6c);
}

void ov7670::InitQVGA(void) {
    // QQVGA
    uint8_t reg_com7;
    sccb_read(REG_COM7, &reg_com7);
    
    sccb_write(REG_COM7,reg_com7|COM7_QVGA);
    
    sccb_write(REG_HSTART,HSTART_QVGA);
    sccb_write(REG_HSTOP,HSTOP_QVGA);
    sccb_write(REG_HREF,HREF_QVGA);
    sccb_write(REG_VSTART,VSTART_QVGA);
    sccb_write(REG_VSTOP,VSTOP_QVGA);
    sccb_write(REG_VREF,VREF_QVGA);
    sccb_write(REG_COM3, COM3_QVGA);
    sccb_write(REG_COM14, COM14_QVGA);
    sccb_write(REG_SCALING_XSC, SCALING_XSC_QVGA);
    sccb_write(REG_SCALING_YSC, SCALING_YSC_QVGA);
    sccb_write(REG_SCALING_DCWCTR, SCALING_DCWCTR_QVGA);
    sccb_write(REG_SCALING_PCLK_DIV, SCALING_PCLK_DIV_QVGA);
    sccb_write(REG_SCALING_PCLK_DELAY, SCALING_PCLK_DELAY_QVGA);
}

void ov7670::InitQQVGA(void) {
    // QQVGA
    uint8_t reg_com7;
    sccb_read(REG_COM7, &reg_com7);
    
    sccb_write(REG_COM7,reg_com7|COM7_QQVGA);

    sccb_write(REG_HSTART,HSTART_QQVGA);
    sccb_write(REG_HSTOP,HSTOP_QQVGA);
    sccb_write(REG_HREF,HREF_QQVGA);
    sccb_write(REG_VSTART,VSTART_QQVGA);
    sccb_write(REG_VSTOP,VSTOP_QQVGA);
    sccb_write(REG_VREF,VREF_QQVGA);
    sccb_write(REG_COM3, COM3_QQVGA);
    sccb_write(REG_COM14, COM14_QQVGA);
    sccb_write(REG_SCALING_XSC, SCALING_XSC_QQVGA);
    sccb_write(REG_SCALING_YSC, SCALING_YSC_QQVGA);
    sccb_write(REG_SCALING_DCWCTR, SCALING_DCWCTR_QQVGA);
    sccb_write(REG_SCALING_PCLK_DIV, SCALING_PCLK_DIV_QQVGA);
    sccb_write(REG_SCALING_PCLK_DELAY, SCALING_PCLK_DELAY_QQVGA);
}

void ov7670::sccb_read(uint8_t address, uint8_t *data)
{
 I2C.beginTransmission(OV7670_ADDDR); // OV7670 Write Address
 I2C.send(address); // register to read
 I2C.endTransmission();
 
 I2C.requestFrom(OV7670_ADDDR, 0x1); // read a byte at OV7670 Read Address
 while(!I2C.available()) {} // wait for data
 *data = I2C.receive();
}

void ov7670::sccb_write(uint8_t address, uint8_t data)
{
 I2C.beginTransmission(OV7670_ADDDR); // OV7670 Write Address
 I2C.send(address); // register to write
 I2C.send(data); // data to write
 I2C.endTransmission();  
}
  


