#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Function to calculate the nth Catalan number
unsigned long long calculate_catalan(int num) {
    unsigned long long result = 1;
    for (int i = 0; i < num; ++i) {
        result = result * (2 * (2 * i + 1)) / (i + 2);
    }
    return result;
}

int main(int argc, char *argv[]) {
    // Check if the number of Catalan numbers to produce is provided
    if (argc != 2) {
        printf("Usage: %s <number_of_catalan_numbers>\n", argv[0]);
        return 1;
    }

    int num_catalan = atoi(argv[1]); // Number of Catalan numbers to produce
    const char *shared_mem_name = "catalan_memory"; // Shared memory name
    size_t shared_mem_size = num_catalan * sizeof(unsigned long long); // Size of shared memory

    // Create the shared memory object
    int shared_mem_fd = shm_open(shared_mem_name, O_CREAT | O_RDWR, 0666);
    if (shared_mem_fd == -1) {
        perror("shm_open");
        return 1;
    }

    // Set the size of the shared memory object
    if (ftruncate(shared_mem_fd, shared_mem_size) == -1) {
        perror("ftruncate");
        return 1;
    }

    // Map the shared memory object in the process's address space
    unsigned long long *shared_mem_ptr = mmap(NULL, shared_mem_size, PROT_WRITE, MAP_SHARED, shared_mem_fd, 0);
    if (shared_mem_ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Generate and write Catalan numbers to shared memory
    for (int i = 0; i < num_catalan; ++i) {
        shared_mem_ptr[i] = calculate_catalan(i);
    }

    // Display the produced Catalan numbers
    printf("Produced Catalan numbers:\n");
    for (int i = 0; i < num_catalan; ++i) {
        printf("%llu ", shared_mem_ptr[i]);
    }
    printf("\n");

    // Clean up
    munmap(shared_mem_ptr, shared_mem_size);
    close(shared_mem_fd);

    return 0;
}


