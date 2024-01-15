
cmake_minimum_required(VERSION 3.10)
project(AllMain)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARY ws2811)

include_directories(./include)

add_library(OFController OBJECT ./src/OFController.cpp)
add_library(LEDController OBJECT ./src/LEDController.cpp)

add_executable(AllMain ./src/AllMain.cpp) 



target_link_libraries(
	AllMain
	PUBLIC
	OFController
	LEDController
	${LIBRARY}
)

