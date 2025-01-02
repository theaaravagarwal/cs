//this code is right

import java.io.*;
import java.util.*;

public class firstUsacoPractice {
    public static void main(String[] args) throws IOException {
        //Scanner sc = new Scanner(new File("billboard.in"));
        Scanner sc = new Scanner(System.in);
        
        // Read the coordinates for the first billboard
        int x1 = sc.nextInt(), y1 = sc.nextInt(), x2 = sc.nextInt(), y2 = sc.nextInt();
        
        // Read the coordinates for the second billboard
        int x3 = sc.nextInt(), y3 = sc.nextInt(), x4 = sc.nextInt(), y4 = sc.nextInt();
        
        // Read the coordinates for the truck
        int x5 = sc.nextInt(), y5 = sc.nextInt(), x6 = sc.nextInt(), y6 = sc.nextInt();
        
        // Calculate the area of both billboards
        int area1 = (x2 - x1) * (y2 - y1);
        int area2 = (x4 - x3) * (y4 - y3);
        
        // Calculate overlapping areas of both billboards
        int overlap1 = Math.max(0, Math.min(x2, x6) - Math.max(x1, x5)) * Math.max(0, Math.min(y2, y6) - Math.max(y1, y5));
        int overlap2 = Math.max(0, Math.min(x4, x6) - Math.max(x3, x5)) * Math.max(0, Math.min(y4, y6) - Math.max(y3, y5));
        
        // Calculate visible areas
        int visible1 = area1 - overlap1;
        int visible2 = area2 - overlap2;
        int totalVisible = visible1 + visible2;
        
        //PrintWriter out = new PrintWriter(new FileWriter("billboard.out"));
        System.out.println(totalVisible);
        sc.close();
    }
}
