import java.io.*;
import java.util.*;
public class IntoBlocksEasy {
    static int n, q, ans;
    static int[] a, r, cnt;
    public static void prework(FastScanner fs) {
        n = fs.nextInt();
        q = fs.nextInt();
        a = new int[n + 1];
        r = new int[maxl];
        cnt = new int[maxl];
        for (int i = 1; i <= n; i++) {
            a[i] = fs.nextInt();
            cnt[a[i]]++;
            r[a[i]] = i;
        }
    }
    public static void mainwork() {
        int l = 1, right = 0, mx = 0;
        for (int i = 1; i <= n; i++) {
            right = Math.max(right, r[a[i]]);
            mx = Math.max(mx, cnt[a[i]]);
            if (right == i) {
                ans += (i - l + 1) - mx;
                l = right + 1;
                right = 0;
                mx = 0;
            }
        }
    }
    public static void print(PrintWriter out) {
        out.println(ans);
    }
    public static void main(String[] args) {
        FastScanner fs = new FastScanner();
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        prework(fs);
        mainwork();
        print(out);
        out.flush();
        out.close();
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
    static final int maxl = 200010;
}