class PrimeNumberThread extends Thread {
    private int maxNumber;

    // Constructor to set the maximum number for prime generation
    public PrimeNumberThread(int maxNumber) {
        this.maxNumber = maxNumber;
    }

    @Override
    public void run(){
        // System.out.println("I am a Worker Thread"); //Here the worker thread is being executed
        generatePrimes(maxNumber);
    }

    // Method to generate and print prime numbers up to the given number
    private void generatePrimes(int maxNumber) {
        for (int num = 2; num <= maxNumber; num++) {
            if (isPrime(num)) {
                System.out.println(num);
            }
        }
    }

    // Method to check if a number is prime
    private boolean isPrime(int num) {
        if (num <= 1) {
            return false;
        }
        for (int i = 2; i <= Math.sqrt(num); i++) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }
}