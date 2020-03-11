# COMP9021 19T3 - Rachid Hamadi
# Quiz 5 *** Due Thursday Week 7
#
# Implements a function that, based on the encoding of
# a single strictly positive integer that in base 2,
# reads as b_1 ... b_n, as b_1b_1 ... b_nb_n, encodes
# a sequence of strictly positive integers N_1 ... N_k
# with k >= 1 as N_1* 0 ... 0 N_k* where for all 0 < i <= k,
# N_i* is the encoding of N_i.
#
# Implements a function to decode a positive integer N
# into a sequence of (one or more) strictly positive
# integers according to the previous encoding scheme,
# or return None in case N does not encode such a sequence.


import sys


def encode(a):
    for i in range(0, len(a)):
        a[i] = ''.join(bin(a[i])[2:])
    binnumber = ''
    for j in a:
        for k in j:
            binnumber = binnumber + k*2
        binnumber = binnumber + '0'
    binnumber = binnumber[:-1]
    return int(binnumber,2)


def decode(a):
    a = list(bin(the_input)[2:])
    b = []
    i = 0
    index = [0]
    if i + 1 == len(a):
        return None
    while i < len(a)-1:
        if a[i] == a[i+1]:
            i = i + 2
            if i == len(a) - 1:
                return None
            if i == len(a):
                b.append(''.join(str(j) for j in a[index[-1]:i]))
        else:
            if a[i] == '0':
                b.append(''.join(str(j) for j in a[index[-1]:i]))
                i = i+1
                index.append(i)
            else:
                return None
    b_1 = []
    binnumber = ''
    for i in b:
        binnumber = ''.join(i[j] for j in range(0, len(i), 2))
        b_1.append(binnumber)
        b_1[-1] = int(b_1[-1], 2)
    return b_1


# We assume that user input is valid. No need to check
# for validity, nor to take action in case it is invalid.
print('Input either a strictly positive integer')
the_input = eval(input('or a nonempty list of strictly positive integers: '))
if type(the_input) is int:
    print('  In base 2,', the_input, 'reads as', bin(the_input)[2:])
    decoding = decode(the_input)
    if decoding is None:
        print('Incorrect encoding!')
    else:
        print('  It encodes: ', decode(the_input))
else:
    print('  In base 2,', the_input, 'reads as',
          f'[{", ".join(bin(e)[2: ] for e in the_input)}]'
         )
    print('  It is encoded by', encode(the_input))
