import java.io.*;
import java.util.concurrent.ThreadLocalRandom;

public class Main { 
    public static void main(String[] args) throws IOException, InterruptedException {
        int r = 255, g = 0, b = 0, step = 45;
        int min = 32, max = 126;
        long delay = 40;
        Integer line_len = 143;
        String original = "\u001B[0m";
        char x = (char) ThreadLocalRandom.current().nextInt(min, max + 1);
        for (int i = 0; i > -1; i++) {
            String color = String.format("\u001B[38;2;%d;%d;%dm", r, g, b);
            System.out.print(color + x + original);
            x = (char) ThreadLocalRandom.current().nextInt(min, max + 1);
            if (r == 255 && g < 255 && b == 0) {
                g = Math.min(g + step, 255);
            } else if (g == 255 && r > 0 && b == 0) {
                r = Math.max(r - step, 0);
            } else if (g == 255 && b < 255 && r == 0) {
                b = Math.min(b + step, 255);
            } else if (b == 255 && g > 0 && r == 0) {
                g = Math.max(g - step, 0);
            } else if (b == 255 && r < 255 && g == 0) {
                r = Math.min(r + step, 255);
            } else if (r == 255 && b > 0 && g == 0) {
                b = Math.max(b - step, 0);
            }
            if (line_len != null) {
                if (i % line_len == 0 && i != 0) {
                    System.out.print("\n");
                    Thread.sleep(delay);
                }
            }
        }
    }
}
