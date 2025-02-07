# Compiles files for devices with no make/sh support

import os,pathlib,time;

start = time.time();

windows = True if os.name == "nt" else False;

missingFile = "";
files = ["../../src/brainuf.cpp", "../../src/utils.cpp", "../../src/main.cpp", "../../src/interpreter.cpp"];
inc_files = ["../../src/includes/brainuf.hpp", "../../src/includes/utils.hpp", "../../src/includes/errors.hpp", "../../src/includes/interpreter.hpp"]
obj_files = ["../../src/bins/brainuf.o", "../../src/bins/utils.o", "../../src/bins/main.o", "../../src/bins/interpreter.o"];

def verify_files() -> bool:

    for x in files:
        if not pathlib.Path.exists(x):
            missingFile = x;
            return False;

    for x in inc_files:
        if not pathlib.Path.exists(x):
            missingFile = x;
            return False;

    return True;

def verify_obj_files() -> bool:

    for x in obj_files:
        if not pathlib.Path.exists(x):
            missingFile = x;
            return False;

    return True;


def pre_compile() -> None:

    #* Remove any pervious compile file
    os.remove("../../src/bins");
    os.mkdir("../../src/bins/");

    for x in files:
        os.system(f"g++ -c {x} -o ../src/bins/{x.removeprefix("../src/").replace("cpp","o")}");

def compile() -> None:

    os.system("g++ ../src/bins/*.o -o ../src/bins/brainlite");

def clean() -> None:

    os.system("del ../src/bins/*.o" if windows else "rm -rf ../src/bins/*.o");


if not verify_files():
    print(f"Error: A file is missing.\nFile:\t{missingFile}");
    os._exit(2);

pre_compile();

if not verify_obj_files():

    print(f"Error: Some file was not compiled and is missing.\nFile:\t{missingFile}");
    os._exit(2);

compile();

clean();

print(f"Compilation done in {time.time()-start} seconds");