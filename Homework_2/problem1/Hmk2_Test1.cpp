#include <iostream>
#include <limits>
#include "ECE_Matrix.h"


int main()
{

    const ECE_Matrix M1(3, 5.0);  // Construct 3 x 3 array set all elements to 5.0
    const ECE_Matrix M2(5, 5, 200.0); // Construct 5 x 5 array, setting all gridElement to 200.0
    const ECE_Matrix M3("data_Problem1.txt"); // Construct matrix from file

    std::cout << "M3: " << std::endl << M3 << std::endl;

    // Doing some simple matrix math
    const ECE_Matrix M4 = M1 - 5.0 + M2;
    const ECE_Matrix M5 = M3 - M2 + 8.0;
    const ECE_Matrix M6 = 10.0 * M1 + M2;
    const ECE_Matrix M7 = M3.transpose();   // Function should not Modify M3 directly
                                            // but just return the transpose of the matrix

    const ECE_Matrix M9 = M1 * 8.0;
    const ECE_Matrix M10 = M1 / 8.0;        // Check for divide by zero. Set all elements equal 0 for that case

    ECE_Matrix M11; // Default constructor size 0 x 0
    M11 += M1;
    ECE_Matrix M12;
    M12 -= M1;

    const ECE_Matrix M13 = M1 + 8.0;
    const ECE_Matrix M14 = M1 - 8.0;

    const ECE_Matrix M15 = 8.0 * M1;
    const ECE_Matrix M17 = 8.0 + M1;
    const ECE_Matrix M18 = 8.0 - M1;

    std::cout << "M4: (M1 - 5.0 + M2): " << std::endl << M4 << std::endl;
    std::cout << "M5: (M3 - M2 + 8.0) " << std::endl << M5 << std::endl;
    std::cout << "M6: (10.0 * M1 + M2) " << std::endl << M6 << std::endl;
    std::cout << "M7: M3 Transposed " << std::endl << M7 << std::endl;
    std::cout << "M9: (M1 * 8.0) " << std::endl << M9 << std::endl;
    std::cout << "M10: (M1 / 8.0) " << std::endl << M10 << std::endl;
    std::cout << "M11: (M11 += M1) " << std::endl << M11 << std::endl;
    std::cout << "M12: (M11 -= M1) " << std::endl << M12 << std::endl;
    std::cout << "M13: (M1 + 8.0) " << std::endl << M13 << std::endl;
    std::cout << "M14: (M1 - 8.0) " << std::endl << M14 << std::endl;
    std::cout << "M15: (8.0 * M1) " << std::endl << M15 << std::endl;
    std::cout << "M17: (8.0 + M1) " << std::endl << M17 << std::endl;
    std::cout << "M18: (8.0 - M1) " << std::endl << M18 << std::endl;

 }
