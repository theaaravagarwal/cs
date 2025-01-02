import java.lang.*;

class thePalindromeProblem {
    public static void main(String[] args) {
        System.out.println("Testing 121");
        System.out.println(isPalindrome(121));
        System.out.println("Testing -121");
        System.out.println(isPalindrome(-121));
        System.out.println("Testing 10");
        System.out.println(isPalindrome(10));
    }
    public static boolean isPalindrome(int x) {
        String str = Integer.toString(x);
        int left = 0;
        int right = str.length() - 1;
        while (left < right) {
            if (str.charAt(left) != str.charAt(right)) return false;
            left++;
            right--;
        }
        return true;
    }
}