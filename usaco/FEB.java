import java.util.*;
public class FEB {
    public static void solve(int N, String S) {
        Set<Integer> excitementLevels = new TreeSet<>();

        // Initial excitement level without 'F'
        int baseExcitement = 0;
        for (int i = 0; i < N - 1; i++) {
            if ((S.charAt(i) == 'B' && S.charAt(i + 1) == 'B') || 
                (S.charAt(i) == 'E' && S.charAt(i + 1) == 'E')) {
                baseExcitement++;
            }
        }
        
        // Add the base excitement level
        excitementLevels.add(baseExcitement);
        int fCount = 0;

        // Iterate through the string to calculate potential contributions of 'F'
        for (int i = 0; i < N; i++) {
            if (S.charAt(i) == 'F') {
                fCount++;

                // Check the left and right neighbors
                char left = i > 0 ? S.charAt(i - 1) : '\0';
                char right = i < N - 1 ? S.charAt(i + 1) : '\0';

                // Determine potential excitement contributions
                if (left == 'B' && right == 'B') {
                    baseExcitement++; // F can become B and form BB
                } else if (left == 'E' && right == 'E') {
                    baseExcitement++; // F can become E and form EE
                }

                // Add excitement levels considering F can be B or E
                excitementLevels.add(baseExcitement + fCount); // All F's as B
                excitementLevels.add(baseExcitement + fCount); // All F's as E
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