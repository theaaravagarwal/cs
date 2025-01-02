import java.io.IOException;
import java.util.Scanner;

public class whiteSheet {
    static class Rect {
        long x1, y1, x2, y2;

        void init(Scanner scanner) {
            x1 = scanner.nextLong();
            y1 = scanner.nextLong();
            x2 = scanner.nextLong();
            y2 = scanner.nextLong();
        }
    }

    static long intersect(Rect p, Rect q) {
        long x = Math.max(0, Math.min(p.x2, q.x2) - Math.max(p.x1, q.x1));
        long y = Math.max(0, Math.min(p.y2, q.y2) - Math.max(p.y1, q.y1));
        return x * y;
    }

    static long intersect(Rect p, Rect q, Rect t) {
        long x = Math.max(0, Math.min(Math.min(p.x2, q.x2), t.x2) - Math.max(Math.max(p.x1, q.x1), t.x1));
        long y = Math.max(0, Math.min(Math.min(p.y2, q.y2), t.y2) - Math.max(Math.max(p.y1, q.y1), t.y1));
        return x * y;
    }

    static void solve(long TC, long TC2, Scanner scanner) {
        Rect w = new Rect();
        Rect b1 = new Rect();
        Rect b2 = new Rect();

        w.init(scanner);
        b1.init(scanner);
        b2.init(scanner);

        long ans = intersect(w, b1) + intersect(w, b2) - intersect(w, b1, b2);
        long area = (w.x2 - w.x1) * (w.y2 - w.y1);

        System.out.println(ans < area ? "YES" : "NO");
    }

    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        solve(1, 1, scanner);
    }
}
