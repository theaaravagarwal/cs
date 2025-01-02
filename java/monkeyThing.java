import javax.swing.*;
import java.awt.*;
import java.util.Scanner;

public class monkeyThing extends JFrame {
    private final int x, y, len;
    public static final int upLim = 10, lowLim = 0;  // Set your limits for drawing
    private static final int MAX_WIDTH = 800;   // Maximum window width
    private static final int MAX_HEIGHT = 800;  // Maximum window height
    private static final int GRID_SIZE = (upLim - lowLim + 1);  // Number of cells in one dimension
    private static final int CELL_SIZE = Math.min(MAX_WIDTH, MAX_HEIGHT) / GRID_SIZE;  // Calculate cell size

    // Constructor to initialize the window
    public monkeyThing(int x, int y, int len) {
        this.x = x;
        this.y = y;
        this.len = len;

        setTitle("Bresenham's Rasterized Square");
        setSize(GRID_SIZE * CELL_SIZE + 100, GRID_SIZE * CELL_SIZE + 100);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    // Bresenham's line-drawing algorithm to draw lines between two points
    private void drawLine(Graphics g, int x0, int y0, int x1, int y1) {
        int dx = Math.abs(x1 - x0);
        int dy = Math.abs(y1 - y0);
        int sx = x0 < x1 ? 1 : -1;
        int sy = y0 < y1 ? 1 : -1;
        int err = dx - dy;

        while (true) {
            // Draw a pixel at (x0, y0)
            g.fillRect(50 + x0 * CELL_SIZE, 50 + (GRID_SIZE - y0 - 1) * CELL_SIZE, CELL_SIZE, CELL_SIZE);

            if (x0 == x1 && y0 == y1) break;
            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x0 += sx;
            }
            if (e2 < dx) {
                err += dx;
                y0 += sy;
            }
        }
    }

    // Paint method to draw the grid and the square
    @Override
    public void paint(Graphics g) {
        super.paint(g);

        // Draw the grid
        g.setColor(Color.LIGHT_GRAY);
        for (int i = lowLim; i <= upLim; i++) {
            g.drawLine(50, 50 + (GRID_SIZE - i - 1) * CELL_SIZE, 50 + GRID_SIZE * CELL_SIZE, 50 + (GRID_SIZE - i - 1) * CELL_SIZE);  // Horizontal lines
            g.drawLine(50 + (i - lowLim) * CELL_SIZE, 50, 50 + (i - lowLim) * CELL_SIZE, 50 + GRID_SIZE * CELL_SIZE);  // Vertical lines
        }

        // Draw the square using Bresenham's algorithm
        g.setColor(Color.BLUE);
        // Draw the outline of the square
        drawLine(g, x, y, x + len, y);        // Top edge
        drawLine(g, x, y, x, y - len);        // Left edge
        drawLine(g, x + len, y, x + len, y - len);  // Right edge
        drawLine(g, x, y - len, x + len, y - len);  // Bottom edge

        // Fill the square
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                g.fillRect(50 + (x + i) * CELL_SIZE, 50 + (GRID_SIZE - (y - j) - 1) * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            }
        }

        // Label the corners
        g.setColor(Color.RED);
        int topLeftX = 50 + x * CELL_SIZE;
        int topLeftY = 50 + (GRID_SIZE - y) * CELL_SIZE;
        g.drawString("Top-left: (" + x + ", " + y + ")", topLeftX + 5, topLeftY - 5);
        g.drawString("Bottom-right: (" + (x + len) + ", " + (y - len) + ")", 
                     topLeftX + len * CELL_SIZE + 5, topLeftY - len * CELL_SIZE + 15);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter x value: ");
        int x = sc.nextInt();
        System.out.print("Enter y value: ");
        int y = sc.nextInt();
        System.out.print("Enter len value: ");
        int len = sc.nextInt();
        int iterCount = 0;
        long start = System.nanoTime();

        // Ensure the square fits within defined limits
        while (true) {
            if (x + len <= upLim && x >= lowLim && y - len >= lowLim && y <= upLim) {
                System.out.println("Time: " + (System.nanoTime() - start) / 1_000_000.0 + " ms");
                System.out.println("Top-left: " + x + ", " + y);
                System.out.println("Bottom-right: " + (x + len) + ", " + (y - len));
                System.out.println("Iterations: " + iterCount);

                // Launch the GUI
                new monkeyThing(x, y, len);
                break;
            } else {
                len--;
                iterCount++;
            }
        }
        sc.close();
    }
}