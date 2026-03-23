/**
 * @file
 * @brief This file contains the main function of the program.
 */

#include "logfunc.h"

/**
 * @brief Main function to execute a logic circuit program.
 *
 * This program reads input circuit data, input combinations, and executes logic operations
 * to calculate the output signal for each combination of given inputs. The results are then
 * saved to an output file. Command-line arguments specify the input and output files.
 *
 * @param argc The number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return 0 on successful execution, 1 on errors.
 *
 * @note Command-line arguments should include the input file with circuit data (-u),
 *       input file with input combinations (-i), and output file (-o).
 * @note The program prints a short guide on how to use it if executed without arguments.
 * @note The program checks the correctness of input files, performs logic operations,
 *       and saves the results to the output file.
 */
int main(int argc, char** argv){
    // VARIABLES FOR STORING INPUT NAMES
    std::string input1;
    std::string input2;
    std::string input3;

    // CHECKING COMMAND LINE ARGUMENTS
    handleArguments(argc, input1, input2, input3, argv);
    
    // OPENING FILES
    std::ifstream inplik1(input1);
    std::ifstream inplik2(input2);
    std::ofstream outplik(input3);

    // CHECKING IF FILES HAVE BEEN OPENED CORRECTLY AND CLOSING THE PROGRAM IF NOT
    if(!checkInFile(inplik1, input1)) return 1;
    if(!checkInFile(inplik2, input2)){
        inplik1.close();
        return 1;
    }
    if(!checkOutFile(outplik, input3)){
        inplik1.close();
        inplik2.close();
        return 1;
    }

    // CREATING VARIABLES
    Map points;
    StrVector inputs;
    StrVector outputs;

    // INITIATE MAP
    initMap(points, inplik1, inputs, outputs);

    // CLOSE FILE 1
    inplik1.close();

    // LOOP FOR ALL INPUTS
    std::string inputLine;
    std::string temp;
    int lineCount = 1;
    while(getline(inplik2, inputLine)){

        // UPDATE INPUT VALUES
        if(!updateInputValues(inputLine, points, lineCount, input2)) break;

        // READING INPUT LOGIC GATES AND VALUES AND EXECUTING THEIR OPERATIONS
        fileToLogic(points, inplik1, input1);

        // PRINTING TO OUTPUT
        if(!printToOutput(points, outplik, inputs, outputs, input1)) break;

        // INCREMENT LINE COUNT
        lineCount++;
    }
    if(inplik2.eof() && lineCount != 1) std::cout << "Operation successful, results have been saved to: " << input3;

    // CLOSING FILES
    inplik2.close();
    outplik.close();
    return 0;
}