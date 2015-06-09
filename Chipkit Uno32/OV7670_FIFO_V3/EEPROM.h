#include "EEPROM_defines.h"

class Catalog_EEPROM {
public:
	Catalog_EEPROM(TwoWire& s);
        HEADER Header;
        
	void init();
        // Write Functions
        void write_Header(HEADER header);
        void write_Header(uint8_t* buffer);
	void write_StarPair(int num, StarPair Pair);
        void write_StarPair(int num, uint8_t* buffer);
        void write_StarID(int num, uint32_t StarID);
        void write_StarID(int num, uint8_t* buffer);
        void write_Uvector(int num, unit_vector u_vector);
        void write_Uvector(int num, uint8_t* buffer);
        // Read Functions
	void read_Header();
        void read_Header(uint8_t *buffer);
	void read_StarPair(int num, StarPair *Pair);
        void read_StarPair(int num, uint8_t *buffer);
        void read_StarID(int num, uint32_t *StarID);
        uint32_t read_StarID(int num);
        void read_StarID(int num, uint8_t *buffer);
        void read_Uvector(int num, unit_vector *u_vector);
        unit_vector read_Uvector(int num);
        void read_Uvector(int num, uint8_t *buffer);
private:
	uint8_t initialized;
        TwoWire& I2C;
        uint32_t _lastWrite; // for waitEEReady
        
        void write_Byte(uint16_t memoryAddress, uint8_t data );
        byte read_Byte (uint16_t memoryAddress );
        void writeBlock(uint16_t memoryAddress, uint8_t* buffer, int length);
        void readBlock(uint16_t memoryAddress, uint8_t* buffer, int length);
        void waitEEReady();
};
