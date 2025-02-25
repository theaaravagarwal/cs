import java.util.*;
import java.io.*;
public class shellGame {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[][] sw = new int[n][3];
        for (int i=0; i<n; i++) {
            sw[i][0] = sc.nextInt();
            sw[i][1] = sc.nextInt();
            sw[i][2] = sc.nextInt();
        }
        int ms = 0;
        for (int start=1; start<=3; start++) {
            int cp = start, s = 0;
            for (int i=0; i<n; i++) {
                int a = sw[i][0], b = sw[i][1];
                int g = sw[i][2];
                if (cp==a) cpos = b;
                else if (cp==b) cpos = a;
                if (cp==g) s++;
            }
            ms = Math.max(ms, s);
        }
        System.out.println(ms);
        sc.close();
    }
}
