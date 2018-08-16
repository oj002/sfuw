# Single File Utils and Wrappers
A collection of some single Util and wrapper libraries.

# Overview
## General
|   | File                                          | Language | description
|---| --------------------------------------------- |:--------:| -----------
|   | [Timer.hpp](sfuw/general/Timer.hpp)           | C++      | \<chrono> wrapper
|   | [Rng_std.hpp](sfuw/general/Rng_std.hpp)       | C++      | \<random> wrapper


# Guidelines
Every .h file is written c and every .hpp file is written in c++.\
The only dependencies are the appropriate standard libraries.\
In c all global visible names are sfuw_ prefixed and in c++ they are written in the sfuw namespace.\
The code is cross platform.