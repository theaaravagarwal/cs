import java.io.*;
import java.util.*;
public class RoadSegmentsUsaco {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        int roadSegNum = sc.nextInt();
        int bessieSegNum = sc.nextInt();
        sc.nextLine();
        int[][] limitSegs = new int[roadSegNum][2];
        for (int s = 0; s < roadSegNum; s++) {
            limitSegs[s] = Arrays.stream(sc.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        }
        int[][] bessieSegs = new int[bessieSegNum][2];
        for (int s = 0; s < bessieSegNum; s++) {
            bessieSegs[s] = Arrays.stream(sc.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        }
        int[] lim = new int[100];
        int start = 0;
        for (int[] s : limitSegs) {
            for (int i = 0; i < s[0]; i++) {
                lim[start + i] = s[1];
            }
            start += s[0];
        }
        int[] bessie = new int[100];
        start = 0;
        for (int[] s : bessieSegs) {
            for (int i = 0; i < s[0]; i++) {
                bessie[start + i] = s[1];
            }
            start += s[0];
        }
        int worst = 0;
        for (int p = 0; p < 100; p++) {
            worst = Math.max(worst, bessie[p] - lim[p]);
        }
        System.out.println(worst);
    }
}