import math, sys
d = eval(str(sys.stdin.readline())) #sensor size
b = eval(str(sys.stdin.readline())) #fov of camera
rad = math.radians(b); #fov of camera in rad
exp = d/(2*math.tan(rad/2)); #math to find focal length
print(f"sensor size in mm: {d} \nfov in degrees: {b} \nfocal length of camera: {round(exp, 3)}"); #nice output :)
#printf can beat my meat consistently for 100 years and i will bust 2 billion times every day