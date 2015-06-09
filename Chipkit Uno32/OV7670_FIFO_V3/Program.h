#include "ov7670.h"
#include <Wire.h>
#include <SPI.h>
#include <SpiRAM.h>
#include "EEPROM.h"
#include <math.h>
#include "MatrixMath.h"
#include "SVD.h"

#define  TRIG    9


//******************************************************************************************************************
//                            CAMERA SETTINGS
//******************************************************************************************************************
// BITs POSITIONs
#define  WEN_bit   2
#define  RRST_bit  5
#define  RCLK_bit  1
#define  OE_bit    0
#define  HREF_bit    4

// READ PORTS
#define  WEN    (int) (PORTD & B00000100)  //6   // RD2
#define  RRST   (int) (PORTD & B00100000)  //34  // RD5
#define  VSYNC  (int) (PORTD & B01000000)  //36  // RD6
#define  RCLK   (int) (PORTD & B00000010)  //5  // RD1
#define  HREF   (int) (PORTD & B00010000)  //10  // RD4

// WRITE PORTS
#define WEN_HIGH   PORTD |= (int) (1<<WEN_bit);
#define WEN_LOW    PORTD &= (int) (~(1<<WEN_bit)); 

#define RRST_HIGH  PORTD |= (int) (1<<RRST_bit); 
#define RRST_LOW   PORTD &= (int) (~(1<<RRST_bit)); 

#define RCLK_HIGH  PORTD |= (int) (1<<RCLK_bit); 
#define RCLK_LOW   PORTD &= (int) (~(1<<RCLK_bit)); 

//  COLOR FORMATS
#define RGB444         1
#define RGB555         2
#define RGB565         3
#define YUV_Color      4
#define BAYER_RGB      5
#define YUV_GreyScale  6

// SCREEN SIZES
#define VGA            1
#define FIFO           2
#define VGA_3_4        3
#define QVGA           4
#define QQVGA          5

//******************************************************************************************************************
//                            SPI-RAM SETTINGS
//******************************************************************************************************************
#define DATAOUT       11  //MOSI
#define DATAIN        12  //MISO 
#define SPICLOCK      13  //sck
#define SLAVESELECT   38  //ss

//******************************************************************************************************************
//                            Structures
//******************************************************************************************************************
typedef struct {
      double X;
      double Y;
} StarCenter;

//******************************************************************************************************************
//                            STAR IDENTIFICATION 
//******************************************************************************************************************
#define CENTROID_BUFFER_SIZE  100

//******************************************************************************************************************
//                            I2C-EEPROM SETTINGS
//******************************************************************************************************************
TwoWire I2C;

//******************************************************************************************************************
//                            PROGRAM VARIABLES
//******************************************************************************************************************
// Camera Config
ov7670  Camera(I2C);
int Image_Files;       
int Image_Columns;     
int Bytes_per_Pixel;   
int Camera_ColorFormat;
int Camera_ImageSize;

// RAM
SpiRAM SpiRam(SLAVESELECT);

// EEPROM
EEPROM_MAP         Star_Catalog;
Catalog_EEPROM     Eeprom(I2C);

//******************************************************************************************************************
//                            STAR IDENTIFICATION
//******************************************************************************************************************
uint8_t ReadPixel_RAM(int ImageNumber, int Line, int Column )
{
    uint8_t result;
    SpiRam.read_camera_pixel(ImageNumber, (Line+1),(Column+1));
    return result;
}

uint8_t ReadPixel_RAM(int Column, int Line )
{
    uint8_t result;
    SpiRam.read_camera_pixel(1, (Line+1),(Column+1));
    return result;
}

