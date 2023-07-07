# ship_inference_py_interface
Python interface for the ship intention inference project https://github.com/NTNU-Autoship-Internal/ship_intention_inference/tree/cleanup_and_fixes

**This is a work in progress, meaning that the interface is not complete.** 
## Setup

Firstly, make sure you have pybind11 installed. It needs to be installed both for C++ and python:

For the C++ install, clone pybind11 from https://github.com/pybind/pybind11 and run the following commands:
```bash
cd pybind11
cmake -S . -B build
cmake --build build
cmake --install build
```
(Source: https://pybind11.readthedocs.io/en/stable/compiling.html)

For python installation, simply run

```bash
pip install pybind11
```

After pybind11 has been successfully installed, you can clone this repo with

```bash
git clone --recurse-submodules <"git clone url"> <"clone folder">
```
where you replace `<"git clone url">` with the clone url, and `<"clone folder">` with the folder you want this repo to be cloned in. After successful clone, run

```bash
cd <"clone folder">
cmake -S . -B build
cmake --build build
```
Now a couple of .so files should have appeared in the build directory. These effectively works as the python modules.

## Usage
To use the interface in python, simply add the following code on top of your .py file:
```python
import sys
sys.path.append("build/")
import intention_model
import parameters
import geometry
```
The `"build/"` string should be replaced with the path to the build folder from where you plan to run the python script. A few examples of the usages of the interface can be found in the `tests/` folder.