cmake_minimum_required(VERSION 3.12)
project(IntentionModelInterface LANGUAGES CXX)

# Set the C++ standard to use
set(CMAKE_CXX_STANDARD 20)

# Add your source files
set(SOURCES
    src/intention_model_interface.cpp
)

set(HEADERS
    ship_intention_inference/intention_model.h
)

include_directories(ship_intention_inference ship_intention_inference/Eigen ship_intention_inference/smile)

# Find packages
find_package(Python 3.11 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)
find_package(Eigen3 REQUIRED)

# Add the module
pybind11_add_module(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE pybind11::module Eigen3::Eigen ${CMAKE_SOURCE_DIR}/ship_intention_inference/smile/libsmile.a)
target_include_directories(${PROJECT_NAME} PRIVATE ${PYBIND11_INCLUDE_DIRS})

# Set the appropriate extension for the module file based on the platform
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".pyd")
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
endif()
