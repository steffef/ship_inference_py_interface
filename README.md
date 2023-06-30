# ship_inference_py_interface
Python interface for the ship intention inference project https://github.com/sverrevr/ship_intention_inference/tree/51ac7fab545fd237cc9d3346c0f1b507a8dace0b

**This is a work in progress, meaning that the interface is not complete.** 
## Setup

Firstly, make sure you have pybind11 installed. Clone pybind11 from https://github.com/pybind/pybind11 and run the following commands:
```bash
cd pybind11
cmake -S . -B build
cmake --build build
cmake --install build
```
(Source: https://pybind11.readthedocs.io/en/stable/compiling.html)

Then, from the source directory you cloned this repo in, run:
```bash
mkdir build 
cmake -S . -B build
cmake --build build
```
Now a .so file starting with the name `IntentionModelInterface` should have appeared in the build directory. This effectively works as the python module.

## Usage
To use the interface in python, simply add the following code on top of your .py file:
```python
import sys
sys.path.append("build/")
import IntentionModelInterface
```
The `"build/"` string should be replaced with the path to the `IntentionModelInterface` from where you plan to run the python script. A few examples of the usages of the interface can be found in the `tests/` folder.