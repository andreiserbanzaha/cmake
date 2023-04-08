# Listfiles and Modules

So far, we have been writing our CMake codes in CMakelists.txt files. These files are collectively called the ListFiles.

Apart from the listfiles, we also have the concept of modules, where the CMake codes are written. These modules have .cmake extension.



CMake provides some standard modules containing the CMake codes so that we can directly use those in any project. You can find those in the /usr/local/share/CMake-3.16/Modules directory.

These modules can be used with the include() command. If you want to use this module, you need to write these 2 lines of code and then the variable VAR will contain the number of processors.

```
include(ProcessorCount)
ProcessorCount(VAR)
message("Number of processors are: ${VAR}")
```


You can use this VAR variable in your project if you want to run parallel jobs of any process.

Apart from the standard modules, you can also make your own module.Let us see an example.



We can create this directory structure with 2 files CMakeLists.txt and my_module.cmake

```
+module7
   -CMakeLists.txt
   -my_module.cmake
   +build
```

The CMakeLists.txt file will contain the following lines:

```
cmake_minimum_required(VERSION 3.0.0)
project(Calculator_Project VERSION 1.0.0)
include(my_module)
```

and the my_module.cmake file will contain just the following line:

```
message("Hello from the my_module.cmake file!")
```

At this time running the CMake command will give an error, because we also need to specify the path which contains the my_module.cmake file. To specify that path, we have a variable called CMAKE_MODULE_PATH which contains the lists of paths to search the module. This variable is a cache variable and you will learn about the cache variable in the next module. For now, we will modify this list inside the CMakeLists.txt file to suit our needs. The final CMakeLists.txt file will contain the following lines:

```
cmake_minimum_required(VERSION 3.0.0)
project(Calculator_Project VERSION 1.0.0)
list(APPEND  CMAKE_MODULE_PATH  <path-to-module5-directory>)
include(my_module)
```

Now you can run the cmake .. command from the build directory and the output will be:

```
Hello from the my_module.cmake file!
```

Now you might think that this command is similar to add_subdirectory() command, but it's not! When we use the include() command, we do not introduce a new scope. This means that if we set or modify a variable inside the my_module.cmake file, that modification is going to reflect inside the CMakeLists.txt file.



The modules are often used if we want to have reusable code in our project. Also if your CMakeLists.txt file is too long, some part of it can be written inside another .cmake file; to improve the readability of the code.



This finishes the lecture, Thank you!
