cmake_minimum_required(VERSION 3.0.0)

project(CalculatorProject)

add_library(my_math
	addition.cpp
	division.cpp
)

add_library(my_print
	print_result.cpp
)

add_executable(calculator
	main.cpp
)

target_link_libraries(calculator PRIVATE
	my_math
	my_print
)
