# Brainlite
The core principle of the language remains completely the same, i.e only 8 operations. 
*Brainlite* is a source-to-source transpiler with an integrated Brainf*ck interpreter which makes writing complex brainf*ck programs easier.

**Note:** This is my first language implementation project developed when I was in my first semester before I had formally studied compiler construction and its design theory. The project itself has many flaws reflecting my understanding at that time and intentionally preserves some of the original implementation and design decisions as a snapshot of my early work. Minor issues affecting correctness or build consistency have been fixed, while the overall structure has been left largely unchanged.

---

# What is Brainfuck?
Brainfuck is an esoteric programming language created in 1993 by Urban Müller, and notable for its extreme minimalism. The language consists of only eight simple commands and an instruction pointer.'
Brainfuck is a programming language that revolves around manipulating a memory array. 
You have a set of eight simple commands to interact with this tape:
```
> and <: These move the pointer one cell to the right or left.
+ and -: These increase or decrease the value in the current cell.
[ and ]: These are for loops. [ starts a loop that runs as long as the current cell's value isn't zero, and ] jumps back to the matching [ if the value is still non-zero.
, and .: These handle input and output. , reads a single character from the user and stores its ASCII value in the current cell, while . prints the character corresponding to the ASCII value in the current cell.
```
---

# How does Brainlite help Brainfuck?
Brainlite introduces multiple keywords which can easen the task of writing a brainfuck program manually.

---

# How to use this transpiler?

1. Clone this repository
2. Build the source code. Multiple alternatives are provided.
3. Write your program.
4. Execute the binary using "./brainuf input.txt -o out.brain"
5. Execute the output using "./brainuf -i out.brain"

The above commands assume that the 'brainuf' binary is available in the source directory. Adjust accordingly.

User options:

Help: -h
intepreter: -i
output: -o

---
## Additional information/Caution
- The memory size of this interpreter is 38000 bytes. So any program running over that will get overflow error. And that's also why the pointer (runtime etc) is Int, not uint64 etc
- This transpiler works only on linux based systems.
---

# License
Licensed under Apache-2.0 license. Refer [License](License).

# Contributers
Developed by @Csral
Idea was given by @CodeLanderV
