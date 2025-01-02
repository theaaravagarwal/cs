import numpy

def algorithm(a, t):
    L, R = 0, len(a)-1
    ans = -1
    while L <= R:
        m = L + (R - L)//2
        if a[m] >= t:
            ans = m
            R = m-1
        else:
            L = m+1
    return ans

arr = numpy.random.randint(0,1000,1000)
print(arr)
index = algorithm(arr, 15)
print(index)
print(arr[index])
arr.sort()
print(arr)
index = algorithm(arr, 15)
print(index)
print(arr[index])