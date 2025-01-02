import java.io.*;
import java.util.*;
public class ModernArtBronze {
    static FastScanner sc = new FastScanner();
    static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
    public static void main(String[] args) {
        int N = sc.nextInt();
        int[][] grid = new int[N][N];
        for (int i = 0; i < N; i++) {
            String line = sc.next();
            for (int j = 0; j < N; j++) grid[i][j] = line.charAt(j) - '0';
        }
        out.println(solve(N, grid));
        out.flush();
        out.close();
    }
    public static int solve(int N, int[][] grid) {
        int[] minX = new int[10], minY = new int[10], maxX = new int[10], maxY = new int[10];
        Arrays.fill(minX, N); Arrays.fill(minY, N); Arrays.fill(maxX, -1); Arrays.fill(maxY, -1);
        Set<Integer> visibleColors = new HashSet<>();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int color = grid[i][j];
                if (color > 0) {
                    visibleColors.add(color);
                    minX[color] = Math.min(minX[color], i);
                    minY[color] = Math.min(minY[color], j);
                    maxX[color] = Math.max(maxX[color], i);
                    maxY[color] = Math.max(maxY[color], j);
                }
            }
        }
        SegmentTree st = new SegmentTree(10);
        boolean[] canBeFirst = new boolean[10];
        Arrays.fill(canBeFirst, true);
        for (int color : visibleColors) {
            for (int i = minX[color]; i <= maxX[color]; i++) {
                for (int j = minY[color]; j <= maxY[color]; j++) {
                    int overlappingColor = grid[i][j];
                    if (overlappingColor != color) {
                        canBeFirst[overlappingColor] = false;
                    }
                }
            }
        }
        int firstColors = 0;
        for (int color : visibleColors) {
            if (canBeFirst[color]) {
                firstColors++;
            }
        }
        return firstColors;
    }
    static class SegmentTree {
        private int[] tree, lazy;
        public SegmentTree(int size) {
            tree = new int[size * 4];
            lazy = new int[size * 4];
        }
        public void update(int node, int start, int end, int l, int r, int value) {
            if (lazy[node] != 0) {
                tree[node] += lazy[node];
                if (start != end) {
                    lazy[node * 2] += lazy[node];
                    lazy[node * 2 + 1] += lazy[node];
                }
                lazy[node] = 0;
            }
            if (start > end || start > r || end < l) return;
            if (start >= l && end <= r) {
                tree[node] += value;
                if (start != end) {
                    lazy[node * 2] += value;
                    lazy[node * 2 + 1] += value;
                }
                return;
            }
            int mid = (start + end) / 2;
            update(node * 2, start, mid, l, r, value);
            update(node * 2 + 1, mid + 1, end, l, r, value);
            tree[node] = Math.max(tree[node * 2], tree[node * 2 + 1]);
        }
        public int query(int node, int start, int end, int l, int r) {
            if (start > end || start > r || end < l) return 0;
            if (lazy[node] != 0) {
                tree[node] += lazy[node];
                if (start != end) {
                    lazy[node * 2] += lazy[node];
                    lazy[node * 2 + 1] += lazy[node];
                }
                lazy[node] = 0;
            }
            if (start >= l && end <= r) return tree[node];
            int mid = (start + end) / 2;
            int q1 = query(node * 2, start, mid, l, r);
            int q2 = query(node * 2 + 1, mid + 1, end, l, r);
            return Math.max(q1, q2);
        }
    }
    static class FastScanner {
        BufferedReader br; StringTokenizer st;
        public FastScanner() { br = new BufferedReader(new InputStreamReader(System.in)); }
        String next() {
            while (st == null || !st.hasMoreElements()) try { st = new StringTokenizer(br.readLine()); } catch (IOException e) { e.printStackTrace(); }
            return st.nextToken();
        }
        int nextInt() { return Integer.parseInt(next()); }
    }
}

//This code takes an average of 0.06 seconds to run for every test case on usaco.guide :)