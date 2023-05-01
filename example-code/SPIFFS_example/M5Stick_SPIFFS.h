//========================================================
// File:    M5Stick_SPIFFS
//
// Author:  J. Hathway 2023
//
// Description:
//          Some functions for using SPIFFS to write to 
//          internal SD:
//              - formatSpiffs()
//              - initSPIFFS()
//              - addSPIFFS()
//              - writeSPIFFS()
//              - appendSPIFFS()
//              - readSPIFFS()
//              - removeSPIFFS()
//========================================================

#include <SPIFFS.h>

#define USING_M5DISPLAY

#ifdef USING_M5DISPLAY
#define Log M5.Lcd 
#elif USING_SERIAL
#define Log Serial 
#endif

//========================================================

/// Format SPIFFS - delete all files on SD
void formatSPIFFS()
{
    Log.print("Formatting SPIFFS...");
    SPIFFS.format();
    Log.println("SPIFFS format completed");
}

//========================================================

/// Initialise SPIFFS - call SPIFFS.begin()
/// @return true on success, false on failure
bool initSPIFFS()
{
    if (!SPIFFS.begin())
    {
        Log.print("ERROR: SPIFFS Failed to Start");
        return false;
    }

    Log.println("SPIFFS Started");
    return true;
}

//========================================================

/// Add SPIFFS - create an empty file on SD
/// @param file_name (const String&) name of new file
/// @return true on success, false on failure
bool addSPIFFS(const String &file_name)
{
    // Check if file exists
    if (SPIFFS.exists(file_name))
    {
        Log.print("ERROR: ");
        Log.println(file_name + ": File Already Exists");
        return false;
    }

    File file = SPIFFS.open(file_name, "w");

    // Check if file opened correctly
    if (!file)
    {
        Log.print("ERROR: ");
        Log.println(file_name + ": Failed to Create File");
        return false;
    }

    Log.print(file_name);
    Log.println(": New File Created");
    file.close();
    return true;
}

//========================================================

/// Write SPIFFS - overwrite file data
/// @param file_name (const String&) name of file
/// @param data (const String&) data to write to file
/// @return true on success, false on failure
bool writeSPIFFS(const String &file_name, const String &data)
{
    // Check if file exists
    if (!SPIFFS.exists(file_name))
    {
        Log.print("ERROR: ");
        Log.println(file_name + ": File Not Found");
        return false;
    }

    File file = SPIFFS.open(file_name, "w");

    // Check if file opened correctly
    if (!file)
    {
        Log.print("ERROR: ");
        Log.println(file_name + ": Failed to Open File");
        return false;
    }

    file.print(data);
    file.close();
    return true;
}

//========================================================

/// Append SPIFFS - append data to file
/// @param file_name (const String&) name of file
/// @param data (const String&) data to append to file
/// @return true on success, false on failure
bool appendSPIFFS(const String &file_name, const String &data)
{
    // Check if file exists
    if (!SPIFFS.exists(file_name))
    {
        Log.print("ERROR: ");
        Log.println(file_name + ": File Not Found");
        return false;
    }

    File file = SPIFFS.open(file_name, "a");

    // Check if file opened correctly
    if (!file)
    {
        Log.print("ERROR: ");
        Log.println(file_name + ": Failed to Open File");
        return false;
    }

    file.print(data);
    file.close();
    return true;
}

//========================================================

/// Read SPIFFS - read data from file
/// @param file_name (const String&) name of file
/// @return data (String) file contents
String readSPIFFS(const String &file_name)
{
    // Check if file exists
    if (!SPIFFS.exists(file_name))
    {
        Log.print("ERROR: ");
        Log.println(file_name + ": File Not Found");
        return "";
    }

    File file = SPIFFS.open(file_name, "r");

    // Check if file opened correctly
    if (!file)
    {
        Log.print("ERROR: ");
        Log.println(file_name + ": Failed to Open File");
        return "";
    }

    // Read contents to data 
    String data = "";
    for (int i = 0; i < file.size(); i++)
        data += (char)file.read();

    file.close();
    return data;
}

//========================================================

/// Remove SPIFFS - remove a file from SD
/// @param file_name (const String&) name of new file
/// @return true on success, false on failure
bool removeSPIFFS(const String &file_name)
{   
    // Check if file exists
    if (!SPIFFS.exists(file_name))
    {
        Log.print("ERROR: ");
        Log.println(file_name + ": File Not Found");
        return false;
    }

    SPIFFS.remove(file_name);
    return true;
}
