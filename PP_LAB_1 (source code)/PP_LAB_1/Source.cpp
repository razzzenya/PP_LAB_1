#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <chrono>

#define PATH_TO_FIRST_MATRIX "C:\\Users\\bucki\\source\\repos\\PP_LAB_1\\x64\\Release\\first matrix.txt"
#define PATH_TO_SECOND_MATRIX "C:\\Users\\bucki\\source\\repos\\PP_LAB_1\\x64\\Release\\second matrix.txt"
#define PATH_TO_SIZE_FILE "C:\\Users\\bucki\\source\\repos\\PP_LAB_1\\x64\\Release\\size.txt"
#define PATH_TO_RESULT_FILE "C:\\Users\\bucki\\source\\repos\\PP_LAB_1\\x64\\Release\\result.txt"

class MainProgram {
public:
    size_t size = 0;
    int** first_matrix = nullptr;
    int** second_matrix = nullptr;

    void LoadSize() {
        std::ifstream file(PATH_TO_SIZE_FILE);

        if (!file.is_open()) {
            std::cerr << "File opening error!" << std::endl;
            return;
        }

        if (file >> size){
            file.close();
            return;
        }

        else {
            std::cerr << "Error reading number from file!" << std::endl;
            file.close();
        }
    }

    void AllocateMemoryForMatrices() {
        if (first_matrix != nullptr && second_matrix != nullptr) {
            for (size_t i = 0; i < size; ++i) {
                delete[] first_matrix[i];
                delete[] second_matrix[i];
            }
            delete[] first_matrix;
            delete[] second_matrix;
        }

        first_matrix = new int* [size];
        second_matrix = new int* [size];
        for (size_t i = 0; i < size; ++i) {
            first_matrix[i] = new int[size];
            second_matrix[i] = new int[size];
        }
    }

    void GenerateMatrices() {
        if (!size) {
            std::cerr << "Matrix size not specified!" << std::endl;
            return;
        }

        AllocateMemoryForMatrices();

        srand(time(NULL));
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                first_matrix[i][j] = rand() % 100;
                second_matrix[i][j] = rand() % 100;
            }
        }
        std::cout << size << " by " << size << " matrices were successfully generated" << std::endl;
    }

    void SaveMatrices() {
        std::ofstream file(PATH_TO_FIRST_MATRIX);

        if (!file.is_open()) {
            std::cerr << "Error opening file for writing!" << std::endl;
            return;
        }

        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                file << first_matrix[i][j] << " ";
            }
            file << std::endl;
        }
        file.close();

        std::ofstream file2(PATH_TO_SECOND_MATRIX);

        if (!file2.is_open()) {
            std::cerr << "Error opening file for writing!" << std::endl;
            return;
        }

        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                file2 << second_matrix[i][j] << " ";
            }
            file2 << std::endl;
        }
        file2.close();
    }

    void LoadMatrices() {
        std::ifstream file(PATH_TO_FIRST_MATRIX);

        if (!file.is_open()) {
            std::cerr << "Error opening first matrix file for reading!" << std::endl;
            return;
        }

        AllocateMemoryForMatrices();

        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                file >> first_matrix[i][j];
            }
        }

        file.close();

        std::ifstream file1(PATH_TO_SECOND_MATRIX);

        if (!file1.is_open()) {
            std::cerr << "Error opening second matrix file for reading!" << std::endl;
            return;
        }

        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                file1 >> second_matrix[i][j];
            }
        }
    }

    void MultiplyMatricesAndSaveResult() {

        int** result_matrix = new int*[size];
        for (size_t i = 0; i < size; ++i) {
            result_matrix[i] = new int[size];
        }

        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                result_matrix[i][j] = 0;
            }
        }

        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();

        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                for (size_t k = 0; k < size; ++k) {
                    result_matrix[i][j] += first_matrix[i][k] * second_matrix[k][j];
                }
            }
        }
        
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;

        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "Time spent in seconds to multiply " << size << " by " << size << " matrices " << elapsed_seconds.count() << std::endl;
        
        std::ofstream file(PATH_TO_RESULT_FILE);
        if (!file.is_open()) {
            std::cerr << "Error opening file for writing!" << std::endl;
            return;
        }

        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                file << result_matrix[i][j] << " ";
            }
            file << std::endl;
        }

        file << "Time spent in seconds to multiply " << size << " by " << size << " matrices: " << elapsed_seconds.count() << std::endl;

        file.close();
        
        SaveMatrices();

        for (size_t i = 0; i < size; ++i) {
            delete[] result_matrix[i];
        }
        delete[] result_matrix;
    }

    void PrintMatrices() { //этот метод только для проверки
        std::cout << "First matrix:" << std::endl;
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                std::cout << first_matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Second matrix:" << std::endl;
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                std::cout << second_matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    ~MainProgram() {
        if (first_matrix != nullptr) {
            for (size_t i = 0; i < size; ++i) {
                delete[] first_matrix[i];
            }
            delete[] first_matrix;
        }

        if (second_matrix != nullptr) {
            for (size_t i = 0; i < size; ++i) {
                delete[] second_matrix[i];
            }
            delete[] second_matrix;
        }
    }

};

int main() {
    MainProgram example;
    example.LoadSize();
    example.GenerateMatrices();
    example.MultiplyMatricesAndSaveResult();
    return 0;
}