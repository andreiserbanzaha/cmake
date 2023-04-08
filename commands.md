# CMake Commands


- **cmake_minimum_required(VERSION \<version>)**
    - minimum cmake version that has the features needed to generate build files


- **project(\<name>)**
    - project name


- **add_executable(\<exec_name> \<source_files>)**
    - when we want an executable file at the end of the process
    - executable name first argument
    - defines a target


- **add_library(\<library_name> \<source_files>)**
    - creates a library
    - can be used in other projects
    - defines a target


- **target_link_libraries(\<executable> PRIVATE \<lib1> \<lib2> ...)**
    - links libraries to executable
    - property **INTERFACE_LINK_LIBRARIES** (PRIVATE, PUBLIC, INTERFACE)


- target properties can be modified using:
    - **set_target_properties()**
    - **set_property()**
    - **get_property()**
    - **get_target_property()**


- **add_subdirectory(\<dir_name>)**
    - go in that sub-directory and find a CMakeLists.txt file and run those


- **target_include_directories(\<target> \<scope> \<dir1> \<dir2> ...)**
    - adds directories to target (e.g. to not use relative paths for .h files)
    - *scope* - ???
    - property **INTERFACE_INCLUDE_DIRECTORIES** (PRIVATE, PUBLIC, INTERFACE)


- commands that require **scope**
    - **target_compile_definitions()** -> property **INTERFACE_COMPILE_DEFINITIONS**
    - **target_sources()** -> property **INTERFACE_SOURCES**
    - **target_compile_features()** -> property **INTERFACE_COMPILE_FEATURES**
    - **target_compile_options()** -> property **INTERFACE_COMPILE_OPTIONS**
    - **target_link_directories()** -> property **INTERFACE_LINK_DIRECTORIES**
    - **target_link_libraries()** -> property **INTERFACE_LINK_LIBRARIES**
    - **target_link_options()** -> property **INTERFACE_LINK_OPTIONS**
    - **target_precompile_headers()** -> property **INTERFACE_PRECOMPILE_HEADERS**

    - e.g. target_include_directories(myLib PRIVATE inc)
        - target_include_directories(target | scope | arguments)


- **message(\<mode_of_display> "the message")**
    - modes of display: \<none>, STATUS, DEBUG, WARNING, FATAL ERROR


- **set(\<variable_name> \<variable_value>)**
    - creates and sets a value to a variable
    - all variables are of string type
    - they have to be *dereferenced* using ${\<variable_name>}


- **list(\<subcommand> \<name_of_list> ... \<arguments_of_subcommand> ... \<return_val>)**
    - subcommands: APPEND, INSERT, FILTER, GET, JOIN etc


- **string()**


- **install(FILES \<file_name> DESTINATION \<dir>)**
  - items to copy
  - destination for pasting the items (default "/usr/local")
    - **CMAKE_INSTALL_PREFIX**


- **install(TARGET \<target_name> DESTINATION \<dir>)**
  - items to copy
  - destination for pasting the items (default "/usr/local")
    - **CMAKE_INSTALL_PREFIX**


- **find_package(\<package_name>)**
  - searches for **\<package_name>-config.cmake** file in "/usr/local/lib/\<package_name>" folder
  - modes of operation:
    - **module** mode -> will look for **Find\<package_name>.cmake**
    - **config** mode -> will look for **\<package_name>-config.cmake**
  - mode can be specified: find_package (\<package_name> MODULE/CONFIG)
    - if not is specified, it will be searched in the MODULE mode and then in the CONFIG mode
  - differences between the 2 modes:
    - in the MODULE mode, the file is searched in the directories specified in **CMAKE_MODULE_PATH** (recommended for packages that are inside our project since it is set by us)
    - the CONFIG mode is often used when using installed packages


- **pkg_check_modules(\<prefix> \<name_of_.pc_file>)**
    - the *prefix* can be used when including directories or linking the library
        - e.g \<prefix>\_INCLUDE_DIRS and \<prefix>\_LIBRARIES
    - if the pkgconfig file is not where we expect (/usr/.../pkgconfig/), we need to specify where to search for it by adding it to:
        - cmake variable: CMAKE_PREFIX_PATH
            - set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}"/home/andrei/Desktop")
        - env variable: PKG_CONFIG_PATH
            - set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/home/andrei/Desktop")


- **pkg_search_module()**


- **find_library(\<var> \<lib-name> \<dir1> \<dir2> ...)**
  - result stored in *var*
  - *lib-name* -> library name
  - *dir1/dir2* ... -> paths where to search for the library

- **find_path()**
  - directory of the library


- **find_package_handle_standard_args()**
