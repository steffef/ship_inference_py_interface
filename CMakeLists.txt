cmake_minimum_required(VERSION 3.12)
project(IntentionModelInterface LANGUAGES CXX)

# Set the C++ standard to use
set(CMAKE_CXX_STANDARD 20)

# Add your source files
set(SOURCES
    src/intention_model_interface.cpp
    src/intention_model_parameters_interface.cpp
    src/intention_model_geometry_interface.cpp
)

set(HEADERS
    ship_intention_inference/intention_model.h
)

include_directories(ship_intention_inference ship_intention_inference/Eigen ship_intention_inference/smile)

# Find packages
find_package(Python 3.11 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)
find_package(Eigen3 REQUIRED)

# Add the intention_model module
pybind11_add_module(intention_model ${SOURCES} ${HEADERS})
target_link_libraries(intention_model PRIVATE pybind11::module Eigen3::Eigen ${CMAKE_SOURCE_DIR}/ship_intention_inference/smile/libsmile.a)
target_include_directories(intention_model PRIVATE ${PYBIND11_INCLUDE_DIRS})

# Add the parameters module
pybind11_add_module(parameters src/intention_model_parameters_interface.cpp)
target_link_libraries(parameters PRIVATE pybind11::module Eigen3::Eigen ${CMAKE_SOURCE_DIR}/ship_intention_inference/smile/libsmile.a)

target_include_directories(parameters PRIVATE ${PYBIND11_INCLUDE_DIRS})

# Add the geometry module
pybind11_add_module(geometry src/intention_model_geometry_interface.cpp)
target_link_libraries(geometry PRIVATE pybind11::module Eigen3::Eigen ${CMAKE_SOURCE_DIR}/ship_intention_inference/smile/libsmile.a)
target_include_directories(geometry PRIVATE ${PYBIND11_INCLUDE_DIRS})

# Set the appropriate extension for the module files based on the platform
if(WIN32)
    set_target_properties(intention_model PROPERTIES SUFFIX ".pyd")
    set_target_properties(parameters PROPERTIES SUFFIX ".pyd")
    set_target_properties(geometry PROPERTIES SUFFIX ".pyd")
else()
    set_target_properties(intention_model PROPERTIES PREFIX "")
    set_target_properties(parameters PROPERTIES PREFIX "")
    set_target_properties(geometry PROPERTIES PREFIX "")
endif()
