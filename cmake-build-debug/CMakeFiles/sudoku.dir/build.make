# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/binrad/Downloads/LINUX/clion-2018.3.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/binrad/Downloads/LINUX/clion-2018.3.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/binrad/Documents/sudoku

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/binrad/Documents/sudoku/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/sudoku.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sudoku.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sudoku.dir/flags.make

CMakeFiles/sudoku.dir/two.cpp.o: CMakeFiles/sudoku.dir/flags.make
CMakeFiles/sudoku.dir/two.cpp.o: ../two.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/binrad/Documents/sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sudoku.dir/two.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sudoku.dir/two.cpp.o -c /home/binrad/Documents/sudoku/two.cpp

CMakeFiles/sudoku.dir/two.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sudoku.dir/two.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/binrad/Documents/sudoku/two.cpp > CMakeFiles/sudoku.dir/two.cpp.i

CMakeFiles/sudoku.dir/two.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sudoku.dir/two.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/binrad/Documents/sudoku/two.cpp -o CMakeFiles/sudoku.dir/two.cpp.s

# Object files for target sudoku
sudoku_OBJECTS = \
"CMakeFiles/sudoku.dir/two.cpp.o"

# External object files for target sudoku
sudoku_EXTERNAL_OBJECTS =

sudoku: CMakeFiles/sudoku.dir/two.cpp.o
sudoku: CMakeFiles/sudoku.dir/build.make
sudoku: CMakeFiles/sudoku.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/binrad/Documents/sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sudoku"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sudoku.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sudoku.dir/build: sudoku

.PHONY : CMakeFiles/sudoku.dir/build

CMakeFiles/sudoku.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sudoku.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sudoku.dir/clean

CMakeFiles/sudoku.dir/depend:
	cd /home/binrad/Documents/sudoku/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/binrad/Documents/sudoku /home/binrad/Documents/sudoku /home/binrad/Documents/sudoku/cmake-build-debug /home/binrad/Documents/sudoku/cmake-build-debug /home/binrad/Documents/sudoku/cmake-build-debug/CMakeFiles/sudoku.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sudoku.dir/depend

