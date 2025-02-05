#include <iostream>
#include <stdio.h>
#include <map>
#include <fstream>
#include <stdlib.h>

#include "brainuf.hpp"
#include "interpreter.hpp"

#ifndef _WIN32

#include <filesystem>
#include <getopt.h>

#else

// todo Windows system.

#endif

void help();