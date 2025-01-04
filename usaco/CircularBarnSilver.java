import java.util.*;
public class CircularBarnSilver {
    public static final int MX = 5000005;
    public static int[] min_turns = new int[MX];
    public static boolean[] composite = new boolean[MX];
    public static int[] max_mod4 = {2, 1, 2, 3};
    public static void main(String[] args) {
        initialize();
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-->0) {
            int n = sc.nextInt();
            int ans = MX;
            for (int i=0; i<n; i++) {
                int a_i = sc.nextInt();
                if (min_turns[a_i]/2<ans/2) ans = min_turns[a_i];
            }
            if (ans%2==1) System.out.println("Farmer John");
            else System.out.println("Farmer Nhoj");
        }
        sc.close();
    }
    public static void initialize() {
        min_turns[0] = 0;
        min_turns[1] = 1;
        for (int i=2; i<MX; i++) {
            if (!composite[i]) {
                for (int j=i; j<MX; j+=i) composite[j] = true;
                max_mod4[i % 4] = i;
            }
            min_turns[i] = (i-max_mod4[i%4])/2+1;
        }
    }
}