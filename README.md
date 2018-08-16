# Single File Utils and Wrappers
A collection of single file Util and wrapper libraries.

# Overview
You can use the [sfuw_wizard](sfuw/sfuw_wizard.py) to extract multiple libraries into a single file.
## General
|   | File                                          | Language | description
|---| --------------------------------------------- |:--------:| -----------
|   | [Timer.hpp](sfuw/general/Timer.hpp)           | C++11    | \<chrono> wrapper
|   | [Rng_std.hpp](sfuw/general/Rng_std.hpp)       | C++14    | \<random> wrapper


# Guidelines
Every .h file is written c and every .hpp file is written in c++.\
The only dependencies are the appropriate standard libraries.\
In c all global visible names are sfuw_ prefixed and in c++ they are written in the sfuw namespace.\
The code is cross platform and  when possible doesn't throw exceptions.
