#include "Program.h"
#include <Wire.h>
#include <SPI.h>

#define   MANUAL        1
#define   STAR_TRACKER  2
#define   Ithresh       (int) 100
#define   aRoi          (int) 11

int Mode;
StarCenter*  Centroides;
unit_vector* Img_Uvectors;
int cont_CM = 0;
int NumStarsMatched = 0;
unit_vector *Candidate_Uvectors;
unit_vector *Catalog_Uvectors;
uint32_t *Catalog_Star_IDs;
double** Attitude = new double*[3];

//******************************************************************************************************************
//                            PROGRAM FUNCTIONS
//******************************************************************************************************************
void setup()
{
   // Trigger
   pinMode(TRIG, INPUT);
   
  // Start serial for output
  Serial.begin(115200);
    
  //I2C 
  I2C.begin(); 
  
  // Camera Signaling
  TRISE = 0xFF;  // Pins 26 - 33 as INPUT for D0-D7 Camera Data
  TRISD = B11011001;  
  WEN_LOW; 
  RRST_HIGH;
  RCLK_LOW;

  Camera.init();
  Camera.setSerial(&Serial);
  
  Serial.println(HEADER_SIZE, DEC);
  Serial.println(STAR_PAIR_SIZE, DEC);
  Serial.println(STAR_ID_SIZE, DEC);
  Serial.println(U_VECTOR_SIZE, DEC);
     
  Serial.println("CAMERA CONFIG PRE");
  Camera.PrintRegister();

  // Default Camera Values
  Set_Camera_Config(YUV_GreyScale,QVGA); 
  
  Serial.println("CAMERA CONFIG POST");
  Camera.PrintRegister();
  
  // SPI RAM
  //  SS Signal
  pinMode(SLAVESELECT,OUTPUT);
  digitalWrite(SLAVESELECT,HIGH); //disable device
  
  Serial.println("SPI RAM Initialized...");

    
  // Catálogo
  Eeprom.init();
  Star_Catalog.header.Number_of_Stars = 385;
  Star_Catalog.StarPairs[Star_Catalog.header.Number_of_Stars];
  
  Mode = MANUAL;
  
}
 
