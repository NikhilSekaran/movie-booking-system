#ifndef MOVIESDATA_H
#define MOVIESDATA_H

#include<string>
#include<map>

#include "FileUtilities.h"

/***************************************************************

Class:          MoviesData
Description:    This is MoviesData Class which has all the
                functions related to reading moviesFile,
                getting movies list
Attributes:
fileUtilitiesInstance   - FileUtilities Class instance
moviesFile              - string, which holds the movies data filename with proper path
movies                  - its a map which stores SlNo (1,2,3..) as key
                          and value as MovieName

****************************************************************/

class MoviesData
{
    public:
        MoviesData();
        virtual ~MoviesData();

        std::map<unsigned int, std::string> getMovies();

    protected:

    private:
        static std::string moviesFile;
        static std::map<unsigned int, std::string> movies;

        FileUtilities fileUtilitiesInstance;

        void readMoviesInfo();
};

#endif // MOVIESDATA_H
