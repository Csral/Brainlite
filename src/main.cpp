#include <iostream>
#include <stdio.h>
#include <map>
#include <filesystem>
#include <fstream>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>

#include "includes/brainuf.hpp"

void help();

int main(int argc, char* argv[]) {

    int verbose = 0;
    std::string outputFileName = "a.brain", sourceFileName = nullptr,line;
    int unoptimized = 0;
    int opt;

    std::string currentDir = std::filesystem::current_path();

    brainfuck bf;

    struct option long_options[] = {
        {"verbose", no_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        {"unoptimized", no_argument, 0, 'u'},
        {"output", required_argument, 0, 'o'},
        {0,0,0,0}
    };


    if (argc < 2) {
        help();
        return 1; // * Exit your program.
    };
    
    opt = getopt_long(argc,argv,"vhuo:", long_options, nullptr);

    while (opt != -1) {
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

    // todo Start the transpiler here.

    if (!std::filesystem::exists(currentDir+sourceFileName)) {
        std::cerr << "Error: Cannot find the source file specified " << sourceFileName << " at " << currentDir << std::endl;
        return 1;
    };

    std::ifstream source(sourceFileName);

    if (!source.is_open()) {
        std::cerr << "Error: Cannot read the source file specified " << sourceFileName << " at " << currentDir << std::endl;
        return 1;
    };
    
    while (std::getline(source,line)) {
        bf.lexCode(line);
    };

    return 0;

};

void help() {

    fprintf(stdout, "\t\t\tBrain-Un-Fuck\t\t\t\n\
    Welcome to brain un fuck, a transpiler which converts the written unfuck program to a pure and optimized brainfuck program\n\
    Usage: brainuf <unfuck source file> [options]\n\
    Options are:\n\
    \t-u --unoptimized\t -> \t Returns a pure brain program which is not optimized.\n\t\t  \t\
    Forces the transpiler to convert given unfuck program to raw brainfuck program");

};