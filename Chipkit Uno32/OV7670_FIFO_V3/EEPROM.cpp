#include "EEPROM.h"

#define STAR_PAIRS_BLOCK_SIZE  (STAR_PAIR_SIZE * Header.Number_of_StarPairs)
#define STAR_IDS_BLOCK_SIZE    (STAR_ID_SIZE * Header.Number_of_Stars)
#define U_VECTORS_BLOCK_SIZE   (U_VECTOR_SIZE * Header.Number_of_Stars)

Catalog_EEPROM::Catalog_EEPROM(TwoWire& s): I2C(s)
{  
   _lastWrite = 0;
   initialized = false;
}
 
void Catalog_EEPROM::init() 
{
  if (!initialized) 
  {
    initialized = true;
  }
}

// ______________________________________________________________________
// HEADER FUNCTIONS
// ______________________________________________________________________
void Catalog_EEPROM::write_Header(HEADER header)
{
  uint16_t address = 0;
  byte buffer[HEADER_SIZE];
  memcpy(buffer, &header, HEADER_SIZE);
  writeBlock(address, buffer, HEADER_SIZE);
  Header = header;
}

void Catalog_EEPROM::write_Header(uint8_t* buffer)
{
  uint16_t address = 0;
  writeBlock(address, buffer, HEADER_SIZE);
  memcpy(&Header, buffer, HEADER_SIZE); 
}

void Catalog_EEPROM::read_Header()
{
  uint16_t address = 0;
  byte buffer[HEADER_SIZE];
  readBlock(address, buffer, HEADER_SIZE);
  memcpy(&Header, buffer, HEADER_SIZE);
}

void Catalog_EEPROM::read_Header(uint8_t *buffer)
{
  uint16_t address = 0;
  readBlock(address, buffer, HEADER_SIZE);
  memcpy(&Header, buffer, HEADER_SIZE);
}

// ______________________________________________________________________
// STAR PAIRS FUNCTIONS
// ______________________________________________________________________
void Catalog_EEPROM::write_StarPair(int num, StarPair Pair)
{
  uint16_t address = (uint16_t)(HEADER_SIZE + (num * STAR_PAIR_SIZE));
  byte buffer[STAR_PAIR_SIZE];
  memcpy(buffer, &Pair, STAR_PAIR_SIZE);
  writeBlock(address, buffer, STAR_PAIR_SIZE);
}

void Catalog_EEPROM::write_StarPair(int num, uint8_t* buffer)
{
  uint16_t address = (uint16_t)(HEADER_SIZE + (num * STAR_PAIR_SIZE));
  writeBlock(address, buffer, STAR_PAIR_SIZE);
}

void Catalog_EEPROM::read_StarPair(int num, StarPair *Pair)
{
  uint16_t address = (uint16_t)(HEADER_SIZE + (num * STAR_PAIR_SIZE));
  byte buffer[STAR_PAIR_SIZE];
  readBlock(address, buffer, STAR_PAIR_SIZE);
  memcpy(Pair, buffer, STAR_PAIR_SIZE);
}

void Catalog_EEPROM::read_StarPair(int num, uint8_t *buffer)
{
  uint16_t address = (uint16_t)(HEADER_SIZE + (num * STAR_PAIR_SIZE));
  readBlock(address, buffer, STAR_PAIR_SIZE);
}

// ______________________________________________________________________
// STAR IDs FUNCTIONS
// ______________________________________________________________________
void Catalog_EEPROM::write_StarID(int num, uint32_t StarID)
{
  uint16_t address = HEADER_SIZE + STAR_PAIRS_BLOCK_SIZE + (num * STAR_ID_SIZE);
  byte buffer[STAR_ID_SIZE];
  memcpy(buffer, &StarID, STAR_ID_SIZE);
  writeBlock(address, buffer, STAR_ID_SIZE);
}

void Catalog_EEPROM::write_StarID(int num, uint8_t* buffer)
{
  uint16_t address = HEADER_SIZE + STAR_PAIRS_BLOCK_SIZE + (num * STAR_ID_SIZE);
  writeBlock(address, buffer, STAR_ID_SIZE);
}

void Catalog_EEPROM::read_StarID(int num, uint32_t *StarID)
{
  uint16_t address = HEADER_SIZE + STAR_PAIRS_BLOCK_SIZE + (num * STAR_ID_SIZE);
  byte buffer[STAR_ID_SIZE];
  readBlock(address, buffer, STAR_ID_SIZE);
  memcpy(StarID, buffer, STAR_ID_SIZE);
}

uint32_t Catalog_EEPROM::read_StarID(int num)
{
  uint32_t *StarID;
  uint16_t address = HEADER_SIZE + STAR_PAIRS_BLOCK_SIZE + (num * STAR_ID_SIZE);
  byte buffer[STAR_ID_SIZE];
  readBlock(address, buffer, STAR_ID_SIZE);
  memcpy(StarID, buffer, STAR_ID_SIZE);
  return *StarID;
}

