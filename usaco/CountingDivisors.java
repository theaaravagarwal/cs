import java.io.*;
public class CountingDivisors {
	public static void main(String[] args) throws IOException {
		BufferedReader read = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(read.readLine());
		StringBuilder ans = new StringBuilder();
		for (int q=0; q<t; q++) {
			int x = Integer.parseInt(read.readLine());
			int d = 0;
			for (int i=1; i*i<=x; i++) if (x%i==0) d+=i*i==x?1:2;
			ans.append(d).append('\n');
		}
		System.out.print(ans);
	}
}