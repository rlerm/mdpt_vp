cmake_minimum_required(VERSION 3.0)

project(mdpt_vp)

# Add our custom library finder directory.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Find the QtWidgets library.
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

# Find the vlc-qt library we need.
find_package(LIBVLCQT REQUIRED)

# For YouCompleteMe support.
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

include(InstallRequiredSystemLibraries)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Enable C++11 goodness.
set(CMAKE_CXX_FLAGS "-std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/src
)

# Define the main executable.
add_executable(mdpt_vp
	WIN32
    app/main.cpp
    resources/resources.qrc)
target_link_libraries(mdpt_vp
    libmdptvp
    Qt5::Core
    ${LIBVLCQT_LIBRARY}
    ${LIBVLCQT_WIDGETS_LIBRARY})
