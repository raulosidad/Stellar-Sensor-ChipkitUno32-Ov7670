using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using Microsoft.VisualBasic.FileIO;
using System.Globalization;

namespace ReadSerial
{
    static class Program
    {
      // Definiciones Globales
      public static EEPROM.HEADER Header = new EEPROM.HEADER();
      public static List<EEPROM.StarPair> StarPairs;
      public static List<uint> StarIDs;
      public static List<EEPROM.unit_vector> StarUvectors;

        /// <summary>
        /// Punto de entrada principal para la aplicación.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }

       
        struct StarInfo
        {
            public int ID;
            public double RA;
            public double DEC;
            public double Magnitude;
        }

        static void CSV_Reader()
        {
            List<StarInfo> Stars = new List<StarInfo>();


            TextFieldParser parser = new TextFieldParser(@"D:\RAÚL\Dropbox\UNED\PROYECTO\PROGRAMAS\Sensor Estelar Matlab\hygfull.csv");
            parser.TextFieldType = FieldType.Delimited;
            parser.SetDelimiters("\t");
            while (!parser.EndOfData)
            {
                //Processing row
                string[] fields = parser.ReadFields();
                StarInfo Star;
                Star.ID = Convert.ToInt32(fields[0]);

                Star.RA = double.Parse(fields[1], CultureInfo.InvariantCulture);
                Star.DEC = double.Parse(fields[2], CultureInfo.InvariantCulture);
                Star.Magnitude = double.Parse(fields[3], CultureInfo.InvariantCulture);
                Stars.Add(Star);
            }
            parser.Close();
        }

    }
}
