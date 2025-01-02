import java.util.*;
import java.util.concurrent.*;
import java.util.stream.*;

public class modulos {
    public static void main(String[] args) {
        long tests = 1000000000L;
        ForkJoinPool forkJoinPool = new ForkJoinPool();
        LongSummaryStatistics stats = forkJoinPool.submit(() ->
            IntStream.range(0, (int) tests).parallel().mapToLong(i -> {
                double a = random(0.0, 1000.0);
                double b = random(1.0, 1000.0);
                return modulo(a, b)==a%b?1:0;
            }).summaryStatistics()).join();
        long pass = stats.getSum();
        long fail = tests - pass;
        System.out.println("Pass: " + pass);
        System.out.println("Fail: " + fail);
        double accuracy = (double) pass/tests;
        System.out.println((accuracy * 100) + "% Accuracy");
    }
    // int modulo
    public static int modulo(int a, int b) {
        return a - ((a / b) * b);
    }
    // long modulo
    public static long modulo(long a, long b) {
        return a - ((a / b) * b);
    }
    // double modulo (accurate)
    public static double modulo(double a, double b) {
        if (b == 0) return Double.NaN;
        return a - (b * Math.floor(a / b));
    }
    // random int qol
    public static int random(int a, int b) {
        return ThreadLocalRandom.current().nextInt(a, b + 1);
    }
    // random double qol
    public static double random(double a, double b) {
        return ThreadLocalRandom.current().nextDouble(a, b + 1);
    }
}