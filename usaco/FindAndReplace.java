import java.util.*;
import java.io.*;
public class FindAndReplace {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();
        for (int t=Integer.parseInt(in.readLine()); t>0; t--) {
            String before = in.readLine();
            String after = in.readLine();
            int[] bec = new int[52];
            Arrays.fill(bec, -1);
            boolean possible = true;
            Set<Character> set = new HashSet<>();
            for (int j=0; j<before.length(); j++) {
                int b = letterToNode(before.charAt(j));
                int a = letterToNode(after.charAt(j));
                set.add(after.charAt(j));
                if (bec[b]!=-1&&bec[b]!=a) possible = false;
                bec[b] = a;
            }
            if (set.size()==52) possible = false;
            if (before.equals(after)) possible = true;
            int ans = 0;
            if (possible) {
                int[] indeg = new int[52];
                for (int a=0; a<52; a++) if (bec[a]!=-1&&bec[a]!=a) indeg[bec[a]]++;
                for (int a=0; a<52; a++) if (bec[a]!=-1&&bec[a]!=a) ans++;
                int[] seen = new int[52];
                for (int r=0; r<52; r++) {
                    if (seen[r]==0) {
                        int a = r;
                        while (a!=-1&&seen[a]==0) {
                            seen[a] = r+1;
                            a = bec[a];
                        }
                        if (a!=-1&&a!=bec[a]&&seen[a]==r+1) {
                            int s = a;
                            boolean freePass = false;
                            do {
                                seen[a] = 2;
                                if (indeg[a]>1) freePass = true;
                                a = bec[a];
                            } while (a!=s);
                            if (!freePass) ans++;
                        }
                    }
                }
            } else ans=-1;
            out.append(ans).append('\n');
        }
        System.out.print(out);
    }
    static int letterToNode(char l) {
        if ('a'<=l&&l<='z') return l-'a';
        else return 26+(l-'A');
    }
}