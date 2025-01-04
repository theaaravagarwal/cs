import java.io.*;
import java.util.*;
public class CakeGame {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine().trim());
        while (t-->0) solve(br);
    }
    public static void solve(BufferedReader br) throws IOException {
        int n = Integer.parseInt(br.readLine().trim());
        StringTokenizer st = new StringTokenizer(br.readLine().trim());
        int[] v = new int[n + 1];
        long sum = 0, mini = Long.MAX_VALUE;
        for (int i = 1; i <= n; i++) {
            v[i] = Integer.parseInt(st.nextToken());
            sum += v[i];
        }
        long ps = 0;
        for (int i=1; i<=n; i++) {
            ps+=v[i];
            if (i>n/2+1) ps-=v[i-n/2-1];
            if (i>=n/2+1) mini=Math.min(mini, ps);
        }
        System.out.println(mini+" "+(sum-mini));
    }
}