void Catalog_EEPROM::read_StarID(int num, uint8_t *buffer)
{
  uint16_t address = HEADER_SIZE + STAR_PAIRS_BLOCK_SIZE + (num * STAR_ID_SIZE);
  readBlock(address, buffer, STAR_ID_SIZE);
}

// ______________________________________________________________________
// U_VECTORs FUNCTIONS
// ______________________________________________________________________
void Catalog_EEPROM::write_Uvector(int num, unit_vector u_vector)
{
  uint16_t address = HEADER_SIZE + STAR_PAIRS_BLOCK_SIZE + STAR_IDS_BLOCK_SIZE + (num * U_VECTOR_SIZE);
  byte buffer[U_VECTOR_SIZE];
  memcpy(buffer, &u_vector, U_VECTOR_SIZE);
  writeBlock(address, buffer, U_VECTOR_SIZE);
}

void Catalog_EEPROM::write_Uvector(int num, uint8_t* buffer)
{
  uint16_t address = HEADER_SIZE + STAR_PAIRS_BLOCK_SIZE + STAR_IDS_BLOCK_SIZE + (num * U_VECTOR_SIZE);
  writeBlock(address, buffer, U_VECTOR_SIZE);
}

void Catalog_EEPROM::read_Uvector(int num, unit_vector *u_vector)
{
  uint16_t address = HEADER_SIZE + STAR_PAIRS_BLOCK_SIZE + STAR_IDS_BLOCK_SIZE + (num * U_VECTOR_SIZE);
  byte buffer[U_VECTOR_SIZE];
  readBlock(address, buffer, U_VECTOR_SIZE);
  memcpy(u_vector, buffer, U_VECTOR_SIZE);
}

void Catalog_EEPROM::read_Uvector(int num, uint8_t *buffer)
{
  uint16_t address = HEADER_SIZE + STAR_PAIRS_BLOCK_SIZE + STAR_IDS_BLOCK_SIZE + (num * U_VECTOR_SIZE);
  readBlock(address, buffer, U_VECTOR_SIZE);
}

unit_vector Catalog_EEPROM::read_Uvector(int num)
{
  unit_vector *u_vector;
  uint16_t address = HEADER_SIZE + STAR_PAIRS_BLOCK_SIZE + STAR_IDS_BLOCK_SIZE + (num * U_VECTOR_SIZE);
  byte buffer[U_VECTOR_SIZE];
  readBlock(address, buffer, U_VECTOR_SIZE);
  memcpy(u_vector, buffer, U_VECTOR_SIZE);
  return *u_vector;
}

//******************************************************************************************************************
// PRIVATE FUNCTIONS
//******************************************************************************************************************
void Catalog_EEPROM::write_Byte(uint16_t memoryAddress, uint8_t data ) 
{
  I2C.beginTransmission(EEPROM_ADDDR);
  I2C.send((int)(memoryAddress >> 8));   // MSB
  I2C.send((int)(memoryAddress & 0xFF)); // LSB
  I2C.send(data);
  I2C.endTransmission();
 
  delay(5);
}
 
byte Catalog_EEPROM::read_Byte(uint16_t memoryAddress ) 
{
  byte rdata = 0xFF;
 
  I2C.beginTransmission(EEPROM_ADDDR);
  I2C.send((int)(memoryAddress >> 8));   // MSB
  I2C.send((int)(memoryAddress & 0xFF)); // LSB
  I2C.endTransmission();
 
  I2C.requestFrom(EEPROM_ADDDR,1);
 
  if (I2C.available()) rdata = I2C.receive();
 
  return rdata;
}

void Catalog_EEPROM::writeBlock(uint16_t memoryAddress, uint8_t* buffer, int length)
{
  waitEEReady();
  I2C.beginTransmission(EEPROM_ADDDR);
  I2C.send((int)(memoryAddress >> 8));   // MSB
  I2C.send((int)(memoryAddress & 0xFF)); // LSB
  I2C.send(buffer,length);
  I2C.endTransmission();
  _lastWrite = micros();
}

void Catalog_EEPROM::readBlock(uint16_t memoryAddress, uint8_t* buffer, int length)
{
  waitEEReady();
  I2C.beginTransmission(EEPROM_ADDDR);
  I2C.send((int)(memoryAddress >> 8));   // MSB
  I2C.send((int)(memoryAddress & 0xFF)); // LSB
  I2C.endTransmission();
  I2C.requestFrom(EEPROM_ADDDR,length);
  uint8_t cnt = 0;
  uint32_t before = millis();
  while(!I2C.available()) {} // wait for data 
 
  while ((cnt < length) && ((millis() - before) < I2C_EEPROM_TIMEOUT))
  {
    if (I2C.available()) buffer[cnt++] = I2C.receive();
  }
}

void Catalog_EEPROM::waitEEReady()
{
  // Wait until EEPROM gives ACK again.
  // this is a bit faster than the hardcoded 5 milliSeconds
  while ((micros() - _lastWrite) <= I2C_WRITEDELAY)
  {
    I2C.beginTransmission(EEPROM_ADDDR);
    int x = I2C.endTransmission();
    if (x == 0) break;
  }
}
