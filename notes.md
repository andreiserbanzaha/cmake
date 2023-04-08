# CMake

- build system generator (meta build system)
- can help with not needing to  recompile the whole project (if written correctly)

### Build systems

- Make
- Ninja
- Ant
- Gradle


### Need of meta build systems

- **build file** (e.g. make) - the build system uses these files to compile and link
- source files(*.h, *.cpp, *.hpp) -> build file(makefile) -> build system(Make)


- **make** - uses build system files to generate executable
- **cmake** - used to generate build system files

- problem is - the building of C++ projects is not standard across platforms
  - if we have the source codes and makefiles of a c++ project from a linux machine, we cannot directly build that code in Windows
  - if we have a visual studio solution from a Windows machine, we cannot directly build that project on Linux
- CMake solves this problem by creating a platform based build system files


### CMake installation

- install from repository
    - sudo apt install cmake


- prebuilt binaries
    - download binaries from cmake.org (e.g. "name".sh)
    - chmod +x "name.sh"
    - run "name.sh"
    - add folder to PATH (in .bashrc)


- source code
    - download source code
    - build using steps on site


### Requirements for using CMake

- a CMakeLists.txt file
- any directory to store the generated build files


### Targets

- libraries
- executables
- **add_executable()** and **add_library()** define a target
- every target in cmake have *properties* and *dependencies* associated with it
    - common properties:
        - INTERFACE_LINK_DIRECTORIES
        - INCLUDE_DIRECTORIES
        - VERSION
        - SOURCES
- cmake properties: https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html
    - these properties are automatically set when running **target_link_libraries()** or **target_include_directories()**


### Target dependencies

- targets can have dependencies on one another
    - e.g. if target B is a dependency of a target A, then target A can only be build after target A is built successfully


### Propagating Target Properties

- a target is capable of propagating its properties in the dependency chain
    - e.g. target_link_libraries(\<exec> PUBLIC \<lib>)
        - property **INTERFACE_LINK_LIBRARIES** is set to **PUBLIC**


### FAQ on Targets

- can we have more than 1 executable in one CMakeLists.txt file?
    - YES. (must have different name)


- can we have 2 targets with the same name?
    - NO, cmake will give an error


- do we have the target files saved in our computer?
    - YES, but the name might not be the same as target (adds prefix/suffix)
    - examples:
        - on windows, an executable target is called "a" -> "a.exe"
        - on linux, a library target "abc" -> **lib**abc**.so**


### Build folder name

- it can be anything, but generally it's just "build"
- sometimes we can also have "debug" and "release"


### Sub-directories

- sub-directories can be added to CMakeLists.txt using **add_subdirectory()**
- they need to contain another CMakeLists.txt file
- useful for organizing


### Header files

- a good practice is to keep all the files of a particular library in one place
    - CMakeLists.txt
    - \*.h in "inc" folder
    - \*.src in "src" folder


- in \*.cpp files we can include \*.h files relative to that cpp file
- however, CMake permits to include directories, and permits us to not need to give relative paths: **target_include_directories()**


- obs:
    - in our example, "main.cpp" does not need to include headers with relative paths, because the dependencies target's properties have been set to PUBLIC


### PUBLIC vs PRIVATE vs INTERFACE (target_include_directories)

- (1) does that target need the directory?
- (2) do the targets that depend on this target need this include directory?

- PUBLIC:    (1)yes (2)yes
- PRIVATE:   (1)yes (2)no
- INTERFACE: (1)no  (2)yes


### CMake scripting

- use **-P** to run CMake as script
- not all commands are supported as script (e.g. **project()** is not)
- a list in CMake is a list of items separated semicolon
- note: a string is a list with a single item


### Quoted and unquoted arguments

| command              | value of VAR | message(${VAR}) | message("${VAR}") |
|----------------------|--------------|-----------------|-------------------|
| set(VAR a b c)       | a;b;c        | abc             | a;b;c             |
| set(VAR a;b;c)       | a;b;c        | abc             | a;b;c             |
| set(VAR "a" "b" "c") | a;b;c        | abc             | a;b;c             |
| set(VAR "a b c")     | a b c        | a b c           | a b c             |
| set(VAR "a;b;c")     | a;b;c        | abc             | a;b;c             |


