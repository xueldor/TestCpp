# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/xue/clion-2020.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/xue/clion-2020.2/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xue/CLionProjects/LinuxProgramming/CppBasic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xue/CLionProjects/LinuxProgramming/CppBasic/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CppBasic.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CppBasic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CppBasic.dir/flags.make

CMakeFiles/CppBasic.dir/main.cpp.o: CMakeFiles/CppBasic.dir/flags.make
CMakeFiles/CppBasic.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xue/CLionProjects/LinuxProgramming/CppBasic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CppBasic.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CppBasic.dir/main.cpp.o -c /home/xue/CLionProjects/LinuxProgramming/CppBasic/main.cpp

CMakeFiles/CppBasic.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CppBasic.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xue/CLionProjects/LinuxProgramming/CppBasic/main.cpp > CMakeFiles/CppBasic.dir/main.cpp.i

CMakeFiles/CppBasic.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CppBasic.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xue/CLionProjects/LinuxProgramming/CppBasic/main.cpp -o CMakeFiles/CppBasic.dir/main.cpp.s

# Object files for target CppBasic
CppBasic_OBJECTS = \
"CMakeFiles/CppBasic.dir/main.cpp.o"

# External object files for target CppBasic
CppBasic_EXTERNAL_OBJECTS =

CppBasic: CMakeFiles/CppBasic.dir/main.cpp.o
CppBasic: CMakeFiles/CppBasic.dir/build.make
CppBasic: CMakeFiles/CppBasic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xue/CLionProjects/LinuxProgramming/CppBasic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable CppBasic"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CppBasic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CppBasic.dir/build: CppBasic

.PHONY : CMakeFiles/CppBasic.dir/build

CMakeFiles/CppBasic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CppBasic.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CppBasic.dir/clean

CMakeFiles/CppBasic.dir/depend:
	cd /home/xue/CLionProjects/LinuxProgramming/CppBasic/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xue/CLionProjects/LinuxProgramming/CppBasic /home/xue/CLionProjects/LinuxProgramming/CppBasic /home/xue/CLionProjects/LinuxProgramming/CppBasic/cmake-build-debug /home/xue/CLionProjects/LinuxProgramming/CppBasic/cmake-build-debug /home/xue/CLionProjects/LinuxProgramming/CppBasic/cmake-build-debug/CMakeFiles/CppBasic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CppBasic.dir/depend

