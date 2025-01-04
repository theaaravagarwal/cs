import java.util.*;
public class Stacking {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int k = sc.nextInt();
        int[] h = new int[n];
        for (int i=0; i<k; i++) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            for (int j=a-1; j<b; j++) h[j]++;
        }
        Arrays.sort(h);
        int m = h[n/2];
        System.out.println(m);
        sc.close();
    }
}