Steps on how to run the C Files on your Computer:

Step 1: Compilation of both C Files into machine code 
gcc -o producer producer.c
gcc -o consumer consumer.c

Step 2: Run the producer machine code 
./producer 5

Step 3: On a different terminal, run the consumer file
./consumer


-------------------------------------------------------------
What you will see at each step:
1) Machine code files produced which will be interpreted by the gcc compiler
2) Producer file will generates Catalan numbers and writes them to the shared memory. It then displays the generated Catalan numbers.
3)Consumer file will open shared memory object created by the  producer and will read from the shared memory. It will then display the catalan numbers read from the shared memory


---------------------------------------------------------------
This fulfills the requirements and instructions given for the assignment question 3