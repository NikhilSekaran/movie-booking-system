#ifndef FILEUTILITIES_H
#define FILEUTILITIES_H

#include<string>

/***************************************************************

Class:          FileUtilities
Description:    This is FileUtilities Class which has all the
                utility functions related to file / directory

****************************************************************/

class FileUtilities
{
    public:
        FileUtilities();
        virtual ~FileUtilities();

        std::string getCurrentDir();
    protected:

    private:
};

#endif // FILEUTILITIES_H
