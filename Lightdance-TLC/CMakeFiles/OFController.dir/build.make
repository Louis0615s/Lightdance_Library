# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/calculus365/Lightdance_Library/Lightdance-TLC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/calculus365/Lightdance_Library/Lightdance-TLC

# Include any dependencies generated for this target.
include CMakeFiles/OFController.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/OFController.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/OFController.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OFController.dir/flags.make

CMakeFiles/OFController.dir/src/OFController.cpp.o: CMakeFiles/OFController.dir/flags.make
CMakeFiles/OFController.dir/src/OFController.cpp.o: src/OFController.cpp
CMakeFiles/OFController.dir/src/OFController.cpp.o: CMakeFiles/OFController.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/calculus365/Lightdance_Library/Lightdance-TLC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OFController.dir/src/OFController.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OFController.dir/src/OFController.cpp.o -MF CMakeFiles/OFController.dir/src/OFController.cpp.o.d -o CMakeFiles/OFController.dir/src/OFController.cpp.o -c /home/calculus365/Lightdance_Library/Lightdance-TLC/src/OFController.cpp

CMakeFiles/OFController.dir/src/OFController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OFController.dir/src/OFController.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/calculus365/Lightdance_Library/Lightdance-TLC/src/OFController.cpp > CMakeFiles/OFController.dir/src/OFController.cpp.i

CMakeFiles/OFController.dir/src/OFController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OFController.dir/src/OFController.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/calculus365/Lightdance_Library/Lightdance-TLC/src/OFController.cpp -o CMakeFiles/OFController.dir/src/OFController.cpp.s

OFController: CMakeFiles/OFController.dir/src/OFController.cpp.o
OFController: CMakeFiles/OFController.dir/build.make
.PHONY : OFController

# Rule to build all files generated by this target.
CMakeFiles/OFController.dir/build: OFController
.PHONY : CMakeFiles/OFController.dir/build

CMakeFiles/OFController.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OFController.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OFController.dir/clean

CMakeFiles/OFController.dir/depend:
	cd /home/calculus365/Lightdance_Library/Lightdance-TLC && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/calculus365/Lightdance_Library/Lightdance-TLC /home/calculus365/Lightdance_Library/Lightdance-TLC /home/calculus365/Lightdance_Library/Lightdance-TLC /home/calculus365/Lightdance_Library/Lightdance-TLC /home/calculus365/Lightdance_Library/Lightdance-TLC/CMakeFiles/OFController.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OFController.dir/depend
