import sys
import multiprocessing
from sympy import *

def solve_expression(expression, var):
    if isinstance(expression, Eq):
        return solve(expression, var)
    else:
        return None

def simplify_expression(expression):
    return simplify(expression)

def differentiate_expression(expression, var):
    return diff(expression, var)

def integrate_expression(expression, var):
    return integrate(expression, var)

def solve_equation(equ, var_str='x'):
    try:
        var = symbols(var_str)
        if '=' in equ:
            left, right = equ.split('=', 1)
            parsed_expr = Eq(sympify(left), sympify(right))
        else:
            parsed_expr = sympify(equ)

        if isinstance(parsed_expr, Eq):
            result = (solve_expression, (parsed_expr, var))
            return f"Solution: {result}"
        else:
            simplified_result = (simplify_expression, (parsed_expr,))
            derivative_result = (differentiate_expression, (parsed_expr, var))
            integral_result = (integrate_expression, (parsed_expr, var))

            return (
                f"Simplified Expression: {simplified_result}\n"
                f"Derivative: {derivative_result}\n"
                f"Integral: {integral_result}"
            )
    except Exception as e:
        return f"Error: {str(e)}"

equ = str(sys.stdin.readline().strip())
print(solve_equation(equ))