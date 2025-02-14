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

#include "includes/main.hpp"

int main(int argc, char* argv[]) {

    int verbose = 0;
    std::string outputFileName = "a.brain", sourceFileName = "",line;
    int unoptimized = 0;
    int opt;

    bool interpret = false;

    std::string currentDir = std::filesystem::current_path();

    brainlite bf;

    struct option long_options[] = {
        {"verbose", no_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        {"unoptimized", no_argument, 0, 'u'},
        {"interpreter", no_argument, 0, 'i'},
        {"output", required_argument, 0, 'o'},
        {0,0,0,0}
    };


    if (argc < 2) {
        help();
        return 1; // * Exit your program.
    };

    while ((opt = getopt_long(argc,argv,"vhuio:", long_options, nullptr)) != -1) {
        switch(opt) {

            case 'v':
                verbose = 1;
                std::cout << "Verbose flag is set\n";
                break;
            
            case 'h':
                help();
                break;

            case 'u':
                unoptimized = 1;
                break;
            
            case 'o':

                outputFileName = optarg;
                break;

            case 'i':

                interpret = true;
            
            case '?':
                /* getopt handles the error */
                break;
            
            default:
                break; /* Do nothing in other cases */

        };
    };

    if (optind < argc) { // ! First non argument index is lesser than args count. i.e., filename is specified at optind

        sourceFileName = argv[optind];

    } else {

        std::cout << "No source file specified.\n";
        return 1;

    };

    // todo support absolute and relative pathing.

    if (!std::filesystem::exists(currentDir+"/"+sourceFileName)) {
        std::cerr << "Error: Cannot find the source file specified " << sourceFileName << " at " << currentDir << std::endl;
        return 1;
    };

    if (interpret) {

        interpreter(sourceFileName);

    } else {

        std::ifstream source(sourceFileName);

        if (!source.is_open()) {
            std::cerr << "Error: Cannot read the source file specified " << sourceFileName << " at " << currentDir << std::endl;
            return 1;
        };
        
        while (std::getline(source,line)) {
            bf.lexCode(line);
        };

        std::ofstream output(outputFileName);

        if (!output.is_open()) {

            std::cerr << "Error: Unable to open the output file for writing." << std::endl;
            return 1;

        };

        std::vector<std::string> code = bf.getCode();

        for (std::string bfCode : code) {
            output << bfCode;
        };

        output << "\n";

    };

    return 0;

};

void help() {

    fprintf(stdout, "\t\t\tBrain-Un-Fuck\t\t\t\n\
    Welcome to brain un fuck, a transpiler which converts the written unfuck program to a pure and optimized brainlite program\n\
    Usage: brainuf <unfuck source file> [options]\n\
    Options are:\n\
    \t-u --unoptimized\t -> \t Returns a pure brain program which is not optimized.\n\t\t  \t\
    Forces the transpiler to convert given unfuck program to raw brainlite program");

};