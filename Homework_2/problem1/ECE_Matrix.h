/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/7/19
Description:
 Defines an ECE matrix class which stores and operates on the stored matrix
*/

#ifndef HOMEWORK_2_ECE_MATRIX_H
#define HOMEWORK_2_ECE_MATRIX_H

#include <vector>
#include <iostream>

/**
 * Class stores a matrix and function associated with the matrix.
 * Stores a load of overloaded functionality
 */
class ECE_Matrix {
public: // Methods
    /**
     * Default ctor that creates a 0 matrix
     */
    ECE_Matrix();

    /**
     * Ctor that creates a square matrix with the default value passed in
     * @param square_size The size of the square matrix
     * @param value The value to initialize the elements to
     */
    ECE_Matrix(unsigned int square_size, double value);

    /**
     * Ctor that creates a rectangular matrix with the default value passed in
     * @param row_num The number of rows
     * @param column_num The number of columns
     * @param value The default value for all the elements
     */
    ECE_Matrix(unsigned int row_num, unsigned int column_num, double value);

    /**
     * Ctor that is passed in a file and reads in the matrix from the file
     * @param filename
     */
    explicit ECE_Matrix(const char* filename);

    /**
     * Overloaded operator:
     *  Adds division between a matrix and a constant
     * @param m1 The Matrix passed in
     * @param constant The constant to divide by
     * @return The result
     */
    friend ECE_Matrix operator/(const ECE_Matrix &m1, const double &constant);

    /**
     * Overloaded operator:
     *  Adds multiplication between a matrix and a constant
     * @param m1 The Matrix passed in
     * @param constant The constant to multiply by
     * @return The result
     */
    friend ECE_Matrix operator*(const ECE_Matrix &m1, const double &constant);

    /**
     * Overloaded operator:
     *  Adds multiplication between a matrix and a constant
     * @param constant The constant to multiply by
     * @param m1 The Matrix passed in
     * @return The result
     */
    friend ECE_Matrix operator*(const double &constant, const ECE_Matrix &m1);

    /**
     * Overloaded operator:
     *  Adds addition between a matrix and another matrix
     * @param m1 The first matrix to add with
     * @param m2 The second matrix to add with
     * @return The result
     */
    friend ECE_Matrix operator+(const ECE_Matrix &m1, const ECE_Matrix &m2);

    /**
     * Overloaded operator:
     *  Adds addition between a matrix and a constant
     * @param m1 The first matrix to add with
     * @param constant The constant to add to the matrix
     * @return The result
     */
    friend ECE_Matrix operator+(const ECE_Matrix &m1, const double &constant);

    /**
     * Overloaded operator:
     *  Adds addition between a matrix and a constant
     * @param constant The constant to subtract from
     * @param m1 The first matrix to subtract with
     * @return The result
     */
    friend ECE_Matrix operator+(const double &constant, const ECE_Matrix &m1);

    /**
     * Overloaded operator:
     *  Adds subtraction between a matrix and another matrix
     * @param m1 The first matrix to subtract from
     * @param m2 The second matrix to subtract with
     * @return The result
     */
    friend ECE_Matrix operator-(const ECE_Matrix &m1, const ECE_Matrix &m2);

    /**
     * Overloaded operator:
     *  Adds subtraction between a matrix and a constant
     * @param m1 The first matrix to subtract from
     * @param constant The constant to subtract to the matrix
     * @return The result
     */
    friend ECE_Matrix operator-(const ECE_Matrix &m1, const double &constant);

    /**
     * Overloaded operator:
     *  Adds subtraction between a matrix and a constant
     * @param constant The constant to add to the matrix
     * @param m1 The first matrix to add with
     * @return The result
     */
    friend ECE_Matrix operator-(const double &constant, const ECE_Matrix &m1);

    /**
     * Overloaded stream operator
     * @param out The input stream
     * @param c The matrix that is being printed
     * @return The formatted stream
     */
    friend std::ostream & operator << (std::ostream &out, const ECE_Matrix &c);

    /**
     * Overload the += operator
     * @param m1 The matrix to add to this object
     * @return The object with the new matrix added to it
     */
    ECE_Matrix &operator+=(const ECE_Matrix &m1);

    /**
     * Overload the -= operator
     * @param m1 The matrix to subtract from this object
     * @return The object with the new matrix subtracted from it
     */
    ECE_Matrix &operator-=(const ECE_Matrix &m1);

    /**
     * Function attempts to retrieve a value from an index.
     * If the index exists if gets the value, if not then it returns 0
     * @param row The row to extract
     * @param column The column to extract
     * @return The value if it exists or 0
     */
    double getElement(unsigned int row, unsigned int column) const;

    /**
     * Returns the transpose of the current class data instance
     * @return The transpose of the data 2D vector
     */
    ECE_Matrix transpose() const;

public: // Members
    /**
     * Stores the number of rows associated with the data
     */
    unsigned int num_rows;

    /**
     * Stores the number of columns associated with the vector
     */
    unsigned int num_columns;

    /**
     * Actually stores the data associated with the 2D vector
     */
    std::vector<std::vector<double>> data;
};


#endif //HOMEWORK_2_ECE_MATRIX_H
