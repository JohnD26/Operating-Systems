import java.util.Scanner;

class FibonacciGenerator {
    public static void main(String[] args) {
        // Check if the user provided a number as an argument
        if (args.length != 1) {
            System.out.println("Please provide the number of Fibonacci numbers to generate");
            System.exit(1);
        }

        // Parse the number from the command line argument
        int n = Integer.parseInt(args[0]);

        // Create an array to store the Fibonacci sequence
        int[] fibonacciSequence = new int[n];

        // Create and start the Fibonacci thread
        FibonacciThread fibonacciThread = new FibonacciThread(fibonacciSequence, n);
        fibonacciThread.start();

        try {
            // Wait for the Fibonacci thread to finish
            fibonacciThread.join();
        } catch (InterruptedException e) {
            System.out.println("Thread interrupted: " + e.getMessage());
        }

        // Print the generated Fibonacci sequence
        System.out.println("Generated Fibonacci sequence:");
        for (int i = 0; i < n; i++) {
            System.out.print(fibonacciSequence[i] + " ");
        }
    }
}