# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jetson/Downloads/iir1-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jetson/Downloads/iir1-master

# Include any dependencies generated for this target.
include test/CMakeFiles/test_rbj.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test_rbj.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test_rbj.dir/flags.make

test/CMakeFiles/test_rbj.dir/rbj.cpp.o: test/CMakeFiles/test_rbj.dir/flags.make
test/CMakeFiles/test_rbj.dir/rbj.cpp.o: test/rbj.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jetson/Downloads/iir1-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test_rbj.dir/rbj.cpp.o"
	cd /home/jetson/Downloads/iir1-master/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_rbj.dir/rbj.cpp.o -c /home/jetson/Downloads/iir1-master/test/rbj.cpp

test/CMakeFiles/test_rbj.dir/rbj.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_rbj.dir/rbj.cpp.i"
	cd /home/jetson/Downloads/iir1-master/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jetson/Downloads/iir1-master/test/rbj.cpp > CMakeFiles/test_rbj.dir/rbj.cpp.i

test/CMakeFiles/test_rbj.dir/rbj.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_rbj.dir/rbj.cpp.s"
	cd /home/jetson/Downloads/iir1-master/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jetson/Downloads/iir1-master/test/rbj.cpp -o CMakeFiles/test_rbj.dir/rbj.cpp.s

# Object files for target test_rbj
test_rbj_OBJECTS = \
"CMakeFiles/test_rbj.dir/rbj.cpp.o"

# External object files for target test_rbj
test_rbj_EXTERNAL_OBJECTS =

test/test_rbj: test/CMakeFiles/test_rbj.dir/rbj.cpp.o
test/test_rbj: test/CMakeFiles/test_rbj.dir/build.make
test/test_rbj: libiir_static.a
test/test_rbj: test/CMakeFiles/test_rbj.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jetson/Downloads/iir1-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_rbj"
	cd /home/jetson/Downloads/iir1-master/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_rbj.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test_rbj.dir/build: test/test_rbj

.PHONY : test/CMakeFiles/test_rbj.dir/build

test/CMakeFiles/test_rbj.dir/clean:
	cd /home/jetson/Downloads/iir1-master/test && $(CMAKE_COMMAND) -P CMakeFiles/test_rbj.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test_rbj.dir/clean

test/CMakeFiles/test_rbj.dir/depend:
	cd /home/jetson/Downloads/iir1-master && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jetson/Downloads/iir1-master /home/jetson/Downloads/iir1-master/test /home/jetson/Downloads/iir1-master /home/jetson/Downloads/iir1-master/test /home/jetson/Downloads/iir1-master/test/CMakeFiles/test_rbj.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test_rbj.dir/depend
