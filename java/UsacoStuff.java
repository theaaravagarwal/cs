import java.io.*;
import java.util.*;

public class UsacoStuff {
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    public static void main(String[] args) {
        try {
            String[] inputs = in.readLine().split(" ");
            int n = Integer.parseInt(inputs[0]);
            int m = Integer.parseInt(inputs[1]);
            HashMap<Integer, Integer> frequencyMap = new HashMap<>();
            for (int i = 0; i < n; i++) {
                int value = Integer.parseInt(in.readLine());
                frequencyMap.put(value, frequencyMap.getOrDefault(value, 0) + 1);
            }
            for (Map.Entry<Integer, Integer> entry : frequencyMap.entrySet()) {
                out.println("Number: " + entry.getKey() + ", Frequency: " + entry.getValue());
            }
            out.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
