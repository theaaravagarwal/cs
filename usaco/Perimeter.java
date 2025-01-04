import java.io.*;
import java.util.*;

public class Perimeter {
    private static int N;
    private static char[][] grid;
    private static boolean[][] visited;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("perimeter.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("perimeter.out")));

        N = Integer.parseInt(br.readLine());
        grid = new char[N][N];
        visited = new boolean[N][N];

        for (int i = 0; i < N; i++) {
            grid[i] = br.readLine().toCharArray();
        }

        int maxArea = 0;
        int minPerimeter = Integer.MAX_VALUE;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == '#' && !visited[i][j]) {
                    int[] result = floodFill(i, j);
                    int area = result[0];
                    int perimeter = result[1];

                    if (area > maxArea) {
                        maxArea = area;
                        minPerimeter = perimeter;
                    } else if (area == maxArea && perimeter < minPerimeter) {
                        minPerimeter = perimeter;
                    }
                }
            }
        }

        pw.println(maxArea + " " + minPerimeter);
        pw.close();
        br.close();
    }

    private static int[] floodFill(int x, int y) {
        Queue<int[]> queue = new LinkedList<>();
        queue.add(new int[]{x, y});
        visited[x][y] = true;

        int area = 0;
        int perimeter = 0;

        int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        while (!queue.isEmpty()) {
            int[] cell = queue.poll();
            int cx = cell[0];
            int cy = cell[1];

            area++;
            int localPerimeter = 0;

            for (int[] direction : directions) {
                int nx = cx + direction[0];
                int ny = cy + direction[1];

                if (nx >= 0 && ny >= 0 && nx < N && ny < N) {
                    if (grid[nx][ny] == '#') {
                        if (!visited[nx][ny]) {
                            visited[nx][ny] = true;
                            queue.add(new int[]{nx, ny});
                        }
                    } else {
                        localPerimeter++;
                    }
                } else {
                    localPerimeter++;
                }
            }

            perimeter += localPerimeter;
        }

        return new int[]{area, perimeter};
    }
}