//    Centroid
//______________________________________________________________________________________________________________________
StarCenter* Centroid (int Ithresh, int aRoi, int *NumStars)
{
  // Definitions
  int r_avge = 7; 
  int x_start = 0;   int y_start=0;
  int x_end = 0;     int y_end = 0;
  int I_top = 0;     int I_botton = 0;
  int I_left = 0;    int I_right = 0; 
  int Iborder = 0;
  double B = 0;
  int cont = 0;      int cont_CM = 0;
  boolean     processed[CENTROID_BUFFER_SIZE];
  StarCenter  Centroides[CENTROID_BUFFER_SIZE];
  StarCenter  Centroides_CM[CENTROID_BUFFER_SIZE];
  double xCM = 0;   double yCM = 0; 
  
  for (int x=0; x<Image_Columns; x++)
  {
     for (int y=0; y<Image_Files; y++)
     {
       if ( ReadPixel_RAM(x,y) > Ithresh)
       {
          //Calculate ROI
            x_start = x - ((aRoi -1)/2);
            y_start = y - ((aRoi -1)/2);
            if (x_start<=0 || y_start<=0 )
                break; //Next pixel
            x_end   = x_start + aRoi;
            y_end   = y_start + aRoi;
            if (x_end>x || y_end>x )
                break; //Next pixel    
             
            //Find the average intensity value of the border pixels Iborder
            I_botton = 0;
            for (int i=x_start; i<=(x_end-1); i++) {
                 I_botton = I_botton + ReadPixel_RAM(i,y_start);
            }
            I_top = 0;
            for (int i=(x_start+1); i<=(x_end); i++){
                 I_top = I_top + ReadPixel_RAM(i,y_end);
            }
            I_left = 0;
            for (int j=(y_start); j<=(y_end-1); j++){
                 I_left = I_left + ReadPixel_RAM(x_start,j);
            }
            I_right = 0;
            for (int j=(y_start+1); j<=(y_end); j++){
                 I_right = I_right + ReadPixel_RAM(x_end,j);
            }
            Iborder = (I_botton + I_top + I_left + I_right) / (4*(aRoi - 1));   
            
           // Normalized light intensity matrix Inorm
           double Inorm[aRoi-2] [aRoi-2];
           for (int i=(x_start+1); i<=(x_end-1); i++){
                for (int j=(y_start+1); j<=(y_end-1); j++){
                    Inorm[i][j] = (double) (ReadPixel_RAM(i,j) - Iborder);
                }
           }
           
           //Calculate the centroid location (xCM; yCM)
           B = 0;
           for (int i=(x_start+1); i<=(x_end-1); i++){
               for (int j=(y_start+1); j<=(y_end-1); j++){  
                   B = B + Inorm[i][j];
               }
           }
           xCM = 0;
           for (int i=(x_start+1); i<=(x_end-1); i++){
               for (int j=(y_start+1); j<=(y_end-1); j++){
                   xCM = xCM + (i * Inorm[i][j] / B);
               }
           }
           yCM = 0;
           for (int i=(x_start+1); i<=(x_end-1); i++){
               for (int j=(y_start+1); j<=(y_end-1); j++){
                   yCM = yCM + (j * Inorm[i][j] / B);
               }
           }
          Centroides[cont].X = xCM;
          Centroides[cont].Y = yCM;
          processed[cont] = 0;
          cont = cont +1;  
       }    
     }// End for Y
  }// End for X
  
    // Final Calculations 
    cont_CM = 1;
    for (int u=1; u<=cont-1; u++){
        if ( processed[u] ==0){
            Centroides_CM[cont_CM] = Centroides[u];
            processed[u] =1;
            for (int v=1; v<=cont-1; v++){
                if(u!=v){
                     if( (abs(Centroides[v].X -  Centroides[u].X) <= r_avge) && (abs(Centroides[v].Y -  Centroides[u].Y) <= r_avge) ){
                      Centroides_CM[cont_CM].X = (Centroides_CM[cont_CM].X  + Centroides[v].X) /2 ;
                      Centroides_CM[cont_CM].Y = (Centroides_CM[cont_CM].Y + Centroides[v].Y) /2 ; 
                      processed[v] =1;     
                     }                             
                }
            } //FOR v            
            cont_CM = cont_CM+1;
        } // If  
    }// FOR u
  
  StarCenter  Centres[CENTROID_BUFFER_SIZE];  
  for (int ii=0; ii<(cont_CM-1);ii++){
    Centres[ii].X = Centroides_CM[ii].X;
    Centres[ii].Y = Centroides_CM[ii].Y;
  }
  *NumStars = cont_CM;
  return Centres;
  
}//End Centrid


//    uvec
//______________________________________________________________________________________________________________________
inline double norm(unit_vector vector)
{
  return sqrt( sq(vector.X) + sq(vector.Y) + sq(vector.Z) );
}

