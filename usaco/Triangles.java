import java.io.*;
import java.util.*;
public class Triangles {
	public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int[] x = new int[n];
		int[] y = new int[n];
		for (int i = 0; i < n; i++) {
			x[i] = sc.nextInt();
			y[i] = sc.nextInt();
		}
		sc.close();
		int maxArea = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					if (y[i] == y[j] && x[i] == x[k]) {
						int area = Math.abs((x[j] - x[i]) * (y[k] - y[i]));
						maxArea = Math.max(maxArea, area);
					}
				}
			}
		}
		System.out.println(maxArea);
	}
}