public class FibonacciThread extends Thread {
    private double[] fibonacciSequence;  // Use double to handle larger numbers and avoid precision issues
    private int count;

    public FibonacciThread(int count) {
        this.count = count;
        this.fibonacciSequence = new double[count];
    }

    @Override
    public void run() {
        double sqrt5 = Math.sqrt(5);
        double phi = (1 + sqrt5) / 2;
        double psi = (1 - sqrt5) / 2;

        for (int i = 0; i < count; i++) {
            fibonacciSequence[i] = Math.round((Math.pow(phi, i + 1) - Math.pow(psi, i + 1)) / sqrt5);
        }
    }

    public double[] getFibonacciSequence() {
        return fibonacciSequence;
    }
}
