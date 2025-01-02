
import java.util.Arrays;
import java.util.concurrent.ThreadLocalRandom;

class oldSearch {

    final static int maxLength = 50, minLength = 10;
    final static int maxInt = (maxLength - minLength) / 2;

    public static void main(String[] args) {
        int[] arr = new int[ThreadLocalRandom.current().nextInt(minLength, maxLength + 1)];
        randomize(arr);
        arrayOut(arr);
        Arrays.sort(arr);
        arrayOut(arr);
        binarySearch(arr, ThreadLocalRandom.current().nextInt(0, maxInt + 1));
        print("");
    }

    public static void binarySearch(int[] arr, int x) {
        int l = 0, r = arr.length - 1, m = -1, i = 0;
        while (l < r) {
            m = l + (r - l) / 2;
            i++;
            if (arr[m] == x) {
                break;
            } else if (arr[m] < x) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        print(arr[m]);
        print(m);
        print(i);
    }

    public static void print(String str) {
        System.out.println(str);
    }

    public static void print(int x) {
        System.out.println(x);
    }

    public static int[] randomize(int[] arr) {
        for (int i = 0; i < arr.length; i++) {
            arr[i] = ThreadLocalRandom.current().nextInt(0, maxInt + 1);
        }
        return arr;
    }

    public static void arrayOut(int[] arr) {
        print("");
        System.out.print("[");
        for (int i = 0; i < arr.length; i++) {
            if (i + 1 == arr.length) {
                System.out.print(arr[i]);
            } else {
                System.out.print(arr[i] + ", ");
            }
        }
        System.out.print("]");
        print("");
    }
}
