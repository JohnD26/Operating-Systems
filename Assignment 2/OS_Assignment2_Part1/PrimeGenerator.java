import java.util.Scanner;

class PrimeGenerator { 
    public static void main(String[] args){
        // Check if the user provided a number as an argument
        if (args.length != 1) {
            System.out.println("Please provide a number as a command line argument.");
            System.exit(1);
        }

        // Parse the number from the command line argument
        int number = Integer.parseInt(args[0]);

        // Create a new thread to generate prime numbers up to the given number
        PrimeNumberThread r1 = new PrimeNumberThread(number);
        r1.start();

        // System.out.println("I am the main Thread"); //Here main thread starts its execution
    }
}