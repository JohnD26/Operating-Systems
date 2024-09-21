class FibonacciThread extends Thread {
    private int[] fibonacciSequence;
    private int n;

    // Constructor to initialize the array and the number of elements to generate
    public FibonacciThread(int[] fibonacciSequence, int n) {
        this.fibonacciSequence = fibonacciSequence;
        this.n = n;
    }

    @Override
    public void run() {
        // Generate the Fibonacci sequence
        if (n > 0) {
            fibonacciSequence[0] = 0;
        }
        if (n > 1) {
            fibonacciSequence[1] = 1;
        }
        for (int i = 2; i < n; i++) {
            fibonacciSequence[i] = fibonacciSequence[i - 1] + fibonacciSequence[i - 2];
        }
    }
}