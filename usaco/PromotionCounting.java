import java.io.*;
import java.util.*;
public class PromotionCounting {
    static FastScanner sc = new FastScanner();
    static BufferedWriter wr = new BufferedWriter(new OutputStreamWriter(System.out));
    public static void main(String[] args) throws IOException {
        sc.nextInt();
        sc.nextInt();
        int befSilv = sc.nextInt();
        int aftSilv = sc.nextInt();
        int befGold = sc.nextInt();
        int aftGold = sc.nextInt();
        int befPlat = sc.nextInt();
        int aftPlat = sc.nextInt();
        int gtp = aftPlat-befPlat;
        int stg = aftGold-befGold+gtp;
        int bts = aftSilv-befSilv+stg;
        wr.write(bts + "\n");
        wr.write(stg + "\n");
        wr.write(gtp + "\n");
        wr.flush();
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