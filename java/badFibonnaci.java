
public class badFibonnaci {
    public static void main(String[] args) {
        Kattio io = new Kattio(System.in, System.out);
        int n = io.getInt();
        System.out.println(fastFibonnaci(n));
        //System.out.println(binaryTreeFibonnaci(n));
    }
    public static int binaryTreeFibonnaci(int n) {
        if (n==0||n==1) return n;
        return binaryTreeFibonnaci(n-1)+binaryTreeFibonnaci(n-2);
    } //just uses recursion to calculate the fibonacci sequence which is very slow: O(2^n)
    public static long fastFibonnaci(int n) {
        long[] fib = new long[n+1];
        fib[0] = 0;
        fib[1] = 1;
        for (int i=2; i<=n; i++) fib[i] = fib[i-1]+fib[i-2];
        return fib[n];
    } //uses a for loop to calculate the fibonacci sequence which is much faster: O(n)
}