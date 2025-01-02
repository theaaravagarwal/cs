import java.util.*;
public class circularBarn {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] rooms = new int[n];
        for (int i=0; i<n; i++) rooms[i] = sc.nextInt();
        int cTotal = rooms[0];
        for (int j=1; j<rooms.length; j++) cTotal += rooms[j];
        int minDist = Integer.MAX_VALUE;
        for (int k=0; k<n; k++) {
            int dist = 0;
            int rem = cTotal;
            for (int l=0; l<n; l++) {
                rem -= rooms[(k+l)%n];
                dist += rem;
            }
            minDist = Math.min(minDist, dist);
        }
        System.out.print(minDist);
        sc.close();
    }
}