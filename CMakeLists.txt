cmake_minimum_required(VERSION 3.0)

project(MyProject)

# Add your source files
set(SOURCES
    src/intention_model_interface.cpp
)

# Add your header files
set(HEADERS
    ship_intention_inference/intention_model.h
)

# Set the executable name and link the source files
add_executable(intention_model_interface ${SOURCES} ${HEADERS})

# Set include directories
add_subdirectory(deps/pybind11)
target_link_libraries(intention_model_interface PRIVATE pybind11::module)
target_include_directories(intention_model_interface PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/deps/pybind11/include ${CMAKE_CURRENT_SOURCE_DIR}/ship_intention_inference)
target_include_directories(intention_model_interface PRIVATE include)
