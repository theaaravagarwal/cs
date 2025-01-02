import pprint, random, time, sys
k = int(sys.stdin.readline())
a, b, c = k, k, k
lst = [[[0 for col in range(a)] for col in range(b)] for row in range(c)]
arr = [[[0 for col in range(a)] for col in range(b)] for row in range(c)]
min = 0
max = 100

def assign(arr):
    for i in range(a):
        for j in range(b):
            for k in range(c):
                arr[i][j][k] = random.randint(min,max)
    return arr

print(assign(lst))
print()
print(assign(arr))
print()

def operation(lst, arr):
    out = [[[0 for col in range(a)] for col in range(b)] for row in range(c)]
    for i in range(a):
        for j in range(b):
            for k in range(c):
                out[i][j][k] = lst[i][j][k] * arr[i][j][k]
    return out

print(operation(lst, arr))