import java.util.*;
public class goodmorning {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        int n = sc.nextInt();
        StringBuilder res = new StringBuilder();
        for (int i=0; i<n; i++) {
            int m = sc.nextInt();
            int offset = 0;
            while (!solve(m+offset) && !solve(m-offset)) offset++;
            if (solve(m+offset)) res.append(m+offset).append("\n");
            else res.append(m-offset).append("\n");
        }
        System.out.print(res.toString());
        sc.close();
    }
    public static boolean solve(int n) {
        String numStr = String.valueOf(n);
        Map<Character, String> keys = new HashMap<>();
        keys.put('1', "1234567890");
        keys.put('2', "2356890");
        keys.put('3', "369");
        keys.put('4', "4567890");
        keys.put('5', "56890");
        keys.put('6', "69");
        keys.put('7', "7890");
        keys.put('8', "890");
        keys.put('9', "9");
        keys.put('0', "0");
        for (int i=0; i<numStr.length()-1; i++) {
            char current = numStr.charAt(i);
            char next = numStr.charAt(i+1);
            if (!keys.get(current).contains(String.valueOf(next))) return false;
        }
        return true;
    }
}