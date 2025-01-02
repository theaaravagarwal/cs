import java.util.*;

public class hashMap {
    public static void main(String[] args) {
        Kattio io = new Kattio(System.in, System.out);
        HashMap<Integer, Integer> map = new HashMap<>();
        int n = io.getInt();
        for (int i = 0; i < n; i++) {
            int a = io.getInt();
            map.put(a, map.getOrDefault(a, 0) + 1);
        }
        for (int i : map.keySet()) {
            io.println(i + " " + map.get(i));
        }
        io.close();
    }
}