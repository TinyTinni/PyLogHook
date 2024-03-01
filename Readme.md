# LogHook for C++ Embedded Python

[![CMake](https://github.com/TinyTinni/PyLogHook/actions/workflows/build.yml/badge.svg)](https://github.com/TinyTinni/PyLogHook/actions/workflows/build.yml)  
Redirects text send to sys.stdout/stderr from Python to a user defined C/C++ function.

When you write your own interpreter for embedded python, you are maybe interested in
the output given by the Python interpreter.
This header-only project provvides the functionality to pass
the output to any given function.

## Features
- redirect stdout/stderr to a plain function, lambda or Functor
- supports GUI programs without default console
- doesn't add any function to pythons global namespace
- doesn't add any additional python module

## Requirements
- [pybind11](https://github.com/pybind/pybind11)
- OR [Boost.Python](http://www.boost.org/) 

If you use Boost, define TYTI_PYLOGHOOK_USE_BOOST before include PyLogHook.h.

## Install

It is header only. Just add [PyLogHook.h](PyLogHook.h) to your project which should already link against boost.python or pybind11.

## How-To
Call one of the functions in namespace ```tyti::pylog```.
```cpp
// in case of using Boost.Python
#define TYTI_PYLOGHOOK_USE_BOOST 
//------------------------------

#include <PyLogHook.h>
void my_stdout(const char* w)
{
    std::cout << w;
}

void my_stderr(const char* w)
{
    std::cerr << w;
}

...

//somewhere e.g. in your main function, after Py_Initialize()
tyti::pylog::redirect_stdout(my_stdout);
tyti::pylog::redirect_stderr(my_stderr);
```

## Preconditions
Before calling one of the functions, make sure
- python is initalized (```Py_Initialize()```)
- you hold the GIL, if multithreading is activated

## Exceptions
If anything went wrong, a Python exception was raised.
You can check, if a there is a pending exception via ```PyErr_Occurred()``` (See [tests](./tests/test.h)).

## License
[MIT License](./LICENSE) © Matthias Möller. Made with ♥ in Germany.
