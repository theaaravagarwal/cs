import java.util.*;
import java.io.*;

public class Hoofball {
    static FastScanner sc = new FastScanner();
    static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
    public static void main(String[] args) {
        int N = sc.nextInt();
        int[] arr = new int[N];
        for (int i = 0; i < N; i++) arr[i] = sc.nextInt();
        out.println(solve(N, arr));
        out.close();
    }
    public static int solve(int n, int[] arr) {
        Arrays.sort(arr);
        int[] dir = processDirections(arr);
        boolean[] covered = new boolean[n];
        int balls = 0;
        for (int i = 0; i < n; i++) {
            if (!covered[i]) {
                if (i > 0 && dir[i - 1] == i && dir[i] == i - 1) {
                    covered[i] = true;
                    covered[i - 1] = true;
                    balls++;
                } else {
                    balls++;
                    coverSegment(i, dir, covered);
                }
            }
        }
        return balls;
    }
    public static int[] processDirections(int[] pos) {
        int n = pos.length;
        int[] dir = new int[n];
        Arrays.fill(dir, -1);
        for (int i = 0; i < n; i++) {
            int left = (i > 0) ? pos[i] - pos[i - 1] : Integer.MAX_VALUE;
            int right = (i < n - 1) ? pos[i + 1] - pos[i] : Integer.MAX_VALUE;
            if (left < right) dir[i] = i - 1;
            else if (right < left) dir[i] = i + 1;
            else dir[i] = i - 1;
        }
        return dir;
    }
    public static void coverSegment(int start, int[] dir, boolean[] covered) {
        int current = start;
        while (current != -1 && !covered[current]) {
            covered[current] = true;
            int next = dir[current];
            if (next < 0 || next >= covered.length || covered[next]) break;
            current = next;
        }
    }
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;
        public FastScanner() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }
        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}