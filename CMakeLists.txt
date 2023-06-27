cmake_minimum_required(VERSION 3.12)
project(IntentionModelInterface LANGUAGES CXX)

# Add your source files
set(SOURCES
    src/intention_model_interface.cpp
)

# Add your header files
set(HEADERS
    ship_intention_inference/intention_model.h
)

# Add the directory containing header files
include_directories(ship_intention_inference)

find_package(pybind11 CONFIG REQUIRED)
pybind11_add_module(intention_model_interface ${SOURCES} ${HEADERS})
