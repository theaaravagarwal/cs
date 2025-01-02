import java.util.Arrays;

public class randomTest {
    public static void main(String args[]) {
        Kattio io = new Kattio(System.in, System.out);
        int in = io.getInt();
        int h1 = io.getInt();
        int h2 = io.getInt();
        int h3 = io.getInt();
        int out = io.getInt();
        int[][][][][] arr = new int[in][h1][h2][h3][out];
        System.out.println(arr.length);
        printArr(arr);
    }

    public static void printArr(int[][][][][] arr) {
        for (int[][][][] arr1 : arr) {
            for (int[][][] arr11 : arr1) {
                for (int[][] innerArr : arr11) {
                    for (int[] innerArr1 : innerArr) {
                        System.out.print(Arrays.toString(innerArr1));
                    }
                }
            }
        }
    }
}