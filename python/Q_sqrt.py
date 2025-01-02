import sys, math, cmath, sympy, struct

def Q_sqrt(x):
    threehalfs = 1.5
    x2 = x * 0.5
    y = float(x)
    i = struct.unpack('I', struct.pack('f', y))[0]  # convert float to bits
    i = 0x5f3759df - (i >> 1)  # What the fuck
    y = struct.unpack('f', struct.pack('I', i))[0]  # convert bits back to float
    y = y * (threehalfs - (x2 * y * y))  # newtons iteration
    return y

x = int(sys.stdin.readline());
res = Q_sqrt(x);
print(f"1/sqrt({x}) = {res}");