unit_vector* uvec(StarCenter *image_coordinates, int cont_CM)
{
  double offset_x;         
  double offset_y;
  unit_vector vector;
  double norma;

  offset_x = Eeprom.Header.Resolution_X/2;
  offset_y = Eeprom.Header.Resolution_Y/2;
  
  // Create centroides Image
  unit_vector Image_Unit_Vectors[cont_CM];
  for (int u=1; u<=cont_CM; u++)
  {
    vector.X = Eeprom.Header.pixel_size * (image_coordinates[u].X - offset_x);
    vector.Y = Eeprom.Header.pixel_size * (image_coordinates[u].Y - offset_y);
    vector.Z = Eeprom.Header.focal;
    norma = norm(vector);
    Image_Unit_Vectors[u].X = vector.X / norma;
    Image_Unit_Vectors[u].Y = vector.Y / norma;
    Image_Unit_Vectors[u].Z = vector.Z / norma;
  }
  return Image_Unit_Vectors;
}// End uvec


//    starid
//______________________________________________________________________________________________________________________
inline int BinarySearch(double Value)
{
   int n = Eeprom.Header.Number_of_StarPairs;
   int first = 0;
   int last = n - 1;
   int middle = (int)((first+last)/2);
   int Index;
   StarPair *Pair_1;
   StarPair *Pair_2;
   double v_middle, v_middle_1;
   
   while( first <= last )
   {
      Eeprom.read_StarPair(middle, Pair_1);
      v_middle = Pair_1->dist;
      Eeprom.read_StarPair(middle+1, Pair_2);
      v_middle_1 = Pair_2->dist;
      if ( (v_middle < Value) &&  (v_middle_1 > Value) )
      {
        Index = middle;
        break;
      }
      else if ( v_middle < Value )
      {
        first = middle + 1;  
      }      
      else
      {
        last = middle - 1;
      }
      middle = int((first + last)/2);
   }// End While

   if ( first > last ) Index = -1;
   return Index;
}

inline int Find(int *Vector, int Size, int Value)
{
  int Index = 0;
  for (int i=0; i<Size; i++){
    if (Vector[i] = Value){
      Index = i;
      break;
    }
  }
  return Index;
}

void starid(unit_vector *Image_UnitVectors, int num_candidates, unit_vector *Candidate_Uvectors, unit_vector *Catalog_Uvectors, uint32_t *Catalog_Star_IDs, int *NumStarsMatched)
{
StarPair *Pair;
int index;
int Maximun;
int start_index;
int cont;

// Tolerance
double diagonal = sqrt( sq(Eeprom.Header.Resolution_X) + sq(Eeprom.Header.Resolution_Y));
double tol = Eeprom.Header.FOV / diagonal;

// ************** CANDIDATE MATCHING ****************************************************
uint32_t num_stars_catalog      = Eeprom.Header.Number_of_Stars;
uint32_t num_catalog_starspairs = Eeprom.Header.Number_of_StarPairs;

int matches  [num_candidates][num_stars_catalog];
int matches_2[num_candidates][num_stars_catalog];
memset(matches,0,sizeof(matches));
memset(matches_2,0,sizeof(matches_2));

double dist, dist_deg, dist_catalog, dist_cat;

for (int i=1; i<=num_candidates-1; i++){
   for (int j=(i+1); j<=num_candidates; j++){ // Symetric distance a->b and b->a
        dist = Mult_Uvectors(Image_UnitVectors[i], Image_UnitVectors[j]);
        dist_deg = acos(dist)*180/M_PI;
        if (dist_deg <= Eeprom.Header.FOV)
        {
             start_index = BinarySearch(dist_deg - tol);
             for (int h=start_index; h<=num_catalog_starspairs; h++)
             {
                 Eeprom.read_StarPair(h, Pair);
                 dist_catalog = Pair->dist;
                 if ( (dist_deg - tol)<=dist_catalog && dist_catalog<=(dist_deg + tol) )
                 {
                     matches[i][Pair->StarNum_1]++;
                     matches[i][Pair->StarNum_2]++; 
                     matches[j][Pair->StarNum_1]++; 
                     matches[j][Pair->StarNum_2]++; 
                 }  
                 if ( dist_catalog>(dist_deg + tol) )break; 
             }// For h   
        }
  } // For j
} // For i


// En matches tenemos para cada estrella candidata un array con la cantidad de veces que ha dado positivo el algoritmo de matching por cada estrella
// del catálogo. Cada posicióin de este array representa la posición de estrella en el array de estrellas del catálogo Para conocer el ID de la
// estrella se debe recuperar el valor de stars
uint32_t final_matching_stars[num_candidates]; // ID de la estrella en el catálogo
int final_matching_index[num_candidates]; // Índice de la estrella en el catálogo
for (int k=1; k<=num_candidates; k++)
{
    Maximun = max_array(matches[k],num_stars_catalog);
    index = Find(matches[k], num_stars_catalog, Maximun);
    final_matching_stars[k] = Eeprom.read_StarID(index);
    final_matching_index[k] = index;
}

// *************** VERIFICATION AND FINAL RESULT ****************************************
for (int i=1; i<=num_candidates; i++)
{
  for (int j=(i+1); j<=num_candidates; j++) // Symetric distance a->b and b->a
  { 
    
    dist_cat = Mult_Uvectors(Eeprom.read_Uvector(final_matching_index[i]) , Eeprom.read_Uvector(final_matching_index[j]));
    dist_cat = acos(dist_cat)*180/M_PI;
    dist = Mult_Uvectors(Image_UnitVectors[i], Image_UnitVectors[j]);
    dist = acos(dist)*180/M_PI;
    if ( (dist - tol)<=dist_cat && dist_cat<=(dist + tol) )
    {
         matches_2[i][final_matching_index[i]]++;
         matches_2[i][final_matching_index[j]]++;
         matches_2[j][final_matching_index[i]]++;
         matches_2[j][final_matching_index[j]]++;
    }  
 } // For j
} // For i


cont=0;
int Maxes [num_candidates];
for (int i=0; i<num_candidates;i++)
{
  Maxes[i] = max_array(matches_2[i],num_stars_catalog);
}

int T = max_array(Maxes,num_candidates) -1;
int *FINAL_index;
for (int k=1; k<=num_candidates; k++)
{
    if (sum_array(matches_2[k],num_stars_catalog) >  T)
    {
         cont++;
         Catalog_Star_IDs[cont] =  final_matching_stars[k];
         FINAL_index[cont] =  final_matching_index[k];
         Candidate_Uvectors[cont]= Image_UnitVectors[k];
         Catalog_Uvectors[cont] = Eeprom.read_Uvector(FINAL_index[cont]);
    }
}

*NumStarsMatched = cont;

}// End function starid



