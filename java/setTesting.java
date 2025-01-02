import java.io.*;
import java.util.*;

public class setTesting {
	public static void main(String[] args) throws IOException {
		Kattio io = new Kattio(System.in, System.out);
		int n = io.getInt();
		Set<Integer> set = new HashSet<>();
		for (int i = 0; i < n; i++) { set.add(io.getInt()); }
		System.out.println(set.size());
		io.close();
	}
}