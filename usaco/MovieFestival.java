import java.util.*;
public class MovieFestival {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int k = sc.nextInt();
        List<int[]> movs = new ArrayList<>();
        for (int i=0; i<n; i++) {
            int s = sc.nextInt();
            int e = sc.nextInt();
            movs.add(new int[]{s, e});
        }
        movs.sort(Comparator.comparingInt(m->m[1]));
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        for (int[] m : movs) {
            if (pq.size()<k) pq.offer(m[1]);
            else if (pq.peek()<=m[0]) {
                    pq.poll();
                    pq.offer(m[1]);
                }
        }
        System.out.println(pq.size());
        sc.close();
    }
}