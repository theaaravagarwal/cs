from cmath import sqrt
import numpy as np
from scipy.optimize import newton

def f(n):
    n = abs(int(n))
    r = set()
    for i in range(1, n + 1):
        if n % i == 0:
            r.add(i)
            r.add(-i)
    return sorted(r)

def eval_poly(c, x):
    return sum(coef * (x ** i) for i, coef in enumerate(reversed(c)))

def syn_div(div, root):
    r = [div[0]]
    for i in range(1, len(div)):
        r.append(div[i] + r[-1] * root)
    return r[:-1]

def rat_roots(c):
    p = f(c[-1])
    q = f(c[0])
    return sorted({i / j for i in p for j in q}.union({-i / j for i in p for j in q}))

def quad_solve(c):
    a, b, c = c
    d = b**2 - 4 * a * c
    if d > 0:
        return [(-b + sqrt(d)) / (2 * a), (-b - sqrt(d)) / (2 * a)]
    elif d == 0:
        return [-b / (2 * a)]
    rp = -b / (2 * a)
    ip = sqrt(abs(d)) / (2 * a)
    return [complex(rp, ip), complex(rp, -ip)]

def fmt_complex(c):
    r, i = c.real, c.imag
    if r == 0:
        return f"{i}i" if i not in (1, -1) else ("i" if i == 1 else "-i")
    if i == 0:
        return f"{r}"
    ip = f"+ {i}i" if i > 0 else f"- {-i}i"
    return f"({r} {ip})"

def approximate_root(c):
    def poly_func(x):
        return eval_poly(c, x)
    
    roots = []
    for guess in np.linspace(-10, 10, 100):
        try:
            root = newton(poly_func, guess)
            if all(abs(root - r) > 1e-5 for r in roots):
                roots.append(root)
        except RuntimeError:
            continue
    return roots

def factor_poly(c):
    r = []
    while len(c) > 1 and c[-1] == 0:
        r.append(0)
        c.pop()
    if all(coef == 0 for coef in c):
        return r, fmt_factored_form(r, c)
    if c[-1] == 0:
        r.append(0)
        c = syn_div(c, 0)
    roots_found = True
    while roots_found:
        roots_found = False
        p_roots = rat_roots(c)
        for root in p_roots:
            if eval_poly(c, root) == 0:
                r.append(root)
                c = syn_div(c, root)
                roots_found = True
                break
    if not roots_found:
        r.extend(approximate_root(c))
    if len(c) == 3:
        r.extend(quad_solve(c))
    elif len(c) == 2:
        r.append(-c[1] / c[0])
    return r, fmt_factored_form(r, c)

def fmt_factored_form(roots, c):
    terms = []
    for r in roots:
        if isinstance(r, complex):
            frmt_root = fmt_complex(r)
            terms.append(f"(x - {frmt_root})")
        else:
            terms.append(f"(x - {r})" if r > 0 else f"(x + {-r})")
    leading = c[0]
    return f"{leading} * " + " * ".join(terms)

def parse_poly(s):
    s = s.replace("-", "+-")
    terms = s.split("+")
    c = []
    for term in terms:
        term = term.strip()
        if "x^" in term:
            coef, degree = term.split("x^")
            coef = int(coef) if coef not in ("", "-") else (-1 if coef == "-" else 1)
            degree = int(degree)
        elif "x" in term:
            coef = int(term.replace("x", "")) if term.replace("x", "") not in ("", "-") else (-1 if term.replace("x", "") == "-" else 1)
            degree = 1
        else:
            coef = int(term)
            degree = 0
        while len(c) <= degree:
            c.append(0)
        c[degree] = coef
    return list(reversed(c))

def main():
    print("Welcome to the polynomial factoring tool!")
    while True:
        poly = input("\nEnter a polynomial (e.g., 2x^2+3x+1) or type 'exit' to quit: ").strip()
        if poly.lower() == 'exit':
            print("Goodbye!")
            break
        try:
            c = parse_poly(poly)
            roots, factored = factor_poly(c)
            if roots:
                formatted_roots = [fmt_complex(r) if isinstance(r, complex) else r for r in roots]
                print(f"\nThe roots of the polynomial {poly} are: {formatted_roots}")
                print(f"The factored form of the polynomial is: {factored}")
            else:
                print(f"\nNo rational roots found for the polynomial {poly}.")
        except Exception as e:
            print(f"Error processing the polynomial: {e}")

main()