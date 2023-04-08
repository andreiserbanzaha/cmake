cmake_minimum_required(VERSION 3.0.0)

project(my_math_test VERSION 1.0.0)

find_package(my_math)

if(my_math_FOUND)
	message("my_math library found!")
	add_executable(calculator main.cpp)
	target_link_libraries(calculator my_math)
else()
	message(FATAL_ERROR "my_math library not found")
endif()

message("i forgot to run the cmake command")
