import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;
import java.util.concurrent.ThreadLocalRandom;
import javax.imageio.ImageIO;

public class double_array {
    static Scanner sc = new Scanner(System.in);
    static int r = sc.nextInt(), c = sc.nextInt();
    static int[][] arr = new int[r][c];
    static int min = 0, max = sc.nextInt();

    public static void main(String[] args) throws IOException, InterruptedException {
        randomize_array();
        // out_array();
        // sort_array();
        // out_array();
        writeImage(1, arr);
        sort_array();
        writeImage(2, arr);
    }

    public static void randomize_array() {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                arr[i][j] = ThreadLocalRandom.current().nextInt(min, max + 1);
            }
        }
    }

    public static void out_array() {
        for (int i = 0; i < r; i++) {
            System.out.println();
            for (int j = 0; j < c; j++) {
                System.out.print(arr[i][j] + " ");
            }
        }
        System.out.println();
    }

    public static void sort_array() {
        int[] flatArray = new int[r * c];
        int index = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                flatArray[index++] = arr[i][j];
            }
        }

        Arrays.sort(flatArray);
        index = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                arr[i][j] = flatArray[index++];
            }
        }
    }

    public static void writeImage(int Name, int[][] color) {
        String directoryPath = "res/world/";
        String filePath = directoryPath + "PNGLevel_" + Name + ".png";
        
        File directory = new File(directoryPath);
        if (!directory.exists()) {
            directory.mkdirs();
        }
        
        BufferedImage image = new BufferedImage(color.length, color[0].length, BufferedImage.TYPE_INT_RGB);
        for (int x = 0; x < color.length; x++) {
            for (int y = 0; y < color[x].length; y++) {
                int red = (color[x][y] >> 16) & 0xFF;
                int green = (color[x][y] >> 8) & 0xFF;
                int blue = color[x][y] & 0xFF;
                int rgb = (red << 16) | (green << 8) | blue;
                image.setRGB(x, y, rgb);
            }
        }
    
        File ImageFile = new File(filePath);
        try {
            ImageIO.write(image, "png", ImageFile);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}