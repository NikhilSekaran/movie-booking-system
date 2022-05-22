#include "FileUtilities.h"
#ifdef _WIN64
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif


/***************************************************************
*
* Function: FileUtilities
* In: -
* Out: -
* Description: This is the default constructor of FileUtilities class
*
****************************************************************/
FileUtilities::FileUtilities()
{
    //ctor
}

/***************************************************************
*
* Function: ~FileUtilities
* In: -
* Out: -
* Description: This is the destructor of FileUtilities class
*
****************************************************************/
FileUtilities::~FileUtilities()
{
    //dtor
}

/***************************************************************
*
* Function: getCurrentDir
* In: -
* Out: string type, current working directory
* Description: This is a utility function which returns the
                current working directory
*
****************************************************************/
std::string FileUtilities::getCurrentDir() {
   char buff[FILENAME_MAX]; //create string buffer to hold path
   GetCurrentDir( buff, FILENAME_MAX );
   std::string current_working_dir(buff);

   return current_working_dir;
}
