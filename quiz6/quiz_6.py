# COMP9021 19T3 - Rachid Hamadi
# Quiz 6 *** Due Thursday Week 8
#
# Randomly fills an array of size 10x10 with 0s and 1s, and outputs the size of
# the largest parallelogram with horizontal sides.
# A parallelogram consists of a line with at least 2 consecutive 1s,
# with below at least one line with the same number of consecutive 1s,
# all those lines being aligned vertically in which case the parallelogram
# is actually a rectangle, e.g.
#      111
#      111
#      111
#      111
# or consecutive lines move to the left by one position, e.g.
#      111
#     111
#    111
#   111
# or consecutive lines move to the right by one position, e.g.
#      111
#       111
#        111
#         111


from random import seed, randrange
import sys


dim = 10


def display_grid():
    for row in grid:
        print('   ', *row) 


def size_of_largest_parallelogram():
    global grid
    area = 0
    l = [[0 for i in range(dim+2)] for j in range(dim+2)]
    for i in range(0, dim):
        for j in range(0, dim):
            l[i+1][j+1] = grid[i][j]
    grid = l
    direction = [(1, 1), (1, 0), (1, -1)]
    for i in range(1, dim+1):
        for j in range(1, dim+1):
            if grid[i][j] == 1:
                row_i = i + 0
                row_j = j + 1
                while grid[row_i][row_j] == 1:          # the number of elements in a row of parallelogram

                    # four direction loop looking for parallelogram
                    for k in direction:
                        x, y = k
                        # the column of parallelogram
                        column_i = i + x
                        column_j = j + y
                        flag = 0
                        while grid[column_i][column_j] == 1:                    # extended column stop
                            count = 0
                            for m in range(0, row_j - j + 1):
                                if column_j + m < dim+2:
                                    if grid[column_i][column_j + m] == 0:
                                        count = count + 1
                                else:
                                    break
                            if count == 0:
                                column_i = column_i + x                 # add elements for column
                                column_j = column_j + y
                                flag = flag + 1
                            else:
                                if row_j - j > 0 and column_i - i > 1:    # the result
                                    if area < (row_j - j + 1) * (column_i - i):
                                        area = (row_j - j + 1) * (column_i - i)
                                break
                        if flag == column_i - i - 1:
                            if row_j - j > 0 and column_i - i > 1:  # the result
                                if area < (row_j - j + 1) * (column_i - i):
                                    area = (row_j - j + 1) * (column_i - i)
                    row_i = row_i + 0                                   # add element for row
                    row_j = row_j + 1
    if area == 0:
        return None
    else:
        return area


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
size = size_of_largest_parallelogram()
if size:
    print('The largest parallelogram with horizontal sides '
          f'has a size of {size}.'
         )
else:
    print('There is no parallelogram with horizontal sides.')
