
cmake_minimum_required(VERSION 3.10)
project(hardware)

set(CMAKE_CXX_STANDARD 17)
set(LED_LIBRARY ws2811)
set(INCLUDES include)

add_library(
	hardware
	STATIC
	./src/OFController.cpp
	./src/LEDController.cpp
) 

target_include_directories(
  hardware
  PUBLIC
  ${INCLUDES}
)

add_subdirectory(./include/rpi_ws281x)

target_link_libraries(
	hardware
	${LED_LIBRARY}
)
