public class FibonnaciGenerator {

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please enter the number of fibonnaci numbers to generate");
            return;
        }

        int numberOfTerms;
        try {
            numberOfTerms = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Please enter a whole nummber.");
            return;
        }

        FibonacciThread fibThread = new FibonacciThread(numberOfTerms);
        fibThread.start();

        try {
            fibThread.join();  // Wait for the child thread to finish
        } catch (InterruptedException e) {
            System.out.println("An interruption occured");
            return;
        }

        double[] fibonacciSequence = fibThread.getFibonacciSequence();
        for (int i = 0; i < fibonacciSequence.length; i++) {
            System.out.println("F(" + i + ") = " + (int)fibonacciSequence[i]);
        }
    }
}