### Generator expressions

- variable:              ${VAR}
- generator expressions: $<TARGET_FILE:library>


### Constants

- **TRUE**: 1, ON, YES, TRUE, Y, non-zero number
- **FALSE**: 0, OFF, NO, FALSE, N, IGNORE, NOTFOUND, empty string, string ending with "-NOTFOUND"


- if something else is provided, it will be treated as a variable or string and evaluate its value


### Evaluation helpers:

- Unary tests
  - **DEFINED** - checks if a variable is set or not
  - **COMMAND** - checks if a command exists or not
  - **EXISTS**  - checks if a file or directory exists or not


- Binary tests
  - **EQUAL**, **LESS**, **GREATER**, **STRLESS**, **STRGREATER**, **STREQUAL**, **MATCHES**


- Boolean operators
  - **NOT**, **OR**, **AND**

```
if (DEFINED Name) # same with COMMAND and EXISTS
  message("var exists")
else
  message("var does not exist")
endif()
```


### Control flow

- if-else
```
if (<condition>)
    <commands>
elseif(<condition2>)
    <commands>
else
    <commands>
endif()
```

- while
```
while (<condition)
    <commands>
endwhile()
```

- foreach
```
foreach (<loop_variable> <items>)
    <commands>
endforeach()
```

- foreach range
```
foreach (x RANGE <start> <stop> <step_size>)
    <commands>
endforeach()
```


### Functions

```
function (<function_name> <arg1> <arg2>  ...)
    <commands>
endfunction()
```

- functions can receive unnamed arguments (**OPTIONAL**)
- functions have their own scopes
  - variables from parent scope are copied in function scope
   - if these are modified, it will only have effect inside the function scope, unless we use **PARENT_SCOPE**


- special function variables:
  - **ARGC**  - total number of arguments (named + optional)
  - **ARGV**  - list of all arguments (named + optional)
  - **ARGN**  - list of **optional** arguments
  - **ARGV0** - first argument
  - **ARGV1** - second argument
  - **ARGV2** - third argument


### Macros

- macros DON'T introduce a new scope
- are case INSENSITIVE

```
macro (<function_name> <function_args>)
    <commands>
endmacro()
```


### Global variables

- persistent cache variables
- environment variables


- when dereferencing a variable, **Local** scope is searched first, **Global** second
  - if same variable is define twice, and once in CACHE, the Local one will be retrieved


#### 1. Persistent cache variables

- cached variables are found in CMakeCache.txt
- some are set automatically by the CMake tool depending on the development environment
- others are set by commands in CMakeLists.txt
- can be set manually set by using the **set()** command and **CACHE** keyword
- cache variable dereferencing: **$CACHE{\<variable_name>}**

```
// set A to "123"
// CACHE - set in CMakeCache.txt
// STRING - means it's the variable type
// last string - summary of the variable
set (A "123" CACHE STRING "This sets variable A in persistent cache")
```

##### Modifying cache variables:

- when running cmake command first time, CMakeCache.txt file is created
- if we try to modify at this point, the commands will be rejected


- solutions:
  - edit CMakeCache.txt file manually
  - use **FORCE** keyword
  - use **-D** flag (recommended) (note: **FORCE** > **-D**)

  ```
  // use Ninja generator
  cmake -DCMAKE_GENERATOR=Ninja ..
  ```

- most used cache variables:
  - CMAKE_VERSION
  - CMAKE_MAJOR_VERSION
  - CMAKE_MINOR_VERSION
  - CMAKE_PATCH_VERSION
  - CMAKE_PROJECT_NAME - top level **project()** name and call
  - PROJECT_NAME - last **project()** command call
  - CMAKE_GENERATOR

```
// build project using Ninja
cmake -GNinja ..
```

