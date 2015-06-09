#include <WProgram.h>
#include <Wire.h>

// 24LC256 EEPROM chip
#define EEPROM_ADDDR  (int) 0x50    //Address of 24LC256 eeprom chip
#define I2C_WRITEDELAY 5000         // to break blocking read/write after n millis()
#define I2C_EEPROM_TIMEOUT 1000    // to break blocking read/write after n millis()

// STAR CATALOG
#define HEADER_SIZE           (int)sizeof(HEADER)  //Bytes
#define STAR_PAIR_SIZE        (int)sizeof(StarPair)
#define STAR_ID_SIZE          (int)sizeof(uint32_t)
#define U_VECTOR_SIZE         (int)sizeof(unit_vector)

typedef struct {
      uint32_t StarNum_1;
      uint32_t StarNum_2;
      float dist;
} StarPair;

typedef struct {
      float X;
      float Y;
      float Z;
} unit_vector;

typedef struct {
      float focal;
      float FOV;
      float pixel_size;
      uint32_t Resolution_X;
      uint32_t Resolution_Y;
      uint32_t Number_of_StarPairs;
      uint32_t Number_of_Stars;
} HEADER;

typedef struct {
      HEADER header;
      StarPair StarPairs[];
      uint32_t StarID[];
      unit_vector U_Vectors[];
} EEPROM_MAP;

inline static double Mult_Uvectors(unit_vector Uvector_1, unit_vector Uvector_2)
{
  return ( (Uvector_1.X * Uvector_2.X) + (Uvector_1.Y * Uvector_2.Y) + (Uvector_1.Z * Uvector_2.Z) );
}

inline static double** Mult_Uvectors_2(unit_vector Uvector_1, unit_vector Uvector_2)
{
  double** Result = new double*[3];
  for (int i = 0; i < 3; ++i)
  {
     Result[i] = new double[3];
  }

  Result[0][0] = Uvector_1.X * Uvector_2.X;
  Result[0][1] = Uvector_1.X * Uvector_2.Y;
  Result[0][2] = Uvector_1.X * Uvector_2.Z;
  
  Result[1][0] = Uvector_1.Y * Uvector_2.X;
  Result[1][1] = Uvector_1.Y * Uvector_2.Y;
  Result[1][2] = Uvector_1.Y * Uvector_2.Z;
  
  Result[2][0] = Uvector_1.Z * Uvector_2.X;
  Result[2][1] = Uvector_1.Z * Uvector_2.Y;
  Result[2][2] = Uvector_1.Z * Uvector_2.Z;
  
  return Result;
}

static int sum_array(int a[], int num_elements)
{
   int i, sum=0;
   for (i=0; i<num_elements; i++)
   {
	 sum = sum + a[i];
   }
   return(sum);
}


static int max_array(int a[], int num_elements)
{
   int i, max=-32000;
   for (i=0; i<num_elements; i++)
   {
	 if (a[i]>max)
	 {
	    max=a[i];
	 }
   }
   return(max);
}



