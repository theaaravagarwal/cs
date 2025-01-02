import math, cmath, sys
g = 9.81;

def calculate_force(mass, acceleration):
    """Calculate force using F = m * a"""
    return round(mass * acceleration, 3)

def calculate_energy(mass, velocity):
    """Calculate kinetic energy using KE = 0.5 * m * v^2"""
    return round(0.5 * mass * velocity ** 2, 3)

def calculate_velocity(distance, time):
    """Calculate velocity using v = d / t"""
    return round(distance / time, 3)

def calculate_incline_forces(mass, angle, coefficient_of_friction):
    """Calculate forces on an incline"""

    fg = mass * g  # gravitational force
    fgx = fg * math.sin(math.radians(angle))  # force parallel to incline
    fgy = fg * math.cos(math.radians(angle))  # force perpendicular to incline
    frictional_force = coefficient_of_friction * fgy  # frictional force

    return round(fg, 3), round(fgx, 3), round(fgy, 3), round(frictional_force, 3)

def calculate_fgy(mass, angle):
    """Calculate force perpendicular to incline (fgy)"""

    fg = mass * g  # gravitational force
    fgy = fg * math.cos(math.radians(angle))  # force perpendicular to incline
    return round(fgy, 3)

def calculate_fgx(mass, angle):
    """Calculate force perpendicular to incline (fgy)"""

    fg = mass * g  # gravitational force
    fgx = fg * math.sin(math.radians(angle))  # force perpendicular to incline
    return round(fgx, 3)

def calculate_coefficient_of_friction(fgx, fgy):
    """Calculate coefficient of friction using fgx = mu * fgy"""
    if fgy == 0:  # Prevent division by zero
        return None  # or raise an exception
    coefficient_of_friction = round(fgx / fgy, 3)
    return round(coefficient_of_friction, 3)

def calculate_average(values):
    """Calculate the average of a list of values"""
    if not values:  # Check if the list is empty
        return None
    return sum(values) / len(values)  # Return the average without rounding

def calculate_percentage_error(experimental_value, theoretical_value):
    """Calculate the percentage of error"""
    if theoretical_value == 0:  # Prevent division by zero
        return None  # or raise an exception
    return round(abs(theoretical_value - experimental_value) / theoretical_value * 100, 3)

def calculate_electric_force(charge1, charge2, distance):
    """Calculate electric force using Coulomb's Law: F = k * |q1 * q2| / r^2"""
    k = 8.99e9  # Coulomb's constant in N m²/C²
    if distance == 0:  # Prevent division by zero
        return None  # or raise an exception
    return round(k * abs(charge1 * charge2) / distance ** 2, 3)

def calculate_electric_field(charge, distance):
    """Calculate electric field using E = k * |q| / r^2"""
    k = 8.99e9  # Coulomb's constant in N m²/C²
    if distance == 0:  # Prevent division by zero
        return None  # or raise an exception
    return round(k * abs(charge) / distance ** 2, 3)

def calculate_potential_energy(charge1, charge2, distance):
    """Calculate potential energy using U = k * q1 * q2 / r"""
    k = 8.99e9  # Coulomb's constant in N m²/C²
    if distance == 0:  # Prevent division by zero
        return None  # or raise an exception
    return round(k * charge1 * charge2 / distance, 3)

def calculate_work(force, distance):
    """Calculate work done using W = F * d * cos(theta)"""
    return round(force * distance, 3)  # Assuming force and distance are in the same direction

def calculate_power(work, time):
    """Calculate power using P = W / t"""
    if time == 0:  # Prevent division by zero
        return None  # or raise an exception
    return round(work / time, 3)

def calculate_momentum(mass, velocity):
    """Calculate momentum using p = m * v"""
    return round(mass * velocity, 3)

def calculate_impulse(force, time):
    """Calculate impulse using J = F * t"""
    return round(force * time, 3)

def calculate_time_of_flight(initial_velocity, angle):
    """Calculate time of flight for projectile motion"""
    return (2 * initial_velocity * math.sin(math.radians(angle))) / g  # Total time of flight

