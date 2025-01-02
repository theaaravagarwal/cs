import java.util.*;
public class BovineGenomicsSilver {
    static int N, M;
    static int toBase4(int a, int b, int c) { return a * 16 + b * 4 + c; }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        M = sc.nextInt();
        sc.nextLine();
        int[][] spotty = new int[N][M];
        int[][] plain = new int[N][M];
        for (int i = 0; i < N; i++) {
            String s = sc.nextLine();
            for (int j = 0; j < M; j++) spotty[i][j] = charToInt(s.charAt(j));
        }
        for (int i = 0; i < N; i++) {
            String s = sc.nextLine();
            for (int j = 0; j < M; j++) plain[i][j] = charToInt(s.charAt(j));
        }
        int result = 0;
        for (int i = 0; i < M; i++) {
            for (int j = i + 1; j < M; j++) {
                for (int k = j + 1; k < M; k++) {
                    Set<Integer> spottySet = new HashSet<>();
                    for (int l = 0; l < N; l++) spottySet.add(toBase4(spotty[l][i], spotty[l][j], spotty[l][k]));
                    boolean hasOverlap = false;
                    for (int l = 0; l < N; l++) {
                        int base4 = toBase4(plain[l][i], plain[l][j], plain[l][k]);
                        if (spottySet.contains(base4)) {
                            hasOverlap = true;
                            break;
                        }
                    }
                    if (!hasOverlap) result++;
                }
            }
        }
        System.out.println(result);
    }
    static int charToInt(char c) {
        switch (c) {
            case 'A': return 0;
            case 'C': return 1;
            case 'G': return 2;
            case 'T': return 3;
            default: throw new IllegalArgumentException("Invalid character: " + c);
        }
    }
}