# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/romeo/ClionProjects/Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/romeo/ClionProjects/Server/bin

# Include any dependencies generated for this target.
include CMakeFiles/tcp_echo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tcp_echo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tcp_echo.dir/flags.make

CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.o: CMakeFiles/tcp_echo.dir/flags.make
CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.o: ../server/tcp_echo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/romeo/ClionProjects/Server/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.o -c /home/romeo/ClionProjects/Server/server/tcp_echo.cpp

CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/romeo/ClionProjects/Server/server/tcp_echo.cpp > CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.i

CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/romeo/ClionProjects/Server/server/tcp_echo.cpp -o CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.s

CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.o.requires:

.PHONY : CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.o.requires

CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.o.provides: CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.o.requires
	$(MAKE) -f CMakeFiles/tcp_echo.dir/build.make CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.o.provides.build
.PHONY : CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.o.provides

CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.o.provides.build: CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.o


CMakeFiles/tcp_echo.dir/server/server.cpp.o: CMakeFiles/tcp_echo.dir/flags.make
CMakeFiles/tcp_echo.dir/server/server.cpp.o: ../server/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/romeo/ClionProjects/Server/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tcp_echo.dir/server/server.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tcp_echo.dir/server/server.cpp.o -c /home/romeo/ClionProjects/Server/server/server.cpp

CMakeFiles/tcp_echo.dir/server/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcp_echo.dir/server/server.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/romeo/ClionProjects/Server/server/server.cpp > CMakeFiles/tcp_echo.dir/server/server.cpp.i

CMakeFiles/tcp_echo.dir/server/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcp_echo.dir/server/server.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/romeo/ClionProjects/Server/server/server.cpp -o CMakeFiles/tcp_echo.dir/server/server.cpp.s

CMakeFiles/tcp_echo.dir/server/server.cpp.o.requires:

.PHONY : CMakeFiles/tcp_echo.dir/server/server.cpp.o.requires

CMakeFiles/tcp_echo.dir/server/server.cpp.o.provides: CMakeFiles/tcp_echo.dir/server/server.cpp.o.requires
	$(MAKE) -f CMakeFiles/tcp_echo.dir/build.make CMakeFiles/tcp_echo.dir/server/server.cpp.o.provides.build
.PHONY : CMakeFiles/tcp_echo.dir/server/server.cpp.o.provides

CMakeFiles/tcp_echo.dir/server/server.cpp.o.provides.build: CMakeFiles/tcp_echo.dir/server/server.cpp.o


CMakeFiles/tcp_echo.dir/server/session.cpp.o: CMakeFiles/tcp_echo.dir/flags.make
CMakeFiles/tcp_echo.dir/server/session.cpp.o: ../server/session.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/romeo/ClionProjects/Server/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tcp_echo.dir/server/session.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tcp_echo.dir/server/session.cpp.o -c /home/romeo/ClionProjects/Server/server/session.cpp

CMakeFiles/tcp_echo.dir/server/session.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcp_echo.dir/server/session.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/romeo/ClionProjects/Server/server/session.cpp > CMakeFiles/tcp_echo.dir/server/session.cpp.i

CMakeFiles/tcp_echo.dir/server/session.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcp_echo.dir/server/session.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/romeo/ClionProjects/Server/server/session.cpp -o CMakeFiles/tcp_echo.dir/server/session.cpp.s

CMakeFiles/tcp_echo.dir/server/session.cpp.o.requires:

.PHONY : CMakeFiles/tcp_echo.dir/server/session.cpp.o.requires

CMakeFiles/tcp_echo.dir/server/session.cpp.o.provides: CMakeFiles/tcp_echo.dir/server/session.cpp.o.requires
	$(MAKE) -f CMakeFiles/tcp_echo.dir/build.make CMakeFiles/tcp_echo.dir/server/session.cpp.o.provides.build
.PHONY : CMakeFiles/tcp_echo.dir/server/session.cpp.o.provides

CMakeFiles/tcp_echo.dir/server/session.cpp.o.provides.build: CMakeFiles/tcp_echo.dir/server/session.cpp.o


# Object files for target tcp_echo
tcp_echo_OBJECTS = \
"CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.o" \
"CMakeFiles/tcp_echo.dir/server/server.cpp.o" \
"CMakeFiles/tcp_echo.dir/server/session.cpp.o"

# External object files for target tcp_echo
tcp_echo_EXTERNAL_OBJECTS =

tcp_echo: CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.o
tcp_echo: CMakeFiles/tcp_echo.dir/server/server.cpp.o
tcp_echo: CMakeFiles/tcp_echo.dir/server/session.cpp.o
tcp_echo: CMakeFiles/tcp_echo.dir/build.make
tcp_echo: /usr/local/lib/libboost_system.so
tcp_echo: CMakeFiles/tcp_echo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/romeo/ClionProjects/Server/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable tcp_echo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcp_echo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tcp_echo.dir/build: tcp_echo

.PHONY : CMakeFiles/tcp_echo.dir/build

CMakeFiles/tcp_echo.dir/requires: CMakeFiles/tcp_echo.dir/server/tcp_echo.cpp.o.requires
CMakeFiles/tcp_echo.dir/requires: CMakeFiles/tcp_echo.dir/server/server.cpp.o.requires
CMakeFiles/tcp_echo.dir/requires: CMakeFiles/tcp_echo.dir/server/session.cpp.o.requires

.PHONY : CMakeFiles/tcp_echo.dir/requires

CMakeFiles/tcp_echo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tcp_echo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tcp_echo.dir/clean

CMakeFiles/tcp_echo.dir/depend:
	cd /home/romeo/ClionProjects/Server/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/romeo/ClionProjects/Server /home/romeo/ClionProjects/Server /home/romeo/ClionProjects/Server/bin /home/romeo/ClionProjects/Server/bin /home/romeo/ClionProjects/Server/bin/CMakeFiles/tcp_echo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tcp_echo.dir/depend

