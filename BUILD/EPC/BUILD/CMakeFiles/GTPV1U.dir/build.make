# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/openair/openair-cn/BUILD/EPC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/openair/openair-cn/BUILD/EPC/BUILD

# Include any dependencies generated for this target.
include CMakeFiles/GTPV1U.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GTPV1U.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GTPV1U.dir/flags.make

CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.o: CMakeFiles/GTPV1U.dir/flags.make
CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.o: /home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/openair/openair-cn/BUILD/EPC/BUILD/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.o   -c /home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c

CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c > CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.i

CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c -o CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.s

CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.o.requires:
.PHONY : CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.o.requires

CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.o.provides: CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.o.requires
	$(MAKE) -f CMakeFiles/GTPV1U.dir/build.make CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.o.provides.build
.PHONY : CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.o.provides

CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.o.provides.build: CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.o

# Object files for target GTPV1U
GTPV1U_OBJECTS = \
"CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.o"

# External object files for target GTPV1U
GTPV1U_EXTERNAL_OBJECTS =

libGTPV1U.a: CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.o
libGTPV1U.a: CMakeFiles/GTPV1U.dir/build.make
libGTPV1U.a: CMakeFiles/GTPV1U.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libGTPV1U.a"
	$(CMAKE_COMMAND) -P CMakeFiles/GTPV1U.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GTPV1U.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GTPV1U.dir/build: libGTPV1U.a
.PHONY : CMakeFiles/GTPV1U.dir/build

CMakeFiles/GTPV1U.dir/requires: CMakeFiles/GTPV1U.dir/home/openair/openair-cn/GTPV1-U/gtpv1u_teid_pool.c.o.requires
.PHONY : CMakeFiles/GTPV1U.dir/requires

CMakeFiles/GTPV1U.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GTPV1U.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GTPV1U.dir/clean

CMakeFiles/GTPV1U.dir/depend:
	cd /home/openair/openair-cn/BUILD/EPC/BUILD && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/openair/openair-cn/BUILD/EPC /home/openair/openair-cn/BUILD/EPC /home/openair/openair-cn/BUILD/EPC/BUILD /home/openair/openair-cn/BUILD/EPC/BUILD /home/openair/openair-cn/BUILD/EPC/BUILD/CMakeFiles/GTPV1U.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GTPV1U.dir/depend

