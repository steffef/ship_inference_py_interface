cmake_minimum_required(VERSION 3.12)
project(IntentionModelInterface LANGUAGES CXX)

# Set the C++ standard to use
set(CMAKE_CXX_STANDARD 20)

# Add your source files
set(SOURCES
    src/intention_model_interface.cpp
)

# Add your header files
set(HEADERS
    ship_intention_inference/intention_model.h
)

# Add the directory containing header files
include_directories(ship_intention_inference ship_intention_inference/Eigen)

# Find packages
find_package(Python 3.11 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)
find_package(Eigen3 REQUIRED)

# Add the module
pybind11_add_module(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE pybind11::module Eigen3::Eigen)
target_include_directories(${PROJECT_NAME} PRIVATE ${PYBIND11_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE Eigen3::Eigen)

# Set the appropriate extension for the module file based on the platform
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".pyd")
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
endif()
