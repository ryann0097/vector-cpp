# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /mnt/c/users/novo/cpp_projects/selan/ryan-david-vector/source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/users/novo/cpp_projects/selan/ryan-david-vector/build

# Include any dependencies generated for this target.
include CMakeFiles/TM.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TM.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TM.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TM.dir/flags.make

CMakeFiles/TM.dir/tm/test_manager.cpp.o: CMakeFiles/TM.dir/flags.make
CMakeFiles/TM.dir/tm/test_manager.cpp.o: /mnt/c/users/novo/cpp_projects/selan/ryan-david-vector/source/tm/test_manager.cpp
CMakeFiles/TM.dir/tm/test_manager.cpp.o: CMakeFiles/TM.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/users/novo/cpp_projects/selan/ryan-david-vector/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TM.dir/tm/test_manager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TM.dir/tm/test_manager.cpp.o -MF CMakeFiles/TM.dir/tm/test_manager.cpp.o.d -o CMakeFiles/TM.dir/tm/test_manager.cpp.o -c /mnt/c/users/novo/cpp_projects/selan/ryan-david-vector/source/tm/test_manager.cpp

CMakeFiles/TM.dir/tm/test_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TM.dir/tm/test_manager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/users/novo/cpp_projects/selan/ryan-david-vector/source/tm/test_manager.cpp > CMakeFiles/TM.dir/tm/test_manager.cpp.i

CMakeFiles/TM.dir/tm/test_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TM.dir/tm/test_manager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/users/novo/cpp_projects/selan/ryan-david-vector/source/tm/test_manager.cpp -o CMakeFiles/TM.dir/tm/test_manager.cpp.s

# Object files for target TM
TM_OBJECTS = \
"CMakeFiles/TM.dir/tm/test_manager.cpp.o"

# External object files for target TM
TM_EXTERNAL_OBJECTS =

libTM.a: CMakeFiles/TM.dir/tm/test_manager.cpp.o
libTM.a: CMakeFiles/TM.dir/build.make
libTM.a: CMakeFiles/TM.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/users/novo/cpp_projects/selan/ryan-david-vector/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libTM.a"
	$(CMAKE_COMMAND) -P CMakeFiles/TM.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TM.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TM.dir/build: libTM.a
.PHONY : CMakeFiles/TM.dir/build

CMakeFiles/TM.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TM.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TM.dir/clean

CMakeFiles/TM.dir/depend:
	cd /mnt/c/users/novo/cpp_projects/selan/ryan-david-vector/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/users/novo/cpp_projects/selan/ryan-david-vector/source /mnt/c/users/novo/cpp_projects/selan/ryan-david-vector/source /mnt/c/users/novo/cpp_projects/selan/ryan-david-vector/build /mnt/c/users/novo/cpp_projects/selan/ryan-david-vector/build /mnt/c/users/novo/cpp_projects/selan/ryan-david-vector/build/CMakeFiles/TM.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TM.dir/depend

