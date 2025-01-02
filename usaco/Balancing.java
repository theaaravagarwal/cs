import java.io.*;
import java.util.*;
public class Balancing {
	public static void main(String[] args) throws IOException {
		Scanner sc = new Scanner(System.in);
		int cowNum = sc.nextInt();
		int maxPos = sc.nextInt();
		int[] xvals = new int[cowNum];
		int[] yvals = new int[cowNum];
		Set<Integer> vfences = new HashSet<>();
		Set<Integer> hfences = new HashSet<>();
		for (int c = 0; c < cowNum; c++) {
			xvals[c] = sc.nextInt();
			yvals[c] = sc.nextInt();
			vfences.add(xvals[c] + 1);
			hfences.add(yvals[c] + 1);
		}
		int minImbalance = cowNum;
		for (int v : vfences) {
			for (int h : hfences) {
				int topLeft = 0;
				int topRight = 0;
				int bottomLeft = 0;
				int bottomRight = 0;
				for (int c = 0; c < cowNum; c++) {
					if (xvals[c] < v && yvals[c] > h) {
						topLeft++;
					} else if (xvals[c] > v && yvals[c] > h) {
						topRight++;
					} else if (xvals[c] < v && yvals[c] < h) {
						bottomLeft++;
					} else if (xvals[c] > v && yvals[c] < h) {
						bottomRight++;
					}
				}
				int currImbalance = Collections.max(
				    Arrays.asList(topLeft, topRight, bottomLeft, bottomRight));
				minImbalance = Math.min(minImbalance, currImbalance);
			}
		}
		System.out.println(minImbalance);
		sc.close();
	}
}