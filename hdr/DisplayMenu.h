#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H

#include <string>
#include <map>
#include <vector>

#include "TheatreData.h"

/***************************************************************

Class:          DisplayMenu
Description:    This is DisplayMenu Class which has all the
                functions related to display of messages to User
                in the command line

****************************************************************/

class DisplayMenu
{
    public:
        DisplayMenu();
        virtual ~DisplayMenu();

        void DisplayMainMenu();
        void DisplayMovieMenu(std::map<unsigned int, std::string> movies);
        void DisplayTheatreMenu(std::vector<std::string> theatreNames);
        void DisplayShowsMenu(std::vector<ShowInfo> shows);
        void DisplayAvailableSeats(std::map< std::string, std::vector<unsigned int> > seatsAvailability);
    protected:

    private:

};

#endif // DISPLAYMENU_H
