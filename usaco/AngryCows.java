import java.io.*;
import java.util.*;
public class AngryCows {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("angry.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("angry.out")));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int k = Integer.parseInt(st.nextToken());
        int[] p = new int[n];
        for (int i=0; i<n; i++) p[i] = Integer.parseInt(br.readLine());
        Arrays.sort(p);
        int l = 0, r = 1000000000, a = r;
        while (l<=r) {
            int m = l+(r-l)/2;
            if (check(p, n, k, m)) {
                a = m;
                r = m-1;
            } else l = m+1;
        }
        pw.println(a);
        pw.close();
        br.close();
    }
    private static boolean check(int[] p, int n, int k, int r) {
        int cu = 0,i = 0;
        while (i<n) {
            cu++;
            if (cu>k) return false;
            int ra = p[i]+2*r;
            while (i<n&&p[i]<=ra) i++;
        }
        return true;
    }
}