#### 2. Environment variables

- have global scope
- are not stored in CMakeCache.txt file
- can be set manually using **set()** and **ENV** keyword
- env variable dereferencing: **$ENV{\<variable_name>}**

```
set (ENV <variable_name> <variable_value>)
```


### Installing and exporting packages

- a library is a part of a package
- a package is a distribution unit which contains source files, header files and other supporting files


- using a package (e.g. developed by the community):
  - **download**
  - **compile**
  - **install**
    - compiled libraries, executables, header files, supporting files are copied from the package directory to one of the predefined directories (e.g. on Linux: /usr/local)
    - once the package is installed, these libraries can be used in other projects
    - to use those, we need to write some commands in the CMakeLists.txt file of our project, which will find the installed package
    - if you create the package that can be used by the community, you need to write code so that other can easily **find** and **install** that package


- **install** - copying files from one folder to another
  - recommendations to install:
    - headers: "/usr/local/include/\<package_name>"
    - targets: "/usr/local/lib/\<package_name>"


- in order to run the install commands, we need to run **sudo make install** (or equivalent depending on build system)


### Exporting a package: install(EXPORT ...)

- in order to be found by **find_package()**, a .cmake file needs to be created and installed (e.g on Linux in "/usr/local/lib/\<package-name>-config.cmake")
- steps:
  1. add targets to export group -> **EXPORT** keyword
    - creates a \<export_name>.cmake file which needs to be installed
  2. install the export group
    - the \<export_name> file need to be renamed \<target_name>-config.cmake
  3. modify the target_include_directories() command
    - when using this command, the INTERFACE_INCLUDE_DIRECTORIES is automatically set
    - if using the **install(EXPORT..)** command, this property will also be exported and every user who wants to use this library, must use the same include directory structure (hardcoded from the machine that it's built on. e.g. "/home/andreiz/my_lib/includes")
    - cmake solution: **generator expressions**
      - not resolved in the configuration stage, but in the building stage of cmake (build system generation) -> any project consuming this library can use the include directories of their choice without any config
      - form $\<...>
      - enables conditional linking, conditional include directories, etc
      - conditions based on: build configuration, target properties, platform
      - **INSTALL_INTERFACE** is used when someone else is using the package (from where it includes the headers)


- From stack overflow:
  - Generator-like expressions $\<BUILD_INTERFACE> and $\<INSTALL_INTERFACE> are used by CMake for distinguishing things, different for the build tree and for the install tree.
  - When building the project itself, $\<BUILD_INTERFACE> is used but $\<INSTALL_INTERFACE> is not.
  - When creating an export file with the install(EXPORT) command, things listed in $\<INSTALL_INTERFACE> will be included into it, but things in $\<BUILD_INTERFACE> won't.
  - But the creation of an export file with the export command uses $\<BUILD_INTERFACE>, but does not use $\<INSTALL_INTERFACE>.
  - Other for differentiate build and install trees expressions $\<BUILD_INTERFACE> and $\<INSTALL_INTERFACE> are not used.
  - E.g. $\<INSTALL_INTERFACE> does NOT affect the install(TARGETS .. PUBLIC_HEADERS) command.


### Using CMake variables in CPP files

- say you want the value of the variable CMAKE_SOURCE_DIR inside your main.cpp. You just need to add one command in CMakeLists.txt:
```
add_definitions(-Dsomevariablename="${CMAKE_SOURCE_DIR}")
```

- now, you can go inside main.cpp and add directly use the somevariablename variable like this:
```
std::cout << somevariablename << "\n";
```

- or like this:
```
#ifdef somevariablename
    do_something()
#endif
```
- note that I've NOT used -D inside main.cpp because it's a part of CMake's syntax.

### Running CMakeLists.txt in Script mode (Linux Specific)

- normal, in terminal:
```
cmake -P CMakeLists.txt
```

- there is another fancy way of doing this in the Linux terminal, which is similar to executing a bash or a python script.
- run the command *which cmake* in your terminal. It will give you the location of the cmake executable (e.g. ""/usr/bin/cmake")
- open the CMakeLists.txt file and paste the following code in it's first line
```
#!/usr/bin/cmake -P
```

- give the execution permission to the CMakeLists.txt file by running the command: *chmod +x CMakeLists.txt*
- now, you can either use the command  **./CMakeLists.txt** or **cmake -P CMakeLists.txt** to run the CMakeLists.txt file in the script mode

### Debug/Release Mode

- there are these 2 case scenarios:

  1. you are making a project, which does not dependent on any external library. In this case, you can directly set a normal variable CMAKE_BUILD_TYPE to Debug or Release, while generating build system files. To do that, simply execute
  ```
  cmake -DCMAKE_BUILD_TYPE=Debug ..
  ```
  or
  ```
  cmake -DCMAKE_BUILD_TYPE=Release ..
  ```
    - you will see that the release build is faster and also has less file size compared to the debug build. When you set the CMAKE_BUILD_TYPE variable, the compiler flags are automatically modified to offer you the desired optimization levels


2. you want to use an external library in the Debug/Release mode

  - (2a) firstly, you will download the external library's source codes and compile it in both debug and release modes
    - you MUST have separate folders containing the debug binaries and release binaries
      - e.g. external debug library is in /some/path/foo/debug/libfoo.so and the release library is in /some/path/foo/release/libfoo.so
  - (2b) the executable in your project is called my_app then you can use the following command in my_app project's CMakeLists.txt file, to link the external foo library
    ```
    target_link_libraries( my_app
        debug /some/path/foo/debug/libfoo.so
        optimized /some/path/foo/release/libfoo.so)
    ```
    - Now, when you will run
    ```
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    ```
    - while generating the build files for my_app project , /some/path/foo/debug/libfoo.so will be linked against my_app

    - similarly, when you will run
    ```
    cmake -DCMAKE_BUILD_TYPE=Release ..
    ```
    - /some/path/foo/release/libfoo.so will be linked against my_app
    - Note here that, running the cmake.. command i.e. without any build type will throw an error

### Using external libraries

- e.g. library name XYZ
- library file name libXYZ.a or libXYZ.so
- steps:
    - download source code
    - cmake -> make -> sudo make install
    - XYZ-config.cmake should be in the installed location
    - use find_package(XYZ)
- what if the "-config.cmake" file is not in the expected location?
    - contact the developers and ask to provide it
    - write your own Find*cmake file
    - write \*config module


- \*config module Standard Directories: "/usr/local"
    - should not be inside your project (not good practice)
- Find* module: inside your project


- if the library used CMake based build generation process
    - \*config.cmake present
    - no \*config.cmake present
- if the library doesn't use CMake build generation process
    - CMake or library provides Find* or \*config modules
    - uses **pkg-config** file
    - no pkg-config file


- variable naming: (These can be found in the \*-config.cmake file of the lib)
    - libraries: XYZ_LIBRARIES, XYZ_LIBS ...
    - include directories: XYZ_INCLUDES, XYZ_INCLUDE_DIRS ...

### Link a library using pkg-config file

- e.g. if you want to install a package "libxyz"
    - compiled library, headers, symbolic links, pkg-config(.pc) files
    - if not found, try installing "libxyz-dev" or "libxyz-devel"


- e.g. using gtk3 package
    - sudo apt install libgtk-3-dev
    - find /usr -name \*gtk*pc -> check the cool stuff inside
    - in project -> find_package(PkgConfig REQUIRED) -> pkg_check_modules(\<alias> REQUIRED \<package_name>)
    - target_include_directories(\<target> PRIVATE \<alias>\_INCLUDE_DIRS)
    - target_link_libraries(\<target> PRIVATE \<alias>\_LIBRARIES)


### Writing a Find*.cmake module

-  


### Other notes:

- if we modify the CMakeLists.txt file and forget to run **cmake** and only run **make**, the make tool automatically runs cmake for us (except the first time it is run)
￼
