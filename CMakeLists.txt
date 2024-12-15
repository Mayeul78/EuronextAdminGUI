cmake_minimum_required(VERSION 3.10)

# Project name
project(APIManagerTest)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Trouver wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})


# Include directories for libcurl and jsoncpp
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(/opt/homebrew/Cellar/jsoncpp/1.9.6/include)

# Find the jsoncpp library dynamically
find_library(JSONCPP_LIB jsoncpp REQUIRED PATHS /opt/homebrew/Cellar/jsoncpp/1.9.6/lib)

# Add the library (APIManager)
add_library(APIManager APIManager.cpp)

# Link the library with curl and jsoncpp
target_link_libraries(APIManager curl ${JSONCPP_LIB})

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# Add the main executable

add_executable(GUI main.cpp LoginFrame.cpp InstrumentListFrame.cpp)
target_link_libraries(GUI APIManager ${wxWidgets_LIBRARIES})

# Add the test executable
add_executable(TestExecutable test.cpp)
target_link_libraries(TestExecutable APIManager)
