# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\axelo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8617.54\bin\cmake\win\x64\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\axelo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8617.54\bin\cmake\win\x64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug

# Include any dependencies generated for this target.
include dependencies/glfw/tests/CMakeFiles/clipboard.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dependencies/glfw/tests/CMakeFiles/clipboard.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/glfw/tests/CMakeFiles/clipboard.dir/progress.make

# Include the compile flags for this target's objects.
include dependencies/glfw/tests/CMakeFiles/clipboard.dir/flags.make

dependencies/glfw/tests/CMakeFiles/clipboard.dir/clipboard.c.obj: dependencies/glfw/tests/CMakeFiles/clipboard.dir/flags.make
dependencies/glfw/tests/CMakeFiles/clipboard.dir/clipboard.c.obj: dependencies/glfw/tests/CMakeFiles/clipboard.dir/includes_C.rsp
dependencies/glfw/tests/CMakeFiles/clipboard.dir/clipboard.c.obj: C:/Users/axelo/Desktop/Tuto_OpenGL/OpenGL_project/dependencies/glfw/tests/clipboard.c
dependencies/glfw/tests/CMakeFiles/clipboard.dir/clipboard.c.obj: dependencies/glfw/tests/CMakeFiles/clipboard.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dependencies/glfw/tests/CMakeFiles/clipboard.dir/clipboard.c.obj"
	cd /d C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\dependencies\glfw\tests && C:\Users\axelo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8617.54\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/glfw/tests/CMakeFiles/clipboard.dir/clipboard.c.obj -MF CMakeFiles\clipboard.dir\clipboard.c.obj.d -o CMakeFiles\clipboard.dir\clipboard.c.obj -c C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\dependencies\glfw\tests\clipboard.c

dependencies/glfw/tests/CMakeFiles/clipboard.dir/clipboard.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clipboard.dir/clipboard.c.i"
	cd /d C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\dependencies\glfw\tests && C:\Users\axelo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8617.54\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\dependencies\glfw\tests\clipboard.c > CMakeFiles\clipboard.dir\clipboard.c.i

dependencies/glfw/tests/CMakeFiles/clipboard.dir/clipboard.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clipboard.dir/clipboard.c.s"
	cd /d C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\dependencies\glfw\tests && C:\Users\axelo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8617.54\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\dependencies\glfw\tests\clipboard.c -o CMakeFiles\clipboard.dir\clipboard.c.s

dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.obj: dependencies/glfw/tests/CMakeFiles/clipboard.dir/flags.make
dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.obj: dependencies/glfw/tests/CMakeFiles/clipboard.dir/includes_C.rsp
dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.obj: C:/Users/axelo/Desktop/Tuto_OpenGL/OpenGL_project/dependencies/glfw/deps/getopt.c
dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.obj: dependencies/glfw/tests/CMakeFiles/clipboard.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.obj"
	cd /d C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\dependencies\glfw\tests && C:\Users\axelo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8617.54\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.obj -MF CMakeFiles\clipboard.dir\__\deps\getopt.c.obj.d -o CMakeFiles\clipboard.dir\__\deps\getopt.c.obj -c C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\dependencies\glfw\deps\getopt.c

dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clipboard.dir/__/deps/getopt.c.i"
	cd /d C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\dependencies\glfw\tests && C:\Users\axelo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8617.54\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\dependencies\glfw\deps\getopt.c > CMakeFiles\clipboard.dir\__\deps\getopt.c.i

dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clipboard.dir/__/deps/getopt.c.s"
	cd /d C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\dependencies\glfw\tests && C:\Users\axelo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8617.54\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\dependencies\glfw\deps\getopt.c -o CMakeFiles\clipboard.dir\__\deps\getopt.c.s

dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/glad_gl.c.obj: dependencies/glfw/tests/CMakeFiles/clipboard.dir/flags.make
dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/glad_gl.c.obj: dependencies/glfw/tests/CMakeFiles/clipboard.dir/includes_C.rsp
dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/glad_gl.c.obj: C:/Users/axelo/Desktop/Tuto_OpenGL/OpenGL_project/dependencies/glfw/deps/glad_gl.c
dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/glad_gl.c.obj: dependencies/glfw/tests/CMakeFiles/clipboard.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/glad_gl.c.obj"
	cd /d C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\dependencies\glfw\tests && C:\Users\axelo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8617.54\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/glad_gl.c.obj -MF CMakeFiles\clipboard.dir\__\deps\glad_gl.c.obj.d -o CMakeFiles\clipboard.dir\__\deps\glad_gl.c.obj -c C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\dependencies\glfw\deps\glad_gl.c

dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clipboard.dir/__/deps/glad_gl.c.i"
	cd /d C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\dependencies\glfw\tests && C:\Users\axelo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8617.54\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\dependencies\glfw\deps\glad_gl.c > CMakeFiles\clipboard.dir\__\deps\glad_gl.c.i

dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clipboard.dir/__/deps/glad_gl.c.s"
	cd /d C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\dependencies\glfw\tests && C:\Users\axelo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8617.54\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\dependencies\glfw\deps\glad_gl.c -o CMakeFiles\clipboard.dir\__\deps\glad_gl.c.s

# Object files for target clipboard
clipboard_OBJECTS = \
"CMakeFiles/clipboard.dir/clipboard.c.obj" \
"CMakeFiles/clipboard.dir/__/deps/getopt.c.obj" \
"CMakeFiles/clipboard.dir/__/deps/glad_gl.c.obj"

# External object files for target clipboard
clipboard_EXTERNAL_OBJECTS =

dependencies/glfw/tests/clipboard.exe: dependencies/glfw/tests/CMakeFiles/clipboard.dir/clipboard.c.obj
dependencies/glfw/tests/clipboard.exe: dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/getopt.c.obj
dependencies/glfw/tests/clipboard.exe: dependencies/glfw/tests/CMakeFiles/clipboard.dir/__/deps/glad_gl.c.obj
dependencies/glfw/tests/clipboard.exe: dependencies/glfw/tests/CMakeFiles/clipboard.dir/build.make
dependencies/glfw/tests/clipboard.exe: dependencies/glfw/src/libglfw3.a
dependencies/glfw/tests/clipboard.exe: dependencies/glfw/tests/CMakeFiles/clipboard.dir/linklibs.rsp
dependencies/glfw/tests/clipboard.exe: dependencies/glfw/tests/CMakeFiles/clipboard.dir/objects1.rsp
dependencies/glfw/tests/clipboard.exe: dependencies/glfw/tests/CMakeFiles/clipboard.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable clipboard.exe"
	cd /d C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\dependencies\glfw\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\clipboard.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dependencies/glfw/tests/CMakeFiles/clipboard.dir/build: dependencies/glfw/tests/clipboard.exe
.PHONY : dependencies/glfw/tests/CMakeFiles/clipboard.dir/build

dependencies/glfw/tests/CMakeFiles/clipboard.dir/clean:
	cd /d C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\dependencies\glfw\tests && $(CMAKE_COMMAND) -P CMakeFiles\clipboard.dir\cmake_clean.cmake
.PHONY : dependencies/glfw/tests/CMakeFiles/clipboard.dir/clean

dependencies/glfw/tests/CMakeFiles/clipboard.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\dependencies\glfw\tests C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\dependencies\glfw\tests C:\Users\axelo\Desktop\Tuto_OpenGL\OpenGL_project\cmake-build-debug\dependencies\glfw\tests\CMakeFiles\clipboard.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : dependencies/glfw/tests/CMakeFiles/clipboard.dir/depend

