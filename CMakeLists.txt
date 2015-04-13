cmake_minimum_required(VERSION 2.6)
project(mdpt_vp)

# Add our custom library finder directory.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Find the QtWidgets library.
find_package(Qt5Widgets REQUIRED)

find_package(LIBVLCQT REQUIRED)

# For YouCompleteMe support.
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Enable C++11 goodness.
set(CMAKE_CXX_FLAGS "-std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)

add_executable(mdpt_vp app/main.cpp)
target_link_libraries(mdpt_vp libmdptvp)
add_dependencies(mdpt_vp libmdptvp)
