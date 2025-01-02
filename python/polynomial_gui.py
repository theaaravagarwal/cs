import re
import subprocess
import sys
import tkinter as tk
from tkinter import messagebox, ttk

# Install sympy if it's not installed
try:
    from sympy import symbols, solve, factor, S, sympify
except ImportError:
    subprocess.check_call([sys.executable, "-m", "pip", "install", "sympy"])
    from sympy import symbols, solve, factor, S, sympify

# Preprocessing the input polynomial expression
def preprocess(expr):
    expr = expr.replace('^', '**')
    expr = re.sub(r'(\d)([a-zA-Z])', r'\1*\2', expr)
    expr = re.sub(r'([a-zA-Z])(\()', r'\1*\2', expr)
    return expr

# Filtering the roots based on user selection
def filter_roots(roots, ftype):
    return [
        r for r in roots if (
            (ftype == "real" and r.is_real) or 
            (ftype == "irrational" and r.is_real and not r.is_rational) or 
            (ftype == "complex" and not r.is_real) or 
            (ftype == "all")
        )
    ]

# Parsing and sympifying the input expression
def parse(expr):
    x = symbols('x')
    expr = preprocess(expr)
    try:
        return sympify(expr, locals={"x": x})
    except Exception as e:
        messagebox.showerror("Error", f"Invalid polynomial: {e}")
        return None

# Handling the factorization and root-solving logic
def factor_and_solve():
    expr = entry_expr.get().strip()
    poly = parse(expr)

    if poly is None:
        return  # Stop if the polynomial is invalid

    # Display factored form
    factored = factor(poly)
    output_factored.set(f"Factored form: {factored}")

    # Solve for roots and display
    roots = solve(poly, domain=S.Complexes)
    all_roots.set(f"All Roots: {roots}")

    # Apply root filtering based on dropdown selection
    update_filtered_roots(roots)

def update_filtered_roots(roots):
    ftype = filter_var.get().lower()
    filtered = filter_roots(roots, ftype)
    filtered_roots.set(f"{ftype.capitalize()} Roots: {filtered}")

# GUI Setup
root = tk.Tk()
root.title("Polynomial Factorizer and Solver")
root.geometry("600x400")
root.configure(bg="#1e1e2e")

# Style Configuration
style = ttk.Style()
style.theme_use("clam")
style.configure("TLabel", foreground="white", background="#1e1e2e", font=("Helvetica", 12))
style.configure("TEntry", fieldbackground="#2e2e3e", foreground="white")
style.configure("TButton", background="#4e4e6e", foreground="white")

# Polynomial Input Section
ttk.Label(root, text="Enter a polynomial:").grid(row=0, column=0, padx=10, pady=10, sticky="w")
entry_expr = ttk.Entry(root, width=40)
entry_expr.grid(row=0, column=1, padx=10, pady=10)

# Button to factorize and solve
ttk.Button(root, text="Factor & Solve", command=factor_and_solve).grid(row=1, column=1, pady=10)

# Factored Form Output
output_factored = tk.StringVar()
ttk.Label(root, textvariable=output_factored).grid(row=2, column=0, columnspan=2, padx=10, pady=5)

# All Roots Output
all_roots = tk.StringVar()
ttk.Label(root, textvariable=all_roots).grid(row=3, column=0, columnspan=2, padx=10, pady=5)

# Root Filtering Section
ttk.Label(root, text="Filter roots:").grid(row=4, column=0, padx=10, pady=10, sticky="w")
filter_var = ttk.Combobox(root, values=["All", "Real", "Irrational", "Complex"])
filter_var.current(0)  # Default to "All"
filter_var.grid(row=4, column=1, padx=10, pady=10)
filter_var.bind("<<ComboboxSelected>>", lambda e: update_filtered_roots(solve(parse(entry_expr.get()), domain=S.Complexes)))

# Filtered Roots Output
filtered_roots = tk.StringVar()
ttk.Label(root, textvariable=filtered_roots).grid(row=5, column=0, columnspan=2, padx=10, pady=5)

# Exit Button
ttk.Button(root, text="Exit", command=root.quit).grid(row=6, column=1, pady=10)

# Run the GUI loop
root.mainloop()