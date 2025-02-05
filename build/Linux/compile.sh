#!/bin/bash
required_files=("../../src/brainuf.cpp" "../../src/main.cpp" "../../src/utils.cpp")

verify_files() {

    if [[ ! -d "../../src" ]]; then

        echo "Src directory not found!!"
        exit 2
    
    elif [[ ! -d "../../src/includes" ]]; then

        echo "Includes not found!!"
        exit 2

    fi

    for file in $required_files; do

        if [[ ! -f "$file" ]]; then
            echo "Missing File Error: $file not found!"
            exit 2
        fi

    done

};

precompile() {

    if [ ! -d "../../BuildFiles/" ]; then
        mkdir -p "../../BuildFiles/Objects"
    fi

    for file in $required_files; do

        g++ -c $file -o "../../BuildFiles/Objects/$(echo $file | cut -d "/" -f 3 | cut -d "." -f 1).o"
    
    done

};

compile() {

    g++ ../../BuildFiles/Objects/*.o -o ../../BuildFiles/brainlite
    cp ../../BuildFiles/brainlite ../../src/brainlite
    exit 0

}

verify_files
precompile
compile