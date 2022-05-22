#include "BookingTicket.h"
#include <fstream>
#include <sstream>

/***************************************************************
*
* Function: BookingTicket
* In: -
* Out: -
* Description: This is the default constructor of BookingTicket class
*
****************************************************************/
BookingTicket::BookingTicket()
{
    //ctor
}

/***************************************************************
*
* Function: ~BookingTicket
* In: -
* Out: -
* Description: This is the destructor of BookingTicket class
*
****************************************************************/
BookingTicket::~BookingTicket()
{
    //dtor
}

/***************************************************************
*
* Function: bookTickets
* In: string, theatreName for which Ticket has to be booked
      string, movieName for which Ticket has to be booked
      unsigned int, showNo for which Ticket has to be booked
      unsigned int, seatStart has the start columnNo for which Ticket has to be booked
      unsigned int, seatEnd, has the end columnNo for which Ticket has to be booked,
      string, seatRow for which Ticket has to be booked
* Out: -
* Description: This function does the following:

1. reads the input file which has the file name in the format "theatreName + "_" + movieName + "_Show" + showNo + .csv"
2. creates a new output file which has the file name in the format "theatreName + "_" + movieName + "_Show" + showNo + New + .csv"
3. for every row data read, its checked for the booking request
4. if the row data and column no match the requested booking, its seats are updated with not available
5. updated information is written back to the output file
6. input file is closed and deleted
7. output file is closed and renamed to input file name
8. this way the update of seats is done in the csv file
*
****************************************************************/
void BookingTicket::bookTickets(const std::string theatreName,
                                const std::string movieName,
                                const unsigned int showNo,
                                const unsigned int seatStart,
                                const unsigned int seatEnd,
                                const std::string seatRow)
{
    const std::lock_guard<std::mutex> lock(booking_mutex);

    std::string fileName = theatreName + "_" + movieName + "_Show" + std::to_string(showNo);
    std::string fileExt = ".csv";
    std::string inputfileName = fileName + fileExt;
    std::string outputfileName = fileName + "New" + fileExt;

    std::string cwd = fileUtilitiesInstance.getCurrentDir();

    inputfileName = cwd + "\\" + inputfileName;
    outputfileName = cwd + "\\" + outputfileName;


    std::ifstream inputFile;
    std::ofstream outputFile;

    inputFile.open(inputfileName);
    outputFile.open(outputfileName);

    if (!inputFile.is_open()) {
        throw std::runtime_error("Cannot Open the File To Book Tickets");
    }

    if (!outputFile.is_open()) {
        throw std::runtime_error("Cannot Open the File To Book Tickets");
    }

    std::string line;
    std::string rowNo, tempString;
    unsigned int isSeatAvailable;
    unsigned int seatColNo;

    while (getline(inputFile, line))
    {
        std::stringstream inputString(line);

        // get rowNo
        getline(inputString, rowNo, ',');

        outputFile << rowNo << ",";

        for (seatColNo = 1; seatColNo <= 5; seatColNo++)
        {
            isSeatAvailable = 1;

            if (rowNo == seatRow && seatStart <= seatColNo && seatColNo <= seatEnd)
            {
                isSeatAvailable = 0;

                rowCountAvailability[rowNo]--;
            }

            outputFile << isSeatAvailable;

            if (seatColNo != 5)
            {
                outputFile << ",";
            }
        }

        if (rowNo != "E")
        {
            outputFile << "\n";
        }

        line = "";
    }

    inputFile.close();
    outputFile.close();

    if ( remove(inputfileName.c_str()) != 0 )
    {
        throw std::runtime_error("Failed To Book Tickets");
    }

    if ( rename(outputfileName.c_str(), inputfileName.c_str()) != 0 )
    {
        throw std::runtime_error("Failed To Book Tickets");
    }
}