// **************************************************************************************
// *************** ATTITUDE determination ****************************************
// **************************************************************************************
double** adet(unit_vector Candidate_Uvectors[], unit_vector Catalog_Uvectors[], int cont )
{

  double W[3] = {0};
  double** Result = new double*[3];
  double** B = new double*[3];
  double** U_aux = new double*[3];
  double** V_aux = new double*[3];
  double** U_plus = new double*[3];
  double** V_plus = new double*[3];
  double** V_plus_T = new double*[3];
  double** A = new double*[3];
  double** U = new double*[3];
  double** V = new double*[3];
  
  for (int i = 0; i < 3; ++i)
  {
     Result[i] = new double[3];
     B[i] = new double[3];
     U_aux[i] = new double[3];
     V_aux[i] = new double[3];
     U_plus[i] = new double[3];
     V_plus[i] = new double[3];
     V_plus_T[i] = new double[3];
     A[i] = new double[3];
     U[i] = new double[3];
     V[i] = new double[3];
  }
  
  for (int k=1; k<=cont; k++)
  {
     Matrix.Add(*B,*Mult_Uvectors_2(Candidate_Uvectors[k],Catalog_Uvectors[k]),3,3,*B);
  }

  Matrix.Copy(*B,3,3,*U);
  dsvd(U,3,3,W,V);
  U_aux[0][0] = 1; U_aux[0][1] = 0; U_aux[0][2] = 0;
  U_aux[1][0] = 0; U_aux[1][1] = 1; U_aux[1][2] = 0;
  U_aux[2][0] = 0; U_aux[2][1] = 0; U_aux[2][2] = Determinant(U);
  
  V_aux[0][0] = 1; V_aux[0][1] = 0; V_aux[0][2] = 0;
  V_aux[1][0] = 0; V_aux[1][1] = 1; V_aux[1][2] = 0;
  V_aux[2][0] = 0; V_aux[2][1] = 0; V_aux[2][2] = Determinant(V);
       
  Matrix.Multiply(*U,*U_aux,3,3,3,*U_plus); 
  Matrix.Multiply(*V,*V_aux,3,3,3,*V_plus); 
  
  Matrix.Transpose(*V_plus,3,3,*V_plus_T);
  Matrix.Multiply(*U_plus,*V_plus_T,3,3,3,*A);
  
  
  Matrix.Copy(*A,3,3,*Result);
  return Result;
}
