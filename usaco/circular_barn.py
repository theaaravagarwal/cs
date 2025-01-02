import sys
n = int(sys.stdin.readline())
rooms = [int(sys.stdin.readline()) for _ in range(n)]
total_c = sum(rooms)
min_dist = float("inf")
for i in range(n):
	dist = 0
	rem = total_c
	for r in range(n):
		rem -= rooms[(i+r)%n]
		dist += rem
	min_dist = min(min_dist, dist)
print(min_dist)
