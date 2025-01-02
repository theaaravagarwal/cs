import numpy as np
from scipy.integrate import quad
import matplotlib.pyplot as plt

# Function to integrate
def f(x):
    # Check if the user input is 'bell' and define a bell curve function
    if function_input.lower() == 'bell':
        return (1 / np.sqrt(2 * np.pi)) * np.exp(-0.85*x**2)  # Standard normal distribution (bell curve)
    try:
        # Ensure numpy functions are used in the evaluated expression
        return eval(function_input, {"__builtins__": None}, {"x": x, "np": np})
    except Exception as e:
        print(f"Error evaluating the function: {e}")
        return np.zeros_like(x)  # Return an array of zeros in case of error

# Get the function from the user
function_input = input("Enter the function of x (e.g., 'x**2'): ")
a = float(input("Enter lower limit of integration: "))
b = float(input("Enter upper limit of integration: "))

# Calculate the area under the curve
area, error = quad(f, a, b)

print(f"The area under the curve from {a} to {b} is: {area}")

# Optional: Plot the function and the area under the curve
x_full = np.linspace(a - 1, b + 1, 400)  # Generate x values slightly beyond the integration limits
y_full = f(x_full)  # Calculate the corresponding y values

plt.figure(figsize=(10, 6))  # Set a fixed figure size

# Set x-axis limits based on the lower and upper limits of integration
plt.xlim(a - 1, b + 1)  # Adjust x-axis limits to be slightly beyond the integration limits

# Set y-axis limits based on the calculated function values
plt.ylim(min(y_full) - 1, max(y_full) + 1)  # Set y-axis limits based on function values

# Plot the function
plt.plot(x_full, y_full, label='y = ' + function_input, color='blue', linewidth=2)  # Plot the function

# Fill the area under the curve
plt.fill_between(x_full, y_full, where=(x_full >= a) & (x_full <= b), alpha=0.3, color='orange', label='Area under curve')  # Highlight area under the curve

# Optional: Adjust aspect ratio for better display
plt.gca().set_aspect('auto', adjustable='box')  # Set aspect ratio to auto for better fitting

plt.title('Area Under the Curve', fontsize=16)  # Increased title font size
plt.xlabel('x', fontsize=14)  # Increased label font size
plt.ylabel('f(x)', fontsize=14)  # Increased label font size
plt.axvline(x=a, color='red', linestyle='--', label='Lower limit', linewidth=1.5)  # Optional: Line for lower limit
plt.axvline(x=b, color='green', linestyle='--', label='Upper limit', linewidth=1.5)  # Optional: Line for upper limit

plt.grid(True)  # Add grid for better readability
plt.legend()
plt.show()