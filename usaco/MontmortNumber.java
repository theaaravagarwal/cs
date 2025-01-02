import java.io.*;
import java.util.*;
public class MontmortNumber {
    static FastScanner sc = new FastScanner();
    static PrintWriter out = new PrintWriter(System.out);
    public static void main(String[] args) {
        int n = sc.nextInt(), m = sc.nextInt();
        print(solve(n, m));
        out.flush();
    }
    public static int[] solve(int n, int m) {
        int[] res = new int[n];
        long aPrev2 = 1, aPrev1 = 0;
        for (int i = 1; i <= n; i++) {
            long aK = (i == 1) ? 0 : (i == 2) ? 1 : (i - 1) * (aPrev1 + aPrev2) % m;
            res[i - 1] = (int) aK;
            aPrev2 = aPrev1;
            aPrev1 = aK;
        }
        return res;
    }
    public static void print(int[] arr) {
        for (int i = 0; i < arr.length; i++) out.print(arr[i] + (i < arr.length - 1 ? " " : ""));
        out.println();
    }
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;
        public FastScanner() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }
        String next() {
            while (st == null || !st.hasMoreElements()) {
                try { st = new StringTokenizer(br.readLine()); } catch (IOException e) { e.printStackTrace(); }
            }
            return st.nextToken();
        }
        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}