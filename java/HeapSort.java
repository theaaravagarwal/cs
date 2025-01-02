import java.util.*;
import java.io.*;

public class HeapSort {

    public void sort(int arr[]) {
        int n = arr.length;

        // Build heap (rearrange array)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // One by one extract an element from heap
        for (int i = n - 1; i > 0; i--) {
            // Move current root to end
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            // call max heapify on the reduced heap
            heapify(arr, i, 0);
        }
    }

    // To heapify a subtree rooted with node i which is an index in arr[].
    void heapify(int arr[], int n, int i) {
        int largest = i; // Initialize largest as root
        int left = 2 * i + 1; // left = 2*i + 1
        int right = 2 * i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (left < n && arr[left] > arr[largest])
            largest = left;

        // If right child is larger than largest so far
        if (right < n && arr[right] > arr[largest])
            largest = right;

        // If largest is not root
        if (largest != i) {
            int swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;

            // Recursively heapify the affected sub-tree
            heapify(arr, n, largest);
        }
    }

    // Method to generate a random array
    public int[] generateRandomArray(int size) {
        Random rand = new Random();
        int[] arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = rand.nextInt(1000); // Random numbers between 0 and 999
        }
        return arr;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the size of the array: ");
        int size = sc.nextInt();

        System.out.print("Do you want to randomize the array? (yes/no): ");
        String randomizeInput = sc.next();
        int[] arr;

        HeapSort heapSort = new HeapSort();

        if (randomizeInput.equalsIgnoreCase("yes")) {
            arr = heapSort.generateRandomArray(size);
        } else {
            arr = new int[size];
            System.out.println("Please enter the elements of the array:");
            for (int i = 0; i < size; i++) {
                arr[i] = sc.nextInt();
            }
        }

        long startTime = System.nanoTime();
        heapSort.sort(arr);
        long endTime = System.nanoTime();
        double duration = (endTime - startTime);
        System.out.println("Sorted array:");
        for (int num : arr) {
            System.out.print(num + " ");
        }
        System.out.println("\nTime taken to sort: " + duration + " nanoseconds");
        sc.close();
    }
}
