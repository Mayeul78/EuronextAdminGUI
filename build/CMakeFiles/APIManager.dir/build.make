# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mayeulboucher/Desktop/Euronext_Project/GUI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mayeulboucher/Desktop/Euronext_Project/GUI/build

# Include any dependencies generated for this target.
include CMakeFiles/APIManager.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/APIManager.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/APIManager.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/APIManager.dir/flags.make

CMakeFiles/APIManager.dir/APIManager.cpp.o: CMakeFiles/APIManager.dir/flags.make
CMakeFiles/APIManager.dir/APIManager.cpp.o: /Users/mayeulboucher/Desktop/Euronext_Project/GUI/APIManager.cpp
CMakeFiles/APIManager.dir/APIManager.cpp.o: CMakeFiles/APIManager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mayeulboucher/Desktop/Euronext_Project/GUI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/APIManager.dir/APIManager.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/APIManager.dir/APIManager.cpp.o -MF CMakeFiles/APIManager.dir/APIManager.cpp.o.d -o CMakeFiles/APIManager.dir/APIManager.cpp.o -c /Users/mayeulboucher/Desktop/Euronext_Project/GUI/APIManager.cpp

CMakeFiles/APIManager.dir/APIManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/APIManager.dir/APIManager.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mayeulboucher/Desktop/Euronext_Project/GUI/APIManager.cpp > CMakeFiles/APIManager.dir/APIManager.cpp.i

CMakeFiles/APIManager.dir/APIManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/APIManager.dir/APIManager.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mayeulboucher/Desktop/Euronext_Project/GUI/APIManager.cpp -o CMakeFiles/APIManager.dir/APIManager.cpp.s

# Object files for target APIManager
APIManager_OBJECTS = \
"CMakeFiles/APIManager.dir/APIManager.cpp.o"

# External object files for target APIManager
APIManager_EXTERNAL_OBJECTS =

libAPIManager.a: CMakeFiles/APIManager.dir/APIManager.cpp.o
libAPIManager.a: CMakeFiles/APIManager.dir/build.make
libAPIManager.a: CMakeFiles/APIManager.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/mayeulboucher/Desktop/Euronext_Project/GUI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libAPIManager.a"
	$(CMAKE_COMMAND) -P CMakeFiles/APIManager.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/APIManager.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/APIManager.dir/build: libAPIManager.a
.PHONY : CMakeFiles/APIManager.dir/build

CMakeFiles/APIManager.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/APIManager.dir/cmake_clean.cmake
.PHONY : CMakeFiles/APIManager.dir/clean

CMakeFiles/APIManager.dir/depend:
	cd /Users/mayeulboucher/Desktop/Euronext_Project/GUI/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mayeulboucher/Desktop/Euronext_Project/GUI /Users/mayeulboucher/Desktop/Euronext_Project/GUI /Users/mayeulboucher/Desktop/Euronext_Project/GUI/build /Users/mayeulboucher/Desktop/Euronext_Project/GUI/build /Users/mayeulboucher/Desktop/Euronext_Project/GUI/build/CMakeFiles/APIManager.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/APIManager.dir/depend

