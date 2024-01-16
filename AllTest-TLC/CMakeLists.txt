
cmake_minimum_required(VERSION 3.10)
project(AllMain)

set(CMAKE_CXX_STANDARD 17)
set(LED_LIBRARY ws2811)

include_directories(./include)

add_library(OFController OBJECT ./src/OFController.cpp)
add_library(LEDController OBJECT ./src/LEDController.cpp)

add_executable(AllMain ./src/AllMain.cpp) 

add_subdirectory(./include/rpi_ws281x)


target_link_libraries(
	AllMain
	PUBLIC
	OFController
	LEDController
	${LED_LIBRARY}
)

