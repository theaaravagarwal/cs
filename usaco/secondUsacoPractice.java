
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class secondUsacoPractice {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int T = Integer.parseInt(br.readLine());
        for (int tc = 1; tc <= T; tc++) {
            performTest(br, out);
        }

        out.close();
    }

    private static void performTest(BufferedReader br, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(br.readLine());
        int w_room = Integer.parseInt(st.nextToken());
        int h_room = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(br.readLine());
        int x1 = Integer.parseInt(st.nextToken());
        int y1 = Integer.parseInt(st.nextToken());
        int x2 = Integer.parseInt(st.nextToken());
        int y2 = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(br.readLine());
        int w_second = Integer.parseInt(st.nextToken());
        int h_second = Integer.parseInt(st.nextToken());
        int ans = Integer.MAX_VALUE;
        if (w_second + (x2 - x1) <= w_room) {
            ans = Math.min(ans, Math.max(0, w_second - x1));
            ans = Math.min(ans, Math.max(0, x2 - (w_room - w_second)));
        }
        if (h_second + (y2 - y1) <= h_room) {
            ans = Math.min(ans, Math.max(0, h_second - y1));
            ans = Math.min(ans, Math.max(0, y2 - (h_room - h_second)));
        }
        if (ans == Integer.MAX_VALUE) {
            out.println(-1);
        } else {
            out.printf("%.9f\n", (double) ans);
        }
    }
}
