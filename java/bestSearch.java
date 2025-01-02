import java.util.Arrays;
import java.util.concurrent.ThreadLocalRandom;

class bestSearch {
    final static Kattio io = new Kattio(System.in, System.out);
    final static long len = io.getLong();
    final static int maxInt = 200;
    final static int n = 20;
    public static void main(String[] args) {
        int[] arr = new int[(int)len];
        randomize(arr);
        //arrayOut(arr);
        print("");
        Arrays.sort(arr);
        fastBinarySearch(arr, n);
        //arrayOut(arr);
        print("");
        slowBinarySearch(arr, n);
    }
    public static void fastBinarySearch(int[] arr, int x) {
        double startTime, endTime, runtime;
        long div = 1000000000;
        startTime = System.nanoTime();
        int l = 0, r = arr.length-1, m = 0, i = 0;
        while (l < r) {
            i++;
            m = l + (r-l)/2;
            if (arr[m] == x) {
                break;
            } else if (arr[m] < x) {
                l = m+1;
            } else {
                r = m-1;
            }
        }
        endTime = System.nanoTime();
        runtime = (endTime-startTime)/div;
        print("position: " + m);
        print("iterations: " + i);
        print("runtime: " + runtime);
    }
    public static void slowBinarySearch(int[] arr, int x) {
        double startTime, endTime, runtime;
        long div = 1000000000L;
        startTime = System.nanoTime();
        int l = 0, r = arr.length-1, m = 0, i = 0, ans = m;
        while (l <= r) {
            i++;
            m = l + (r-l)/2;
            if (arr[m] >= x) {
                ans = m;
                r = m-1;
            } else {
                l = m+1;
            }
        }
        endTime = System.nanoTime();
        runtime = (endTime-startTime)/div;
        print("position: " + ans);
        print("iterations: " + i);
        print("runtime: " + runtime);
    }
    public static void print(String str) {
        System.out.println(str);
    }
    public static void print(int x) {
        System.out.println(x);
    }
    public static int[] randomize(int[] arr) {
        for (int i=0; i<arr.length; i++) {
            arr[i] = ThreadLocalRandom.current().nextInt(0,maxInt+1);
        }
        return arr;
    }
    public static void arrayOut(int[] arr) {
        print("");
        System.out.print("[");
        for (int i=0; i<arr.length; i++) {
            if (i+1==arr.length) {
                System.out.print(arr[i]);
            } else {
                System.out.print(arr[i] + ", ");
            }
        }
        System.out.print("]");
        print("");
    }

    public static int getMaxInt() {
        return maxInt;
    }
}