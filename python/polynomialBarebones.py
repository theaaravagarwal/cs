from cmath import sqrt
from fractions import Fraction
import math

def get_factors(n):
    """Return a set of factors of the integer n."""
    if n == 0:
        return {1, -1}
    n = abs(n)
    factors = {i for i in range(1, n + 1) if n % i == 0}
    return factors | {-i for i in factors}

def evaluate_polynomial(coeffs, x):
    """Evaluate polynomial with given coefficients at x."""
    return sum(coef * (x ** i) for i, coef in enumerate(reversed(coeffs)))

def synthetic_division(dividend, root):
    """Perform synthetic division."""
    result = [dividend[0]]
    for coeff in dividend[1:]:
        result.append(coeff + result[-1] * root)
    return result[:-1]

def rational_root_candidates(coeffs):
    """Generate possible rational roots based on the Rational Root Theorem."""
    if coeffs[-1] == 0:
        return {0}
    p_factors = get_factors(abs(int(coeffs[-1])))
    q_factors = get_factors(abs(int(coeffs[0])))
    return {Fraction(p, q) for p in p_factors for q in q_factors if q != 0}

def quadratic_solver(a, b, c):
    """Return the roots of a quadratic equation."""
    discriminant = b ** 2 - 4 * a * c
    if discriminant > 0:
        return [(-b + sqrt(discriminant)) / (2 * a), (-b - sqrt(discriminant)) / (2 * a)]
    elif discriminant == 0:
        return [-b / (2 * a)]
    else:
        real_part = -b / (2 * a)
        imaginary_part = sqrt(-discriminant) / (2 * a)
        return [complex(real_part, imaginary_part), complex(real_part, -imaginary_part)]

def format_complex(c):
    """Format complex numbers into a readable string."""
    real = c.real
    imag = c.imag
    if imag == 0:
        return f"{real}"
    elif real == 0:
        return f"{'+' if imag > 0 else ''}{imag}i"
    else:
        return f"{real}{'+' if imag > 0 else ''}{imag}i"

def format_fraction(num):
    """Format a Fraction or integer as a string."""
    if isinstance(num, Fraction):
        return f"{num.numerator}/{num.denominator}" if num.denominator != 1 else str(num.numerator)
    return str(num)

def is_irrational_sqrt(value):
    """Check if the value is close to an irrational square root."""
    if value == 0:
        return False
    sqrt_approx = math.sqrt(abs(value))
    sqrt_floor = math.floor(sqrt_approx)
    if math.isclose(sqrt_approx, sqrt_floor):
        return False
    return True

def format_sqrt_if_applicable(value):
    if value == 0:
        return '0'
    abs_value = abs(value)
    sqrt_value = math.sqrt(abs_value)
    if sqrt_value.is_integer():
        return f"√{int(sqrt_value ** 2)}" if value > 0 else f"-√{int(sqrt_value ** 2)}"
    if math.isclose(abs_value, math.sqrt(2), rel_tol=1e-9):
        return f"√2" if value > 0 else f"-√2"
    if math.isclose(abs_value, math.sqrt(3), rel_tol=1e-9):
        return f"√3" if value > 0 else f"-√3"
    return str(value)

def simplify_decimal_root(root):
    real_part = root.real
    imag_part = root.imag
    simplified_real = format_sqrt_if_applicable(real_part)
    simplified_imag = format_sqrt_if_applicable(imag_part) if imag_part != 0 else ''
    if real_part == 0:
        return f"{simplified_imag}i" if simplified_imag else '0'
    if imag_part == 0:
        return simplified_real
    else:
        return f"{simplified_real}{'+' if imag_part > 0 else ''}{simplified_imag}i"

def factor_polynomial(coeffs):
    """Factor the polynomial represented by the coefficients."""
    roots = []
    while len(coeffs) > 1 and coeffs[-1] == 0:
        roots.append(0)
        coeffs.pop()
    found_root = True
    while found_root:
        found_root = False
        for root in rational_root_candidates(coeffs):
            if evaluate_polynomial(coeffs, float(root)) == 0:
                roots.append(root)
                coeffs = synthetic_division(coeffs, root)
                found_root = True
                break
    if len(coeffs) == 3:
        roots.extend(quadratic_solver(coeffs[0], coeffs[1], coeffs[2]))
    elif len(coeffs) == 2:
        roots.append(-coeffs[1] / coeffs[0])
    return roots, format_factored_form(roots, coeffs)

def format_factored_form(roots, coeffs):
    """Format the polynomial in its factored form."""
    terms = []
    leading_coefficient = coeffs[0]
    for r in roots:
        if isinstance(r, complex):
            simplified_root = simplify_decimal_root(r)
            terms.append(f"(x - {simplified_root})")
        else:
            formatted_root = format_fraction(r) if r != 0 else '0'
            terms.append(f"(x - {formatted_root})" if r > 0 else f"(x + {format_fraction(-r)})")
    return f"{leading_coefficient} * " + " * ".join(terms)

def parse_polynomial(s):
    """Parse polynomial string into coefficients."""
    s = s.replace(" ", "").replace("-", "+-")
    terms = s.split("+")
    coeffs = []
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
        while len(coeffs) <= degree:
            coeffs.append(0)
        coeffs[degree] = coef
    return list(reversed(coeffs))

def main():
    print("Welcome to the polynomial factoring tool!")
    while True:
        poly = input("\nEnter a polynomial (e.g., 2x^2+3x+1) or type 'exit' to quit: ").strip()
        if poly.lower() == 'exit':
            print("Exiting...")
            break
        try:
            coeffs = parse_polynomial(poly)
            roots, factored_form = factor_polynomial(coeffs)
            if roots:
                formatted_roots = [simplify_decimal_root(r) if isinstance(r, complex) else format_fraction(r) for r in roots]
                print(f"\nThe roots of the polynomial {poly} are: {formatted_roots}")
                print(f"The factored form of the polynomial is: {factored_form}")
            else:
                print(f"\nNo rational roots found for the polynomial {poly}.")
        except Exception as e:
            print(f"Error processing the polynomial: {e}")

main()