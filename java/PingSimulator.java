import java.io.*;
import java.net.*;
import java.util.*;

public class PingSimulator {
    static class PingClient extends Thread {
        private String ipAddress;
        private int pingCount;

        public PingClient(String ipAddress, int pingCount) {
            this.ipAddress = ipAddress;
            this.pingCount = pingCount;
        }

        @Override
        public void run() {
            for (int i = 0; i < pingCount; i++) {
                try {
                    InetAddress inet = InetAddress.getByName(ipAddress);
                    long startTime = System.nanoTime();
                    boolean reachable = inet.isReachable(1000);
                    long endTime = System.nanoTime();

                    if (reachable) {
                        long pingTime = (endTime - startTime) / 1_000_000; // Convert to milliseconds
                        System.out.println("Client " + Thread.currentThread().getName() + " pinged " + ipAddress + " - Response time: " + pingTime + " ms");
                    } else {
                        System.out.println("Client " + Thread.currentThread().getName() + " pinged " + ipAddress + " - No response");
                    }
                } catch (IOException e) {
                    System.out.println("Client " + Thread.currentThread().getName() + " encountered an error: " + e.getMessage());
                }
                try {
                    Thread.sleep(10);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the IP address to ping: ");
        String ipAddress = scanner.nextLine();

        System.out.print("Enter the number of clients to simulate: ");
        int numberOfClients = Integer.parseInt(scanner.nextLine());

        System.out.print("Enter the number of pings per client: ");
        int pingCount = Integer.parseInt(scanner.nextLine());

        for (int i = 0; i < numberOfClients; i++) {
            PingClient client = new PingClient(ipAddress, pingCount);
            client.setName("Client-" + (i + 1));
            client.start();
        }

        scanner.close();
    }
}
