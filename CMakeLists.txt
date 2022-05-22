cmake_minimum_required(VERSION 3.0)

project(movie_booking)

# Make sure all exe's end up in one directory:
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Build an 64Bit Application
set(CMAKE_C_FLAGS -m64)
set(CMAKE_CXX_FLAGS "-m64 -fpermissive -std=c++11 -Wno-write-strings")
set(CMAKE_RC_FLAGS "--target=pe-x86-64 ${CMAKE_RC_FLAGS}")

set(DATA_STORE_DIR "datastore/")

include_directories("hdr")

set(SOURCE  "src/main.cpp"
			"src/BookingTicket.cpp"
			"src/DisplayMenu.cpp"
			"src/FileUtilities.cpp"
			"src/MoviesData.cpp"
			"src/TheatreData.cpp"
   )

set(HEADER  "hdr/BookingTicket.h"
			"hdr/DisplayMenu.h"
			"hdr/FileUtilities.h"
			"hdr/MoviesData.h"
			"hdr/TheatreData.h"
   )
   
add_executable(Movie_Booking
				${SOURCE}
				${HEADER}
			  )
			  
file(COPY   ${DATA_STORE_DIR}
		DESTINATION ${CMAKE_CURRENT_BINARY_DIR})