class MultithreadingDemo extends Thread {
    @SuppressWarnings("deprecation")
    public void run()
    {
        try {
            System.out.println(
                "Thread " + Thread.currentThread().getId()
                + " is running");
        }
        catch (Exception e) {
            System.out.println("Err:" + e);
        }
    }
}
 
public class multithreading {
    public static void main(String[] args)
    {
        int n = 8;
        for (int i = 0; i < n; i++) {
            MultithreadingDemo movement1
                = new MultithreadingDemo();
            movement1.start();
        }
    }
}