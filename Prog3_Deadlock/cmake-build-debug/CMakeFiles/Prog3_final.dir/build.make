# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\casey\Desktop\Prog3_final

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\casey\Desktop\Prog3_final\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Prog3_final.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Prog3_final.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Prog3_final.dir/flags.make

CMakeFiles/Prog3_final.dir/main.cpp.obj: CMakeFiles/Prog3_final.dir/flags.make
CMakeFiles/Prog3_final.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\casey\Desktop\Prog3_final\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Prog3_final.dir/main.cpp.obj"
	C:\PROGRA~1\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Prog3_final.dir\main.cpp.obj -c C:\Users\casey\Desktop\Prog3_final\main.cpp

CMakeFiles/Prog3_final.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Prog3_final.dir/main.cpp.i"
	C:\PROGRA~1\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\casey\Desktop\Prog3_final\main.cpp > CMakeFiles\Prog3_final.dir\main.cpp.i

CMakeFiles/Prog3_final.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Prog3_final.dir/main.cpp.s"
	C:\PROGRA~1\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\casey\Desktop\Prog3_final\main.cpp -o CMakeFiles\Prog3_final.dir\main.cpp.s

# Object files for target Prog3_final
Prog3_final_OBJECTS = \
"CMakeFiles/Prog3_final.dir/main.cpp.obj"

# External object files for target Prog3_final
Prog3_final_EXTERNAL_OBJECTS =

Prog3_final.exe: CMakeFiles/Prog3_final.dir/main.cpp.obj
Prog3_final.exe: CMakeFiles/Prog3_final.dir/build.make
Prog3_final.exe: CMakeFiles/Prog3_final.dir/linklibs.rsp
Prog3_final.exe: CMakeFiles/Prog3_final.dir/objects1.rsp
Prog3_final.exe: CMakeFiles/Prog3_final.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\casey\Desktop\Prog3_final\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Prog3_final.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Prog3_final.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Prog3_final.dir/build: Prog3_final.exe

.PHONY : CMakeFiles/Prog3_final.dir/build

CMakeFiles/Prog3_final.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Prog3_final.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Prog3_final.dir/clean

CMakeFiles/Prog3_final.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\casey\Desktop\Prog3_final C:\Users\casey\Desktop\Prog3_final C:\Users\casey\Desktop\Prog3_final\cmake-build-debug C:\Users\casey\Desktop\Prog3_final\cmake-build-debug C:\Users\casey\Desktop\Prog3_final\cmake-build-debug\CMakeFiles\Prog3_final.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Prog3_final.dir/depend

