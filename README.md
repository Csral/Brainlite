# Brainlite
The core principle of the language remains completely the same, i.e only 8 operations. 
*Brainlite* is a translation layer (or compiler) which makes writing  complex brainf*ck programs easier.

---

# What is Brainf*ck?
Brainf*ck is an esoteric programming language created in 1993 by Urban Müller, and notable for its extreme minimalism. The language consists of only eight simple commands and an instruction pointer.'
Brainf*ck is a programming language that revolves around manipulating a memory array. 
You have a set of eight simple commands to interact with this tape:
> and <: These move the pointer one cell to the right or left.
+ and -: These increase or decrease the value in the current cell.
[ and ]: These are for loops. [ starts a loop that runs as long as the current cell's value isn't zero, and ] jumps back to the matching [ if the value is still non-zero.
, and .: These handle input and output. , reads a single character from the user and stores its ASCII value in the current cell, while . prints the character corresponding to the ASCII value in the current cell.

---

# How does Brainlite help Brainfuck?
Brainlite introduces multiple keywords which can easen the task of writing a brainf*ck program manually.

---

# How to use this compiler?
## NOTE: THIS COMPILER WORKS ONLY ON LINUX.

1. Clone this repository
2. Run 
3. Write your program.
4. use command: ./brainuf inputdih.txt -o dih.brain


User options:
1. Verbose: -v
2. Help: -h
3. Unoptimized: -u Returns a pure brain program which is not optimized.
4. intepreter: -i
5. output: -o
6. 
---
### future works:
Use euclidian GCD algorithm, early-lookup write optimizations and in general compiler optimizations are not available
---

---
## Additional information/Caution
- The memory size of this interpreter is 38000 bytes. So any program running over that will get overflow error. And that's also why the pointer (runtime etc) is Int, not uint64 etc
- This compiler works only on linux based systems.
---

# Contributers
Developed by @Csral
Idea was given by @CodeLanderV

