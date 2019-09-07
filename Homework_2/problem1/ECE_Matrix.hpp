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
    ECE_Matrix();
    ECE_Matrix(unsigned int square_size, double value);
    ECE_Matrix(unsigned int row_num, unsigned int column_num, double value);
    ECE_Matrix(char filename[]);

    friend ECE_Matrix operator+(const ECE_Matrix &m1, const ECE_Matrix &m2);
    friend ECE_Matrix operator+(const ECE_Matrix &m1, const double &constant);
    friend ECE_Matrix operator+(const double &constant, const ECE_Matrix &m1);
    friend ECE_Matrix operator-(const ECE_Matrix &m1, const ECE_Matrix &m2);
    friend ECE_Matrix operator-(const ECE_Matrix &m1, const double &constant);
    friend ECE_Matrix operator-(const double &constant, const ECE_Matrix &m1);

    friend std::ostream & operator << (std::ostream &out, const ECE_Matrix &c);

    double getElement(unsigned int row, unsigned int column) const;

public: // Members
    unsigned int num_rows;
    unsigned int num_columns;
    std::vector<std::vector<double>> data;
    static constexpr unsigned kBuffSize{1024};
};


#endif //HOMEWORK_2_ECE_MATRIX_HPP
