#include "TheatreData.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include<bits/stdc++.h>

// global data
std::string TheatreData::theatresFile = "theatre_shows_list.csv";
std::vector<ShowInfo> TheatreData::ShowInfoList;
std::unordered_map< std::string, std::vector<std::string> > TheatreData::movieTheatres;
std::unordered_map< std::string, std::vector<ShowInfo> > TheatreData::movieShowsInfo;

/***************************************************************
*
* Function: TheatreData
* In: -
* Out: -
* Description: This is the default constructor of TheatreData class
*
****************************************************************/
TheatreData::TheatreData()
{
    //ctor
    if (movieTheatres.empty())
    {
        std::string cwd = fileUtilitiesInstance.getCurrentDir();
        theatresFile = cwd + "\\" + theatresFile;

        readTheatreShowsInfo();
    }
}

/***************************************************************
*
* Function: ~TheatreData
* In: -
* Out: -
* Description: This is the destructor of TheatreData class
*
****************************************************************/
TheatreData::~TheatreData()
{
    //dtor
}

/***************************************************************
*
* Function: getTheatres
* In: string, movieName for which theatres List has to be fetched
* Out: is a vector which has list of theatres
* Description: This function returns a vector of theatres which run the movie passed as input
*
****************************************************************/
std::vector<std::string> TheatreData::getTheatres(const std::string movieName)
{
    return movieTheatres[movieName];
}

/***************************************************************
*
* Function: getTheatreShows
* In: string, theatreName for which Shows has to be fetched
      string, movieName for which Shows has to be fetched
* Out: is a vector which has list of Shows with Time
* Description: This function returns a vector of Shows for the theatre Name and movie Name passed as input
*
****************************************************************/
std::vector<ShowInfo> TheatreData::getTheatreShows(const std::string theatreName, const std::string movieName)
{
    std::vector<ShowInfo> showsList;

    for (auto iter = movieShowsInfo[theatreName].begin(); iter != movieShowsInfo[theatreName].end(); iter++)
    {
        if ((*iter).movieName == movieName)
        {
            showsList.push_back(*iter);
        }
    }

    return showsList;
}

/***************************************************************
*
* Function: readTheatreShowsInfo
* In: -
* Out: -
* Description: This function reads the file theatre_shows_list.csv to get
                all the information related to theatre and shows for all movies
*
****************************************************************/
void TheatreData::readTheatreShowsInfo()
{
    std::ifstream inputFile;
    inputFile.open(theatresFile);

    if (!inputFile.is_open()) {
        throw std::runtime_error("Cannot Open the Theatres-Shows File List");
    }

    std::string line;
    unsigned int MAXNOOFSHOWS = 4, index;
    std::string theatreName, tempString, movieName, movieTime;

    // skip the header information from 1st line in CSV
    getline(inputFile, line);

    while (getline(inputFile, line))
    {
        std::stringstream inputString(line);

        // get slNo
        getline(inputString, tempString, ',');

        // get theatreName
        getline(inputString, theatreName, ',');

        for (index = 1; index <= MAXNOOFSHOWS; index++)
        {
            // get movieName
            getline(inputString, movieName, ',');

            // get movieTime
            getline(inputString, movieTime, ',');

            ShowInfo ShowInfoObject(index, movieName, movieTime);

            ShowInfoList.push_back(ShowInfoObject);

            auto iter = std::find (movieTheatres[movieName].begin(), movieTheatres[movieName].end(), theatreName);

            if (iter == movieTheatres[movieName].end())
            {
                movieTheatres[movieName].push_back(theatreName);
            }

            movieShowsInfo[theatreName].push_back(ShowInfoObject);
        }

        line = "";
    }

    inputFile.close();
}
