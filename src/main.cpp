#include <iostream>
#include <string>

#include "DisplayMenu.h"
#include "BookingTicket.h"
#include "MoviesData.h"
#include "MoviesData.h"

int main()
{
    try
    {
        uint8_t userOption = 0;
        unsigned int movieOption = 0, theatreOption = 0, showOption = 0, seatStart = 0, seatEnd = 0, seatCount = 0;

        DisplayMenu dispMenuInstance;
        MoviesData moviesDataInstance;
        TheatreData theatreDataInstance;
        BookingTicket bookingTicketInstance;

        std::string movieSelected, seatRow;
        std::map<unsigned int, std::string> movies;

    Start:
        dispMenuInstance.DisplayMainMenu();

        std::cin >> userOption;

    InValidMovie:
        switch(userOption)
        {
        case '1':
            {
                system("cls");
                std::cout << "Select a Movie:" << std::endl;
                movies = moviesDataInstance.getMovies();
                dispMenuInstance.DisplayMovieMenu(movies);

                std::cin >> movieOption;

                if (movies.find(movieOption) == movies.end())
                {
                    std::cout << "Invalid Choice, Please Select a Valid Movie Option." << std::endl;
                    goto InValidMovie;
                }

                std::string movieName = movies[movieOption];
                std::vector<std::string> theatres = theatreDataInstance.getTheatres(movieName);

            InValidTheatre:
                system("cls");

                std::cout << "List of Theatres playing " << movieName << ":" << std::endl;
                dispMenuInstance.DisplayTheatreMenu(theatres);

                std::cout << "Select a Theatre to Book Tickets!" << std::endl;

                std::cin >> theatreOption;

                if (theatreOption == 0 || theatreOption > theatres.size())
                {
                    std::cout << "Invalid Choice, Please Select a Valid Theatre Option." << std::endl;
                    goto InValidTheatre;
                }

                std::string theatreName = theatres[theatreOption - 1];
                std::vector<ShowInfo> showList = theatreDataInstance.getTheatreShows(theatreName, movieName);

            InValidShow:
                system("cls");
                std::cout << "Select a Show to Book Tickets!" << std::endl;
                dispMenuInstance.DisplayShowsMenu(showList);

                std::cin >> showOption;

                if (showOption == 0 || showOption > showList.size())
                {
                    std::cout << "Invalid Choice, Please Select a Valid Show Option." << std::endl;
                    goto InValidShow;
                }

                std::map< std::string, std::vector<unsigned int> > availableSeats = bookingTicketInstance.getAvailableSeats(theatreName, movieName, showOption);

                system("cls");

                std::cout << "Available Seats:" << std::endl;
                dispMenuInstance.DisplayAvailableSeats(availableSeats);

                std::cout << "Enter SeatRow, SeatStartColumn, SeatEndColumn to Book Tickets" << std::endl;
                std::cin >> seatRow;
                std::cin >> seatStart;
                std::cin >> seatEnd;

                seatCount = seatEnd - seatStart + 1;

                bookingTicketInstance.validateSeats(seatRow, seatCount);

                bookingTicketInstance.bookTickets(theatreName, movieName, showOption, seatStart, seatEnd, seatRow);

                std::cout << "Requested Tickets for the Selected Movie is booked Successfully" << std::endl;
            }
            break;
        case '2':
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid Choice, Please Select a Valid Option." << std::endl;
            goto Start;
        }
    }
    catch (std::exception &errorVar)
    {
        std::cout << "Movie ticket booking system is terminating abnormally with the "
                  << "following exception:\n" << errorVar.what() << "\n"
                  << "Exiting Application " << std::endl;
        return -1;
    }

    std::cout << "Exiting the Movie Booking System..." << std::endl;

    return 0;
}
