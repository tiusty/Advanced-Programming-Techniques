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

ECE_Matrix::ECE_Matrix(int square_size, double value)
: data(square_size, std::vector<double>(square_size, value))
{}

ECE_Matrix::ECE_Matrix(int num_rows, int num_columns, double value)
: data(num_rows, std::vector<double>(num_columns, value))
{}

ECE_Matrix::ECE_Matrix(char filename[])
{
    char buff[ECE_Matrix::kBuffSize]{0};
    int num_rows{};
    int num_columns{};
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

    for(int i=0; i < num_rows; i++)
    {
        data.emplace_back(num_columns, 0);
        for(int j=0; j < num_columns; j++)
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