/***************************************************************
*
* Function: getAvailableSeats
* In: string, theatreName for which Ticket has to be booked
      string, movieName for which Ticket has to be booked
      unsigned int, showNo for which Ticket has to be booked
* Out: std::map< std::string, std::vector<unsigned int> > which has the seats availability (key is seatRow, value is list of column availability for booking)
        for the passed theatreName, movieName, showNo as input
* Description: This function does the following:

1. open the file which has the file name in the format "theatreName + "_" + movieName + "_Show" + showNo + .csv"
2. if the file open fails in read mode, then its understood that the csv file does not exist for the current theatre, Movie and Show
3. if the csv file does not exist, then create it and fill information with all seats (A to E) and columns (1 to 5) available for booking and get seating availability
4. if the csv file exist already, then read it and get seating availability
5. rowCountAvailability is also updated here to maintain the seat row with this availability, as rowCountAvailability is used for validation of seats
6. close the csv file
7. return the seating availability
*
****************************************************************/
std::map< std::string, std::vector<unsigned int> > BookingTicket::getAvailableSeats(const std::string theatreName, const std::string movieName, const unsigned int showNo)
{
    const std::lock_guard<std::mutex> lock(booking_mutex);

    std::string fileName = theatreName + "_" + movieName + "_Show" + std::to_string(showNo) + ".csv";
    std::string cwd = fileUtilitiesInstance.getCurrentDir();

    fileName = cwd + "\\" + fileName;

    std::map< std::string, std::vector<unsigned int> > seatsAvailable;
    unsigned int seatColNo;
    std::fstream inputFileRead, inputFileWrite;

    // create a file to read
    inputFileRead.open(fileName, std::ios::in);

    if (!inputFileRead.is_open()) {

        inputFileRead.close();

        // create a file to write or append
        inputFileWrite.open(fileName, std::ios::out | std::ios::app);

        if (!inputFileWrite.is_open()) {
            throw std::runtime_error("Cannot Open the Seats Availability File");
        }

        char rowNo;
        std::string key;
        for (rowNo = 'A'; rowNo <= 'E'; rowNo++)
        {
            key = rowNo;

            inputFileWrite << key << ",";

            for (seatColNo = 1; seatColNo <= 5; seatColNo++)
            {
                // 1 here means seat is available for booking
                seatsAvailable[key].push_back(1);

                rowCountAvailability[key]++;

                inputFileWrite << 1;

                if (seatColNo != 5)
                {
                    inputFileWrite << ",";
                }
            }

            if (rowNo != 'E')
            {
                inputFileWrite << "\n";
            }
        }

        inputFileWrite.close();
    }
    else
    {
        std::string line;
        std::string rowNo, tempString;
        unsigned int isSeatAvailable;

        while (getline(inputFileRead, line))
        {
            std::stringstream inputString(line);

            // get rowNo
            getline(inputString, rowNo, ',');

            for (seatColNo = 1; seatColNo <= 5; seatColNo++)
            {
                // get seat availability (1 means available, 0 means unavailable)
                getline(inputString, tempString, ',');
                isSeatAvailable = stoi(tempString);

                seatsAvailable[rowNo].push_back(isSeatAvailable);

                if (isSeatAvailable == 1)
                {
                    rowCountAvailability[rowNo]++;
                }
            }

            line = "";
        }

        inputFileRead.close();
    }

    return seatsAvailable;
}

/***************************************************************
*
* Function: validateSeats
* In: string, rowNo for which Seats has to be validated
      unsigned int, seatsCount for which Seats has to be validated
* Out: -
* Description: This function does the following:

1. looks for the seat rowNo passed as input, if its not available, it raises an exception
2. looks for the seat count availability in rowNo passed as input,
    if the seatsCount requested to book is less than the available seats then it raises an exception
*
****************************************************************/
void BookingTicket::validateSeats(const std::string rowNo, const unsigned int seatsCount)
{
    if ( rowCountAvailability.find(rowNo) == rowCountAvailability.end() )
    {
        throw std::runtime_error("Invalid RowNo Requested for Booking Tickets");
    }

    if (rowCountAvailability[rowNo] < seatsCount)
    {
        throw std::runtime_error("Requested Number of Seats for the Requested Row is not possible for Booking Tickets");
    }
}
