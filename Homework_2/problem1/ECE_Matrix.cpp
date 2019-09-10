/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/7/19
Description:
 Implements ECE matrix functions
*/

#include "ECE_Matrix.h"

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>

ECE_Matrix::ECE_Matrix()
: ECE_Matrix(0,0)
{}

ECE_Matrix::ECE_Matrix(unsigned int squareSize, double value)
: ECE_Matrix(squareSize, squareSize, value)
{}

ECE_Matrix::ECE_Matrix(unsigned int rowNum, unsigned int columnNum, double value)
: numRows(rowNum), numColumns(columnNum), data(numRows, std::vector<double>(numColumns, value))
{}

ECE_Matrix::ECE_Matrix(const char* filename)
: ECE_Matrix(0,0,0)
{
    std::ifstream file(filename);

    if(!file)
    {
        std::cerr << "Cannot open file" << std::endl;
        exit(1);
    }

    std::string line;

    file >> numRows >> numColumns;
    std::getline(file, line);

    // Reserve the vector size for the number of rows
    data.reserve(numRows);

    // Read in every gridElement to a new spot in the data
    for(unsigned int i=0; i < numRows; i++)
    {
        data.emplace_back(numColumns, 0);
        for(unsigned int j=0; j < numColumns; j++)
        {
            file >> data.at(i).at(j);
        }
    }
}

std::ostream & operator << (std::ostream &out, const ECE_Matrix &m)
{
    // Print out every gridElement and only add a new line at the end of a row
    for(const auto & i : m.data)
    {
        for(double j : i)
        {
            out << std::scientific << std::setw(12) << std::setprecision(3) << j;
        }
        out << std::endl;
    }
    return out;
}

ECE_Matrix operator+(const ECE_Matrix &m1, const ECE_Matrix &m2)
{
    ECE_Matrix result{std::max(m1.numRows, m2.numRows),
                      std::max(m1.numColumns, m2.numColumns),
                      0};

    // Just add the corresponding elements
    for(unsigned int i=0; i < result.numRows; i++)
    {
        for(unsigned int j=0; j < result.numColumns; j++)
        {
            result.data.at(i).at(j) = m1.getElement(i,j) + m2.getElement(i,j);
        }
    }

    return result;
}

ECE_Matrix operator+(const double &constant, const ECE_Matrix &m1)
{
    // Use the already created addition operator
    return std::move(m1 + constant);
}

ECE_Matrix operator+(const ECE_Matrix &m1, const double &constant)
{
    ECE_Matrix result{m1.numRows,
                      m1.numColumns,
                      0};

    // Just add the constant to every gridElement
    for(unsigned int i=0; i < result.numRows; i++)
    {
        for(unsigned int j=0; j < result.numColumns; j++)
        {
            result.data.at(i).at(j) = m1.getElement(i,j) + constant;
        }
    }

    return result;
}

ECE_Matrix operator-(const ECE_Matrix &m1, const ECE_Matrix &m2)
{
    ECE_Matrix result{std::max(m1.numRows, m2.numRows),
                      std::max(m1.numColumns, m2.numColumns),
                      0};

    // Just subtract the corresponding elements
    for(unsigned int i=0; i < result.numRows; i++)
    {
        for(unsigned int j=0; j < result.numColumns; j++)
        {
            result.data.at(i).at(j) = m1.getElement(i,j) - m2.getElement(i,j);
        }
    }

    return result;
}

ECE_Matrix operator-(const double &constant, const ECE_Matrix &m1)
{
    ECE_Matrix result{m1.numRows,
                      m1.numColumns,
                      0};

    // Just subtract the constant and the matrix
    for(unsigned int i=0; i < result.numRows; i++)
    {
        for(unsigned int j=0; j < result.numColumns; j++)
        {
            result.data.at(i).at(j) = constant - m1.getElement(i,j);
        }
    }

    return result;
}

ECE_Matrix operator-(const ECE_Matrix &m1, const double &constant)
{
    ECE_Matrix result{m1.numRows,
                      m1.numColumns,
                      0};

    // Just subtract the constant from the matrix
    for(unsigned int i=0; i < result.numRows; i++)
    {
        for(unsigned int j=0; j < result.numColumns; j++)
        {
            result.data.at(i).at(j) = m1.getElement(i,j) - constant;
        }
    }

    return result;
}

ECE_Matrix operator*(const double &constant, const ECE_Matrix &m1)
{
    // Use the already created matrix operation
    return std::move(m1 * constant);
}

ECE_Matrix operator*(const ECE_Matrix &m1, const double &constant)
{
    ECE_Matrix result{m1.numRows,
                      m1.numColumns,
                      0};

    // Just multiple each gridElement by the constant
    for(unsigned int i=0; i < result.numRows; i++)
    {
        for(unsigned int j=0; j < result.numColumns; j++)
        {
            result.data.at(i).at(j) = m1.getElement(i,j) * constant;
        }
    }

    return result;
}


ECE_Matrix operator/(const ECE_Matrix &m1, const double &constant)
{
    ECE_Matrix result{m1.numRows,
                      m1.numColumns,
                      0};
    // If the constant is 0 then return the 0 matrix
    if (constant == 0)
    {
        return result;
    }

    // Divide every gridElement in the marix by the constant
    for(unsigned int i=0; i < result.numRows; i++)
    {
        for(unsigned int j=0; j < result.numColumns; j++)
        {
            result.data.at(i).at(j) = m1.getElement(i,j) / constant;
        }
    }

    return result;
}

ECE_Matrix& ECE_Matrix::operator-=(const ECE_Matrix &m1)
{
    // Use the created subtraction overloaded operator
    *this = *this - m1;
    return *this;
}

ECE_Matrix& ECE_Matrix::operator+=(const ECE_Matrix &m1)
{
    // Use the created addition overloaded operator
    *this = *this + m1;
    return *this;
}

ECE_Matrix ECE_Matrix::transpose() const
{
    ECE_Matrix result{numColumns, numRows, 0};

    // Swap the rows and the columns
    for(unsigned int i=0; i < numRows; i++)
    {
        for(unsigned int j=0; j < numColumns; j++)
        {
            result.data.at(j).at(i) = data.at(i).at(j);
        }
    }

    return result;
}

double ECE_Matrix::getElement(unsigned int row, unsigned int column) const
{
    // If the index is out of bounds return 0
    if(row >= numRows || column >= numColumns)
    {
        return 0;
    }

    // Otherwise return the value
    return data[row][column];
}


