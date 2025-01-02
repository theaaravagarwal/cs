import java.util.*;

public class WordShuffle {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String str;
        while (!false) {
            System.out.println("Enter a word: ");
            str = sc.nextLine();
            System.out.println(shuffle(str));
        }
    }
    public static String shuffle(String str) {
        List<Character> chars = new ArrayList<>();
        for (char c:str.toCharArray()) chars.add(c);
        Random random = new Random();
        for (int i=chars.size()-1; i>0; i--) {
            int j = random.nextInt(i + 1);
            char temp = chars.get(i);
            chars.set(i, chars.get(j));
            chars.set(j, temp);
        }
        StringBuilder shuffled = new StringBuilder();
        for (char c:chars) shuffled.append(c);
        return shuffled.toString();
    }
}
