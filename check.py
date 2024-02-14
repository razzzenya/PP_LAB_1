import os
import numpy
RESULT_FILENAME = "result.txt"
FIRST_MATRIX_FILENAME = "first_matrix.txt"
SECOND_MATRIX_FILENAME = "second_matrix.txt"
SIZE_FILENAME = "size.txt"


if __name__ == "__main__":
    with open(SIZE_FILENAME, "r") as size_file:
        size = int(size_file.read())
