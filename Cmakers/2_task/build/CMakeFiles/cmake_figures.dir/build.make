# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/tanyko/Desktop/file&bibl"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/tanyko/Desktop/file&bibl/build"

# Include any dependencies generated for this target.
include CMakeFiles/cmake_figures.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cmake_figures.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cmake_figures.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmake_figures.dir/flags.make

CMakeFiles/cmake_figures.dir/src/main.cpp.o: CMakeFiles/cmake_figures.dir/flags.make
CMakeFiles/cmake_figures.dir/src/main.cpp.o: /Users/tanyko/Desktop/file&bibl/src/main.cpp
CMakeFiles/cmake_figures.dir/src/main.cpp.o: CMakeFiles/cmake_figures.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/tanyko/Desktop/file&bibl/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cmake_figures.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cmake_figures.dir/src/main.cpp.o -MF CMakeFiles/cmake_figures.dir/src/main.cpp.o.d -o CMakeFiles/cmake_figures.dir/src/main.cpp.o -c "/Users/tanyko/Desktop/file&bibl/src/main.cpp"

CMakeFiles/cmake_figures.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cmake_figures.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tanyko/Desktop/file&bibl/src/main.cpp" > CMakeFiles/cmake_figures.dir/src/main.cpp.i

CMakeFiles/cmake_figures.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cmake_figures.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tanyko/Desktop/file&bibl/src/main.cpp" -o CMakeFiles/cmake_figures.dir/src/main.cpp.s

CMakeFiles/cmake_figures.dir/src/figure_base.cpp.o: CMakeFiles/cmake_figures.dir/flags.make
CMakeFiles/cmake_figures.dir/src/figure_base.cpp.o: /Users/tanyko/Desktop/file&bibl/src/figure_base.cpp
CMakeFiles/cmake_figures.dir/src/figure_base.cpp.o: CMakeFiles/cmake_figures.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/tanyko/Desktop/file&bibl/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cmake_figures.dir/src/figure_base.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cmake_figures.dir/src/figure_base.cpp.o -MF CMakeFiles/cmake_figures.dir/src/figure_base.cpp.o.d -o CMakeFiles/cmake_figures.dir/src/figure_base.cpp.o -c "/Users/tanyko/Desktop/file&bibl/src/figure_base.cpp"

CMakeFiles/cmake_figures.dir/src/figure_base.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cmake_figures.dir/src/figure_base.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tanyko/Desktop/file&bibl/src/figure_base.cpp" > CMakeFiles/cmake_figures.dir/src/figure_base.cpp.i

CMakeFiles/cmake_figures.dir/src/figure_base.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cmake_figures.dir/src/figure_base.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tanyko/Desktop/file&bibl/src/figure_base.cpp" -o CMakeFiles/cmake_figures.dir/src/figure_base.cpp.s

CMakeFiles/cmake_figures.dir/src/quadrangle.cpp.o: CMakeFiles/cmake_figures.dir/flags.make
CMakeFiles/cmake_figures.dir/src/quadrangle.cpp.o: /Users/tanyko/Desktop/file&bibl/src/quadrangle.cpp
CMakeFiles/cmake_figures.dir/src/quadrangle.cpp.o: CMakeFiles/cmake_figures.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/tanyko/Desktop/file&bibl/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cmake_figures.dir/src/quadrangle.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cmake_figures.dir/src/quadrangle.cpp.o -MF CMakeFiles/cmake_figures.dir/src/quadrangle.cpp.o.d -o CMakeFiles/cmake_figures.dir/src/quadrangle.cpp.o -c "/Users/tanyko/Desktop/file&bibl/src/quadrangle.cpp"

CMakeFiles/cmake_figures.dir/src/quadrangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cmake_figures.dir/src/quadrangle.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tanyko/Desktop/file&bibl/src/quadrangle.cpp" > CMakeFiles/cmake_figures.dir/src/quadrangle.cpp.i

CMakeFiles/cmake_figures.dir/src/quadrangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cmake_figures.dir/src/quadrangle.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tanyko/Desktop/file&bibl/src/quadrangle.cpp" -o CMakeFiles/cmake_figures.dir/src/quadrangle.cpp.s

CMakeFiles/cmake_figures.dir/src/triangle.cpp.o: CMakeFiles/cmake_figures.dir/flags.make
CMakeFiles/cmake_figures.dir/src/triangle.cpp.o: /Users/tanyko/Desktop/file&bibl/src/triangle.cpp
CMakeFiles/cmake_figures.dir/src/triangle.cpp.o: CMakeFiles/cmake_figures.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/tanyko/Desktop/file&bibl/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/cmake_figures.dir/src/triangle.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cmake_figures.dir/src/triangle.cpp.o -MF CMakeFiles/cmake_figures.dir/src/triangle.cpp.o.d -o CMakeFiles/cmake_figures.dir/src/triangle.cpp.o -c "/Users/tanyko/Desktop/file&bibl/src/triangle.cpp"

CMakeFiles/cmake_figures.dir/src/triangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cmake_figures.dir/src/triangle.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tanyko/Desktop/file&bibl/src/triangle.cpp" > CMakeFiles/cmake_figures.dir/src/triangle.cpp.i

CMakeFiles/cmake_figures.dir/src/triangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cmake_figures.dir/src/triangle.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tanyko/Desktop/file&bibl/src/triangle.cpp" -o CMakeFiles/cmake_figures.dir/src/triangle.cpp.s

# Object files for target cmake_figures
cmake_figures_OBJECTS = \
"CMakeFiles/cmake_figures.dir/src/main.cpp.o" \
"CMakeFiles/cmake_figures.dir/src/figure_base.cpp.o" \
"CMakeFiles/cmake_figures.dir/src/quadrangle.cpp.o" \
"CMakeFiles/cmake_figures.dir/src/triangle.cpp.o"

# External object files for target cmake_figures
cmake_figures_EXTERNAL_OBJECTS =

cmake_figures: CMakeFiles/cmake_figures.dir/src/main.cpp.o
cmake_figures: CMakeFiles/cmake_figures.dir/src/figure_base.cpp.o
cmake_figures: CMakeFiles/cmake_figures.dir/src/quadrangle.cpp.o
cmake_figures: CMakeFiles/cmake_figures.dir/src/triangle.cpp.o
cmake_figures: CMakeFiles/cmake_figures.dir/build.make
cmake_figures: CMakeFiles/cmake_figures.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/tanyko/Desktop/file&bibl/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable cmake_figures"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmake_figures.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmake_figures.dir/build: cmake_figures
.PHONY : CMakeFiles/cmake_figures.dir/build

CMakeFiles/cmake_figures.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cmake_figures.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cmake_figures.dir/clean

CMakeFiles/cmake_figures.dir/depend:
	cd "/Users/tanyko/Desktop/file&bibl/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/tanyko/Desktop/file&bibl" "/Users/tanyko/Desktop/file&bibl" "/Users/tanyko/Desktop/file&bibl/build" "/Users/tanyko/Desktop/file&bibl/build" "/Users/tanyko/Desktop/file&bibl/build/CMakeFiles/cmake_figures.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/cmake_figures.dir/depend

