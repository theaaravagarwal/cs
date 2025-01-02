import java.util.*;
public class HuzzTranslator {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        System.out.println("Name:");
        String s = sc.nextLine();
        if (s.equals("girl")||s.equals("girls")) System.out.println("huzz");
        else if (s.length()>=2) System.out.println(s.substring(0, 2)+"uzz");
        else System.out.println(s.substring(0, 1)+"uzz");
    }
}