import java.util.*;
public class NumberOfIslands {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int row = sc.nextInt(); //read x size of grid (num of rows)
        int col = sc.nextInt(); //read y size of grid (num of columns)
        int[][] a = new int[row][col];
        for (int i=0; i<row; i++) for (int j=0; j<col; j++) a[i][j] = sc.nextInt(); //read grid of islands
        int c = 0;
        for (int i=0; i<row; i++) for (int j=0; j<col; j++) { //iterate through the entire grid
            if (a[i][j]==1) { //if the grid has a 1 we will do dfs on the sections around it to see how big the island is, and then mark it as an island
                c++;
                dfs(a, i, j);
            }
        }
        System.out.println(c);
    }
    public static void dfs(int[][] a, int i, int j) { //iterative dfs rather than recursive because it is faster on higher grid sizes
        Stack<int[]> stack = new Stack<>();
        stack.push(new int[]{i, j});
        while (!stack.isEmpty()) {
            int[] pos = stack.pop();
            int x = pos[0];
            int y = pos[1];
            if (x<0||y<0||x>=a.length||y>=a[0].length||a[x][y]==0) continue;
            a[x][y] = 0; //mark as visited
            stack.push(new int[]{x+1, y}); //checks right
            stack.push(new int[]{x-1, y}); //checks left
            stack.push(new int[]{x, y+1}); //checks down
            stack.push(new int[]{x, y-1}); //checks up
            /* we do not check diagonals because it is not necessary and would lead to wrong results sometimes */
            /* where 1 is the places that are checked
             * example shape:
             * 0 1 0
             * 1 1 1
             * 0 1 0
            */
        }
    }
}
//Time Complexity: O(row*col)
//Space Complexity: O(row*col)