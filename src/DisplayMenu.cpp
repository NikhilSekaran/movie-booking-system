#include "DisplayMenu.h"
#include <iostream>

/***************************************************************
*
* Function: DisplayMenu
* In: -
* Out: -
* Description: This is the default constructor of DisplayMenu class
*
****************************************************************/
DisplayMenu::DisplayMenu()
{
    //ctor
}

/***************************************************************
*
* Function: ~DisplayMenu
* In: -
* Out: -
* Description: This is the destructor of DisplayMenu class
*
****************************************************************/
DisplayMenu::~DisplayMenu()
{
    //dtor
}

/***************************************************************
*
* Function: DisplayMainMenu
* In: -
* Out: -
* Description: This function displays the Main Menu information
*
****************************************************************/
void DisplayMenu::DisplayMainMenu()
{
    std::cout << "Welcome to the Movie Ticket Booking System" << std::endl;
    std::cout << "1. View All Playing Movies" << std::endl;
    std::cout << "2. Exit Application" << std::endl;
}

/***************************************************************
*
* Function: DisplayMovieMenu
* In: movies, is a map which has information about all movies (key is SlNo, value is movie Name)
* Out: -
* Description: This function displays the Movies Menu information
*
****************************************************************/
void DisplayMenu::DisplayMovieMenu(std::map<unsigned int, std::string> movies)
{
    for (auto iter = movies.begin(); iter != movies.end(); iter++)
    {
        std::cout << iter->first << ". " << iter->second << std::endl;
    }
}

/***************************************************************
*
* Function: DisplayTheatreMenu
* In: theatreNames, is a list which has information about all theatres
* Out: -
* Description: This function displays the Theatre Menu information for a Movie
*
****************************************************************/
void DisplayMenu::DisplayTheatreMenu(std::vector<std::string> theatreNames)
{
    for (unsigned index = 0; index < theatreNames.size(); index++)
    {
        std::cout << index + 1 << ". " << theatreNames[index] << std::endl;
    }
}

/***************************************************************
*
* Function: DisplayShowsMenu
* In: shows, is a list which has information about all shows
* Out: -
* Description: This function displays the Shows Menu information for a Movie in Theatre
*
****************************************************************/
void DisplayMenu::DisplayShowsMenu(std::vector<ShowInfo> shows)
{
    for (unsigned index = 0; index < shows.size(); index++)
    {
        std::cout << index + 1 << ". " << shows[index].movieTime << std::endl;
    }
}

/***************************************************************
*
* Function: DisplayAvailableSeats
* In: seatsAvailability, is a map which has information about seats Availability (key is Row, value is seat Availability for all 5 columns)
* Out: -
* Description: This function displays the Seats Availability for a Movie in a Theatre of a particular Show
                [] means Seat is available for Booking
                [X] means Seat is already Booked
*
****************************************************************/
void DisplayMenu::DisplayAvailableSeats(std::map< std::string, std::vector<unsigned int> > seatsAvailability)
{
    std::cout << "Seat Row" << "\tColumn No 1\tColumn No 2\tColumn No 3\tColumn No 4\tColumn No 5" << std::endl;
    for (auto iter = seatsAvailability.begin(); iter != seatsAvailability.end(); iter++)
    {
        std::cout << iter->first;

        for (auto seatsIter = iter->second.begin(); seatsIter != iter->second.end(); seatsIter++)
        {
            if (*seatsIter == 1)
            {
                std::cout << "\t\t" << "[ ]";
            }
            else
            {
                std::cout << "\t\t" << "[X]";
            }
        }

        std::cout << std::endl;
    }
}
