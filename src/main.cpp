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

    std::string outputFileName = "a.brain", sourceFileName = "", line;
    int opt;
    bool interpret = false;
    std::string currentDir = std::filesystem::current_path();
    brainlite bf;

    struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"interpreter", no_argument, 0, 'i'},
        {"output", required_argument, 0, 'o'},
        {0,0,0,0}
    };

    if (argc < 2) {
        help();
        return 1; // * Exit program.
    };

    while ((opt = getopt_long(argc,argv,"hio:", long_options, nullptr)) != -1) {
        switch(opt) {
            
            case 'h':
                help();
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

    if (optind < argc) {
        // ! First non argument index is lesser than args count. i.e., filename is specified at optind
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
            return 3;
        };
        
        while (std::getline(source,line)) {
            bf.lexCode(line);
        };

        std::ofstream output(outputFileName);
        if (!output.is_open()) {
            std::cerr << "Error: Unable to open the output file for writing." << std::endl;
            return 4;
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
    std::cout << "\n\t\t\tBrainlite\n"
              << "------------------------------------------------------------\n"
              << "Welcome to Brainlite, a transpiler that converts a Brainlite\n"
              << "source file into a standard Brainfuck-compatible output.\n\n"
              << "Usage:\n"
              << "    brainlite <source_file> [options]\n\n"
              << "Options:\n"
              << "    -h, --help           Show this help message and exit\n"
              << "    -i, --interpret      Run the program using the interpreter instead\n"
              << "    -o, --output <file>  Specify output file name for transpiled code\n\n"
              << "Example:\n"
              << "    brainlite program.bl -o out.bf        Transpile only\n"
              << "    brainlite program.bl -i               Interpret only\n"
              << "    brainlite program.bl -i -o out.bf     Interpret and save transpiled code\n"
              << "\n";
}