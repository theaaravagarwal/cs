import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.text.*;

public class AsciiArtConverter {

    // ASCII characters used for grayscale conversion (from dense to sparse)
    private static final String ASCII_CHARS = "@%#*+=-:. ";
    
    // Quality slider (now affects both width and height)
    private static int quality = 2; // Default quality
    
    // Additional parameters for fine-tuning (you can adjust these)
    private static final int BASE_WIDTH = 100; // Base width for quality 1
    private static final double ASPECT_RATIO_CORRECTION = 0.4; // Adjust this to fine-tune aspect ratio
    private static final int MIN_FONT_SIZE = 1;
    private static final int MAX_FONT_SIZE = 12;

    public static void main(String[] args) {
        // Create a JFrame to hold the file chooser
        JFrame frame = new JFrame("ASCII Art Converter");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Automatically scale the window to a percentage of screen size
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        frame.setSize(screenSize.width / 3, screenSize.height / 3);
        frame.setLayout(new BorderLayout());

        // Create a button to open the file chooser
        JButton button = new JButton("Choose an Image");
        button.setPreferredSize(new Dimension(200, 50));
        button.addActionListener(e -> chooseAndConvertImage());

        JPanel panel = new JPanel(new GridBagLayout());
        panel.add(button);

        // Add quality slider
        JSlider qualitySlider = new JSlider(JSlider.HORIZONTAL, 1, 10, quality);
        qualitySlider.setMajorTickSpacing(1);
        qualitySlider.setPaintTicks(true);
        qualitySlider.setPaintLabels(true);
        qualitySlider.addChangeListener(e -> {
            quality = qualitySlider.getValue();
            System.out.println("Slider updated quality to: " + quality); // Debugging output
        });

        frame.add(panel, BorderLayout.CENTER);
        frame.add(qualitySlider, BorderLayout.SOUTH);

        frame.setVisible(true);
    }

    private static void chooseAndConvertImage() {
        // Use the system's native file chooser
        JFileChooser fileChooser = new JFileChooser();
        FileNameExtensionFilter filter = new FileNameExtensionFilter(
            "Image files", ImageIO.getReaderFileSuffixes());
        fileChooser.setFileFilter(filter);
        fileChooser.setDialogTitle("Select an Image File");
        int option = fileChooser.showOpenDialog(null);
        if (option == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            System.out.println("Selected file: " + file.getAbsolutePath()); // Debug output

            try {
                BufferedImage image = ImageIO.read(file);
                if (image == null) {
                    System.out.println("Failed to read image: " + file.getName()); // Debug output
                    JOptionPane.showMessageDialog(null, 
                        "Failed to read the image. Supported formats are: " + 
                        String.join(", ", ImageIO.getReaderFormatNames()),
                        "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                System.out.println("Image successfully read. Dimensions: " + 
                                   image.getWidth() + "x" + image.getHeight()); // Debug output
                System.out.println("Quality value: " + quality);

                String asciiArt = convertToAscii(image);
                displayAsciiArt(asciiArt);
            } catch (IOException ex) {
                ex.printStackTrace();
                JOptionPane.showMessageDialog(null, "An error occurred while reading the image file.", "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    // Method to convert the image to colored ASCII art
    private static String convertToAscii(BufferedImage image) {
        // Get screen size
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        int screenWidth = screenSize.width;

        // Calculate new dimensions while maintaining aspect ratio
        double aspectRatio = (double) image.getHeight() / image.getWidth();
        int scaledWidth = BASE_WIDTH * quality;
        int scaledHeight = (int) Math.round(scaledWidth * aspectRatio * ASPECT_RATIO_CORRECTION);
        
        // Ensure the scaled image fits within the screen
        if (scaledWidth > screenWidth) {
            scaledWidth = screenWidth;
            scaledHeight = (int) Math.round(scaledWidth * aspectRatio * ASPECT_RATIO_CORRECTION);
        }
        
        System.out.println("Scaled dimensions: " + scaledWidth + "x" + scaledHeight); // Debugging output

        BufferedImage scaledImage = new BufferedImage(scaledWidth, scaledHeight, BufferedImage.TYPE_INT_RGB);
        Graphics2D g2d = scaledImage.createGraphics();
        g2d.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);
        g2d.drawImage(image, 0, 0, scaledWidth, scaledHeight, null);
        g2d.dispose();

        StringBuilder asciiArt = new StringBuilder();
        for (int y = 0; y < scaledHeight; y++) {
            for (int x = 0; x < scaledWidth; x++) {
                Color color = new Color(scaledImage.getRGB(x, y));
                int grayValue = (color.getRed() + color.getGreen() + color.getBlue()) / 3;
                int asciiIndex = grayValue * (ASCII_CHARS.length() - 1) / 255;
                char asciiChar = ASCII_CHARS.charAt(asciiIndex);
                
                // Add color information
                String colorCode = String.format("\u001B[38;2;%d;%d;%dm", color.getRed(), color.getGreen(), color.getBlue());
                asciiArt.append(colorCode).append(asciiChar).append("\u001B[0m");
            }
            asciiArt.append("\n");
        }

        return asciiArt.toString();
    }

    // Method to display colored ASCII art in a JFrame
    private static void displayAsciiArt(String asciiArt) {
        JFrame artFrame = new JFrame("Colored ASCII Art");
        artFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        JTextPane textPane = new JTextPane();
        textPane.setEditable(false);
        
        // Set up the styled document
        StyledDocument doc = textPane.getStyledDocument();
        Style defaultStyle = StyleContext.getDefaultStyleContext().getStyle(StyleContext.DEFAULT_STYLE);
        
        try {
            String[] lines = asciiArt.split("\n");
            for (String line : lines) {
                String[] coloredChars = line.split("\u001B\\[");
                for (String coloredChar : coloredChars) {
                    if (coloredChar.isEmpty()) continue;
                    if (coloredChar.startsWith("38;2;")) {
                        String[] parts = coloredChar.split("m");
                        String[] rgb = parts[0].split(";");
                        Color color = new Color(Integer.parseInt(rgb[2]), Integer.parseInt(rgb[3]), Integer.parseInt(rgb[4]));
                        Style colorStyle = textPane.addStyle("ColorStyle", defaultStyle);
                        StyleConstants.setForeground(colorStyle, color);
                        doc.insertString(doc.getLength(), String.valueOf(parts[1].charAt(0)), colorStyle);
                    } else {
                        doc.insertString(doc.getLength(), coloredChar, defaultStyle);
                    }
                }
                doc.insertString(doc.getLength(), "\n", defaultStyle);
            }
        } catch (BadLocationException e) {
            e.printStackTrace();
        }

        // Calculate font size based on window size and ASCII art dimensions
        String[] lines = asciiArt.split("\n");
        int maxLineLength = Arrays.stream(lines).mapToInt(String::length).max().orElse(1);
        int lineCount = lines.length;

        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        int maxWidth = screenSize.width - 40;  // Leave a small margin
        int maxHeight = screenSize.height - 80;  // Leave space for title bar and taskbar

        int fontSize = Math.max(MIN_FONT_SIZE, 
                                Math.min(MAX_FONT_SIZE, 
                                         Math.min(maxWidth / maxLineLength, maxHeight / lineCount)));

        textPane.setFont(new Font("Monospaced", Font.PLAIN, fontSize));

        JScrollPane scrollPane = new JScrollPane(textPane);
        scrollPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);

        artFrame.add(scrollPane);
        artFrame.setSize(maxWidth, maxHeight);
        artFrame.setLocationRelativeTo(null);
        artFrame.setVisible(true);
    }
}