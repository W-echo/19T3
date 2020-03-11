# COMP9021 19T3 - Rachid Hamadi
# Quiz 7 *** Due Thursday Week 9
#
# Randomly generates a grid of 0s and 1s and determines
# the maximum number of "spikes" in a shape.
# A shape is made up of 1s connected horizontally or vertically (it can contain holes).
# A "spike" in a shape is a 1 that is part of this shape and "sticks out"
# (has exactly one neighbour in the shape).


from random import seed, randrange
import sys


dim = 10


def display_grid():
    for row in grid:
        print('   ', *row) 


# Returns the number of shapes we have discovered and "coloured".
# We "colour" the first shape we find by replacing all the 1s
# that make it with 2. We "colour" the second shape we find by
# replacing all the 1s that make it with 3.
def colour_shapes():
    global grid
    global flag
    global direction
    global shape
    l = [[0 for i in range(dim + 2)] for j in range(dim + 2)]
    for i in range(0, dim):
        for j in range(0, dim):
            l[i + 1][j + 1] = grid[i][j]
    grid = l
    count = 0
    for i in range(1, dim + 1):
        for j in range(1, dim + 1):
            if grid[i][j] == 1:
                count = count + 1
    while count != 0:
        for i in range(1, dim + 1):
            for j in range(1, dim + 1):
                if grid[i][j] == 1:
                    shape[flag].append((i, j))
                    color_area(i, j)
                    # turn every elements in the shape[flag] into 0
                    for k in range(0, len(shape[flag])):
                        p, q = shape[flag][k]
                        grid[p][q] = 0
                    # shape ：row + 1
                    flag = flag + 1
                    shape.append([])
                    # count if there is all 0 in grid
                    count = 0
                    for m in range(1, dim + 1):
                        for n in range(1, dim + 1):
                            if grid[m][n] == 1:
                                count = count + 1
    return len(shape)-1


shape = [[]]
direction = [(-1, 0), (0, 1), (1, 0), (0, -1)]
flag = 0


def max_number_of_spikes(nb_of_shapes):
    global shape
    global direction
    for i in range(0, nb_of_shapes):
        for j in range(0, len(shape[i])):
            p, q = shape[i][j]
            grid[p][q] = 1
    result = 0
    for i in range(0, nb_of_shapes):
        spike = 0
        for j in range(0, len(shape[i])):       # in a shape
            count = 0
            for k in direction:
                x, y = k
                m, n = shape[i][j]
                next_i = m + x
                next_j = n + y
                if grid[next_i][next_j] == 0:
                    count = count+1
            if count >= 3:
                spike = spike + 1
        if spike > result:
            result = spike
    return result


def color_area(i, j):
    global flag
    global direction
    global shape
    for k in direction:
        x, y = k
        next_i = i + x
        next_j = j + y
        if grid[next_i][next_j] == 1:
            if (next_i, next_j) not in shape[flag]:
                shape[flag].append((next_i, next_j))
                color_area(next_i, next_j)


try:
    for_seed, density = (int(x) for x in input('Enter two integers, the second '
                                               'one being strictly positive: '
                                               ).split()
                         )
    if density <= 0:
        raise ValueError

except ValueError:
    print('Incorrect input, giving up.')
    sys.exit()
seed(for_seed)
grid = [[int(randrange(density) != 0) for _ in range(dim)]
            for _ in range(dim)
       ]
print('Here is the grid that has been generated:')
display_grid()
nb_of_shapes = colour_shapes()
print('The maximum number of spikes of some shape is:',
      max_number_of_spikes(nb_of_shapes)
     )
