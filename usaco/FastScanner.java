import java.io.*;
import java.util.*;
public class FastScanner {
    BufferedReader br; StringTokenizer st;
    public FastScanner() { br = new BufferedReader(new InputStreamReader(System.in)); }
    String next() {
        while (st == null || !st.hasMoreElements()) try { st = new StringTokenizer(br.readLine()); } catch (IOException e) { e.printStackTrace(); }
        return st.nextToken();
    }
    int nextInt() { return Integer.parseInt(next()); }
}