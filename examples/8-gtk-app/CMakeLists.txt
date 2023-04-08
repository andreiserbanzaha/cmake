cmake_minimum_required(VERSION 3.0.0)

project(GTK_PC)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_executable(${PROJECT_NAME}_APP main.cpp)

target_include_directories(${PROJECT_NAME}_APP PRIVATE ${GTK3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_APP PRIVATE ${GTK3_LIBRARIES})
