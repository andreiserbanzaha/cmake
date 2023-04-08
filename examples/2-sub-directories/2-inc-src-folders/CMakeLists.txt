cmake_minimum_required(VERSION 3.0.0)

project(CalculatorProject)

add_subdirectory(my_math_dir)
add_subdirectory(my_print_dir)

add_executable(calculator
	main.cpp
)

target_link_libraries(calculator
	PRIVATE my_math
	PRIVATE my_print
)
