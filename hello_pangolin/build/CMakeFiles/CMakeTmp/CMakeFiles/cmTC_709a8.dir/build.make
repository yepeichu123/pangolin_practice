# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ypc/xiaoc/code/pangolin_practice/hello_pangolin/build/CMakeFiles/CMakeTmp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ypc/xiaoc/code/pangolin_practice/hello_pangolin/build/CMakeFiles/CMakeTmp

# Include any dependencies generated for this target.
include CMakeFiles/cmTC_709a8.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cmTC_709a8.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmTC_709a8.dir/flags.make

CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.o: CMakeFiles/cmTC_709a8.dir/flags.make
CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.o: /home/ypc/xiaoc/code/pangolin_practice/hello_pangolin/build/CMakeFiles/feature_tests.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/ypc/xiaoc/code/pangolin_practice/hello_pangolin/build/CMakeFiles/CMakeTmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.o -c /home/ypc/xiaoc/code/pangolin_practice/hello_pangolin/build/CMakeFiles/feature_tests.cxx

CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.i: cmake_force
	@echo "Preprocessing CXX source to CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ypc/xiaoc/code/pangolin_practice/hello_pangolin/build/CMakeFiles/feature_tests.cxx > CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.i

CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.s: cmake_force
	@echo "Compiling CXX source to assembly CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ypc/xiaoc/code/pangolin_practice/hello_pangolin/build/CMakeFiles/feature_tests.cxx -o CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.s

CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.o.requires:

.PHONY : CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.o.requires

CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.o.provides: CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.o.requires
	$(MAKE) -f CMakeFiles/cmTC_709a8.dir/build.make CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.o.provides.build
.PHONY : CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.o.provides

CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.o.provides.build: CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.o


# Object files for target cmTC_709a8
cmTC_709a8_OBJECTS = \
"CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.o"

# External object files for target cmTC_709a8
cmTC_709a8_EXTERNAL_OBJECTS =

cmTC_709a8: CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.o
cmTC_709a8: CMakeFiles/cmTC_709a8.dir/build.make
cmTC_709a8: CMakeFiles/cmTC_709a8.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/ypc/xiaoc/code/pangolin_practice/hello_pangolin/build/CMakeFiles/CMakeTmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cmTC_709a8"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmTC_709a8.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmTC_709a8.dir/build: cmTC_709a8

.PHONY : CMakeFiles/cmTC_709a8.dir/build

CMakeFiles/cmTC_709a8.dir/requires: CMakeFiles/cmTC_709a8.dir/feature_tests.cxx.o.requires

.PHONY : CMakeFiles/cmTC_709a8.dir/requires

CMakeFiles/cmTC_709a8.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cmTC_709a8.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cmTC_709a8.dir/clean

CMakeFiles/cmTC_709a8.dir/depend:
	cd /home/ypc/xiaoc/code/pangolin_practice/hello_pangolin/build/CMakeFiles/CMakeTmp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ypc/xiaoc/code/pangolin_practice/hello_pangolin/build/CMakeFiles/CMakeTmp /home/ypc/xiaoc/code/pangolin_practice/hello_pangolin/build/CMakeFiles/CMakeTmp /home/ypc/xiaoc/code/pangolin_practice/hello_pangolin/build/CMakeFiles/CMakeTmp /home/ypc/xiaoc/code/pangolin_practice/hello_pangolin/build/CMakeFiles/CMakeTmp /home/ypc/xiaoc/code/pangolin_practice/hello_pangolin/build/CMakeFiles/CMakeTmp/CMakeFiles/cmTC_709a8.dir/DependInfo.cmake
.PHONY : CMakeFiles/cmTC_709a8.dir/depend

