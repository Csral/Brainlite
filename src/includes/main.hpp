/*

  Copyright 2025 Chaturya Reddy (@Csral) <chaturyasral@gmail.com>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

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