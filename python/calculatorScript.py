import re
from sympy import symbols, solve, factor, S, sympify

def preprocess(expr):
    expr = expr.replace('^', '**')
    expr = expr.replace(' ', '')
    return expr

def parse(expr):
    try:
        expr = preprocess(expr)
        coeffs = []
        terms = re.findall(r'([+-]?\d*x\^\d+|[+-]?\d*x|[+-]?\d+)', expr)
        max_degree = 0

        for term in terms:
            if 'x^' in term:
                coeff, degree = term.split('x^')
                coeff = int(coeff) if coeff not in ('+', '-') else int(coeff + '1')
                degree = int(degree)
                while len(coeffs) <= degree:
                    coeffs.append(0)
                coeffs[degree] = coeff
                max_degree = max(max_degree, degree)
            elif 'x' in term:
                coeff = term[:-1]
                coeff = int(coeff) if coeff not in ('+', '-') else int(coeff + '1')
                while len(coeffs) <= 1:
                    coeffs.append(0)
                coeffs[1] = coeff
                max_degree = max(max_degree, 1)
            else:
                coeff = int(term)
                while len(coeffs) <= 0:
                    coeffs.append(0)
                coeffs[0] = coeff

        while len(coeffs) <= max_degree:
            coeffs.append(0)

        return coeffs
    except Exception as e:
        print(f"Error in parsing expression: {e}")
        return None

def factor_and_solve(expr):
    x = symbols('x')
    try:
        poly = sympify(expr)
        factored = factor(poly)
        roots = solve(poly, domain=S.Complexes)
        return str(factored), roots
    except Exception as e:
        return f"Error in factoring: {e}", []

def filter_roots(roots, ftype):
    if ftype == "real":
        return [r for r in roots if r.is_real]
    elif ftype == "irrational":
        return [r for r in roots if r.is_real and not r.is_rational]
    elif ftype == "complex":
        return [r for r in roots if not r.is_real]
    return roots

def main():
    print("=" * 40)
    print("Polynomial Factorizer and Solver")
    print("=" * 40)

    while True:
        expr = input("Enter a polynomial (e.g., 2x^2 + 3x + 1): ")
        poly = parse(expr)

        if poly is None:
            print("Invalid input. Please try again.\n")
            continue

        factored, roots = factor_and_solve(expr)
        print(f"\nFactored form: {factored}")
        print(f"All Roots: {roots}")

        ftype = input("\nFilter roots (all, real, irrational, complex): ").strip().lower()
        filtered = filter_roots(roots, ftype)
        print(f"{ftype.capitalize()} Roots: {filtered}")

        if input("\nFactor another polynomial? (y/n): ").strip().lower() != 'y':
            print("Goodbye!\n")
            break

main()