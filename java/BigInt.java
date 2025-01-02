public class BigInt {
    private int[] digits; // Array to store digits
    private int size; // Number of digits

    public BigInt(String number) {
        size = number.length();
        digits = new int[size];

        for (int i = 0; i < size; i++) {
            digits[i] = Character.getNumericValue(number.charAt(i));
        }
    }

    // Method to add two BigInt numbers
    public BigInt add(BigInt other) {
        int maxSize = Math.max(this.size, other.size);
        int[] resultDigits = new int[maxSize + 1]; // One extra for carry
        int carry = 0;

        for (int i = 0; i < maxSize; i++) {
            int digit1 = (i < this.size) ? this.digits[this.size - 1 - i] : 0;
            int digit2 = (i < other.size) ? other.digits[other.size - 1 - i] : 0;

            int sum = digit1 + digit2 + carry;
            resultDigits[maxSize - i] = sum % 10; // Store the digit
            carry = sum / 10; // Calculate carry
        }
        resultDigits[0] = carry; // Store the final carry if it exists

        // Determine the actual size of the result
        int actualSize = (resultDigits[0] == 0) ? maxSize : maxSize + 1;
        BigInt result = new BigInt("");
        result.digits = new int[actualSize];
        result.size = actualSize;

        System.arraycopy(resultDigits, 0, result.digits, 0, actualSize);
        return result;
    }

    // Method to print the BigInt
    public void print() {
        for (int i = 0; i < size; i++) {
            System.out.print(digits[i]);
        }
        System.out.println();
    }

    public static void main(String[] args) {
        BigInt num1 = new BigInt("999999999999999999999999999999");
        BigInt num2 = new BigInt("1");
        BigInt sum = num1.add(num2);

        sum.print(); // Outputs: 1000000000000000000000000000000
    }
}
