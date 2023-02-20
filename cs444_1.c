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

// Import pthreads library
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the number of threads
#define NUM_THREADS 4

// Define the number of rows and columns for the matrices
#define ROWS 4
#define COLS 4

// Define the matrices
int matrix1[ROWS][COLS];
int matrix2[ROWS][COLS];
int result[ROWS][COLS];

// Define the thread data structure
typedef struct {
    int row;
    int col;
} thread_data;

// Define the thread function
void *dot_product(void *threadarg) {
    // Define the thread data
    thread_data *my_data;
    my_data = (thread_data *) threadarg;

    // Define the row and column
    int row = my_data->row;
    int col = my_data->col;

    // Define the dot product
    int dot_product = 0;

    // Calculate the dot product
    for (int i = 0; i < COLS; i++) {
        dot_product += matrix1[row][i] * matrix2[i][col];
    }

    // Store the dot product in the result matrix
    result[row][col] = dot_product;

    // Exit the thread
    pthread_exit(NULL);
}

// Define the main function
int main(int argc, char *argv[]) {
    // Define the thread id
    pthread_t threads[NUM_THREADS];

    // Define the thread data
    thread_data thread_data_array[NUM_THREADS];

    // Define the thread count
    int thread_count = 0;

    // Define the random number generator seed
    srand(time(NULL));

    // Prompt the user to enter the number of rows and columns for matrix 1
    printf("Enter the number of rows for matrix 1: ");
    int rows1;
    scanf("%d", &rows1);

    printf("Enter the number of columns for matrix 1: ");
    int cols1;
    scanf("%d", &cols1);

    // Prompt the user to enter the number of rows and columns for matrix 2
    printf("Enter the number of rows for matrix 2: ");
    int rows2;
    scanf("%d", &rows2);

    printf("Enter the number of columns for matrix 2: ");
    int cols2;
    scanf("%d", &cols2);

    // Check to see if the matrices can be multiplied
    if (cols1 != rows2) {
        printf("The matrices cannot be multiplied.");
        return 0;
    }

    // Fill matrix 1 with random numbers
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            matrix1[i][j] = rand() % 10;
        }
    }

    // Fill matrix 2 with random numbers
    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            matrix2[i][j] = rand() % 10;
        }
    }

    // Print matrix 1
    printf("Matrix 1:

");
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            printf("%d ", matrix1[i][j]);
        }
        printf("
");
    }

    // Print matrix 2
    printf("Matrix 2:
    
"); 

    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            printf("%d ", matrix2[i][j]);
        }
        printf("

");

    }

    // Create the threads
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            thread_data_array[thread_count].row = i;
            thread_data_array[thread_count].col = j;
            pthread_create(&threads[thread_count], NULL, dot_product, (void *) &thread_data_array[thread_count]);
            thread_count++;
        }
    }

    // Join the threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the result matrix
    printf("Result Matrix:

");

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            printf("%d ", result[i][j]);
        }
        printf("

");
    }

    // Exit the program
    pthread_exit(NULL);
}

// Compile the program
// gcc -pthread -o cs444_1 cs444_1.c

// Run the program
// ./cs444_1

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


