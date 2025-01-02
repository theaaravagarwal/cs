import random, sys, time, pprint
r = int(sys.stdin.readline())
c = r
arr = [[0 for g in range(r)] for g in range(c)]
l = [[0 for g in range(r)] for g in range(c)]
def fill(arr):
    for i in range(r):
        for j in range(c):
            arr[i][j] = random.randint(0,100)
    return arr

def addition(a, b):
    d = [[0 for g in range(r)] for g in range(c)]
    for i in range(r):
        for j in range(c):
            d[i][j] = a[i][j] +  b[i][j]
    return d

pprint.pprint(fill(arr))
pprint.pprint(fill(l))
pprint.pprint(addition(arr, l))