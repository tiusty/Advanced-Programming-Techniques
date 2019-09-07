/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/7/19
Description:
 Implements ECE matrix functions
*/

#include "ECE_Matrix.hpp"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>

ECE_Matrix::ECE_Matrix()
: ECE_Matrix(0,0)
{}

ECE_Matrix::ECE_Matrix(unsigned int square_size, double value)
: ECE_Matrix(square_size, square_size, value)
{}

ECE_Matrix::ECE_Matrix(unsigned int row_num, unsigned int column_num, double value)
: num_rows(row_num), num_columns(column_num), data(num_rows, std::vector<double>(num_columns, value))
{}

ECE_Matrix::ECE_Matrix(char filename[])
{
    char buff[ECE_Matrix::kBuffSize]{0};
    std::ifstream file(filename);

    if(!file)
    {
        std::cerr << "Cannot open file" << std::endl;
        exit(1);
    }

    std::string line;

    file >> num_rows >> num_columns;
    std::getline(file, line);

    // Reserve the vector size for the number of rows
    data.reserve(num_rows);

    for(unsigned int i=0; i < num_rows; i++)
    {
        data.emplace_back(num_columns, 0);
        for(unsigned int j=0; j < num_columns; j++)
        {
            file >> data.at(i).at(j);
        }
    }
}

std::ostream & operator << (std::ostream &out, const ECE_Matrix &m)
{
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
    ECE_Matrix result{std::max(m1.num_rows, m2.num_rows),
                      std::max(m1.num_columns, m2.num_columns),
                      0};

    for(unsigned int i=0; i < result.num_rows; i++)
    {
        for(unsigned int j=0; j < result.num_columns; j++)
        {
            result.data.at(i).at(j) = m1.getElement(i,j) + m2.getElement(i,j);
        }
    }

    return result;
}

ECE_Matrix operator+(const double &constant, const ECE_Matrix &m1)
{
    return std::move(m1 + constant);
}

ECE_Matrix operator+(const ECE_Matrix &m1, const double &constant)
{
    ECE_Matrix result{m1.num_rows,
                      m1.num_columns,
                      0};

    for(unsigned int i=0; i < result.num_rows; i++)
    {
        for(unsigned int j=0; j < result.num_columns; j++)
        {
            result.data.at(i).at(j) = m1.getElement(i,j) + constant;
        }
    }

    return result;
}

ECE_Matrix operator-(const ECE_Matrix &m1, const ECE_Matrix &m2)
{
    ECE_Matrix result{std::max(m1.num_rows, m2.num_rows),
                      std::max(m1.num_columns, m2.num_columns),
                      0};

    for(unsigned int i=0; i < result.num_rows; i++)
    {
        for(unsigned int j=0; j < result.num_columns; j++)
        {
            result.data.at(i).at(j) = m1.getElement(i,j) - m2.getElement(i,j);
        }
    }

    return result;
}

ECE_Matrix operator-(const double &constant, const ECE_Matrix &m1)
{
    return std::move(m1 - constant);
}

ECE_Matrix operator-(const ECE_Matrix &m1, const double &constant)
{
    ECE_Matrix result{m1.num_rows,
                      m1.num_columns,
                      0};

    for(unsigned int i=0; i < result.num_rows; i++)
    {
        for(unsigned int j=0; j < result.num_columns; j++)
        {
            result.data.at(i).at(j) = m1.getElement(i,j) - constant;
        }
    }

    return result;
}

ECE_Matrix ECE_Matrix::transpose()
{
    ECE_Matrix result{num_columns, num_rows, 0};

    for(unsigned int i=0; i<num_rows; i++)
    {
        for(unsigned int j=0; j<num_columns; j++)
        {
            result.data.at(j).at(i) = data.at(i).at(j);
        }
    }

    return result;
}

double ECE_Matrix::getElement(unsigned int row, unsigned int column) const
{
    if(row >= num_rows || column >= num_columns)
    {
        return 0;
    }
    return data[row][column];
}


