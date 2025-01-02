import java.util.Scanner;

public class thirdUsacoPractice {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int lawnmowerX1 = sc.nextInt(), lawnmowerY1 = sc.nextInt(), lawnmowerX2 = sc.nextInt(), lawnmowerY2 = sc.nextInt();
        int cowFeedX1 = sc.nextInt(), cowFeedY1 = sc.nextInt(), cowFeedX2 = sc.nextInt(), cowFeedY2 = sc.nextInt();
        int lawnmowerArea = (lawnmowerX2 - lawnmowerX1) * (lawnmowerY2 - lawnmowerY1);
        int tarpArea = lawnmowerArea;
        if (cowFeedY1 <= lawnmowerY1 && cowFeedY2 >= lawnmowerY2 && cowFeedX1 <= lawnmowerX1 && cowFeedX2 >= lawnmowerX2) {
            tarpArea = 0;
        } else {
            if (cowFeedY1 <= lawnmowerY1 && cowFeedY2 >= lawnmowerY2) {
                int overlapWidth = Math.max(0, Math.min(lawnmowerX2, cowFeedX2) - Math.max(lawnmowerX1, cowFeedX1));
                tarpArea -= overlapWidth * (lawnmowerY2 - lawnmowerY1);
            }
            if (cowFeedX1 <= lawnmowerX1 && cowFeedX2 >= lawnmowerX2) {
                int overlapHeight = Math.max(0, Math.min(lawnmowerY2, cowFeedY2) - Math.max(lawnmowerY1, cowFeedY1));
                tarpArea -= (lawnmowerX2 - lawnmowerX1) * overlapHeight;
            }
            if (cowFeedX1 < lawnmowerX1 && cowFeedX2 > lawnmowerX2 && cowFeedY1 < lawnmowerY1 && cowFeedY2 > lawnmowerY2) {
                tarpArea = 0;
            }
        }
        System.out.println(tarpArea);
        sc.close();
    }
}