#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *shared_mem_name = "catalan_memory"; // Shared memory name

    // Open the shared memory object
    int shared_mem_fd = shm_open(shared_mem_name, O_RDONLY, 0666);
    if (shared_mem_fd == -1) {
        perror("shm_open");
        return 1;
    }

    // Get the size of the shared memory object
    struct stat shared_mem_stat;
    if (fstat(shared_mem_fd, &shared_mem_stat) == -1) {
        perror("fstat");
        return 1;
    }

    // Map the shared memory object in the process's address space
    unsigned long long *shared_mem_ptr = mmap(NULL, shared_mem_stat.st_size, PROT_READ, MAP_SHARED, shared_mem_fd, 0);
    if (shared_mem_ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Display the consumed Catalan numbers
    printf("Consumed Catalan numbers:\n");
    int num_catalan = shared_mem_stat.st_size / sizeof(unsigned long long);
    for (int i = 0; i < num_catalan; ++i) {
        printf("%llu ", shared_mem_ptr[i]);
    }
    printf("\n");

    // Clean up
    munmap(shared_mem_ptr, shared_mem_stat.st_size);
    close(shared_mem_fd);
    shm_unlink(shared_mem_name); // Remove the shared memory object

    return 0;
}

