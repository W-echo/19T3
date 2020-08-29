# 19T3
>>> from maze import *
>>> maze = Maze('maze_1.txt')
>>> maze.analyse()



The maze has 12 gates.
The maze has 8 sets of walls that are all connected.
The maze has 2 inaccessible inner points.
The maze has 4 accessible areas.
The maze has 3 sets of accessible cul-de-sacs that are all connected.
The maze has a unique entry-exit path with no intersection not to cul-de-sacs. >>> maze.display()


The effect of executing maze.display() is to produce a file named maze_1.tex that can be given as argument to 
pdflatex to produce a file named maze_1.pdf that views as follows.

![image](9021/assignment2/maze_tex_report .png)
