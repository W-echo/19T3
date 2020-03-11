# COMP9021 19T3 - Rachid Hamadi
# Assignment 2 *** Due Sunday Week 10


# IMPORT ANY REQUIRED MODULE
import sys
import traceback


class MazeError(Exception):
    def __init__(self, message):
        self.message = message


class Maze:
    def __init__(self, filename):
        self.filename = filename
        f = open(filename, 'r')
        content = []
        for line in f:
            line = line.replace(' ', '')
            line = line.replace('\n', '')
            if line != '':
                content.append(list(line))

        try:
            length = len(content[0])
            for i in range(0, len(content)):
                # non-blank line contains different number of digits
                if length != len(content[i]):
                    raise MazeError('Incorrect input.')
                if len(content) < 2 or len(content[0]) < 2 or len(content) > 31 or len(content[0]) > 41:
                    raise MazeError('Incorrect input.')
                for j in range(0, len(content[i])):
                    # digit is not 1,2,3,4
                    if content[i][j] != '0' and content[i][j] != '1' and content[i][j] != '2' and content[i][j] != '3':
                        raise MazeError('Incorrect input.')
            # maze constraints
            for i in content:
                if i[-1] == '1' or i[-1] == '3':
                    raise MazeError('Input does not represent a maze.')

            for i in content[-1]:
                if i == '2' or i == '3':
                    raise MazeError('Input does not represent a maze.')
        except MazeError as e:
            traceback.print_exc()
            sys.exit()
        self.content = content
        # update the self.content
        grid = [[], []]
        for i in range(0, len(self.content)):
            for j in range(0, len(self.content[i])):
                if self.content[i][j] == '0':
                    grid[2 * i].append('0')
                    grid[2 * i].append('0')
                    grid[2 * i + 1].append('0')
                    grid[2 * i + 1].append('0')
                if self.content[i][j] == '1':
                    grid[2 * i].append('1')
                    grid[2 * i].append('1')
                    grid[2 * i + 1].append('0')
                    grid[2 * i + 1].append('0')
                if self.content[i][j] == '2':
                    grid[2 * i].append('2')
                    grid[2 * i].append('0')
                    grid[2 * i + 1].append('2')
                    grid[2 * i + 1].append('0')
                if self.content[i][j] == '3':
                    grid[2 * i].append('3')
                    grid[2 * i].append('3')
                    grid[2 * i + 1].append('3')
                    grid[2 * i + 1].append('0')
            grid.append([])
            grid.append([])

        grid = grid[:-2]

        for i in range(0, len(grid)):
            for j in range(0, len(grid[i])):
                if grid[i][j] == '1':
                    if grid[i][j + 1] == '0':
                        grid[i][j + 1] = '4'
                if grid[i][j] == '2':
                    if grid[i + 1][j] == '0':
                        grid[i + 1][j] = '4'
                if grid[i][j] == '3':
                    if grid[i][j + 1] == '3':
                        if grid[i][j + 2] == '0':
                            grid[i][j + 2] = '4'
                    if grid[i + 1][j] == '3':
                        if grid[i + 2][j] == '0':
                            grid[i + 2][j] = '4'

        self.show = [['0' for i in range(len(grid[0]) + 2)] for j in range(len(grid) + 2)]
        for i in range(0, len(grid)):
            for j in range(0, len(grid[0])):
                self.show[i + 1][j + 1] = grid[i][j]

        l = [['0' for i in range(len(grid[0]) + 2)] for j in range(len(grid) + 2)]
        for i in range(0, len(grid)):
            for j in range(0, len(grid[0])):
                l[i + 1][j + 1] = grid[i][j]
                if l[i + 1][j + 1] != '0':
                    l[i + 1][j + 1] = '1'
        # basic maze matrix 0,1 with skirt 0
        self.grid = l
        # for i in self.grid:
        #     print(i)

        self.direction = [(-1, 0), (0, 1), (1, 0), (0, -1)]
        # count number
        self.flag = 0
        # store some kind of area locations of number . len(shape) kinds. shape[i] = [(x,y), ...]
        self.shape = [[]]

        # display
        self.innerpoints = []
        self.cul = []
        self.path = []
        self.wall = []
        # count gates
        gate = 0
        # row
        for i in range(0, len(self.content[0]) - 1):
            if self.content[0][i] == '0':
                gate = gate + 1
            if self.content[0][i] == '2':
                gate = gate + 1
        for i in range(0, len(self.content[-1]) - 1):
            if self.content[-1][i] == '0':
                gate = gate + 1
        # column
        for i in range(0, len(self.content) - 1):
            if self.content[i][0] == '0':
                gate = gate + 1
            if self.content[i][0] == '1':
                gate = gate + 1
        for i in range(0, len(self.content) - 1):
            if self.content[i][-1] == '0':
                gate = gate + 1
        self.gate = gate

        # count walls
        count = 0
        for i in range(1, len(self.grid) - 1):
            for j in range(1, len(self.grid[i]) - 1):
                if self.grid[i][j] == '1':
                    count = count + 1
        while count != 0:
            for i in range(1, len(self.grid) - 1):
                for j in range(1, len(self.grid[i]) - 1):
                    if self.grid[i][j] == '1':
                        self.shape[self.flag].append((i, j))
                        self.color_area1(i, j)
                        # turn every elements in the shape[flag] into 0
                        for k in range(0, len(self.shape[self.flag])):
                            p, q = self.shape[self.flag][k]
                            self.grid[p][q] = '0'
                        # shape ?row + 1
                        self.flag = self.flag + 1
                        self.shape.append([])
                        # count if there is all 0 in grid
                        count = 0
                        for m in range(1, len(self.grid) - 1):
                            for n in range(1, len(self.grid[m]) - 1):
                                if self.grid[m][n] == '1':
                                    count = count + 1
        shape = self.shape[:-1]
        self.wall = self.shape
        wall = len(shape)
        self.countwall = wall
        # release the content ----- important!!!
        self.flag = 0
        for i in range(0, wall):
            for j in range(0, len(self.shape[i])):
                p, q = shape[i][j]
                #  turn all not 0 to 1,  with  0 out of skirt
                self.grid[p][q] = '1'
        self.shape = [[]]

        # count inaccessible inner point
        l = [['1' for i in range(len(self.grid[0]) + 2)] for j in range(len(self.grid) + 2)]
        for i in range(0, len(self.grid)):
            for j in range(0, len(self.grid[0])):
                l[i + 1][j + 1] = self.grid[i][j]
        # another 0 skirt
        self.grid = l
        # for i in self.grid:
        #     print(i)
        count = 0
        for i in range(1, len(self.grid) - 1):
            for j in range(1, len(self.grid[i]) - 1):
                if self.grid[i][j] == '0':
                    count = count + 1
        while count != 0:
            for i in range(1, len(self.grid) - 1):
                for j in range(1, len(self.grid[i]) - 1):
                    if self.grid[i][j] == '0':
                        self.shape[self.flag].append((i, j))
                        self.color_area0(i, j)
                        # turn every elements in the shape[flag] into 1
                        for k in range(0, len(self.shape[self.flag])):
                            p, q = self.shape[self.flag][k]
                            self.grid[p][q] = '1'
                        # shape ?row + 1
                        self.flag = self.flag + 1
                        self.shape.append([])
                        # count if there is all 0 in grid
                        count = 0
                        for m in range(1, len(self.grid) - 1):
                            for n in range(1, len(self.grid[m]) - 1):
                                if self.grid[m][n] == '0':
                                    count = count + 1
        self.shape = self.shape[:-1]
        inner_point = 0
        inner_area = 0
        ip_location = [[]]
        for i in self.shape:
            if (1, 1) not in i:
                # print(i)
                inner_point = inner_point + int(len(i) / 2) + 1
                for j in range(0, len(i)):
                    p, q = i[j]
                    p = p - 1
                    q = q - 1
                    ip_location[inner_area].append((p, q))
                ip_location.append([])
                inner_area = inner_area + 1
        ip_location = ip_location[:-1]
        # print(ip_location)
        self.inner = inner_point
        # release the  content ----- important!!!
        self.flag = 0
        for i in range(0, len(self.shape)):
            for j in range(0, len(self.shape[i])):
                p, q = self.shape[i][j]
                #  turn all not 0 to 1,  with  0 out of skirt
                self.grid[p][q] = '0'
        l = [['0' for i in range(len(self.grid[0]) - 2)] for j in range(len(self.grid) - 2)]
        for i in range(1, len(self.grid) - 1):
            for j in range(1, len(self.grid[i]) - 1):
                l[i - 1][j - 1] = self.grid[i][j]
        self.grid = l
        self.shape = [[]]
        # for i in self.grid:
        #     print(i)
        # Q4: count accessible areas
        access_area = 0
        # turn skirt into 1
        for i in range(0, len(self.grid)):
            for j in range(0, len(self.grid[i])):
                if i == 0 or j == 0 or i == len(self.grid) - 1 or j == len(self.grid[i]) - 1:
                    self.grid[i][j] = '1'

        # turn last row and last column into 1
        for i in range(0, len(self.grid[0])):
            self.grid[-2][i] = '1'
        for j in self.grid:
            j[-2] = '1'

        # find shape of 0
        count = 0
        for i in range(1, len(self.grid) - 1):
            for j in range(1, len(self.grid[i]) - 1):
                if self.grid[i][j] == '0':
                    count = count + 1
        while count != 0:
            for i in range(1, len(self.grid) - 1):
                for j in range(1, len(self.grid[i]) - 1):
                    if self.grid[i][j] == '0':
                        self.shape[self.flag].append((i, j))
                        self.color_area0(i, j)
                        # turn every elements in the shape[flag] into 1
                        for k in range(0, len(self.shape[self.flag])):
                            p, q = self.shape[self.flag][k]
                            self.grid[p][q] = '1'
                        # shape ?row + 1
                        self.flag = self.flag + 1
                        self.shape.append([])
                        # count if there is all 0 in grid
                        count = 0
                        for m in range(1, len(self.grid) - 1):
                            for n in range(1, len(self.grid[m]) - 1):
                                if self.grid[m][n] == '0':
                                    count = count + 1

        self.shape = self.shape[:-1]
        access_area = len(self.shape) - inner_area
        self.area = access_area

        # release self.grid
        for i in range(0, len(self.shape)):
            for j in range(0, len(self.shape[i])):
                p, q = self.shape[i][j]
                #  turn all not 0 to 1,  with  0 out of skirt
                self.grid[p][q] = '0'
        self.flag = 0

        for i in range(0, len(self.grid[0])):
            self.grid[0][i] = '0'
            self.grid[-1][i] = '0'
            self.grid[-2][i] = '0'

        for j in range(0, len(self.grid)):
            self.grid[j][0] = '0'
            self.grid[j][-1] = '0'
            self.grid[j][-2] = '0'

        # Q5: count sets of accessible cul-de-sacs
        for i in ip_location:
            self.shape.remove(i)
        b = 0
        for i in range(0, len(self.shape)):
            for j in range(0, len(self.shape[i])):
                p, q = self.shape[i][j]
                if self.grid[p][q] == '0':
                    a = 0
                    if self.grid[p][q + 1] == '1' or self.grid[p][q + 1] == '2':
                        a = a + 1
                    if self.grid[p][q - 1] == '1' or self.grid[p][q - 1] == '2':
                        a = a + 1
                    if self.grid[p + 1][q] == '1' or self.grid[p + 1][q] == '2':
                        a = a + 1
                    if self.grid[p - 1][q] == '1' or self.grid[p - 1][q] == '2':
                        a = a + 1
                    if a >= 3:
                        b = b + 1
        while b != 0:
            for i in range(0, len(self.shape)):
                for j in range(0, len(self.shape[i])):
                    p, q = self.shape[i][j]
                    if self.grid[p][q] == '0':
                        count = 0
                        if self.grid[p][q + 1] == '1' or self.grid[p][q + 1] == '2':
                            count = count + 1
                        if self.grid[p][q - 1] == '1' or self.grid[p][q - 1] == '2':
                            count = count + 1
                        if self.grid[p + 1][q] == '1' or self.grid[p + 1][q] == '2':
                            count = count + 1
                        if self.grid[p - 1][q] == '1' or self.grid[p - 1][q] == '2':
                            count = count + 1
                        if count >= 3:
                            self.grid[p][q] = '2'
            b = 0
            for m in range(0, len(self.shape)):
                for n in range(0, len(self.shape[m])):
                    p, q = self.shape[m][n]
                    if self.grid[p][q] == '0':
                        a = 0
                        if self.grid[p][q + 1] == '1' or self.grid[p][q + 1] == '2':
                            a = a + 1
                        if self.grid[p][q - 1] == '1' or self.grid[p][q - 1] == '2':
                            a = a + 1
                        if self.grid[p + 1][q] == '1' or self.grid[p + 1][q] == '2':
                            a = a + 1
                        if self.grid[p - 1][q] == '1' or self.grid[p - 1][q] == '2':
                            a = a + 1
                        if a >= 3:
                            b = b + 1

        # count number of shape of 2  = culde
        self.shape = [[]]
        culde = 0
        count = 0


        for i in range(1, len(self.grid) - 1):
            for j in range(1, len(self.grid[i]) - 1):
                if self.grid[i][j] == '2':
                    count = count + 1
        while count != 0:
            for i in range(1, len(self.grid) - 1):
                for j in range(1, len(self.grid[i]) - 1):
                    if self.grid[i][j] == '2':
                        self.shape[self.flag].append((i, j))
                        self.color_area2(i, j)
                        # turn every elements in the shape[flag] into 1
                        for k in range(0, len(self.shape[self.flag])):
                            p, q = self.shape[self.flag][k]
                            self.grid[p][q] = '1'
                        # shape ?row + 1
                        self.flag = self.flag + 1
                        self.shape.append([])
                        # count if there is all 0 in grid
                        count = 0
                        for m in range(1, len(self.grid) - 1):
                            for n in range(1, len(self.grid[m]) - 1):
                                if self.grid[m][n] == '2':
                                    count = count + 1

        sets = []
        for i in self.shape:
            if i != []:
                sets.append(i)
        culde = len(sets)
        self.cul = sets
        self.culde = culde

        # Q6: count entry paths
        for i in range(0, len(ip_location)):
            for j in range(0, len(ip_location[i])):
                p, q = ip_location[i][j]
                self.grid[p][q] = '1'
        for i in range(0, len(self.grid)):
            self.grid[i][0] = '1'
            self.grid[i][-1] = '1'
            self.grid[i][-2] = '1'
        for j in range(0, len(self.grid[0])):
            self.grid[0][j] = '1'
            self.grid[-1][j] = '1'
            self.grid[-2][j] = '1'
        # for i in self.grid:
        #   print(i)
        self.shape = [[]]
        self.flag = 0
        path = 0
        count = 0
        for i in range(1, len(self.grid) - 1):
            for j in range(1, len(self.grid[i]) - 1):
                if self.grid[i][j] == '0':
                    count = count + 1
        while count != 0:
            for i in range(1, len(self.grid) - 1):
                for j in range(1, len(self.grid[i]) - 1):
                    if self.grid[i][j] == '0':
                        self.shape[self.flag].append((i, j))
                        self.color_area0(i, j)
                        # turn every elements in the shape[flag] into 1
                        for k in range(0, len(self.shape[self.flag])):
                            p, q = self.shape[self.flag][k]
                            self.grid[p][q] = '1'
                        # shape ?row + 1
                        self.flag = self.flag + 1
                        self.shape.append([])
                        # count if there is all 0 in grid
                        count = 0
                        for m in range(1, len(self.grid) - 1):
                            for n in range(1, len(self.grid[m]) - 1):
                                if self.grid[m][n] == '0':
                                    count = count + 1
        self.shape = self.shape[:-1]

        for i in range(0, len(self.shape)):
            for j in range(0, len(self.shape[i])):
                p, q = self.shape[i][j]
                self.grid[p][q] = '0'

        result = []
        for i in range(0, len(self.shape)):
            spike = 0
            for j in range(0, len(self.shape[i])):  # in a shape
                count = 0
                for k in self.direction:
                    x, y = k
                    m, n = self.shape[i][j]
                    next_i = m + x
                    next_j = n + y
                    if self.grid[next_i][next_j] == '1':
                        count = count + 1
                if count >= 3:
                    spike = spike + 1
            if spike < 3:
                self.path.append(self.shape[i])
            result.append(spike)
        count = 0
        for i in result:
            if i < 3:
                count = count + 1
        path = count
        self.aspath = path

        # release the grid
        for i in range(0, len(ip_location)):
            for j in ip_location[i]:
                p, q = j
                self.grid[p][q] = '0'
        for i in range(0, len(self.grid)):
            self.grid[i][0] = '0'
            self.grid[i][-1] = '0'
            self.grid[i][-2] = '0'
        for j in range(0, len(self.grid[0])):
            self.grid[0][j] = '0'
            self.grid[-1][j] = '0'
            self.grid[-2][j] = '0'


    def analyse(self):

        # show gate
        if self.gate == 0:
            print('The maze has no gate.')
        elif self.gate == 1:
            print('The maze has a single gate.')
        else:
            print('The maze has', self.gate, 'gates.')


        # show the number of walls
        if self.countwall == 0:
            print('The maze has no wall.')
        elif self.countwall == 1:
            print('The maze has walls that are all connected.')
        else:
            print('The maze has', self.countwall, 'sets of walls that are all connected.')


        # show inaccessible inner point
        if self.inner == 0:
            print('The maze has no inaccessible inner point.')
        elif self.inner == 1:
            print('The maze has a unique inaccessible inner point.')
        else:
            print('The maze has', self.inner, 'inaccessible inner points.')


        # show inaccessible inner point
        if self.area == 0:
            print('The maze has no accessible area.')
        elif self.area == 1:
            print('The maze has a unique accessible area.')
        else:
            print('The maze has', self.area, 'accessible areas.')


        # show the number of accessible cul_de_sacs
        if self.culde == 0:
            print('The maze has no accessible cul-de-sac.')
        elif self.culde == 1:
            print('The maze has accessible cul-de-sacs that are all connected.')
        else:
            print('The maze has', self.culde, 'sets of accessible cul-de-sacs that are all connected.')


        # show entry paths
        if self.aspath == 0:
            print('The maze has no entry-exit path with no intersection not to cul-de-sacs.')
        elif self.aspath == 1:
            print('The maze has a unique entry-exit path with no intersection not to cul-de-sacs.')
        else:
            print('The maze has', self.aspath, 'entry-exit paths with no intersections not to cul-de-sacs.')



    # find out shape of 1
    def color_area1(self, i, j):
        for k in self.direction:
            x, y = k
            next_i = i + x
            next_j = j + y
            if self.grid[next_i][next_j] == '1':
                if (next_i, next_j) not in self.shape[self.flag]:
                    self.shape[self.flag].append((next_i, next_j))
                    self.color_area1(next_i, next_j)

    # find out shape of 0
    def color_area0(self, i, j):
        for k in self.direction:
            x, y = k
            next_i = i + x
            next_j = j + y
            if self.grid[next_i][next_j] == '0':
                if (next_i, next_j) not in self.shape[self.flag]:
                    self.shape[self.flag].append((next_i, next_j))
                    self.color_area0(next_i, next_j)

    # find out shape of 2
    def color_area2(self, i, j):
        for k in self.direction:
            x, y = k
            next_i = i + x
            next_j = j + y
            if self.grid[next_i][next_j] == '2':
                if (next_i, next_j) not in self.shape[self.flag]:
                    self.shape[self.flag].append((next_i, next_j))
                    self.color_area2(next_i, next_j)

    def display(self):

        for i in range(0, len(self.filename)):
            if self.filename[i] == '.':
                self.filename = self.filename[:i]
                break
        file = open(self.filename + '.tex', 'w')
        direct = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
        for i in range(1, len(self.grid) - 2):
            for j in range(1, len(self.grid[0]) - 2):
                if self.grid[i][j] == '0':
                    count = 0
                    for k in direct:
                        p, q = k
                        x = i + p
                        y = j + q
                        if self.grid[x][y] == '0':
                            count = count + 1
                    if count == 8:
                        self.innerpoints.append((i, j))
        # write
        file.write('\documentclass[10pt]{article}\n')
        file.write(r'\usepackage{tikz}')
        file.write('\n')
        file.write(r'\usetikzlibrary{shapes.misc}')
        file.write('\n')
        file.write(r'\usepackage[margin=0cm]{geometry}')
        file.write('\n')
        file.write(r'\pagestyle{empty}')
        file.write('\n')
        file.write(r'\tikzstyle{every node}=[cross out, draw, red]')
        file.write('\n')
        file.write('\n')
        file.write(r'\begin{document}')
        file.write('\n')
        file.write('\n')
        file.write(r'\vspace*{\fill}')
        file.write('\n')
        file.write(r'\begin{center}')
        file.write('\n')
        file.write(r'\begin{tikzpicture}[x=0.25cm, y=-0.25cm, ultra thick, blue]')
        file.write('\n')
        file.write(r'% Walls')
        file.write('\n')
        # show walls
        for i in self.wall:
            for j in i:
                p, q = j
                if p % 2 == 1 and q % 2 == 1:
                    if self.show[p][q] == '1':
                        file.writelines(f'    \draw (' + str(q) + ',' + str(p) + ') -- (' + str(q + 2) + ',' + str(p) + ');\n')
                    if self.show[p][q] == '2':
                        file.writelines(f'    \draw (' + str(q) + ',' + str(p) + ') -- (' + str(q) + ',' + str(p + 2) + ');\n')
                    if self.show[p][q] == '3':
                        file.writelines(f'    \draw (' + str(q) + ',' + str(p) + ') -- (' + str(q + 2) + ',' + str(p) + ');\n')
                        file.writelines(f'    \draw (' + str(q) + ',' + str(p) + ') -- (' + str(q) + ',' + str(p + 2) + ');\n')
        # show green points
        file.write('% Pillars\n')
        for i in self.innerpoints:
            p, q = i
            file.write('    ')
            file.writelines(r'\fill[green] (' + str(q) + ',' + str(p) + ') ' + 'circle(0.4);')
            file.write('\n')
        # show accessible cul-de-sacs
        file.write('% Inner points in accessible cul-de-sacs\n')
        for i in self.cul:
            for j in i:
                p, q = j
                if p % 2 == 0 and q % 2 == 0:
                    file.write('    ')
                    file.writelines(r'\node at (' + str(q) + ',' + str(p) + ') {};\n')
        # show entry exit path
        file.write('% Entry-exit paths without intersections\n')
        if len(self.path) != 0:
            for i in range(0, len(self.path)):
                for j in range(0, len(self.path[i])):
                    p, q = self.path[i][j]
                    if p % 2 == 1 and q % 2 == 1:
                        self.show[p][q] = '1'
        if len(self.path) != 0:
            for i in range(0, len(self.path)):
                for j in range(0, len(self.path[i])):
                    p, q = self.path[i][j]
                    if p == 1 and self.show[p][q] == '0':
                        file.write('    ')
                        file.writelines(r'\draw[dashed, yellow] (' + str(q) + ',' + str(p) + ') -- (' + str(q) + ',' + str(p - 1) + ');\n')
                        self.show[p][q] = '1'
                        break
                    if q == 1 and self.show[p][q] == '0':
                        file.write('    ')
                        file.writelines(r'\draw[dashed, yellow] (' + str(q) + ',' + str(p) + ') -- (' + str(q - 1) + ',' + str(p) + ');\n')
                        self.show[p][q] = '1'
                        break
                    if p == len(self.show) - 3 and self.show[p][q] == '0':
                        file.write('    ')
                        file.writelines(r'\draw[dashed, yellow] (' + str(q) + ',' + str(p) + ') -- (' + str(q) + ',' + str(p + 1) + ');\n')
                        self.show[p][q] = '1'
                        break
                    if q == len(self.show[0]) - 3 and self.show[p][q] == '0':
                        file.write('    ')
                        file.writelines(r'\draw[dashed, yellow] (' + str(q) + ',' + str(p) + ') -- (' + str(q + 1) + ',' + str(p) + ');\n')
                        self.show[p][q] = '1'
                        break
                self.findpath(i, p, q, file)
        file.write('\end{tikzpicture}\n\end{center}\n')
        file.write(r'\vspace*{\fill}')
        file.write('\n')
        file.write('\n')
        file.write('\end{document}')

    def findpath(self, i, p, q, file):
        for k in self.direction:
            m, n = k
            x = p + m
            y = q + n
            if (x, y) in self.path[i] and self.show[x][y] == '0':
                if x == 1 or y == 1 or x == len(self.show) - 3 or y == len(self.show[0]) - 3:
                    if x == 1:
                        file.write('    ')
                        file.writelines(r'\draw[dashed, yellow] (' + str(q) + ',' + str(p) + ') -- (' + str(y) + ',' + str(x) + ');\n')
                        file.write('    ')
                        file.writelines(r'\draw[dashed, yellow] (' + str(y) + ',' + str(x) + ') -- (' + str(y) + ',' + str(x - 1) + ');\n')
                        self.show[p][q] = '1'
                    if y == 1:
                        file.write('    ')
                        file.writelines(r'\draw[dashed, yellow] (' + str(q) + ',' + str(p) + ') -- (' + str(y) + ',' + str(x) + ');\n')
                        file.write('    ')
                        file.writelines(r'\draw[dashed, yellow] (' + str(y) + ',' + str(x) + ') -- (' + str(y - 1) + ',' + str(x) + ');\n')
                        self.show[p][q] = '1'
                    if x == len(self.show) - 3:
                        file.write('    ')
                        file.writelines(r'\draw[dashed, yellow] (' + str(q) + ',' + str(p) + ') -- (' + str(y) + ',' + str(x) + ');\n')
                        file.write('    ')
                        file.writelines(r'\draw[dashed, yellow] (' + str(y) + ',' + str(x) + ') -- (' + str(y) + ',' + str(x + 1) + ');\n')
                        self.show[p][q] = '1'
                    if y == len(self.show[0]) - 3:
                        file.write('    ')
                        file.writelines(r'\draw[dashed, yellow] (' + str(q) + ',' + str(p) + ') -- (' + str(y) + ',' + str(x) + ');\n')
                        file.write('    ')
                        file.writelines(r'\draw[dashed, yellow] (' + str(y) + ',' + str(x) + ') -- (' + str(y + 1) + ',' + str(x) + ');\n')
                        self.show[p][q] = '1'
                else:
                    file.write('    ')
                    file.writelines(r'\draw[dashed, yellow] (' + str(q) + ',' + str(p) + ') -- (' + str(y) + ',' + str(x) + ');\n')
                    self.show[x][y] = '1'
                    self.findpath(i, x, y, file)


maze = Maze('maze_1.txt')
maze.analyse()
maze.display()
