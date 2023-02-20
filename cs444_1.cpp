// Operating Systems - CS444/544
// Spring 2023
// Alif Jakir
// jakirab@clarkson.edu
// This assignment is meant to be a review of the C/C++ programming language and the pthreads library.
// Parallel programming is a very important skill to have in the field of computer science.
// Program Description: This program uses the pthreads library to perform matrix multiplication (dot-product).
// Last updated 2/19/22
// YouTube Code Review & Demo link: 

// Write a program in C/C++ that uses the pthreads library to perform matrix multiplication (dot-product).

// The program requirements:

//  See Programming Assignment Information for general guidelines relevant to all programming assignments
// The program must prompt the user to input the sizes of two matrices.
// Matrix 1 rows & columns
// Matrix 2 rows & columns
// The program has to check to verify that it can actually multiply the two matrices. (ie. # of rows in matrix 1 = # of columns in matrix 2)
// Once validated the program then fills both matrices with random numbers and prints them to the screen.
// Now the multi-threading begins! You must use pthreads to parallelize the matrix multiplication and dot product result matrix generation.
// Each row and column dot product process should be handled by an individual thread, in parallel.
// Once all threads have finished the final result matrix can be printed to the screen.

#pragma GCC diagnostic ignored "-Wreturn-type" // For some reason, this is needed to get rid of the warning about the main function not returning a value

// INCLUDE STATEMENTS
#include <pthread.h> // Import pthreads library
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// END INCLUDE STATEMENTS

// GLOBAL VARIABLES
// Define the number of threads
#define NUM_THREADS 4

// Define the number of rows and columns for the matrices
#define ROWS 4
#define COLS 4

// Define the matrices
int matrix1[ROWS][COLS];
int matrix2[ROWS][COLS];
int result[ROWS][COLS];
// END GLOBAL VARIABLES

// Define the thread data structure
typedef struct {
    int row;
    int col;
} thread_data;

// Define the thread function that will be executed by each thread
// The thread function will calculate the dot product of a row and column
// The thread function will also store the dot product in the result matrix
// This calculates the dot product of each row and column
// Parallel processing occurs by having each thread calculate the dot product of a row and column
void *dot_product(void *threadarg) {
    // Define the thread data by casting the threadarg to a thread_data pointer
    thread_data *my_data;
    my_data = (thread_data *) threadarg;

    // Define the row and column by accessing the thread data
    int row = my_data->row;
    int col = my_data->col;

    // Define the dot product to start with 0
    int dot_product = 0;

    // Calculate the dot product by multiplying the row and column
    for (int i = 0; i < COLS; i++) {
        dot_product += matrix1[row][i] * matrix2[i][col];
    }

    // Store the dot product in the result matrix
    result[row][col] = dot_product;

    // Exit the thread
    pthread_exit(NULL);
    }

// Define the main function
// argc is the number of arguments passed to the program
// argv is an array of strings containing the arguments passed to the program
int main(int argc, char *argv[]) {
    // Define the thread id
    // The thread id is used to identify the thread
    pthread_t threads[NUM_THREADS];

    // Define the thread data
    // The thread data is used to pass data to the thread function
    thread_data thread_data_array[NUM_THREADS];

    // Define the thread count
    // The thread count is used to keep track of the number of threads
    int thread_count = 0;

    // Define the random number generator seed
    srand(time(NULL));

    // Prompt the user to enter the number of rows and columns for matrix 1
    // The number of columns in matrix 1 must equal the number of rows in matrix 2!
    printf("Enter the number of rows for matrix 1: ");
    int rows1;
    scanf("%d", &rows1);

    printf("Enter the number of columns for matrix 1: ");
    int cols1;
    scanf("%d", &cols1);

    // Prompt the user to enter the number of rows and columns for matrix 2
    // The number of columns in matrix 1 must equal the number of rows in matrix 2!
    printf("Enter the number of rows for matrix 2: ");
    int rows2;
    scanf("%d", &rows2);

    printf("Enter the number of columns for matrix 2: ");
    int cols2;
    scanf("%d", &cols2);

    // Check to see if the matrices can be multiplied
    // The number of columns in matrix 1 must equal the number of rows in matrix 2!
    if (cols1 != rows2) {
        printf("The matrices cannot be multiplied.");
        return 0;
    }

    // Fill matrix 1 with random numbers
    // The rand() function returns a random number between 0 and RAND_MAX
    // The % 10 will return a random number between 0 and 9
    // Creating a random matrix with random numbers between 0 and 9
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            matrix1[i][j] = rand() % 10;
        }
    }

    // Fill matrix 2 with random numbers
    // Same logic as matrix 1
    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            matrix2[i][j] = rand() % 10;
        }
    }

    // Print matrix 1
    // It works by printing the matrix row by row
    // The first row is printed by printing the first element of the first row, 
    // then the second element of the first row, then the third element of the first row, etc.
    printf("Matrix 1:\n");
    
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            printf("%d ", matrix1[i][j]);
        }
        printf("\n");
    }

    // Print matrix 2
    // It works the same way as matrix 1
    printf("Matrix 2:\n"); 

    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");

    }

    // Create the threads by calling the dot_product function
    // The dot_product function will calculate the dot product for each row and column
    // We will store the dot product in the result matrix
    // Then the function will be called for each row and column for each thread by passing the thread data to the function
    // The thread data will contain the row and column for the dot product
    // The thread data will be passed to the dot_product function using the thread_data_array
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            thread_data_array[thread_count].row = i;
            thread_data_array[thread_count].col = j;
            // Create the thread by calling the dot_product function
            pthread_create(&threads[thread_count], NULL, dot_product, (void *) &thread_data_array[thread_count]);
            thread_count++;
        }
    }

    // Join the threads by waiting for them to finish
    // This is necessary to ensure that the result matrix is printed after all the threads have finished
    // Otherwise, the result matrix may be printed before all the threads have finished
    // This will result in the result matrix being printed with some of the values being 0
    // This is because the threads have not finished calculating the dot products
    // The threads are still running in the background
    // By joining the threads, the main thread will wait for the threads to finish before printing the result matrix
    // This ensures that the result matrix is printed after all the threads have finished
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the result matrix
    printf("Result Matrix:\n");

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Exit the program
    pthread_exit(NULL);
}

// Compile the program
// gcc -pthread -o cs444_1 cs444_1.cpp

// Run the program
// ./cs444_1
// I used windows 10 with MSYS2 UCRT 64-bit to compile and run the program

// Output
// Enter the number of rows for matrix 1: 4
// Enter the number of columns for matrix 1: 4
// Enter the number of rows for matrix 2: 4
// Enter the number of columns for matrix 2: 4
// Matrix 1:
// 2 1 2 2
// 2 2 2 2
// 2 2 2 2
// 2 2 2 2
// Matrix 2:
// 2 2 2 2
// 2 2 2 2
// 2 2 2 2
// 2 2 2 2
// Result Matrix:
// 16 16 16 16
// 16 16 16 16
// 16 16 16 16
// 16 16 16 16

// End of Program


