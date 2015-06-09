using System;
using System.Runtime.InteropServices;
using Microsoft.VisualBasic.FileIO;
using System.Globalization;
using System.Collections.Generic;
using System.Reflection;

// STAR CATALOG
 static class EEPROM
 {
    public static int HEADER_SIZE = Marshal.SizeOf(typeof(HEADER));  //Bytes
    public static int STAR_PAIR_SIZE = Marshal.SizeOf(typeof(StarPair));
    public static int STAR_ID_SIZE = Marshal.SizeOf(typeof(uint));
    public static int U_VECTOR_SIZE = Marshal.SizeOf(typeof(unit_vector));

    public struct StarPair
    {
        public uint StarNum_1;
        public uint StarNum_2;
        public float dist;
    } 
    public struct unit_vector
    {
      public float X;
      public float Y;
      public float Z;
    } 

    public struct HEADER
    {
        public float focal;
        public float FOV;
        public float pixel_size;
        public uint Resolution_X;
        public uint Resolution_Y;
        public uint Number_of_StarPairs;
        public uint Number_of_Stars;
    } 

    public struct EEPROM_MAP
    {
        public HEADER header;
        public StarPair[] StarPairs;
        public uint[] StarID;
        public unit_vector[] U_Vectors;
    }

    public static byte[] StructureToByteArray(object obj)
    {
      int len = Marshal.SizeOf(obj);
      byte[] arr = new byte[len];
      IntPtr ptr = Marshal.AllocHGlobal(len);
      Marshal.StructureToPtr(obj, ptr, true);
      Marshal.Copy(ptr, arr, 0, len);
      Marshal.FreeHGlobal(ptr);
      return arr;
    }

    public static object ByteArrayToStructure(byte[] bytearray, object structureObj)
    {
      int length = Marshal.SizeOf(structureObj);
      IntPtr ptr = Marshal.AllocHGlobal(length);
      Marshal.Copy(bytearray, 0, ptr, length);
      structureObj = Marshal.PtrToStructure(Marshal.UnsafeAddrOfPinnedArrayElement(bytearray, 0), structureObj.GetType());
      Marshal.FreeHGlobal(ptr);
      return structureObj;
    }

    public static HEADER ReadHeaderFile(string FilePath)
    {
        int ii = 0;
        object Data = new object();
        HEADER Header = new HEADER();
        FieldInfo[] HeaderFields;
        TextFieldParser parser = new TextFieldParser(FilePath);
        parser.TextFieldType = FieldType.Delimited;
        parser.SetDelimiters("\t");
        HeaderFields = Header.GetType().GetFields(BindingFlags.Public | BindingFlags.Instance);

        while (!parser.EndOfData)
        {
            //Processing row
            string[] fields = parser.ReadFields();
            switch (HeaderFields[ii].FieldType.Name)
            {
                case "Single":
                    Data = float.Parse(fields[0].ToString(), CultureInfo.InvariantCulture);
                    break;
                case "Double":
                    Data = double.Parse(fields[0].ToString(), CultureInfo.InvariantCulture);
                    break;
                case "UInt32":
                    Data = Convert.ToUInt32(fields[0]);
                    break;
            }
            HeaderFields[ii].SetValueDirect(__makeref(Header), Data);
            ii++;
        }
        parser.Close();
        return Header;
    }



    public static List<StarPair> ReadStarPairsFile(string FilePath)
    {
        List<StarPair> StarPairs = new List<StarPair>();
        TextFieldParser parser = new TextFieldParser(FilePath);
        parser.TextFieldType = FieldType.Delimited;
        parser.SetDelimiters("\t");
        while (!parser.EndOfData)
        {
            //Processing row
            string[] fields = parser.ReadFields();
            StarPair Pair;
            Pair.StarNum_1 = Convert.ToUInt32(fields[0]);
            Pair.StarNum_2 = Convert.ToUInt32(fields[1]);
            Pair.dist = float.Parse(fields[2], CultureInfo.InvariantCulture);
            StarPairs.Add(Pair);
        }
        parser.Close();
        return StarPairs;
    }

    public static List<uint> ReadStarIDsFile(string FilePath)
    {
        List<uint> StarIDs = new List<uint>();
        TextFieldParser parser = new TextFieldParser(FilePath);
        parser.TextFieldType = FieldType.Delimited;
        parser.SetDelimiters("\t");
        while (!parser.EndOfData)
        {
            //Processing row
            string[] fields = parser.ReadFields();
            uint ID;
            ID = Convert.ToUInt32(fields[0]);
            StarIDs.Add(ID);
        }
        parser.Close();
        return StarIDs;
    }

    public static List<unit_vector> ReadUvectorsFile(string FilePath)
    {
        List<unit_vector> Uvectors = new List<unit_vector>();
        TextFieldParser parser = new TextFieldParser(FilePath);
        parser.TextFieldType = FieldType.Delimited;
        parser.SetDelimiters("\t");
        while (!parser.EndOfData)
        {
            //Processing row
            string[] fields = parser.ReadFields();
            unit_vector Uvector;
            Uvector.X = float.Parse(fields[0], CultureInfo.InvariantCulture);
            Uvector.Y = float.Parse(fields[1], CultureInfo.InvariantCulture);
            Uvector.Z = float.Parse(fields[2], CultureInfo.InvariantCulture);
            Uvectors.Add(Uvector);
        }
        parser.Close();
        return Uvectors;
    }

 }


