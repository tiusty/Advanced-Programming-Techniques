/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/22/2019
Description: 
*/

#ifndef FINALPROJECT_FOOTBALLFIELD_H
#define FINALPROJECT_FOOTBALLFIELD_H

// Football field parameters
constexpr float yardToMeter(float yardValue)
{
    return yardValue*.9144;
}

class FootballField {
public: // Methods
    void drawField();
public: // Members
    static constexpr float lenFootballField{yardToMeter(120)};
    static constexpr float widthFootballField{yardToMeter((53*3+1)/3)};
};


#endif //FINALPROJECT_FOOTBALLFIELD_H
