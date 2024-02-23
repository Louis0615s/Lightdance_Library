
cmake_minimum_required(VERSION 3.10)
project(hardware)

set(CMAKE_CXX_STANDARD 17)
set(LED_LIBRARY ws2811)
set(INCLUDES inc)

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

target_link_libraries(
	hardware
	${LED_LIBRARY}
)
