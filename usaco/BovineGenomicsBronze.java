import java.io.*;
import java.util.*;
public class BovineGenomicsBronze {
	public static void main(String[] args) throws IOException {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int m = sc.nextInt();
		char[][] spottedCows = new char[n][];
		char[][] plainCows = new char[n][];
		for (int i = 0; i < n; i++) { spottedCows[i] = sc.next().toCharArray(); }
		for (int i = 0; i < n; i++) { plainCows[i] = sc.next().toCharArray(); }
		sc.close();
		int possPositions = 0;
		for (int i = 0; i < m; i++) {
			boolean dupe = false;
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					if (spottedCows[j][i] == plainCows[k][i]) {
						dupe = true;
						break;
					}
				}
			}
			if (!dupe) { possPositions++; }
		}
		System.out.println(possPositions);
	}
}