void loop()
{
   String DataRead= "";

// *********************************************************************************************************************
//               MODO MANUAL
// *********************************************************************************************************************
 if (Mode == MANUAL)
 {
    if (digitalRead(TRIG) == HIGH)
  {  
   GetImage_FIFO_to_RAM(1);
   Image_RAM_to_Serial(1);
   delay(500);
   }  
  
  // Read Commands from Serial Port
   DataRead = Serial_ReadLine();
   if (DataRead == "<CAPTURE_IMAGE_FIFO>")
   {
    CaptureImage_to_FIFO();
    GetImage_FIFO_to_RAM(1);
    Serial.println("<CAPTURE_IMAGE_FIFO><ACK>");      
   }
   else if (DataRead == "<READ_IMAGE_FIFO>")
   {
     Serial.println("<READ_IMAGE_FIFO><ACK>");
     Image_RAM_to_Serial(1);
     //GetImage_FIFO_to_Serial_Line();      
   }
   else if (DataRead == "<READ_CAMERA_CONFIG>")
   {
     Serial.println("<READ_CAMERA_CONFIG><ACK>");
     Camera.PrintRegister();      
   }
   
   // CATALOG HEADER
   // __________________________________________________________________
   else if (DataRead == "<STORE_CATALOG_HEADER>")
   {
     uint8_t buffer[HEADER_SIZE];
     Serial.println("<STORE_CATALOG_HEADER><ACK>");   
     delay(200); 
     // Read Catalog from Serial
     Serial_ReadBytes(buffer, HEADER_SIZE);
     // Store in EEPROM
     Eeprom.write_Header(buffer); 
   }
   else if (DataRead == "<READ_CATALOG_HEADER>")
   {
     uint8_t buffer[HEADER_SIZE];
     Serial.println("<READ_CATALOG_HEADER><ACK>");     
     // Read Catalog from EEPROM
     Eeprom.read_Header(buffer);
     // Send to PC
     Serial.write(buffer,HEADER_SIZE);
   }
   
   // STAR PAIRS
   // __________________________________________________________________
    else if (DataRead == "<STORE_STAR_PAIR>")
   {
     uint8_t buffer[STAR_PAIR_SIZE]; 
     // Send ACK 
     Serial.println("<STORE_STAR_PAIR><ACK>");   
     delay(200); 
     // Read Num
     int Num = Serial_ReadNum(); 
     Serial.println(Num); 
     delay(200);
    // Read Catalog from Serial
     Serial_ReadBytes(buffer, STAR_PAIR_SIZE);
     // Store in EEPROM
     Eeprom.write_StarPair(Num, buffer); 
   }
   else if (DataRead == "<READ_STAR_PAIR>")
   {
     uint8_t buffer[STAR_PAIR_SIZE];
      // Send ACK 
     Serial.println("<READ_STAR_PAIR><ACK>"); 
     delay(200); 
     //Read Num
     int Num = Serial_ReadNum(); 
     Serial.println(Num); 
     delay(200);
     // Read Catalog from EEPROM  
     Eeprom.read_StarPair(Num, buffer);
     // Send to PC
     Serial.write(buffer,STAR_PAIR_SIZE);
   }
   
   // STAR IDs
   // __________________________________________________________________
    else if (DataRead == "<STORE_STAR_ID>")
   {
     uint8_t buffer[STAR_ID_SIZE]; 
     // Send ACK 
     Serial.println("<STORE_STAR_ID><ACK>");   
     delay(200); 
     // Read Num
     int Num = Serial_ReadNum(); 
     Serial.println(Num); 
     delay(200);
    // Read Catalog from Serial
     Serial_ReadBytes(buffer, STAR_ID_SIZE);
     // Store in EEPROM
     Eeprom.write_StarID(Num, buffer); 
   }
   else if (DataRead == "<READ_STAR_ID>")
   {
     uint8_t buffer[STAR_ID_SIZE];
      // Send ACK 
     Serial.println("<READ_STAR_ID><ACK>"); 
     delay(200); 
     //Read Num
     int Num = Serial_ReadNum(); 
     Serial.println(Num); 
     delay(200);
     // Read Catalog from EEPROM  
     Eeprom.read_StarID(Num, buffer);
     // Send to PC
     Serial.write(buffer,STAR_ID_SIZE);
   }
   
   // U Vectors
   // __________________________________________________________________
    else if (DataRead == "<STORE_UVECTOR>")
   {
     uint8_t buffer[U_VECTOR_SIZE]; 
     // Send ACK 
     Serial.println("<STORE_UVECTOR><ACK>");   
     delay(200); 
     // Read Num
     int Num = Serial_ReadNum(); 
     Serial.println(Num); 
     delay(200);
    // Read Catalog from Serial
     Serial_ReadBytes(buffer, U_VECTOR_SIZE);
     // Store in EEPROM
     Eeprom.write_Uvector(Num, buffer); 
   }
   else if (DataRead == "<READ_UVECTOR>")
   {
     uint8_t buffer[U_VECTOR_SIZE];
      // Send ACK 
     Serial.println("<READ_UVECTOR><ACK>"); 
     delay(200); 
     //Read Num
     int Num = Serial_ReadNum(); 
     Serial.println(Num); 
     delay(200);
     // Read Catalog from EEPROM  
     Eeprom.read_Uvector(Num, buffer);
     // Send to PC
     Serial.write(buffer,U_VECTOR_SIZE);
   }
   
   // Pasamos a modo Satr_Tracker, si así es solicitado por el control
   else if (DataRead == "<STAR_TRACKER_MODE>")
   {
      Mode = STAR_TRACKER;
      Serial.println("<STAR_TRACKER_MODE><ACK>");      
   }
   
   delay(50);
 }
 
// *********************************************************************************************************************
//               MODO STAR_TRACKE
// *********************************************************************************************************************
else if (Mode = STAR_TRACKER)
{
   DataRead = Serial_ReadLine();
   
   // Pasamos a modo manual, si así es solicitado por el control
   if (DataRead == "<MANUAL_MODE>")
   {
      Mode = MANUAL;
      Serial.println("<MANUAL_MODE><ACK>");      
   }
   else
   // _____________________________________________________________________
   // Algoritmo para Star Tracker
   // _____________________________________________________________________
   {
      // loadimage
      CaptureImage_to_FIFO();
      GetImage_FIFO_to_RAM(1);
      
      // centroid
      Centroides = Centroid (Ithresh, aRoi, &cont_CM);
      
      // uvec
      Img_Uvectors = uvec(Centroides, cont_CM);
      if (cont_CM >2)
      {
         // starid
        starid(Img_Uvectors, cont_CM, Candidate_Uvectors, Catalog_Uvectors, Catalog_Star_IDs, &NumStarsMatched);
      
        // attdet   
        Attitude = adet(Candidate_Uvectors, Catalog_Uvectors, NumStarsMatched);
      }
   }
}  
   
}

