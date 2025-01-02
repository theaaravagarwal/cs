import java.util.Scanner;

public class shellGame {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int[][] swaps = new int[N][3];
        
        for (int i = 0; i < N; i++) {
            swaps[i][0] = sc.nextInt();  // a
            swaps[i][1] = sc.nextInt();  // b
            swaps[i][2] = sc.nextInt();  // g
        }

        int maxScore = 0;

        // Try all possible starting positions for the pebble (1, 2, or 3)
        for (int start = 1; start <= 3; start++) {
            int currentPosition = start;  // The initial position of the pebble
            int score = 0;  // Initialize the score for this starting position

            // Simulate the swaps and guesses
            for (int i = 0; i < N; i++) {
                int a = swaps[i][0];
                int b = swaps[i][1];
                int guess = swaps[i][2];

                // Swap the position of the pebble if it's under shell 'a' or 'b'
                if (currentPosition == a) {
                    currentPosition = b;
                } else if (currentPosition == b) {
                    currentPosition = a;
                }

                // Check if Elsie's guess matches the current position of the pebble
                if (currentPosition == guess) {
                    score++;
                }
            }

            // Update the maximum score
            maxScore = Math.max(maxScore, score);
        }

        // Output the maximum score
        System.out.println(maxScore);
        sc.close();
    }
}