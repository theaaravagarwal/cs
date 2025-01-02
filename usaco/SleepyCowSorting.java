import java.util.*;
import java.io.*;
public class SleepyCowSorting {
    static FastScanner sc = new FastScanner();
    public static void main(String[] args) {
        int N = sc.nextInt();
        int[] cows = new int[N];
        for (int i = 0; i < N; i++) cows[i] = sc.nextInt();
        int sortedSuffixStart = N - 1;
        while (sortedSuffixStart > 0 && cows[sortedSuffixStart - 1] < cows[sortedSuffixStart]) sortedSuffixStart--;
        int result = sortedSuffixStart;
        System.out.println(result);
    }
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;
        public FastScanner() { br = new BufferedReader(new InputStreamReader(System.in)); }
        String next() {
            while (st == null || !st.hasMoreElements()) try { st = new StringTokenizer(br.readLine()); } catch (IOException e) { e.printStackTrace(); }
            return st.nextToken();
        }
        int nextInt() { return Integer.parseInt(next()); }
    }
}
