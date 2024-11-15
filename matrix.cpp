#include <iostream>
#include <pthread.h>


const int MATRIX_SIZE = 3;

int matrixA[MATRIX_SIZE][MATRIX_SIZE], matrixB[MATRIX_SIZE][MATRIX_SIZE], result[MATRIX_SIZE][MATRIX_SIZE];



struct ThreadData {

    int row;

    int col;

};



void* multiply(void* arg) {

    ThreadData* data = (ThreadData*)arg;

    int row = data->row;

    int col = data->col;

    result[row][col] = 0;



    for (int i = 0; i < MATRIX_SIZE; ++i) {

        result[row][col] += matrixA[row][i] * matrixB[i][col];

    }



    pthread_exit(nullptr);

}



void* add(void* arg) {

    ThreadData* data = (ThreadData*)arg;

    int row = data->row;

    int col = data->col;

    result[row][col] = matrixA[row][col] + matrixB[row][col];



    pthread_exit(nullptr);

}



void* subtract(void* arg) {

    ThreadData* data = (ThreadData*)arg;

    int row = data->row;

    int col = data->col;

    result[row][col] = matrixA[row][col] - matrixB[row][col];



    pthread_exit(nullptr);

}



void inputMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], char name) {

    std::cout << "Enter elements of Matrix " << name << " (3x3):\n";

    for (int i = 0; i < MATRIX_SIZE; ++i) {

        for (int j = 0; j < MATRIX_SIZE; ++j) {

            std::cin >> matrix[i][j];

        }

    }

}



void displayMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {

    for (int i = 0; i < MATRIX_SIZE; ++i) {

        for (int j = 0; j < MATRIX_SIZE; ++j) {

            std::cout << matrix[i][j] << " ";

        }

        std::cout << std::endl;

    }

}



void performOperation(void* (*operation)(void*)) {

    pthread_t threads[MATRIX_SIZE][MATRIX_SIZE];

    ThreadData threadData[MATRIX_SIZE][MATRIX_SIZE];



    for (int i = 0; i < MATRIX_SIZE; ++i) {

        for (int j = 0; j < MATRIX_SIZE; ++j) {

            threadData[i][j].row = i;

            threadData[i][j].col = j;

            pthread_create(&threads[i][j], nullptr, operation, (void*)&threadData[i][j]);

        }

    }



    for (int i = 0; i < MATRIX_SIZE; ++i) {

        for (int j = 0; j < MATRIX_SIZE; ++j) {

            pthread_join(threads[i][j], nullptr);

        }

    }

}



int main() {

    inputMatrix(matrixA, 'A');

    inputMatrix(matrixB, 'B');



    int choice;

    std::cout << "Choose the operation:\n1. Multiplication\n2. Addition\n3. Subtraction\n";

    std::cin >> choice;



    switch (choice) {

        case 1:

            performOperation(multiply);

            std::cout << "Resultant Matrix after Multiplication:\n";

            displayMatrix(result);

            break;

        case 2:

            performOperation(add);

            std::cout << "Resultant Matrix after Addition:\n";

            displayMatrix(result);

            break;

        case 3:

            performOperation(subtract);

            std::cout << "Resultant Matrix after Subtraction:\n";

            displayMatrix(result);

            break;

        default:

            std::cout << "Invalid choice!\n";

    }



    return 0;

}
