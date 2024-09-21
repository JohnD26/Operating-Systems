import java.util.*;

public class PageReplacement {

    // Generate a random page reference string
    public static List<Integer> generatePageReferenceString(int length, int maxPageNumber) {
        List<Integer> referenceString = new ArrayList<>();
        Random random = new Random();
        for (int i = 0; i < length; i++) {
            referenceString.add(random.nextInt(maxPageNumber + 1));
        }
        return referenceString;
    }

    // Implementation of the FIFO algorithm for page replacement
    public static int fifoAlgorithm(List<Integer> referenceString, int frameCount) {
        Queue<Integer> frames = new LinkedList<>();
        int pageFaults = 0;
        for (int page : referenceString) {
            // Check if the page is already in the frames
            if (!frames.contains(page)) {
                // If frames are full, remove the oldest page
                if (frames.size() >= frameCount) {
                    frames.poll();
                }
                // Add the new page to the frames
                frames.add(page);
                // Increment the page fault count
                pageFaults++;
                System.out.println("FIFO - Page fault! Added page: " + page + " | Frames: " + frames);
            } else {
                System.out.println("FIFO - Page hit: " + page + " | Frames: " + frames);
            }
        }
        return pageFaults;
    }

    // Implementation of the LRU algorithm for page replacement
    public static int lruAlgorithm(List<Integer> referenceString, int frameCount) {
        List<Integer> frames = new ArrayList<>();
        int pageFaults = 0;
        for (int i = 0; i < referenceString.size(); i++) {
            int page = referenceString.get(i);
            // Check if the page is already in the frames
            if (!frames.contains(page)) {
                // If frames are full, remove the least recently used page
                if (frames.size() >= frameCount) {
                    int lruIndex = findLeastRecentlyUsed(frames, referenceString, i);
                    frames.remove(lruIndex);
                }
                // Add the new page to the frames
                frames.add(page);
                // Increment the page fault count
                pageFaults++;
                System.out.println("LRU - Page fault! Added page: " + page + " | Frames: " + frames);
            } else {
                // Move the page to the most recently used position
                frames.remove((Integer) page);
                frames.add(page);
                System.out.println("LRU - Page hit: " + page + " | Frames: " + frames);
            }
        }
        return pageFaults;
    }

    // Helper method to find the least recently used page
    private static int findLeastRecentlyUsed(List<Integer> frames, List<Integer> referenceString, int currentIndex) {
        int lruIndex = -1;
        int farthest = currentIndex;
        for (int i = 0; i < frames.size(); i++) {
            int lastIndex = referenceString.subList(0, currentIndex).lastIndexOf(frames.get(i));
            if (lastIndex < farthest) {
                farthest = lastIndex;
                lruIndex = i;
            }
        }
        return lruIndex;
    }

    public static void main(String[] args) {
        int referenceStringLength = 20; // Length of the reference string
        int maxPageNumber = 9; // Maximum page number
        List<Integer> referenceString = generatePageReferenceString(referenceStringLength, maxPageNumber);

        System.out.println("Page Reference String: " + referenceString);
        System.out.println();

        for (int frameSize = 1; frameSize <= 7; frameSize++) {
            System.out.println("Frame Size: " + frameSize);

            System.out.println("FIFO Algorithm:");
            int fifoFaults = fifoAlgorithm(referenceString, frameSize);
            System.out.println("FIFO Page Faults: " + fifoFaults);
            System.out.println();

            System.out.println("LRU Algorithm:");
            int lruFaults = lruAlgorithm(referenceString, frameSize);
            System.out.println("LRU Page Faults: " + lruFaults);
            System.out.println();
        }
    }
}
