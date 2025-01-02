public class ParseIntExample {
    final static Kattio io = new Kattio(System.in, System.out);
    public static void main(String[] args) {
        double startTime, endTime;
        String str;
        while (true) {
            str = io.getWord();
            startTime = System.nanoTime();
            System.out.println(solve(str));
            endTime = System.nanoTime();
            System.out.printf("runtime: %.9f nanoseconds (%.9f seconds)%n", (endTime-startTime), (endTime-startTime)/1000000000.0);
            System.out.println("type 'exit' to quit");
            if (io.getWord().equals("exit")) break;
        }
        io.close();
    }
    public static long solve(String x) {
        long n = parse(x), sum = 0;
        while (n!=0) {
            sum+=n%10;
            n/=10;
        }
        return sum;
    }

    public static long parse(String s) {
        String str = "";
        for (int i=0; i<s.length(); i++) if (Character.isDigit(s.charAt(i))) str+=s.charAt(i)-'0';
        if (str.equals("")) return 0;
        return Long.parseLong(str);
    }
}
