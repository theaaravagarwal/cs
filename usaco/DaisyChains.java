import java.io.*;
import java.util.*;

public class DaisyChains {
	public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int[] flowers = new int[n];
		for (int i = 0; i < n; i++) {
			flowers[i] = sc.nextInt();
		}
		int validPhotos = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				double avgPetals = 0;
				for (int f = i; f <= j; f++) avgPetals += flowers[f];
				avgPetals /= j - i + 1;
				for (int index = i; index <= j; index++) {
					if (flowers[index] == avgPetals) {
						validPhotos++;
						break;
					}
				}
			}
		}
		System.out.println(validPhotos);
		sc.close();
	}
}