
# Quiz 6： 

Input:  Randomly fills an array of size 10x10 with 0s and 1s
Output: the size of the largest parallelogram with horizontal sides.

Instruction: A parallelogram consists of a line with at least 2 consecutive 1s, with below at least one line with the same number of consecutive 1s, 
all those lines being aligned vertically in which case the parallelogram
   is actually a rectangle, e.g.
        111
        111
        111
        111
   or consecutive lines move to the left by one position, e.g.
        111
       111
      111
     111
   or consecutive lines move to the right by one position, e.g.
        111
         111
          111
           111


# Quiz 7: 

Input:  Randomly generates a grid of 0s and 1s.
Output: the maximum number of "spikes" in a shape.

Instruction:  A shape is made up of 1s connected horizontally or vertically (it can contain holes).
              A "spike" in a shape is a 1 that is part of this shape and "sticks out" (has exactly one neighbour in the shape).
              More specific illustration is recorded in file Quiz7/spike.png



# Assignment2 : 

Input:  Randomly generates a grid of 0s,1s,2s,3s, which can be seen as walls of a maze according to some rules.

Output: 
        1.show the number of 
          gates, 
          sets of walls that are all connected, 
          inaccessible inner points, 
          accessible areas,
          sets of accessible cul-de-sacs that are all connected,
          unique entry-exit path with no intersection not to cul-de-sacs of the maze.
        2. mark these gates, sets of walls that are all connected..., on the maze.
        3. maze.display ()
          grid -> maze.tex -> maze.pdf (using LaTeX )

![images](https://github.com/W-echo/19T3/blob/master/9021/assignment2/maze_tex_report%20.png)