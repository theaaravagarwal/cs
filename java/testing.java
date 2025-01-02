import java.io.*;
import java.util.*;

public class testing {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) throws IOException, InterruptedException {
        System.out.println("what is ur target str?");
        String target = sc.nextLine();
        System.out.println("what is ur complete description?");
        String description = sc.nextLine();
        System.out.println(contains(target, description));
        while (!target.equals("exit")||!description.equals("exit")) {
            System.out.println("what is ur target str?");
            target = sc.nextLine();
            System.out.println("what is ur complete description?");
            description = sc.nextLine();
        }
    }
    public static boolean contains(String str, String d) {
        String a = " " + str + " ";
        String b = " " + str;
        String c = str + " ";
        if (d.indexOf(a)>=0||d.indexOf(b)>=0||d.indexOf(c)>=0) {
            return true;
        } else {
            return d.equals(str);
        }
    }
}