def calculate_projectile_motion(initial_velocity, angle):
    """Calculate the horizontal and vertical displacement of a projectile and final velocities"""
    time = calculate_time_of_flight(initial_velocity, angle)  # Calculate time of flight
    horizontal_displacement = round(initial_velocity * math.cos(math.radians(angle)) * time, 3)
    vertical_displacement = round((initial_velocity * math.sin(math.radians(angle)) * time) - (0.5 * g * time ** 2), 3)
    
    # Final velocities
    final_velocity_horizontal = round(initial_velocity * math.cos(math.radians(angle)), 3)
    final_velocity_vertical = round(initial_velocity * math.sin(math.radians(angle)) - g * time, 3)
    overall_final_velocity = round(math.sqrt(final_velocity_horizontal**2 + final_velocity_vertical**2), 3)

    return horizontal_displacement, vertical_displacement, final_velocity_horizontal, final_velocity_vertical, overall_final_velocity, time  # Return time as well

def calculate_final_velocity(initial_velocity, acceleration, time):
    """Calculate final velocity using v = u + at"""
    return round(initial_velocity + acceleration * time, 3)

def calculate_displacement_with_time(initial_velocity, time, acceleration):
    """Calculate displacement using s = ut + 0.5at^2"""
    return round(initial_velocity * time + 0.5 * acceleration * time ** 2, 3)

def calculate_final_velocity_squared(initial_velocity, acceleration, displacement):
    """Calculate final velocity using v^2 = u^2 + 2as"""
    return round(math.sqrt(initial_velocity ** 2 + 2 * acceleration * displacement), 3)

def calculate_displacement_with_average_velocity(initial_velocity, final_velocity, time):
    """Calculate displacement using s = (u + v)/2 * t"""
    return round((initial_velocity + final_velocity) / 2 * time, 3)

