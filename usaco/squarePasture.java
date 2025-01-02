import java.io.IOException;

public class squarePasture {
    // solve
    public static int calculateArea(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
        return Math.max(Math.max(x2, x4) - Math.min(x1, x3), 0) * Math.max(Math.max(x2, x4) - Math.min(x1, x3), 0);
    }

    public static void main(String[] args) throws IOException {
        // tests
        System.out.println(calculateArea(1, 1, 3, 3, 2, 2, 4, 4)); // Expected output: 9
        System.out.println(calculateArea(1, 1, 2, 2, 3, 3, 4, 4)); // Expected output: 9
        System.out.println(calculateArea(1, 1, 2, 2, 2, 1, 3, 2)); // Expected output: 4
        System.out.println(calculateArea(1, 1, 5, 5, 2, 2, 3, 3)); // Expected output: 16
        System.out.println(calculateArea(1, 1, 2, 2, 1, 1, 2, 2)); // Expected output: 1
        System.out.println(calculateArea(100, 100, 200, 200, 150, 150, 250, 250)); // Expected output: 22500

        // more tests cuz i was bored
        System.out.println(calculateArea(0, 0, 1, 1, 1, 1, 2, 2)); // Expected output: 0
        System.out.println(calculateArea(0, 0, 2, 2, 1, 1, 3, 3)); // Expected output: 4
        System.out.println(calculateArea(-1, -1, 1, 1, 0, 0, 2, 2)); // Expected output: 4
        System.out.println(calculateArea(0, 0, 5, 5, 5, 5, 10, 10)); // Expected output: 25
        System.out.println(calculateArea(1, 1, 3, 3, 1, 1, 3, 3)); // Expected output: 4
        System.out.println(calculateArea(1, 1, 4, 4, 2, 2, 3, 3)); // Expected output: 9
        System.out.println(calculateArea(10, 10, 20, 20, 15, 15, 25, 25)); // Expected output: 75
        System.out.println(calculateArea(0, 0, 0, 0, 0, 0, 0, 0)); // Expected output: 0
        System.out.println(calculateArea(1, 1, 2, 2, 1, 2, 2, 3)); // Expected output: 1
        System.out.println(calculateArea(1, 1, 3, 3, 0, 0, 4, 4)); // Expected output: 16
        System.out.println(calculateArea(5, 5, 10, 10, 6, 6, 8, 8)); // Expected output: 9
        System.out.println(calculateArea(0, 0, 10, 10, 5, 5, 15, 15)); // Expected output: 50
        System.out.println(calculateArea(1, 1, 10, 10, 10, 10, 20, 20)); // Expected output: 81
        System.out.println(calculateArea(1, 1, 2, 2, 3, 3, 4, 4)); // Expected output: 0
        System.out.println(calculateArea(1, 1, 5, 5, 1, 1, 5, 5)); // Expected output: 16
        System.out.println(calculateArea(0, 0, 100, 100, 50, 50, 150, 150)); // Expected output: 2500
        System.out.println(calculateArea(-10, -10, 10, 10, -5, -5, 5, 5)); // Expected output: 400
        System.out.println(calculateArea(1000, 1000, 2000, 2000, 1500, 1500, 2500, 2500)); // Expected output: 2250000
        System.out.println(calculateArea(0, 0, 0, 0, 0, 0, 0, 0)); // Expected output: 0
        System.out.println(calculateArea(1, 1, 2, 2, 1, 1, 2, 2)); // Expected output: 1
        System.out.println(calculateArea(1, 1, 3, 3, 2, 2, 4, 4)); // Expected output: 9
        System.out.println(calculateArea(1, 1, 2, 2, 3, 3, 4, 4)); // Expected output: 9
        System.out.println(calculateArea(1, 1, 2, 2, 2, 1, 3, 2)); // Expected output: 4
        System.out.println(calculateArea(1, 1, 5, 5, 2, 2, 3, 3)); // Expected output: 16
        System.out.println(calculateArea(1, 1, 2, 2, 1, 1, 2, 2)); // Expected output: 1
        System.out.println(calculateArea(100, 100, 200, 200, 150, 150, 250, 250)); // Expected output: 22500
    }
}