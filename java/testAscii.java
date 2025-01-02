import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import javax.imageio.ImageIO;
import javax.imageio.ImageReader;
import javax.imageio.stream.ImageInputStream;
import javax.swing.*; // Add this import
import javax.swing.text.*; // Add this import statement

public class testAscii {

    // Expanded ASCII characters set (from dense to sparse)
    private static final String ASCII_CHARS = "@%#*+=-:. ";
    
    // Quality slider (now affects both width and height)
    private static int quality = 3; // Default quality
    
    // Additional parameters for fine-tuning (you can adjust these)
    private static final int BASE_WIDTH = 100; // Base width for quality 1
    private static final double ASPECT_RATIO_CORRECTION = 0.45; // Adjust this to fine-tune aspect ratio

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
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("Select an Image File");
        int option = fileChooser.showOpenDialog(null);
        if (option == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            System.out.println("Selected file: " + file.getAbsolutePath()); // Debug output

            try {
                List<BufferedImage> frames = readImage(file);
                if (frames.isEmpty()) {
                    System.out.println("Failed to read image: " + file.getName()); // Debug output
                    JOptionPane.showMessageDialog(null, 
                        "Failed to read the image. Supported formats are: " + 
                        String.join(", ", ImageIO.getReaderFormatNames()),
                        "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }
                
                System.out.println("Image successfully read. Number of frames: " + frames.size()); // Debug output
                System.out.println("Quality value: " + quality);
                
                List<String> asciiFrames = new ArrayList<>();
                for (BufferedImage frame : frames) {
                    asciiFrames.add(convertToColoredAscii(frame));
                }
                displayColoredAsciiGif(asciiFrames, frames.get(0).getWidth(), frames.get(0).getHeight());
            } catch (IOException ex) {
                ex.printStackTrace();
                System.out.println("Exception while reading image: " + ex.getMessage()); // Debug output
                JOptionPane.showMessageDialog(null, 
                    "An error occurred while reading the image file: " + ex.getMessage(), 
                    "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    private static List<BufferedImage> readImage(File file) throws IOException {
        List<BufferedImage> frames = new ArrayList<>();
        String fileName = file.getName().toLowerCase();
        
        if (fileName.endsWith(".gif")) {
            ImageReader reader = ImageIO.getImageReadersByFormatName("gif").next();
            try (ImageInputStream in = ImageIO.createImageInputStream(file)) {
                reader.setInput(in);
                int numImages = reader.getNumImages(true);
                for (int i = 0; i < numImages; i++) {
                    BufferedImage frame = reader.read(i);
                    frames.add(new BufferedImage(frame.getWidth(), frame.getHeight(), BufferedImage.TYPE_INT_ARGB));
                    Graphics2D g2d = frames.get(i).createGraphics();
                    g2d.drawImage(frame, 0, 0, null);
                    g2d.dispose();
                }
            }
            reader.dispose();
        } else {
            BufferedImage image = ImageIO.read(file);
            if (image != null) {
                frames.add(new BufferedImage(image.getWidth(), image.getHeight(), BufferedImage.TYPE_INT_ARGB));
                Graphics2D g2d = frames.get(0).createGraphics();
                g2d.drawImage(image, 0, 0, null);
                g2d.dispose();
            }
        }
        
        return frames;
    }

    private static String convertToColoredAscii(BufferedImage image) {
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

        StringBuilder coloredAsciiArt = new StringBuilder();
        for (int y = 0; y < scaledHeight; y++) {
            for (int x = 0; x < scaledWidth; x++) {
                Color color = new Color(scaledImage.getRGB(x, y));
                // Adjusted grayscale calculation for better accuracy
                int grayValue = (int)(0.2126 * color.getRed() + 0.7152 * color.getGreen() + 0.0722 * color.getBlue());
                
                // Determine ASCII character based on perceived brightness
                int asciiIndex = grayValue * (ASCII_CHARS.length() - 1) / 255;
                char asciiChar = ASCII_CHARS.charAt(asciiIndex);
                
                // Darken the color by reducing RGB values (e.g., 20% darker)
                int darkenFactor = 80; // Adjust this value to control darkness (0-100)
                int darkRed = Math.max(0, (color.getRed() * darkenFactor) / 100);
                int darkGreen = Math.max(0, (color.getGreen() * darkenFactor) / 100);
                int darkBlue = Math.max(0, (color.getBlue() * darkenFactor) / 100);
                
                // Add ANSI color codes with darkened RGB values
                coloredAsciiArt.append(String.format("\u001B[38;2;%d;%d;%dm%c\u001B[0m", 
                                                     darkRed, darkGreen, darkBlue, asciiChar));
            }
            coloredAsciiArt.append("\n");
        }

        return coloredAsciiArt.toString();
    }

    private static void displayColoredAsciiGif(List<String> asciiFrames, int imageWidth, int imageHeight) {
        JFrame gifFrame = new JFrame("Colored ASCII GIF");
        gifFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        // Get screen size
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        int screenWidth = screenSize.width;
        int screenHeight = screenSize.height;

        // Calculate the window size to fit the screen
        int windowWidth = screenWidth - 40;  // Leave a small margin
        int windowHeight = screenHeight - 80;  // Leave space for title bar and taskbar

        JTextPane textPane = new JTextPane();
        textPane.setEditable(false);
        textPane.setFont(new Font("Monospaced", Font.PLAIN, 5)); // Adjust font size as needed

        JScrollPane scrollPane = new JScrollPane(textPane);
        scrollPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);

        gifFrame.add(scrollPane);
        gifFrame.setSize(windowWidth, windowHeight);
        gifFrame.setLocationRelativeTo(null);
        gifFrame.setVisible(true);

        // Create a timer to update the frames
        Timer timer = new Timer(5, null); // 100ms delay, adjust as needed
        final int[] currentFrame = {0};
        timer.addActionListener(e -> {
            setColoredText(textPane, asciiFrames.get(currentFrame[0]));
            currentFrame[0] = (currentFrame[0] + 1) % asciiFrames.size();
            if (currentFrame[0] == 0 && !timer.isRepeats()) {
                timer.stop();
            }
        });
        timer.start();
    }

    private static void setColoredText(JTextPane textPane, String coloredText) {
        StyledDocument doc = textPane.getStyledDocument();
        try {
            doc.remove(0, doc.getLength()); // Clear existing text
            String[] lines = coloredText.split("\n");
            for (String line : lines) {
                String[] coloredChars = line.split("\u001B\\[");
                for (String coloredChar : coloredChars) {
                    if (coloredChar.isEmpty()) continue;
                    if (coloredChar.startsWith("0m")) {
                        doc.insertString(doc.getLength(), coloredChar.substring(2), null);
                    } else {
                        String[] parts = coloredChar.split("m");
                        if (parts.length == 2) {
                            String[] colorValues = parts[0].split(";");
                            if (colorValues.length == 5) {
                                int r = Integer.parseInt(colorValues[2]);
                                int g = Integer.parseInt(colorValues[3]);
                                int b = Integer.parseInt(colorValues[4]);
                                SimpleAttributeSet attrs = new SimpleAttributeSet();
                                StyleConstants.setForeground(attrs, new Color(r, g, b));
                                doc.insertString(doc.getLength(), parts[1], attrs);
                            }
                        }
                    }
                }
                doc.insertString(doc.getLength(), "\n", null);
            }
        } catch (BadLocationException e) {
            e.printStackTrace();
        }
    }

    private static String resizeAsciiArt(String originalAsciiArt, int originalWidth, int originalHeight, int newWidth, int newHeight) {
        String[] lines = originalAsciiArt.split("\n");
        StringBuilder resizedArt = new StringBuilder();

        for (int y = 0; y < newHeight; y++) {
            int originalY = Math.min(y * originalHeight / newHeight, lines.length - 1);
            for (int x = 0; x < newWidth; x++) {
                int originalX = Math.min(x * originalWidth / newWidth, lines[originalY].length() - 1);
                resizedArt.append(lines[originalY].charAt(originalX));
            }
            resizedArt.append("\n");
        }

        return resizedArt.toString();
    }
}