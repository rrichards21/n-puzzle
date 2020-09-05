# N-Puzzle Solving
N-puzzle (2x2,3x3,4x4) solution using path finding algorithms such as A*, Greedy, BFS and DFS

Usage:

Compile with "g++ npuzzle.cpp -o npuzzle"

Modify puzzle.txt, where:

​	-First number indicates the type of puzzle:

​		-If puzzle is 2x2 the number must be 2

​		-If puzzle is 3x3 the number must be 3

​		-If puzzle is 4x4 the number must be 4

​	-The puzzle is described by its numbers according the type of the puzzle you want to work in the next lines of the file with numbers separated by a space character and setting a '0' where the puzzle has a free space for moving

Execute in terminal with ./npuzzle if on linux or WSL  