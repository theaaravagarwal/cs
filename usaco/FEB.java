import java.util.*;
public class FEB {
    public static void solve(int N, String S) {
        Set<Integer> excitementLevels = new TreeSet<>();
        int baseExcitement = 0;
        for (int i = 0; i < N - 1; i++) {
            if ((S.charAt(i) == 'B' && S.charAt(i + 1) == 'B') || 
                (S.charAt(i) == 'E' && S.charAt(i + 1) == 'E')) {
                baseExcitement++;
            }
        }
        excitementLevels.add(baseExcitement);
        int fCount = 0;
        for (int i = 0; i < N; i++) {
            if (S.charAt(i) == 'F') {
                fCount++;
                char left = i > 0 ? S.charAt(i - 1) : '\0';
                char right = i < N - 1 ? S.charAt(i + 1) : '\0';
                if (left == 'B' && right == 'B') baseExcitement++;
                else if (left == 'E' && right == 'E') baseExcitement++;
                excitementLevels.add(baseExcitement + fCount);
                excitementLevels.add(baseExcitement + fCount);
            }
        }
        System.out.println(excitementLevels.size());
        for (int level : excitementLevels) {
            System.out.println(level);
        }
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = Integer.parseInt(sc.nextLine().trim());
        String S = sc.nextLine().trim();
        solve(N, S);
        sc.close();
    }
}