def main():
    print("Physics Calculator")
    print("1. Calculate Force (F = m * a)")
    print("2. Calculate Kinetic Energy (KE = 0.5 * m * v^2)")
    print("3. Calculate Velocity (v = d / t)")
    print("4. Calculate Forces on Incline")
    print("5. Calculate Average of Values")
    print("6. Calculate Percentage of Error")
    print("7. Calculate Electric Force (Coulomb's Law)")
    print("8. Calculate Electric Field")
    print("9. Calculate Potential Energy")
    print("10. Calculate Work Done (W = F * d)")
    print("11. Calculate Power (P = W / t)")
    print("12. Calculate Momentum (p = m * v)")
    print("13. Calculate Impulse (J = F * t)")
    print("14. Calculate Projectile Motion")
    print("15. Kinematic Equations")
    print("  1. Calculate Final Velocity (v = u + at)")
    print("  2. Calculate Displacement (s = ut + 0.5at^2)")
    print("  3. Calculate Final Velocity Squared (v^2 = u^2 + 2as)")
    print("  4. Calculate Displacement with Average Velocity (s = (u + v)/2 * t)")
    
    choice = input("Select an option (1-15): ")
    
    if choice == '1':
        mass = float(input("Enter mass (kg): "))
        acceleration = float(input("Enter acceleration (m/s^2): "))
        force = calculate_force(mass, acceleration)
        print(f"Force: {round(force, 3)} N")
    
    elif choice == '2':
        mass = float(input("Enter mass (kg): "))
        velocity = float(input("Enter velocity (m/s): "))
        energy = calculate_energy(mass, velocity)
        print(f"Kinetic Energy: {round(energy, 3)} J")
    
    elif choice == '3':
        distance = float(input("Enter distance (m): "))
        time = float(input("Enter time (s): "))
        velocity = calculate_velocity(distance, time)
        print(f"Velocity: {round(velocity, 3)} m/s")
    
    elif choice == '4':
        mass = float(input("Enter mass (kg): "))
        angle = float(input("Enter angle (degrees): "))
        fgy = calculate_fgy(mass, angle)  # Calculate fgy
        fgx = calculate_fgx(mass, angle)  # Calculate fgx
        frictional_force = fgx  # Assume fgx is the frictional force
        coefficient_of_friction = calculate_coefficient_of_friction(fgx, fgy)  # Calculate coefficient of friction
        print(f"Force parallel to incline (fgx): {round(fgx, 3)} N")
        print(f"Force perpendicular to incline (fgy): {round(fgy, 3)} N")
        print(f"Frictional Force: {round(frictional_force, 3)} N")
        print(f"Coefficient of Friction: {round(coefficient_of_friction, 3)}")
    
    elif choice == '5':
        values = input("Enter values separated by commas: ")
        values_list = [float(value.replace(',', '.')) for value in values.split(',')]
        average = calculate_average(values_list)
        print(f"Average: {round(average, 3)}")
    
    elif choice == '6':
        experimental_value = eval(str(input("Enter experimental value: ")))
        theoretical_value = eval(str(input("Enter theoretical value: ")))
        percentage_error = calculate_percentage_error(experimental_value, theoretical_value)
        print(f"Percentage of Error: {percentage_error}%")
    
    elif choice == '7':
        charge1 = float(input("Enter charge 1 (C): "))
        charge2 = float(input("Enter charge 2 (C): "))
        distance = float(input("Enter distance between charges (m): "))
        electric_force = calculate_electric_force(charge1, charge2, distance)
        print(f"Electric Force: {electric_force} N")
    
    elif choice == '8':
        charge = float(input("Enter charge (C): "))
        distance = float(input("Enter distance from charge (m): "))
        electric_field = calculate_electric_field(charge, distance)
        print(f"Electric Field: {electric_field} N/C")
    
    elif choice == '9':
        charge1 = float(input("Enter charge 1 (C): "))
        charge2 = float(input("Enter charge 2 (C): "))
        distance = float(input("Enter distance between charges (m): "))
        potential_energy = calculate_potential_energy(charge1, charge2, distance)
        print(f"Potential Energy: {potential_energy} J")
    
    elif choice == '10':
        force = float(input("Enter force (N): "))
        distance = float(input("Enter distance (m): "))
        work = calculate_work(force, distance)
        print(f"Work Done: {round(work, 3)} J")
    
    elif choice == '11':
        work = float(input("Enter work (J): "))
        time = float(input("Enter time (s): "))
        power = calculate_power(work, time)
        print(f"Power: {round(power, 3)} W")
    
    elif choice == '12':
        mass = float(input("Enter mass (kg): "))
        velocity = float(input("Enter velocity (m/s): "))
        momentum = calculate_momentum(mass, velocity)
        print(f"Momentum: {round(momentum, 3)} kg m/s")
    
    elif choice == '13':
        force = float(input("Enter force (N): "))
        time = float(input("Enter time (s): "))
        impulse = calculate_impulse(force, time)
        print(f"Impulse: {round(impulse, 3)} Ns")
    
    elif choice == '14':
        initial_velocity = float(input("Enter initial velocity (m/s): "))
        angle = float(input("Enter angle (degrees): "))
        horizontal_displacement, vertical_displacement, vf_horizontal, vf_vertical, vf_overall, time_of_flight = calculate_projectile_motion(initial_velocity, angle)
        print(f"Horizontal Displacement: {horizontal_displacement} m")
        print(f"Vertical Displacement: {vertical_displacement} m")
        print(f"Final Velocity Horizontal: {vf_horizontal} m/s")
        print(f"Final Velocity Vertical: {vf_vertical} m/s")
        print(f"Overall Final Velocity: {vf_overall} m/s")
        print(f"Time of Flight: {round(time_of_flight, 3)} s")  # Print the time of flight
    
    elif choice == '15':
        kinematic_choice = input("Select a kinematic equation (1-4): ")
        
        if kinematic_choice == '1':
            initial_velocity = float(input("Enter initial velocity (u) (m/s): "))
            acceleration = float(input("Enter acceleration (a) (m/s^2): "))
            time = float(input("Enter time (t) (s): "))
            final_velocity = calculate_final_velocity(initial_velocity, acceleration, time)
            print(f"Final Velocity: {final_velocity} m/s")
        
        elif kinematic_choice == '2':
            initial_velocity = float(input("Enter initial velocity (u) (m/s): "))
            time = float(input("Enter time (t) (s): "))
            acceleration = float(input("Enter acceleration (a) (m/s^2): "))
            displacement = calculate_displacement_with_time(initial_velocity, time, acceleration)
            print(f"Displacement: {displacement} m")
        
        elif kinematic_choice == '3':
            initial_velocity = float(input("Enter initial velocity (u) (m/s): "))
            acceleration = float(input("Enter acceleration (a) (m/s^2): "))
            displacement = float(input("Enter displacement (s) (m): "))
            final_velocity = calculate_final_velocity_squared(initial_velocity, acceleration, displacement)
            print(f"Final Velocity Squared: {final_velocity} m/s")
        
        elif kinematic_choice == '4':
            initial_velocity = float(input("Enter initial velocity (u) (m/s): "))
            final_velocity = float(input("Enter final velocity (v) (m/s): "))
            time = float(input("Enter time (t) (s): "))
            displacement = calculate_displacement_with_average_velocity(initial_velocity, final_velocity, time)
            print(f"Displacement with Average Velocity: {displacement} m")
    
    else:
        print("Invalid option selected.")

if __name__ == "__main__":
    main()