void CaptureImage_to_FIFO(void)
{
    while(VSYNC!=0){}; //While VSYNC_HIGH
    while(VSYNC==0){}; //While VSYNC_LOW

    WEN_HIGH;
    while(VSYNC!=0)
    {
       while(HREF==0 && VSYNC!=0){};
       while(HREF!=0 && VSYNC!=0){};
    } 
    while(VSYNC==0){};
    WEN_LOW;  
}

void GetImage_FIFO_to_Serial_byte(void)
{
   int ii =0;
   int jj =0;
   uint8_t val;
   
   ReadStart();

  // for IMAGE_COLUMNS*IMAGE_FILES*2 times, pulse the RCLK and read the digital pins for image data
 for (jj=0; jj<Image_Files; jj++)
  {
   for (ii=0; ii<Image_Columns; ii++)
   {           
      val = ReadOneByte();
      Serial.write((uint8_t) val);
      val = ReadOneByte();       
      Serial.flush();
     }
  } 
  ReadStop();
}

void GetImage_FIFO_to_Serial_Line(void)
{
   int ii =0;
   int jj =0;
   uint8_t Line[Image_Columns];
   uint8_t val;
   
     ReadStart();

  // for IMAGE_COLUMNS*IMAGE_FILES*2 times, pulse the RCLK and read the digital pins for image data
 for (jj=0; jj<Image_Files; jj++)
  {
   for (ii=0; ii<Image_Columns; ii++)
   {           
      val = ReadOneByte();
      Line[ii] = val;
      val = ReadOneByte();     
    }
    Serial.write(Line,Image_Columns);
    Serial.flush();
  } 
  ReadStop();
}

void GetImage_FIFO_to_RAM(int ImageNumber)
{
   int ii =0;
   int jj =0;
   uint8_t Line[Image_Columns];
   uint8_t val;
   
  ReadStart();

  // for IMAGE_COLUMNS*IMAGE_FILES*2 times, pulse the RCLK and read the digital pins for image data
 for (jj=0; jj<Image_Files; jj++)
  {
   for (ii=0; ii<Image_Columns; ii++)
   {           
      val = ReadOneByte();
      Line[ii] = val;
      val = ReadOneByte();      
    }
    SpiRam.write_camera_line(ImageNumber,(jj+1),Line);
  } 
  ReadStop();
}

void Image_RAM_to_Serial(int ImageNumber)
{
   int jj =0;
   uint8_t Line[Image_Columns];
   
  // for IMAGE_COLUMNS*IMAGE_FILES*2 times, pulse the RCLK and read the digital pins for image data
 for (jj=0; jj<Image_Files; jj++)
  {
    SpiRam.read_camera_line(1,(jj+1),Line);
    Serial.write(Line,Image_Columns);
    Serial.flush();
  } 
}


// Data Read
uint8_t ReadOneByte(void)
{
    uint8_t result;
    RCLK_HIGH;
    result = (uint8_t) PORTE;
    RCLK_LOW;
    return result;
}

// Data Start
void ReadStart(void)
{                      
    // Cycle n
    RCLK_HIGH; 
    RRST_LOW; 
    RCLK_LOW; 
    
    // Reset cycle
    RCLK_HIGH; 
    RCLK_LOW;  
    RCLK_HIGH; 
    
    // Cycle 0
    RCLK_LOW;  
    RRST_HIGH;       
}

