# opencl-bindings-and-helpers
Very simple library containing some bindings, defines and helper functions for writing programs that utilize OpenCL.

# How To Include In Project
Import the repo as a submodule into your repo. After that, you must add this repo's include folder to your include paths in whatever compiler you're using.

# Platforms
You can use whatever compiler you want as long as it compiles the code successfully (I'm not exactly sure what the minimum C++ version needs to be for the code to compile,
probably C++17, maybe C++11).

This library only works on Windows at the moment, but maybe that'll change in the future because it shouldn't be too hard to get it to work on another platform.
