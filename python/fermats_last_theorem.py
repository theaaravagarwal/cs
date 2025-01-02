def test_fermat(a_max, b_max, c_max, n_min, n_max):
    for n in range(n_min, n_max + 1):
        if n <= 2:
            continue
        print(f"\nTesting n = {n}...")
        for a in range(1, a_max + 1):
            for b in range(1, b_max + 1):
                for c in range(1, c_max + 1):
                    if a**n + b**n == c**n:
                        print(f"Found a solution: a = {a}, b = {b}, c = {c}, n = {n}")
                        return False
    print("No solutions found, Fermat's Last Theorem holds for the tested range.")
    return True
a_max = int(input("Enter a max value for a: "))
b_max = int(input("Enter a max value for b: "))
c_max = int(input("Enter a max value for c: "))
n_min = int(input("Enter a min value for n: "))
n_max = int(input("Enter a max value for n: "))
test_fermat(a_max, b_max, c_max, n_min, n_max)