// Data Stop
void ReadStop(void)
{
    ReadOneByte();
    RCLK_HIGH;
}

    
void Set_Camera_Config(int ColorFormat, int ImageSize)
{
  Camera_ColorFormat = ColorFormat;
  Camera_ImageSize = ImageSize;
  
  Serial.print("Camera resetting..\r\n");
  Camera.Reset();
  delay(200);
  
  switch (Camera_ColorFormat) 
  {
      case RGB444:
          Camera.InitRGB444();
          Serial.print("Camera RGB444 \r\n");
          break;
      case RGB555:
          Camera.InitRGB555();
          Serial.print("Camera RGB555 \r\n");
          break;
      case RGB565:
          Camera.InitRGB565();
          Serial.print("Camera RGB565 \r\n");
          break;
      case YUV_Color:
          Serial.print("Camera YUV Color \r\n");
          Camera.InitYUV();
          break;
      case BAYER_RGB:
          Camera.InitBayerRGB();
          Camera_ImageSize = VGA;
          Serial.print("Camera RGB Bayer \r\n");
          break;
      case YUV_GreyScale:
          Serial.print("Camera YUV Gray Scale \r\n");
          Camera.InitYUV();
          break;
  }
    
  switch (Camera_ImageSize) 
  {
      case VGA:
          Image_Files = VGA_FILES;
          Image_Columns = VGA_COLUMNS;
          Camera.InitVGA();
          Serial.print("Camera VGA \r\n");
          break;
      case FIFO:
          Image_Files = FIFO_FILES;
          Image_Columns = FIFO_COLUMNS;
          Camera.InitFIFO_2bytes_color_nealy_limit_size();
          Serial.print("Camera FIFO \r\n");
          break;
      case VGA_3_4:
          Image_Files = VGA_3_4_FILES;
          Image_Columns = VGA_3_4_COLUMNS;
          Camera.InitVGA_3_4();
          Serial.print("Camera VGA 3/4 \r\n");
          break;
      case QVGA:
          Image_Files = QVGA_FILES;
          Image_Columns = QVGA_COLUMNS;
          Camera.InitQVGA();
          Serial.print("Camera QVGA \r\n");
          break;
      case QQVGA:
          Image_Files = QQVGA_FILES;
          Image_Columns = QQVGA_COLUMNS;
          Camera.InitQQVGA();
          Serial.print("Camera QQVGA \r\n");
          break;
  }
  
  Camera.InitForFIFOWriteReset();
  Camera.InitDefaultReg();
  Serial.print("Camera Initialized!!! \r\n");
  
  // Set RAM Image Columns Size
  SpiRam.Set_Image_Columns(Image_Columns);
}
    
// 80MHz ==> 12,5 ns per instruction
void DelayCycles (int Cycles)
{
  int ii = 0;
  int jj = 0;
  for(ii=0;ii<Cycles;ii++)
  {
    jj++;
  } 
}

String Serial_ReadLine ()
{
  String DataRead = "";
  char character;
  
  while(Serial.available()) 
  {
      character = Serial.read();
      if (!((character == '\r') || (character == '\n'))) DataRead.concat(character);
  }
  return DataRead;  
}

void Serial_ReadBytes (uint8_t *buffer, int length)
{
  uint8_t character;
  int cnt = 0;
  
  while(!Serial.available() ) {}
  while(Serial.available() ) 
  {
      character = Serial.read();
      if (!((character == '\r') || (character == '\n')))
      {
        buffer[cnt] = character;
        cnt++;
      }
  }
}

int Serial_ReadNum ()
{
  byte buffer[4];
  uint8_t character;
  int cnt = 0;
  int Result = 0;
  
  while(!Serial.available() ) {}
  while(Serial.available() ) 
  {
      character = Serial.read();
      if ( !((character == '\r') || (character == '\n')) || cnt<4)
      {
        buffer[cnt] = character;
        cnt++;
      }
  }
   memcpy(&Result, buffer, 4);
   return Result;
}


