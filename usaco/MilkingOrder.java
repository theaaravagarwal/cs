import java.util.*;
import java.io.*;
public class MilkingOrder {
    static FastScanner sc = new FastScanner();
    public static void main(String[] args) {
        
        int N = sc.nextInt();
        int M = sc.nextInt();
        int K = sc.nextInt();
        
        int[] hierarchy = new int[M];
        for (int i = 0; i < M; i++) {
            hierarchy[i] = sc.nextInt();
        }
        
        int[] fixedPositions = new int[N + 1];
        Arrays.fill(fixedPositions, -1); // -1 indicates no fixed position
        
        for (int i = 0; i < K; i++) {
            int cow = sc.nextInt();
            int pos = sc.nextInt();
            fixedPositions[cow] = pos;
        }
        
        int left = 1, right = N, answer = N;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            if (canPlaceCow1(mid, N, hierarchy, fixedPositions)) {
                answer = mid;
                right = mid - 1; // Try earlier positions
            } else {
                left = mid + 1; // Try later positions
            }
        }
        
        System.out.println(answer);
    }
    
    static boolean canPlaceCow1(int pos, int N, int[] hierarchy, int[] fixedPositions) {
        int[] order = new int[N + 1]; // Tracks which cow is at each position
        Arrays.fill(order, -1); // -1 indicates the position is unoccupied
        
        // Assign fixed positions
        for (int cow = 1; cow <= N; cow++) {
            if (fixedPositions[cow] != -1) {
                int fixedPos = fixedPositions[cow];
                if (fixedPos == pos && cow != 1) {
                    return false; // Cow 1 can't be placed here
                }
                order[fixedPos] = cow;
            }
        }
        
        // Try placing cow 1 at `pos`
        if (order[pos] != -1) return false; // Position already occupied
        order[pos] = 1;
        
        // Place hierarchy cows in order
        int currentPos = 1;
        for (int cow : hierarchy) {
            // Skip already placed cows
            while (currentPos <= N && order[currentPos] != -1) {
                currentPos++;
            }
            if (currentPos > N) return false; // No position available
            
            // Place the cow if it’s not already placed
            if (order[currentPos] == -1) {
                order[currentPos] = cow;
            }
        }
        
        return true; // All constraints satisfied
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