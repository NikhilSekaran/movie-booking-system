#include "MoviesData.h"

#include <iostream>
#include <fstream>
#include <sstream>

// global data
std::string MoviesData::moviesFile = "movies_list.csv";
std::map<unsigned int, std::string> MoviesData::movies;

/***************************************************************
*
* Function: MoviesData
* In: -
* Out: -
* Description: This is the default constructor of MoviesData class
*
****************************************************************/
MoviesData::MoviesData()
{
    //ctor
    if (movies.empty())
    {
        std::string cwd = fileUtilitiesInstance.getCurrentDir();
        moviesFile = cwd + "\\" + moviesFile;

        readMoviesInfo();
    }
}

/***************************************************************
*
* Function: ~MoviesData
* In: -
* Out: -
* Description: This is the destructor of MoviesData class
*
****************************************************************/
MoviesData::~MoviesData()
{
    //dtor
}

/***************************************************************
*
* Function: getMovies
* In: -
* Out: is a map which has SlNo (1,2,3..) as key and value as MovieName
* Description: This function returns the map which has all the Movies
*
****************************************************************/
std::map<unsigned int, std::string> MoviesData::getMovies()
{
    return movies;
}

/***************************************************************
*
* Function: readMoviesInfo
* In: -
* Out: -
* Description: This function reads the file movies_list.csv to get
                all the information related to movies
*
****************************************************************/
void MoviesData::readMoviesInfo()
{
    std::ifstream inputFile;
    inputFile.open(moviesFile);

    if (!inputFile.is_open()) {
        throw std::runtime_error("Cannot Open the Movies File List");
    }

    std::string line;
    unsigned int slNo;
    std::string movieName, tempString;

    // skip the header information from 1st line in CSV
    getline(inputFile, line);

    while (getline(inputFile, line))
    {
        std::stringstream inputString(line);

        // get slNo
        getline(inputString, tempString, ',');
        slNo = stoi(tempString);

        // get MovieName
        getline(inputString, movieName, ',');

        line = "";

        movies[slNo] = movieName;
    }

    inputFile.close();
}
