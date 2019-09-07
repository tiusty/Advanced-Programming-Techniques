/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/7/19
Description:
 Defines an ECE matrix class which stores and operates on the stored matrix
*/

#ifndef HOMEWORK_2_ECE_MATRIX_HPP
#define HOMEWORK_2_ECE_MATRIX_HPP

#include <vector>
#include <iostream>

class ECE_Matrix {
public: // Methods
    ECE_Matrix(int square_size, double value);
    ECE_Matrix(int num_rows, int num_columns, double value);
    ECE_Matrix(char filename[]);
    friend std::ostream & operator << (std::ostream &out, const ECE_Matrix &c);

public: // Members

    std::vector<std::vector<double>> data;
    static constexpr unsigned kBuffSize{1024};
};


#endif //HOMEWORK_2_ECE_MATRIX_HPP
