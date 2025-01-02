import java.util.*;
public class PolynomialFactorizer {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the degree of the polynomial: ");
        int degree = sc.nextInt();
        int[] coefficients = new int[degree + 1];
        for (int i = degree; i >= 0; i--) {
            System.out.println("Enter the coefficient for x^" + i + ": ");
            coefficients[i] = sc.nextInt();
        }
        System.out.println("Factoring the polynomial: " + polynomialToString(coefficients));
        List<String> factors = factorPolynomial(coefficients);
        System.out.println("Factored form: " + String.join(" * ", factors));
    }
    public static List<String> factorPolynomial(int[] coefficients) {
        List<String> factors = new ArrayList<>();
        List<Double> zeros = new ArrayList<>();
        coefficients = Arrays.copyOf(coefficients, coefficients.length); // Copy to prevent modification issues
        while (true) {
            Map<Double, Integer> rationalRoots = findRationalRootsWithMultiplicity(coefficients);
            if (rationalRoots.isEmpty()) {
                break; // No more rational roots found
            }
            for (Map.Entry<Double, Integer> entry : rationalRoots.entrySet()) {
                double root = entry.getKey();
                int multiplicity = entry.getValue();
                // Add linear factors to the result
                for (int i = 0; i < multiplicity; i++) {
                    factors.add(formatLinearFactor(root));
                    zeros.add(root); // Store the zero
                    coefficients = polynomialLongDivision(coefficients, root);
                }
            }
        }
        // Check for remaining polynomial (quadratic or higher)
        if (coefficients.length == 3) {
            Complex[] complexRoots = findComplexRoots(coefficients[0], coefficients[1], coefficients[2]);
            factors.add(formatComplexFactor(complexRoots[0], complexRoots[1]));
            zeros.add(complexRoots[0].real);
            zeros.add(complexRoots[1].real);
        } else if (coefficients.length > 1) {
            // Output remaining polynomial if it can't be factored further
            factors.add(polynomialToString(coefficients));
        }
        // Output the zeros of the polynomial
        System.out.println("Zeros of the polynomial: " + zeros);
        return factors;
    }
    public static String formatLinearFactor(double root) {
        return root == 0 ? "x" : "(x - " + root + ")";
    }
    public static String formatComplexFactor(Complex root1, Complex root2) {
        return "(x - (" + root1 + ")) * (x - (" + root2 + "))";
    }
    public static int[] polynomialLongDivision(int[] coefficients, double root) {
        int n = coefficients.length;
        int[] newCoefficients = new int[n - 1];
        newCoefficients[0] = coefficients[0];
        for (int i = 1; i < n - 1; i++) {
            newCoefficients[i] = coefficients[i] + (int) (root * newCoefficients[i - 1]);
        }
        int remainder = coefficients[n - 1] + (int) (root * newCoefficients[n - 2]);
        if (remainder != 0) {
            return coefficients; // Return original if division failed
        }
        return newCoefficients;
    }
    public static Map<Double, Integer> findRationalRootsWithMultiplicity(int[] coefficients) {
        Map<Double, Integer> rootsWithMultiplicity = new HashMap<>();
        List<Double> possibleRoots = generatePossibleRoots(coefficients);

        for (double root : possibleRoots) {
            int multiplicity = 0;
            int[] reducedCoefficients = coefficients.clone(); // Work with a copy
            while (reducedCoefficients.length > 1) {
                int[] result = polynomialLongDivision(reducedCoefficients, root);
                if (Arrays.equals(result, reducedCoefficients)) break; // Stop if no further reduction
                reducedCoefficients = result;
                multiplicity++;
            }
            if (multiplicity > 0) {
                rootsWithMultiplicity.put(root, multiplicity);
            }
        }
        return rootsWithMultiplicity;
    }
    public static List<Double> generatePossibleRoots(int[] coefficients) {
        int constantTerm = coefficients[coefficients.length - 1];
        int leadingCoefficient = coefficients[0];
        List<Integer> factorsOfConstant = findFactors(Math.abs(constantTerm));
        List<Integer> factorsOfLeading = findFactors(Math.abs(leadingCoefficient));
        List<Double> possibleRoots = new ArrayList<>();
        for (int p : factorsOfConstant) {
            for (int q : factorsOfLeading) {
                double root = (double) p / q;
                possibleRoots.add(root);
                possibleRoots.add(-root);
            }
        }
        return possibleRoots;
    }
    public static List<Integer> findFactors(int num) {
        List<Integer> factors = new ArrayList<>();
        for (int i = 1; i <= Math.sqrt(num); i++) {
            if (num % i == 0) {
                factors.add(i);
                if (i != num / i) {
                    factors.add(num / i);
                }
            }
        }
        return factors;
    }
    public static Complex[] findComplexRoots(int a, int b, int c) {
        double discriminant = b * b - 4 * a * c;
        Complex root1, root2;
        if (discriminant >= 0) {
            root1 = new Complex((-b + Math.sqrt(discriminant)) / (2 * a), 0);
            root2 = new Complex((-b - Math.sqrt(discriminant)) / (2 * a), 0);
        } else {
            double realPart = -b / (2.0 * a);
            double imaginaryPart = Math.sqrt(-discriminant) / (2.0 * a);
            root1 = new Complex(realPart, imaginaryPart);
            root2 = new Complex(realPart, -imaginaryPart);
        }
        return new Complex[]{root1, root2};
    }
    public static String polynomialToString(int[] coefficients) {
        StringBuilder sb = new StringBuilder();
        for (int i = coefficients.length - 1; i >= 0; i--) {
            if (coefficients[i] != 0) {
                if (sb.length() > 0 && coefficients[i] > 0) sb.append(" + ");
                else if (coefficients[i] < 0) sb.append(" - ");
                if (Math.abs(coefficients[i]) != 1 || i == 0) {
                    sb.append(Math.abs(coefficients[i]));
                }
                if (i > 0) {
                    sb.append("x");
                    if (i > 1) sb.append("^").append(i);
                }
            }
        }
        return sb.toString();
    }
}
// class Complex {
//     double real, imaginary;
//     public Complex(double real, double imaginary) {
//         this.real = real;
//         this.imaginary = imaginary;
//     }
//     @Override
//     public String toString() {
//         return imaginary == 0 ? real + "" : real + " + " + imaginary + "i";
//     }
// }