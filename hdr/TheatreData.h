#ifndef THEATREDATA_H
#define THEATREDATA_H

#include <string>
#include <vector>
#include <unordered_map>

#include "FileUtilities.h"

/***************************************************************

Structure:      ShowInfo
Description:    This is ShowInfo structure which stores
                every Show information (Movie Name and Time) related
                to a movie.
Attributes:
movieName              - string, holds the movie Name
movieTime              - string, holds the movie Time

****************************************************************/

struct ShowInfo
{
    public:
        std::string movieName;
        std::string movieTime;
        unsigned int showNo;

        ShowInfo(unsigned int showNo, std::string movie, std::string showTime)
        {
            this->showNo = showNo;
            this->movieName = movie;
            this->movieTime = showTime;
        }
};

/***************************************************************

Class:          TheatreData
Description:    This is TheatreData Class which has all the
                functions related to reading theatresFile,
                getting Theatres List, Shows List
Attributes:
fileUtilitiesInstance   - FileUtilities Class instance
theatresFile            - string, which holds the theatres data filename with proper path
ShowInfoList            - list of ShowInfo instances
movieTheatres           - un-ordered map which stores movie Name as key
                            and list of theatres as value
movieShowsInfo          - un-ordered map which stores theatre Name as key
                            and list of ShowInfo objects as value

****************************************************************/

class TheatreData
{
    public:
        TheatreData();
        virtual ~TheatreData();

        std::vector<std::string> getTheatres(const std::string movieName);
        std::vector<ShowInfo> getTheatreShows(const std::string theatreName, const std::string movieName);

    protected:

    private:
        static std::string theatresFile;
        static std::vector<ShowInfo> ShowInfoList;
        static std::unordered_map< std::string, std::vector<std::string> > movieTheatres;
        static std::unordered_map< std::string, std::vector<ShowInfo> > movieShowsInfo;

        FileUtilities fileUtilitiesInstance;

        void readTheatreShowsInfo();
};

#endif // THEATREDATA_H
