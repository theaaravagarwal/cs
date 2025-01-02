import java.util.*;

public class TreeOfStars {
    public static final String[] colors = {
        "\u001B[31m", "\u001B[33m", 
        "\u001B[32m", "\u001B[36m", 
        "\u001B[34m", "\u001B[35m"
    };
    public static final String reset = "\u001B[0m";

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("How many rows do you want in the tree? ");
        try {
            makeATree(sc.nextInt());
        } catch (Exception e) {
            System.out.println("Err: " + e);
        }
    }
    public static void makeATree(int n) {
        double startTime, endTime, runtime;
        startTime = System.currentTimeMillis();
        int max = 2 * n - 1, index = 0;
        for (int i = 0; i < n; i++) {
            int space = i, total = 2 * (n - i) - 1;
            for (int j = 0; j < (max - total) / 2; j++) {
                System.out.print(" ");
            }
            for (int k = 0; k < total; k++) {
                if (k % 2 == 0) {
                    System.out.print(colors[index] + "*" + reset);
                    index = (index + 1) % colors.length;
                } else {
                    System.out.print(" ");
                }
            }
            System.out.println();
        }
        endTime = System.currentTimeMillis();
        runtime = (endTime-startTime)/1000;
        System.out.println("runtime" + runtime);
    }
}