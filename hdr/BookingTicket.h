#ifndef BOOKINGTICKET_H
#define BOOKINGTICKET_H

#include <string>
#include <map>
#include <vector>
#include <mutex>

#include "FileUtilities.h"

/***************************************************************

Class:          BookingTicket
Description:    This is BookingTicket Class which has all the
                functions related to booking tickets,
                getting available tickets, validate seats selected
Attributes:
fileUtilitiesInstance - FileUtilities Class instance
rowCountAvailability  - its a map which stores the seatRow as key
                        and remaining seats count for validating
                        the booking of seats
booking_mutex         - mutex instance for lock and unlock during
                        booking tickets, getting available tickets

****************************************************************/

class BookingTicket
{
    public:
        BookingTicket();
        virtual ~BookingTicket();

        void bookTickets(const std::string theatreName, const std::string movieName, const unsigned int showNo, const unsigned int seatStart, const unsigned int seatEnd, const std::string seatRow);
        std::map< std::string, std::vector<unsigned int> > getAvailableSeats(const std::string theatreName, const std::string movieName, const unsigned int showNo);

        void validateSeats(const std::string rowNo, const unsigned int seatsCount);

    protected:

    private:
        FileUtilities fileUtilitiesInstance;
        std::map<std::string, unsigned int> rowCountAvailability;
        std::mutex booking_mutex;
};

#endif // BOOKINGTICKET_H
